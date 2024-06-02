#pragma once
#include<cstdint>

/**
 * @brief 图像处理类
 *
 * 该类用于表示和操作图像，包括图像的初始化、像素值的设置和获取、图像分割等操作。
 * 支持自定义图像的大小和阈值，以适应不同的图像处理需求。
 */
class Image
{
	int threshold; /**< 图像处理的阈值 */
	uint8_t * pixel; /**< 图像的像素数据指针 */
	int row, column, divideRow, divideColumn; /**< 图像的行数、列数及分割后的行数、列数 */

public:
	int number; /**< 图像的编号 */
	int width, height; /**< 图像的宽度和高度 */
	uint8_t * dividePixel; /**< 分割后的图像像素数据指针 */

	/**
	 * @brief 构造函数，用于创建指定大小的图像
	 *
	 * @param row 图像的行数
	 * @param column 图像的列数
	 * @param threshold 图像处理的阈值，默认为0
	 */
	Image(int row, int column, int threshold = 0);

	/**
	 * @brief 构造函数，用于创建默认大小的图像
	 *
	 * @param threshold 图像处理的阈值，默认为0
	 */
	Image(int threshold = 0);

	/**
	 * @brief 获取图像的像素数据
	 *
	 * @return uint8_t* 图像的像素数据指针
	 */
	uint8_t * getPixel() const;

	/**
	 * @brief 初始化图像的大小
	 *
	 * @param row 图像的行数
	 * @param column 图像的列数
	 */
	void initImage(int row, int column);

	/**
	 * @brief 设置图像中指定位置的像素值
	 *
	 * @param x 像素的x坐标
	 * @param y 像素的y坐标
	 * @param value 要设置的像素值
	 */
	void setPixel(int x, int y, uint8_t value) const;

	/**
	 * @brief 设置图像的编号
	 *
	 * @param value 图像的编号
	 */
	void setNumber(int value);

	/**
	 * @brief 打印图像信息
	 */
	void print()const;

	/**
	 * @brief 获取图像的行数
	 *
	 * @return int 图像的行数
	 */
	int getRow()const;

	/**
	 * @brief 获取图像的列数
	 *
	 * @return int 图像的列数
	 */
	int getColumn()const;

	/**
	 * @brief 析构函数，用于释放图像资源
	 */
	~Image();
};
