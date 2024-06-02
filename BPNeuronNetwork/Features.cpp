#include "pch.h"
#include "Features.h"

/**
 * 缩放图像，根据图像面积决定使用插值方法
 * @param srcImage 原始图像
 * @param size 目标尺寸
 */
void resizeImage(Mat& srcImage, Size size) {
    // 根据图像面积决定使用的缩放方法
    if (srcImage.rows * srcImage.cols < size.area()) {
        resize(srcImage, srcImage, size, 0, 0, INTER_CUBIC);
    } else if (srcImage.rows * srcImage.cols > size.area()) {
        resize(srcImage, srcImage, size, 0, 0, INTER_AREA);
    }
}

/**
 * 初始化二值化过程
 * @param srcDataMat 原始数据矩阵
 * @param size 目标尺寸
 */
//��ֵ��
void binaryInit(Mat& srcDataMat, Size size) {
    srcDataMat.convertTo(srcDataMat, CV_8UC1);
    normal(srcDataMat, srcDataMat);
    resizeImage(srcDataMat, size);
    threshold(srcDataMat, srcDataMat, 0, 255, CV_THRESH_OTSU + CV_THRESH_BINARY);
    srcDataMat.convertTo(srcDataMat, CV_32FC1);
}

/**
 * 对图像进行归一化处理，并裁剪出包含物体的区域
 * @param srcImage 原始图像
 * @param dstImage 处理后的图像
 */
//��һ��
void normal(Mat& srcImage, Mat& dstImage) {
    int bottom = srcImage.rows + 1;
    int top = 0;
    int left = srcImage.cols + 1;
    int right = 0;
    // 遍历图像，找到物体区域的最上、下、左、右边界
    for (int i = 0; i < srcImage.rows; ++i) {
        for (int j = 0; j < srcImage.cols; ++j) {
            if (srcImage.at<uchar>(i, j) > 0) {
                bottom = min(bottom, i);
                top = max(top, i);
                left = min(left, j);
                right = max(right, j);
            }
        }
    }
    // 根据边界计算物体区域，并复制到目标图像
    Rect rec = Rect(left, bottom, right - left + 1, top - bottom + 1);
    Mat roi = srcImage(rec);
    int width = roi.cols;
    int height = roi.rows;
    int longLen = max(width, height);
    int shortLen = width + height - longLen;
    dstImage = Mat(longLen, longLen, CV_8UC1, Scalar::all(0));
    roi.copyTo(dstImage(Rect((longLen - width) / 2, (longLen - height) / 2, width, height)));
}

/**
 * 计算大于阈值的像素数量
 * @param srcDataMat 原始数据矩阵
 * @param thresh 阈值
 * @return 大于阈值的像素数量
 */
//ͳ�ƴ�����ֵ�����ظ���
float calBigNumber(const Mat& srcDataMat, float thresh) {
    float sum = 0.0;
    // 遍历图像，计算大于阈值的像素数量
    for (int i = 0; i < srcDataMat.rows; ++i) {
        for (int j = 0; j < srcDataMat.cols; ++j) {
            if (srcDataMat.at<float>(i, j) > thresh) {
                sum += 1.0;
            }
        }
    }
    return sum;
}

/**
 * 计算图像的直方图
 * @param srcMat 原始图像
 * @param histogramMat 直方图矩阵
 * @param flag 计算方式标志（0：按行计算，1：按列计算）
 */
void getHistogram(const Mat& srcMat, Mat& histogramMat, int flag) {//flagΪ0ʱ�����е�ֱ��ͼ��Ϊ1ʱ�����е�ֱ��ͼ
    float sum = 0.0;
    int size = flag == 0 ? srcMat.rows : srcMat.cols;
    Mat listOfMat;
    // 根据标志值按行或按列计算直方图
    for (int i = 0; i < size; ++i) {
        listOfMat = flag == 0 ? srcMat.row(i) : srcMat.col(i);
        sum = calBigNumber(listOfMat, 0);
        histogramMat.at<float>(0, i) = sum;
    }
    normalize(histogramMat, histogramMat, 1.0, 0.0, NORM_MINMAX);
}

/**
 * 提取所有像素的特征
 * @param srcDataMat 原始数据矩阵
 * @param dstDataMat 特征矩阵
 * @param size 目标尺寸
 */
void getAllPixelsFeature(const Mat& srcDataMat, Mat& dstDataMat, Size size) {
    Mat tmpDataMat = srcDataMat.clone();
    binaryInit(tmpDataMat, size);
    image2Vec(tmpDataMat, dstDataMat);
}

/**
 * 提取图像的直方图特征
 * @param srcDataMat 原始数据矩阵
 * @param dstDataMat 特征矩阵
 * @param size 目标尺寸
 */
void getHistogramFeature(const Mat& srcDataMat, Mat& dstDataMat, Size size) {
    Mat tmpDataMat = srcDataMat.clone();
    binaryInit(tmpDataMat, size);
    Mat rowHistogram = Mat::zeros(1, tmpDataMat.rows, CV_32FC1), colHistogram = Mat::zeros(1, tmpDataMat.cols, CV_32FC1);
    // 计算行和列的直方图
    getHistogram(tmpDataMat, rowHistogram, 0);
    getHistogram(tmpDataMat, colHistogram, 1);
    int cnt = 0;
    Mat tmpDstMat = Mat::zeros(1, rowHistogram.cols + colHistogram.cols, CV_32FC1);
    // 合并行和列的直方图
    for (int i = 0; i < rowHistogram.cols; ++i) {
        tmpDstMat.at<float>(0, cnt++) = rowHistogram.at<float>(0, i);
    }
    for (int i = 0; i < colHistogram.cols; ++i) {
        tmpDstMat.at<float>(0, cnt++) = colHistogram.at<float>(0, i);
    }
    dstDataMat = tmpDstMat.clone();
}

/**
 * 将图像数据转换为向量形式
 * @param srcImage 原始图像
 * @param dstImage 转换后的向量图像
 */
void image2Vec(const Mat& srcImage, Mat& dstImage) {
    // 如果图像连续，直接重塑为一维向量
    if (srcImage.isContinuous()) {
        dstImage = srcImage.reshape(1, 1);
    } else {
        // 否则，逐行复制到向量中
        for (int i = 0; i < srcImage.rows; ++i) {
            for (int j = 0; j < srcImage.cols; ++j) {
                dstImage.at<float>(i * srcImage.cols + j) = srcImage.at<float>(i, j);
            }
        }
    }
}

/**
 * 获取混合特征
 * @param srcDataMat 原始数据矩阵
 * @param dstDataMat 特征矩阵
 * @param size 目标尺寸
 */
void getMixedFeature(const Mat& srcDataMat, Mat& dstDataMat, Size size) {
    Mat tmpDataMat1;
    getAllPixelsFeature(srcDataMat, tmpDataMat1, Size(8, 8));
    normalize(tmpDataMat1, tmpDataMat1, 1.0, 0.0, NORM_MINMAX);//��һ��Ϊ0��1����
    Mat tmpDataMat2;
    getHistogramFeature(srcDataMat, tmpDataMat2, size);
    Mat tmpDataMat3 = Mat::zeros(1, tmpDataMat1.cols + tmpDataMat2.cols, CV_32FC1);
    int cnt = 0;
    // 合并所有像素特征和直方图特征
    for (int i = 0; i < tmpDataMat1.cols; ++i) {
        tmpDataMat3.at<float>(0, cnt++) = tmpDataMat1.at<float>(i);
    }
    for (int i = 0; i < tmpDataMat2.cols; ++i) {
        tmpDataMat3.at<float>(0, cnt++) = tmpDataMat2.at<float>(i);
    }
    dstDataMat = tmpDataMat3.clone();
}
