#pragma once
#include<opencv2/opencv.hpp>
#include <opencv2\imgproc\types_c.h>

#include<vector>
#include<string>
#include<iostream>
#include<fstream>
using namespace std;
using namespace cv;

// 定义一个函数指针类型，用于获取BP特征
typedef void(*getBPfeature)(const Mat& srcDataMat, Mat& dstDataMat, Size size);

/**
 * @brief 缩小图像尺寸
 * @param srcImage 原始图像
 * @param size 目标尺寸
 */
void resizeImage(Mat& srcImage, Size size);

/**
 * @brief 初始化二值化处理
 * @param srcDataMat 原始图像矩阵
 * @param size 图像尺寸
 */
void binaryInit(Mat& srcDataMat, Size size);

/**
 * @brief 计算图像的直方图特征
 * @param srcDataMat 原始图像矩阵
 * @param dstDataMat 目标特征矩阵
 * @param size 图像尺寸
 */
void getHistogramFeature(const Mat& srcDataMat, Mat& dstDataMat, Size size);

/**
 * @brief 获取所有像素点的特征
 * @param srcDataMat 原始图像矩阵
 * @param dstDataMat 目标特征矩阵
 * @param size 图像尺寸
 */
void getAllPixelsFeature(const Mat& srcDataMat, Mat& dstDataMat, Size size);

/**
 * @brief 获取混合特征
 * @param srcImage 原始图像
 * @param dstImage 目标图像
 * @param size 图像尺寸
 */
void getMixedFeature(const Mat& srcImage, Mat& dstImage, Size size);

/**
 * @brief 将图像转换为向量
 * @param srcImage 原始图像
 * @param dstImage 目标向量图像
 */
void image2Vec(const Mat& srcImage, Mat& dstImage);

/**
 * @brief 图像归一化处理
 * @param srcImage 原始图像
 * @param dstImage 目标图像
 */
void normal(Mat& srcImage, Mat& dstImage);
