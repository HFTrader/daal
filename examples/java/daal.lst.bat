@echo off
rem ============================================================================
rem Copyright 2014-2016 Intel Corporation
rem
rem Licensed under the Apache License, Version 2.0 (the "License");
rem you may not use this file except in compliance with the License.
rem You may obtain a copy of the License at
rem
rem     http://www.apache.org/licenses/LICENSE-2.0
rem
rem Unless required by applicable law or agreed to in writing, software
rem distributed under the License is distributed on an "AS IS" BASIS,
rem WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
rem See the License for the specific language governing permissions and
rem limitations under the License.
rem ============================================================================

rem  Content:
rem      Intel(R) Data Analytics Acceleration Library examples list
rem ============================================================================

set Java_example_list=association_rules\AprioriBatch ^
boosting\brownboost\BrownBoostBatch ^
boosting\adaboost\AdaBoostBatch ^
boosting\logitboost\LogitBoostBatch ^
cholesky\CholeskyBatch ^
compression\CompressorExample ^
compression\CompressionBatch ^
compression\CompressionOnline ^
covariance\CovarianceDenseBatch ^
covariance\CovarianceDenseDistributed ^
covariance\CovarianceDenseOnline ^
covariance\CovarianceCSRBatch ^
covariance\CovarianceCSRDistributed ^
covariance\CovarianceCSROnline ^
datasource\DataStructuresHomogen ^
datasource\DataStructuresHomogenTensor ^
datasource\DataStructuresAOS ^
datasource\DataStructuresSOA ^
datasource\DataStructuresCSR ^
datasource\DataStructuresMerged ^
datasource\DataStructuresMatrix ^
datasource\DataStructuresPacked ^
distance\CorrelationDistanceBatch ^
distance\CosineDistanceBatch ^
em\EmGmmBatch ^
kmeans\KMeansDenseBatch ^
kmeans\KMeansCSRBatch ^
kmeans\KMeansDenseDistributed ^
kmeans\KMeansCSRDistributed ^
linear_regression\LinearRegressionNormEqBatch ^
linear_regression\LinearRegressionNormEqDistributed ^
linear_regression\LinearRegressionNormEqOnline ^
linear_regression\LinearRegressionQRBatch ^
linear_regression\LinearRegressionQRDistributed ^
linear_regression\LinearRegressionQROnline ^
moments\LowOrderMomentsDenseBatch ^
moments\LowOrderMomentsDenseDistributed ^
moments\LowOrderMomentsDenseOnline ^
moments\LowOrderMomentsCSRBatch ^
moments\LowOrderMomentsCSRDistributed ^
moments\LowOrderMomentsCSROnline ^
naive_bayes\MultinomialNaiveBayesDenseBatch ^
naive_bayes\MultinomialNaiveBayesCSRBatch ^
naive_bayes\MultinomialNaiveBayesDenseOnline ^
naive_bayes\MultinomialNaiveBayesDenseDistributed ^
naive_bayes\MultinomialNaiveBayesCSROnline ^
naive_bayes\MultinomialNaiveBayesCSRDistributed ^
outlier_detection\OutlierDetectionUnivariateBatch ^
outlier_detection\OutlierDetectionMultivariateBaconBatch ^
outlier_detection\OutlierDetectionMultivariateDefaultBatch ^
pca\PCACorrelationDenseBatch ^
pca\PCACorrelationDenseDistributed ^
pca\PCACorrelationDenseOnline ^
pca\PCACorrelationCSRBatch ^
pca\PCACorrelationCSRDistributed ^
pca\PCACorrelationCSROnline ^
pca\PCASVDDenseBatch ^
pca\PCASVDDenseDistributed ^
pca\PCASVDDenseOnline ^
qr\QRBatch ^
qr\QRDistributed ^
qr\QROnline ^
serialization\SerializationExample ^
stump\StumpBatch ^
svd\SVDBatch ^
svd\SVDDistributed ^
svd\SVDOnline ^
svm\SVMMultiClassDenseBatch ^
svm\SVMMultiClassCSRBatch ^
svm\SVMTwoClassDenseBatch ^
svm\SVMTwoClassCSRBatch ^
services\LibraryVersionInfoExample ^
quantiles\QuantilesBatch ^
pivoted_qr\PivotedQRBatch ^
quality_metrics\SVMTwoClassQualityMetricSetBatchExample ^
quality_metrics\SVMMulticlassQualityMetricSetBatchExample ^
kernel_function\KernelFunctionLinearDenseBatch ^
kernel_function\KernelFunctionLinearCSRBatch ^
kernel_function\KernelFunctionRbfDenseBatch ^
kernel_function\KernelFunctionRbfCSRBatch ^
implicit_als\ImplicitAlsCSRBatch ^
implicit_als\ImplicitAlsCSRDistributed ^
implicit_als\ImplicitAlsDenseBatch ^
set_number_of_threads\SetNumberOfThreads ^
datasource\DataStructuresMerged ^
sorting\SortingBatch ^
error_handling\ErrorHandling ^
math\SoftmaxBatch ^
math\AbsDenseBatch ^
math\AbsCSRBatch ^
math\SmoothReLUBatch ^
math\LogisticBatch ^
math\ReLUCSRBatch ^
math\ReLUDenseBatch ^
math\TanhDenseBatch ^
math\TanhCSRBatch ^
normalization\ZScore ^
optimization_solver\SGDBatch ^
optimization_solver\SGDMiniBatch ^
optimization_solver\LBFGSBatch ^
optimization_solver\MSEBatch ^
neural_networks\ReLULayerBatch ^
neural_networks\AbsLayerBatch ^
neural_networks\DropoutLayerBatch ^
neural_networks\FullyconnectedLayerBatch ^
neural_networks\SplitLayerBatch ^
neural_networks\BatchNormalizationLayerBatch ^
neural_networks\SmoothReLULayerBatch ^
neural_networks\SoftmaxLayerBatch ^
neural_networks\PReLULayerBatch ^
neural_networks\TanhLayerBatch ^
neural_networks\LRNLayerBatch ^
neural_networks\Convolution2DLayerBatch ^
neural_networks\AveragePooling1DLayerBatch ^
neural_networks\MaximumPooling1DLayerBatch ^
neural_networks\AveragePooling2DLayerBatch ^
neural_networks\MaximumPooling2DLayerBatch ^
neural_networks\AveragePooling3DLayerBatch ^
neural_networks\MaximumPooling3DLayerBatch ^
neural_networks\LogisticLayerBatch ^
neural_networks\ConcatLayerBatch ^
neural_networks\NeuralNetworkBatch
