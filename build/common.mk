#===============================================================================
# Copyright 2012-2016 Intel Corporation
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#===============================================================================

# new line character
define \n


endef

empty =
space = $(empty) $(empty)
comma = ,

# variable name to hold auxiliary (required by build system only) target's depedencies (as opposed to dependencies from which target is being built)
mkdeps-var-name = $@.mkdeps
# list of prerequisites without auxiliary dependencies
^.no-mkdeps = $(filter-out $($(mkdeps-var-name)),$^)
# Filter out words from the list (arg $2) containing particular substring (arg $1)
mktemp = $(shell f=$${TMP:+$${TMP//\\//}/}.mkl-tmp-$$$$-$$(date +'%s') && : > $$f && echo $$f)

filter-out-containing = $(foreach w,$2,$(if $(findstring $1,$(w)),,$(w)))
filter-containing = $(strip $(foreach w,$2,$(foreach s,$1,$(if $(findstring $s,$(w)),$(w),))))
# Get base name of executable file to be called in supplied macro
# Args:
#   $1: Command definition via GNU Make macro
get-command-name = $(patsubst %.exe,%,$(notdir $(subst \,/,$(firstword $(1)))))

# xargs analog for calling GNU Make macro
# Args:
#   $1: macro to call, can take up to 5 parameters, $6 parameter is not empty if there will be additional call.
#   $2: list of words to call macro on
# Limit on words passed to xarged commands:
xargs.limit = 120
xargs.limit+1 = 121
xargs = $(call $1,$(wordlist 1,$(xargs.limit),$2),$3,$4,$5,$6,$(word $(xargs.limit+1),$2))\
	$(if $(word $(xargs.limit+1),$2),$(call $0,$1,$(wordlist $(xargs.limit+1),$(words $2),$2),$3,$4,$5,$6))

# logged shell command execution
exec = $(if $(DEBUG_EXEC),$(info $1)$(info$(shell $1)),$(info$(shell $1)))

# create directory for the target if it does not exists
mkdir = $(if $(wildcard $(if $1,$1,$(@D))),,$(info $(mkdir.cmd): $(shell $(mkdir.cmd);)))
mkdir.cmd = mkdir -vp $(if $1,$1,$(@D))

rm    = $(if $(wildcard $1),$(call exec,rm -f $1))

# Calculate md5 sum of the value passed as an argument
md5 = $(strip $(call md5.impl,$1,$(call mktemp)))
md5.impl = $(call xargs,md5.dump,$1,$2)md5:$(word 1,$(shell $(md5sum.cmd) $2 && rm $2))
md5.dump = $(shell printf -- "$1$(if $6, )" >> $2)
md5sum.cmd = $(md5sum.cmd.$(_OS))
md5sum.cmd.lnx = md5sum
md5sum.cmd.win = md5sum
md5sum.cmd.mac = md5 -q

# Enable compiler-provided defences as recommended by Intel Security Development Lifecycle document (SW.01)
secure.opts.icc.win = -GS
secure.opts.icc.lnx = -Wformat -Wformat-security -O2 -D_FORTIFY_SOURCE=2 -fstack-protector
                                                                         # disabled due to known issue in compiler. see DPD200371640
secure.opts.icc.mac = -Wformat -Wformat-security -O2 -D_FORTIFY_SOURCE=2 # -fstack-protector
secure.opts.link.win = -DYNAMICBASE -NXCOMPAT $(if $(IA_is_ia32),-SAFESEH)
secure.opts.link.lnx = -z relro -z now -z noexecstack
secure.opts.link.mac =

RC.COMPILE = rc.exe $(RCOPT) -fo$@ $<

C.COMPILE = $(if $(COMPILER.$(_OS).$(COMPILER)),$(COMPILER.$(_OS).$(COMPILER)),$(error COMPILER.$(_OS).$(COMPILER) must be defined)) \
            $(secure.opts.icc.$(_OS)) $(COPT) $(INCLUDES) -c $1 $(-Fo)$@ $<

# Write target's dependencies to target file
# Args:
#   $1: [optional] word list to write into the file
#   $2: [optional] word separator (\n by default)
WRITE.PREREQS = $(if $@,$(info : Writing $(words $(write.prereqs.args)) prerequisites to $@ ..)$(call rm,$@)$(call write.prereqs.impl,$(write.prereqs.args),$(or $2,\n)): .. prerequisites written to $@)
write.prereqs.args = $(or $1,$(^.no-mkdeps))
write.prereqs.impl = $(call xargs,write.prereqs.dump,$1,$2)
write.prereqs.dump = $(call exec,printf -- "$(subst $(space),$2,$1)$(if $6,$2)" >> $@)

# Link static lib
LINK.STATIC = $(mkdir)$(call rm,$@)$(link.static.cmd)
link.static.cmd = $(call link.static.$(_OS),$(LOPT) $(or $1,$(^.no-mkdeps)))
link.static.lnx = $(if $(filter %.a,$1),$(link.static.lnx.script),$(link.static.lnx.cmdline))
link.static.lnx.cmdline = ar rs $@ $(1:%_link.txt=@%_link.txt)
.addlib = $(foreach lib,$(filter %.a,$1),addlib $(lib)\n)
.addmod = $(if $(filter %.o,$1),addmod $(filter %.o,$1))
.addlink = $(if $(filter %_link.txt,$1),addmod $(shell tr '\n' ', ' < $(filter %_link.txt,$1)))
link.static.lnx.script = printf "create $@\n$(call .addlib,$1)\n$(call .addmod,$1)\n$(call .addlink,$1)\nsave\n" | ar -M
link.static.win = lib $(link.static.win.$(COMPILER)) -nologo -out:$@ $(1:%_link.txt=@%_link.txt)
link.static.mac = libtool -V -static -o $@ $(1:%_link.txt=-filelist %_link.txt)

# Link dynamic lib
LINK.DYNAMIC = $(mkdir)$(call rm,$@)$(link.dynamic.cmd)
link.dynamic.cmd = $(call link.dynamic.$(_OS),$(secure.opts.link.$(_OS)) $(or $1,$(^.no-mkdeps)) $(LOPT))
link.dynamic.lnx = $(if $(link.dynamic.lnx.$(COMPILER)),$(link.dynamic.lnx.$(COMPILER)),$(error link.dynamic.lnx.$(COMPILER) must be defined)) -shared $(-sGRP) $(1:%_link.txt=@%_link.txt) $(-eGRP) -o $@
link.dynamic.win = link $(link.dynamic.win.$(COMPILER)) -nologo -map -dll $(-DEBL) $(1:%_link.txt=@%_link.txt) -out:$@
link.dynamic.mac = $(if $(link.dynamic.mac.$(COMPILER)),$(link.dynamic.mac.$(COMPILER)),$(error link.dynamic.mac.$(COMPILER) must be defined)) \
                   -undefined dynamic_lookup -dynamiclib -Wl,-flat_namespace -Wl,-install_name,@rpath/$(@F)  -Wl,-headerpad_max_install_names $(1:%_link.txt=-filelist %_link.txt) -o $@
#TODO think on dependence from include sequence for $(if $(link.dynamic.lnx.$(COMPILER)),...)

LINK.DYNAMIC.POST = $(call link.dynamic.post.$(_OS))
link.dynamic.post.lnx =
link.dynamic.post.win =
link.dynamic.post.mac = install_name_tool -change "libtbb.dylib"                 "@rpath/libtbb.dylib" $@;                       \
                        install_name_tool -change "libdaal_mkl_sequential.dylib" "@rpath/rpath/libdaal_mkl_sequential.dylib" $@; \
                        install_name_tool -change "libdaal_mkl_thread.dylib"     "@rpath/rpath/libdaal_mkl_thread.dylib" $@;     \
                        install_name_tool -add_rpath "@loader_path/../../tbb/lib" $@;                                            \
                        install_name_tool -add_rpath "@loader_path/" $@;                                                         \
                        install_name_tool -add_rpath "@executable_path/" $@;                                                     \
                        install_name_tool -add_rpath "." $@

info.building.%:; $(info ========= Building $* =========)
%/.:; mkdir -p $*

# symbols dump
nm = $(if $(OS_is_win),dumpbin -symbols $@ | grep ' External ' | grep -v ' __ImageBase$$' | grep -v '(.string.)' ,nm $@ )

# sed's -b option for binary files on win
sed.-b = $(if $(OS_is_win),-b)

sed.-i = $(sed.-i.$(_OS))
sed.-i.mac = -i.bak
sed.-i.win = -i
sed.-i.lnx = -i

# sed
PATCHBIN = $(patchbin.cmd)
patchbin.cmd = cp $< $@.patchbin.tmp && $(patchbin.workaround.$(_OS)) sed -n $(sed.-i) $(sed.-b) -e $(PATCHBIN.OPTS) -e "w $@" $@.patchbin.tmp && rm -f $@.patchbin.tmp || { rm -f $@ $@.patchbin.tmp; false; }
patchbin.workaround.mac = LANG=C
