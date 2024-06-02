#include"pch.h"
#include"Image.h"
#include<iostream>
#include<bitset>

/**
 * @brief Image类的构造函数，用于初始化图像对象
 *
 * @param row 图像的行数
 * @param column 图像的列数
 * @param threshold 图像的阈值，用于像素值的处理
 */
Image::Image(int row, int column, int threshold) :threshold(threshold), divideRow(4), divideColumn(4) {
	initImage(row, column);
}

/**
 * @brief Image类的构造函数，用于初始化图像对象，不指定图像大小
 *
 * @param threshold 图像的阈值，用于像素值的处理
 */
Image::Image(int threshold) : threshold(threshold), row(0), column(0), divideRow(4), divideColumn(4) {

}

/**
 * @brief Image类的析构函数
 */
Image::~Image() {

}

/**
 * @brief 获取图像的像素数据指针
 *
 * @return uint8_t* 像素数据指针
 */
uint8_t* Image::getPixel()const {
	return pixel;
}

/**
 * @brief 初始化图像的尺寸和像素数据
 *
 * @param row 图像的行数
 * @param column 图像的列数
 */
void Image::initImage(int row, int column) {
	this->row = row;
	this->column = column;
	pixel = new uint8_t[row*column];
}

/**
 * @brief 设置图像中指定位置的像素值
 *
 * @param x 像素的x坐标
 * @param y 像素的y坐标
 * @param value 像素的值
 */
void Image::setPixel(int x, int y, uint8_t value)const {
	//if (value > threshold)
	//	value = 1;
	pixel[x*column + y] = value;
}

/**
 * @brief 设置图像的编号
 *
 * @param value 图像的编号值
 */
void Image::setNumber(int value) {
	this->number = value;
}

/**
 * @brief 打印图像的编号和像素表示
 */
void Image::print()const {
	using namespace std;
	cout << endl << number << endl;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			cout << (pixel[i*column + j] == 0 ? " " : "*");
		}
		cout << endl;
	}
}

/**
 * @brief 获取图像的列数
 *
 * @return int 图像的列数
 */
int Image::getColumn()const {
	return column;
}

/**
 * @brief 获取图像的行数
 *
 * @return int 图像的行数
 */
int Image::getRow()const {
	return row;
}
