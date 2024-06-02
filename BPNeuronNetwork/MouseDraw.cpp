#include"pch.h"
#include"MouseDraw.h"

// 构造函数
BoxExtractor::BoxExtractor() {

}

// 鼠标事件处理函数，将鼠标事件转发给opencv_mouse_callback处理
void BoxExtractor::mouseHandler(int event, int x, int y, int flags, void *param) {
	BoxExtractor *self = static_cast<BoxExtractor*>(param);
	self->opencv_mouse_callback(event, x, y, flags, param);
}

// OpenCV的鼠标回调函数，根据鼠标事件收集绘制的点
void BoxExtractor::opencv_mouse_callback(int event, int x, int y, int, void *param) {
	handlerT * data = (handlerT *)param;
	switch (event)
	{
	case EVENT_MOUSEMOVE:
		if (data->isDrawing) {
			data->points.push_back(cv::Point(x, y));
		}
		break;
	case EVENT_LBUTTONDOWN:
		data->isDrawing = true;
		data->points.clear();
		data->points.push_back(cv::Point(x, y));
		break;
	case EVENT_LBUTTONUP:
		data->isDrawing = false;
		break;
	}
}

// 通过鼠标在图像上绘制并返回处理后的图像
Mat BoxExtractor::MouseDraw(Mat& img) {
	MouseDraw("Draw an digital", img, Scalar(0, 0, 0), 4);
	return img;
}

// 主要的鼠标绘制函数，处理图像绘制逻辑并响应键盘事件
int BoxExtractor::MouseDraw(const std::string& windowName, Mat& img, Scalar color, int border) {
	int key = 0;
	imshow(windowName, img);
	cout << "利用鼠标写下一个或多个数字，按回车输出预测结果并进行下一次书写，esc退出" << endl;
	params.image = img.clone();
	setMouseCallback(windowName, mouseHandler, (void *)&params);
	int cnt = 0;
	while (!(key == 32 || key == 27 || key == 13)) { // 空格、ESC、回车键退出循环
		int length = params.points.size();
		for (int i = 0; i < length&&length>2; i++) {
			if (i == length - 1) {
				cv::line(params.image, params.points.at(i), params.points.at(i), color, border);
			}
			else {
				cv::line(params.image, params.points.at(i), params.points.at(i + 1), color, border);
			}
		}
		imshow(windowName, params.image);
		key = waitKey(1);
	}
	params.image.copyTo(img);
	return key;
}
