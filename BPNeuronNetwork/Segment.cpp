#include"pch.h"
#include"Segment.h"
using namespace cv;

// 比较函数，用于矩形区域的x坐标排序
bool cmp(const Rect& a, const Rect& b) {
	return a.x < b.x;
}

// 比较函数，用于矩形区域的y坐标排序
bool cmp2(const Rect& a, const Rect& b) {
	return a.tl().y < b.tl().y;
}

// 对矩形区域进行排序，首先按y坐标排序，然后按x坐标排序
void sortRect(vector<Rect>& arr) {
	sort(arr.begin(), arr.end(), cmp2);
	vector<Rect>::iterator s = arr.begin();
	vector<Rect>::iterator e = arr.end();
	vector<Rect>::iterator ptr = arr.begin();
	vector<Rect>::iterator preptr = ptr++;
	for (;; ++ptr, ++preptr) {
		if (ptr == arr.end() || ptr->tl().y > preptr->br().y) {
			e = ptr;
			sort(s, e, cmp);
			s = ptr;
			if (ptr == arr.end())
				break;
		}
	}
}

// 根据输入图像获取分割区域
// srcImage: 输入图像
// arr: 存储分割后的区域
// showImage: 用于显示分割结果的图像
void getSegment(const Mat& srcImage, vector<Mat>& arr, Mat& showImage) {
	// 创建临时图像以进行处理
	Mat tmpImage = srcImage.clone();
	// 如果图像不是单通道灰度图，则转换为灰度图
	if (tmpImage.type() != CV_8UC1) {
		cvtColor(tmpImage, tmpImage, CV_BGR2GRAY);
	}
	// 二值化处理图像
	threshold(tmpImage, tmpImage, 0, 255, CV_THRESH_BINARY);
	// 存储轮廓的向量
	vector<vector<Point>> contours;
	// 查找图像中的轮廓
	findContours(tmpImage, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	// 创建另一个临时图像以进行绘制
	Mat tmpImage3 = srcImage.clone();
	// 存储矩形区域的向量
	vector<Rect> rectArr;
	// 遍历所有轮廓，计算其边界矩形
	for (int i = 0; i < contours.size(); ++i) {
		Rect rec = boundingRect(contours[i]);
		// 如果矩形面积大于等于64，则添加到矩形数组中
		if (rec.area() >= 8 * 8) {
			rectArr.push_back(rec);
		}
	}
	// 对矩形区域进行排序
	sortRect(rectArr);
	// 遍历所有矩形区域，提取并存储每个区域
	for (int i = 0; i < rectArr.size(); ++i) {
		// 从临时图像中提取当前区域
		Mat tmp = tmpImage3(rectArr[i]);
		// 在显示图像上绘制当前区域的边界
		rectangle(showImage, rectArr[i], Scalar(100), 2);
		// 对当前区域进行某种处理（函数normal未定义，此处仅为示例）
		normal(tmp, tmp);
		// 将当前区域添加到分割区域的数组中
		arr.push_back(tmp);
	}
}
