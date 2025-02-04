/* file: DataFeature.java */
/*******************************************************************************
* Copyright 2014-2016 Intel Corporation
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

package com.intel.daal.data_management.data;

import com.intel.daal.services.DaalContext;
import java.nio.ByteBuffer;

/**
 * <a name="DAAL-CLASS-DATA__DATADFEATURE__DATADFEATURE"></a>
 * @brief Class used to describe a feature. The structure is used in the
 *        com.intel.daal.data.DataDictionary class.
 */
public class DataFeature extends SerializableBase {
    /** @private */
    static {
        System.loadLibrary("JavaAPI");
    }

    /**
     * Default constructor
     */
    public DataFeature(DaalContext context) {
        super(context);
        this.cObject = init();
        vectorUpCast = new DataFeatureUtils.VectorUpCastIface[3];
        vectorDownCast = new DataFeatureUtils.VectorDownCastIface[3];
    }

    /**
     * Sets PMML data type of the feature
     * @param pmmlType      PMML data type of the feature
     */
    public void setPMMLNumType(DataFeatureUtils.PMMLNumType pmmlType) {
        cSetPMMLNumType(this.cObject, pmmlType.getType());
    }

    /**
     * Sets  type of the feature(continuous, ordinal or categorical)
     * @param featureType   Type of the feature
     */
    public void setFeatureType(DataFeatureUtils.FeatureType featureType) {
        cSetFeatureType(this.cObject, featureType.getType());
    }

    /**
     * Sets number of category levels
     * @param categoryNumber    Number of category levels
     */
    public void setCategoryNumber(int categoryNumber) {
        cSetCategoryNumber(this.cObject, categoryNumber);
    }

    private void initializeCasts(Class<?> cls) {
        vectorUpCast[0] = DataFeatureUtils.VectorUpCast.getCast(cls, float.class);
        vectorUpCast[1] = DataFeatureUtils.VectorUpCast.getCast(cls, double.class);
        vectorUpCast[2] = DataFeatureUtils.VectorUpCast.getCast(cls, int.class);

        vectorDownCast[0] = DataFeatureUtils.VectorDownCast.getCast(float.class, cls);
        vectorDownCast[1] = DataFeatureUtils.VectorDownCast.getCast(double.class, cls);
        vectorDownCast[2] = DataFeatureUtils.VectorDownCast.getCast(int.class, cls);
    }

    /**
     * @private
     */
    void setType(Class<?> cls) {
        if (Double.class == cls || double.class == cls) {
            cSetDoubleType(this.cObject);
        } else if (Float.class == cls || float.class == cls) {
            cSetFloatType(this.cObject);
        } else if (Long.class == cls || long.class == cls) {
            cSetLongType(this.cObject);
        } else if (Integer.class == cls || int.class == cls) {
            cSetIntType(this.cObject);
        } else {
            throw new IllegalArgumentException("type unsupported");
        }
        initializeCasts(cls);
    }

    /**
     * Gets PMML data type of the feature
     *
     * @return PMML data type of the feature
     */
    public native DataFeatureUtils.PMMLNumType getPMMLNumType();

    /**
     * Gets  type of the feature(continuous, ordinal or categorical)
     *
     * @return Type of the feature
     */
    public native DataFeatureUtils.FeatureType getFeatureType();

    /**
     * Gets number of category levels
     *
     * @return Number of category levels
     */
    public native int getCategoryNumber();

    /* Constructs C++ data feature object */
    private native long init();

    private native void cSetInternalNumType(long cObject, int intType);

    private native void cSetPMMLNumType(long cObject, int pmmlType);

    private native void cSetFeatureType(long cObject, int featureType);

    private native void cSetCategoryNumber(long cObject, int categoryNumber);

    private native void cSetName(long cObject, String name);

    private native void cSetDoubleType(long cObject);

    private native void cSetFloatType(long cObject);

    private native void cSetLongType(long cObject);

    private native void cSetIntType(long cObject);

    private native ByteBuffer cSerializeCObject(long cObject);
    private native long cDeserializeCObject(ByteBuffer buffer, long size);

    /** @private */
    DataFeatureUtils.VectorUpCastIface[]   vectorUpCast;
    /** @private */
    DataFeatureUtils.VectorDownCastIface[] vectorDownCast;
}
