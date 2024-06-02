#pragma once
#include<opencv2/opencv.hpp>
#include<fstream>
#include<iostream>

// 使用标准命名空间std和OpenCV的命名空间cv
using namespace std;
using namespace cv;

/**
 * @brief 盒子提取器类
 * 该类用于通过鼠标绘制操作从图像中提取矩形框。
 */
class BoxExtractor {
	public:
		/**
		 * @brief BoxExtractor的构造函数
		 * 初始化鼠标绘制参数。
		 */
		BoxExtractor();

		/**
		 * @brief 使用鼠标绘制矩形框
		 * @param img 输入图像
		 * @return 处理后的图像
		 * 该函数允许用户通过鼠标在图像上绘制矩形框，并返回绘制后的图像。
		 */
		Mat MouseDraw(Mat& img);

		/**
		 * @brief 鼠标绘制矩形框的辅助函数
		 * @param windowName 窗口名称
		 * @param img 输入图像
		 * @param color 矩形框的颜色
		 * @param border 矩形框的边框宽度
		 * @return 用户绘制的矩形框数量
		 * 该函数设置鼠标回调函数，允许用户在指定窗口的图像上绘制矩形框。
		 */
		int MouseDraw(const std::string& windowName, Mat& img, Scalar color, int border);

		/**
		 * @brief 鼠标事件处理参数
		 * 包含绘制状态、绘制点集合、当前操作的图像。
		 */
		struct handlerT{
			bool isDrawing; /**< 绘制状态，表示是否正在绘制矩形框 */
			std::vector<cv::Point> points; /**< 绘制的点集合，用于存储矩形框的角点 */
			Mat image; /**< 当前操作的图像 */
			/**
			 * @brief handlerT的构造函数
			 * 初始化绘制状态为非绘制状态。
			 */
			handlerT() :isDrawing(false) {};
		}params; /**< 鼠标事件处理的参数实例 */

	private:
		/**
		 * @brief 鼠标事件的回调函数
		 * @param event 鼠标事件类型
		 * @param x 鼠标事件的x坐标
		 * @param y 鼠标事件的y坐标
		 * @param flags 鼠标事件的标志位
		 * @param param 额外的参数，指向handlerT对象
		 * 该函数是鼠标事件的回调函数，根据不同的鼠标事件，进行相应的处理。
		 */
		static void mouseHandler(int event, int x, int y, int flags, void *param);

		/**
		 * @brief 鼠标回调函数的内部实现
		 * @param event 鼠标事件类型
		 * @param x 鼠标事件的x坐标
		 * @param y 鼠标事件的y坐标
		 * @param flags 鼠标事件的标志位
		 * @param param 额外的参数，指向handlerT对象
		 * 该函数是mouseHandler的内部实现，具体处理鼠标事件，并更新handlerT对象的状态。
		 */
		void opencv_mouse_callback(int event, int x,int y, int, void *param);
};
