#include "pch.h"
#include <iostream>
#include<fstream>
#include<future>
#include<sys/timeb.h>
#include"BPNeuronNet.h"
#include"NeuronUtils.h"
#include"Image.h"
#include"ProgressBar.h"
#include"Recognize.h"


// 定义常量，指向MNIST数据集的各个文件
#define TRAIN_IMAGES_URL "train-images.idx3-ubyte"
#define TRAIN_LABELS_URL "train-labels.idx1-ubyte"
#define TEST_IMAGES_URL "t10k-images.idx3-ubyte"
#define TEST_LABELS_URL "t10k-labels.idx1-ubyte"

// 将大端字节序转换为小端字节序
#define big_to_little32(A) ((((uint32_t)(A) & 0xff000000)>>24)|(((uint32_t)(A) & 0x00ff0000)>>8)|(((uint32_t)(A) & 0x0000ff00)<<8)|(((uint32_t)(A) & 0x000000ff)<<24))
// 从输入流中读取一个大端字节序的32位整数，并转换为小端字节序
#define load_from_big_to_little32(istream,value) istream.read(reinterpret_cast<char*>(&value),sizeof value);value=big_to_little32(value)

// 定义一个结构体，用于存储图像列表
typedef struct List {
	Image * imageList;
	int lenght;
}ImageList;

// 初始化进度条，用于显示加载图像和标签文件的进度
ProgressBar progressBar(70000, "loading test and train image...");

// 加载图像和标签文件，并返回一个包含图像和标签的结构体
ImageList loadImageAndLabelFile(const std::string& imagePath, const std::string& labelPath);
// 在新线程中加载图像和标签文件
void loadImageAndLabelFileInThread(std::promise<ImageList> &promiseObj, const std::string& imagePath, const std::string& labelPath);
// 重置图像和标签文件的读取位置
void reset(const std::string& imagePath, const std::string& labelPath);
// 获取当前时间，以毫秒为单位
long long getCurrentTime();
// 对输入图像数据添加噪声并进行预处理
void preProcessInputDataWithNoise(const uint8_t *pixel, double *out, int size);
// 对输入图像数据进行预处理
void preProcessInputData(const uint8_t *pixel, double *out, int size);
// 训练神经网络
double train(const ImageList& trainList, BPNeuronNet& bpNeuronNet);
// 测试神经网络
int test(const ImageList& testList, BPNeuronNet& bpNeuronNet);


int main()
{
	using namespace std;
	// 创建两个promise对象，用于在新线程中加载训练和测试数据
	promise<ImageList> trainingObj;
	future<ImageList> trainFutureObj = trainingObj.get_future();

	promise<ImageList> testObj;
	future<ImageList> testFutureObj = testObj.get_future();

	// 创建两个线程，分别加载训练和测试数据
	thread t1(loadImageAndLabelFileInThread, ref(trainingObj), TRAIN_IMAGES_URL, TRAIN_LABELS_URL);
	thread t2(loadImageAndLabelFileInThread, ref(testObj), TEST_IMAGES_URL, TEST_LABELS_URL);

	// 等待线程完成，获取加载的图像和标签数据
	ImageList trainingImageList = trainFutureObj.get();
	ImageList testImageList = testFutureObj.get();

	t1.join();
	t2.join();

	// 记录训练开始时间
	auto startTime = getCurrentTime();
	// 创建一个BP神经网络实例，指定输入层大小和学习率
	BPNeuronNet bpNeuronNet(trainingImageList.imageList[0].getRow()*trainingImageList.imageList[0].getColumn(), 0.1);
	// 添加隐藏层和输出层
	bpNeuronNet.addLayer(100);
	bpNeuronNet.addLayer(10);
	// 训练神经网络
	double error = train(trainingImageList, bpNeuronNet);
	// 测试神经网络
	int success = test(testImageList, bpNeuronNet);

	// 输出训练结果和测试结果
	cout << "error rate: " << error << endl;
	cout << "time:" << getCurrentTime() - startTime << endl;
	cout << "success: " << success << "count:" << testImageList.lenght << endl;
	cout << "time:" << getCurrentTime() - startTime << endl;

	// 进行手写数字识别测试
	cout << "手写数字识别测试" << endl;
	handWritingRecognize(bpNeuronNet);

}
// 重置图像和标签文件的读取位置
void reset(const std::string& imagePath, const std::string& labelPath){
	using namespace std;
	ifstream digitalImage;
	ifstream digitalLabel;

	digitalImage.open(imagePath, ios::binary);
	digitalLabel.open(labelPath, ios::binary);

	if (digitalImage.is_open()) {
		digitalImage.clear();
		digitalImage.seekg(0);
	}
	if (digitalLabel.is_open()) {
		digitalLabel.clear();
		digitalLabel.seekg(0);
	}
}
// 对输入图像数据添加噪声并进行预处理
void preProcessInputDataWithNoise(const uint8_t *pixel, double *out, int size) {
	for (int i = 0; i < size; i++) {
		out[i] = ((pixel[i] > 0) ? 1.0 : 0.0);
	}
}
// 对输入图像数据进行预处理
void preProcessInputData(const uint8_t *pixel, double *out, int size) {
	for (int i = 0; i < size; i++) {
		out[i] = ((pixel[i] > 0) ? 1.0 : 0.0);
	}
}
// 获取当前时间，以毫秒为单位
long long getCurrentTime() {
	timeb t;
	ftime(&t);
	return t.time * 1000 + t.millitm;
}
// 加载图像和标签文件，并返回一个包含图像和标签的结构体
ImageList loadImageAndLabelFile(const std::string& imagePath, const std::string& labelPath) {
	using namespace std;
	ImageList list = {};
	ifstream digitalImage;
	ifstream digitalLabel;

	digitalLabel.open(labelPath, ios::binary);
	digitalImage.open(imagePath, ios::binary);

	int32_t imageMagicNumber, imageCount, rows, columns;
	int32_t labelMagicNumber, labelCount;
	if (digitalImage.is_open() && digitalLabel.is_open()) {
		load_from_big_to_little32(digitalLabel, labelMagicNumber);
		load_from_big_to_little32(digitalLabel, labelCount);

		load_from_big_to_little32(digitalImage, imageMagicNumber);
		load_from_big_to_little32(digitalImage, imageCount);
		load_from_big_to_little32(digitalImage, rows);
		load_from_big_to_little32(digitalImage, columns);
		if (imageCount != labelCount) {
			digitalImage.close();
			digitalLabel.close();
			throw exception("input file have some error");
		}
		Image * imageList = new Image[imageCount];
		for (int i = 0; i < imageCount; i++) {
			imageList[i].initImage(rows, columns);
		}
		for (int i = 0; i < imageCount; i++) {
			for (int x = 0; x < rows; x++) {
				for (int y = 0; y < columns; y++) {
					uint8_t grayScale;
					digitalImage.read(reinterpret_cast<char *>(&grayScale), sizeof grayScale);
					imageList[i].setPixel(x, y, grayScale);
				}
			}
			uint8_t label;
			digitalLabel.read(reinterpret_cast<char *>(&label), sizeof label);
			imageList[i].setNumber(label);

			++progressBar;
		}
		list.imageList = imageList;
		list.lenght = imageCount;
	}
	digitalImage.close();
	digitalLabel.close();
	return list;
}
// 在新线程中加载图像和标签文件
void loadImageAndLabelFileInThread(std::promise<ImageList> &promiseObj, const std::string& imagePath, const std::string& labelPath) {
	promiseObj.set_value(loadImageAndLabelFile(imagePath, labelPath));

}

// 训练神经网络
double train(const ImageList& trainList, BPNeuronNet& bpNeuronNet) {
	double netTarget[10]; //输出层
	double netTrain[28 * 28]; // 输入层
	//重置进度条
	progressBar.reset(trainList.lenght, "start training...");
	for (int i = 0; i < trainList.lenght; i++) {
		memset(netTarget, 0, 10 * sizeof(double));
		netTarget[trainList.imageList[i].number] = 1.0;
		//给样本加入随机噪声
		preProcessInputDataWithNoise(trainList.imageList[i].getPixel(), netTrain, 28 * 28);
		// 训练神经网络
		bpNeuronNet.training(netTrain, netTarget);
		++progressBar;
	}
	// 返回误差
	return bpNeuronNet.getError();
}
// 测试神经网络
int test(const ImageList& testList, BPNeuronNet& bpNeuronNet) {
	int success = 0;
	double * netOut = nullptr;
	double netTest[28 * 28];
	progressBar.reset(testList.lenght, "testing neuron net...");
	for (int i = 0; i < testList.lenght; i++) {
		preProcessInputData(testList.imageList[i].getPixel(), netTest, 28 * 28);
		bpNeuronNet.predict(netTest, &netOut);

		int id = -1;
		double maxValue = -999;
		for (int j = 0; j < 10; j++) {
			if (netOut[j] > maxValue) {
				maxValue = netOut[j];
				id = j;
			}
		}
		if (id == testList.imageList[i].number) {
			success++;
		}
		++progressBar;
	}
	return success;
}

