#include"pch.h"
#include"Recognize.h"
#include"BPNeuronNet.h"

// 定义窗口名称
#define WINDOW_NAME "predict"

/**
 * 手写数字识别函数
 * @param bpNeuronNet 一个已经训练好的BP神经网络，用于识别手写数字
 */
void handWritingRecognize(BPNeuronNet& bpNeuronNet) {
    // 初始化一个500x500的灰度图像，用于绘制手写数字
    Mat srcImage(500, 500, CV_8UC1, Scalar::all(0)), image;
    // 创建一个窗口用于显示绘制的数字
    namedWindow(WINDOW_NAME);
    while (true) {
        // 初始化框提取器，用于绘制矩形框选择手写数字区域
        BoxExtractor box;
        // 将srcImage复制到image，用于绘制和处理
        srcImage.copyTo(image);
        // 调用box.MouseDraw在窗口中绘制并返回按键值
        int key = box.MouseDraw(WINDOW_NAME, image, Scalar::all(255), 5);
        // 如果按键值不为13（回车键），则退出循环
        if (key != 13) {
            break;
        }
        // 分割图像中的每个数字
        vector<Mat> arr;
        getSegment(image, arr, image);
        cout << "predict result:" << endl;
        for (int i = 0; i < arr.size(); ++i) {
            // 对每个数字进行尺寸调整和边界填充
            resize(arr[i], arr[i], Size(20, 20));//归一化
            copyMakeBorder(arr[i], arr[i], 4, 4, 4, 4, BORDER_CONSTANT, Scalar::all(0));//边界填充，填充纯黑边界
            // 将Mat转换为二维数组，以满足神经网络的输入要求
            uchar **array = new uchar*[arr[i].rows];
            for (int j = 0; j < arr[i].rows; j++) {
                array[j] = new uchar[arr[i].cols];
            }
            for (int j = 0; j < arr[i].rows; j++) {
                for (int k = 0; k < arr[i].cols; k++) {
                    array[j][k] = arr[i].at<uchar>(j, k);
                }
            }
            // 准备神经网络的输入数据
            double netTest[28 * 28];
            double * netOut = nullptr;
            for (int j = 0; j < 28; j++) {
                for (int k = 0; k < 28; k++) {
                    netTest[j * 28 + k] = (double)array[j][k] > 0 ? 1.0 : 0.0;
                }
            }
            // 使用神经网络进行预测
            bpNeuronNet.predict(netTest, &netOut);
            // 找到预测结果中概率最高的数字
            int id = -1;
            double maxValue = -999;
            for (int j = 0; j < 10; j++) {
                if (netOut[j] > maxValue) {
                    maxValue = netOut[j];
                    id = j;
                }
            }
            // 输出预测的数字
            cout << id << " ";
        }
        cout << endl;
        // 显示处理后的图像
        imshow(WINDOW_NAME, image);
       // cout << "输入任意字符进行下一次的输入，输入esc回到上一级" << endl;
        //cout << "输入任意字符进行下一次的输入，输入esc回到上一级\n";
        key = waitKey(0);
        // 如果按键为ESC，则退出循环
        if (key == 27) {
            break;
        }
    }
    // 关闭窗口
    destroyWindow(WINDOW_NAME);
}
