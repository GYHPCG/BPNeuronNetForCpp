#pragma once
#include<vector>
#include<algorithm>
#include"NeuronLayer.h"

// 定义激活函数的阈值
constexpr auto ACTIVE_RESPONSE = 0.7;

/**
 * 误差函数的导数阈值
 */
constexpr auto ERROR_RESPONSE = 0.7;

/**
 * 反向传播神经网络类
 * 该类实现了反向传播算法的神经网络模型，包括多层神经网络的训练和预测功能。
 */
class BPNeuronNet
{
public:
	// 输入层神经元数量
	int numInput;
	// 隐藏层神经元数量
	int numHiddenLayer;
	// 学习率，控制网络学习的速度
	double learningRate;
	// 累计误差，用于网络训练过程中的误差调整
	double errorSum = 0;
	// 神经网络的层结构，包括输入层、隐藏层和输出层
	std::vector<NeuronLayer> neuronLayers;

	/**
	 * 激活函数
	 * @param activation 激活值
	 * @param response 阈值
	 * @return 处理后的激活值
	 */
	static inline double sigmoidActive(double activation, double response);

	/**
	 * 反向传播激活函数
	 * @param x 输入值
	 * @param response 阈值
	 * @return 反向传播后的值
	 */
	static inline double backActive(double x, double response);

	/**
	 * 更新神经元层的权重和偏置
	 * @param nl 待更新的神经元层
	 * @param inputs 输入值数组
	 */
	void updateNeuronLayer(NeuronLayer& nl, const double inputs[]) const;

	/**
	 * 训练神经元层，计算误差和调整权重
	 * @param nl 待训练的神经元层
	 * @param activations 激活值数组
	 * @param errorArr 误差数组
	 */
	void trainNeuronLayer(NeuronLayer& nl, const double activations[], double errorArr[]) const;

	/**
	 * 在整个网络上进行一次训练更新
	 * @param inputs 输入值数组
	 * @param targets 目标值数组
	 */
	void trainUpdate(const double inputs[], const double targets[]);

	/**
	 * 获取网络的总误差
	 * @return 网络的总误差
	 */
	double getError() const;

	/**
	 * 训练神经网络
	 * @param inputs 输入值数组
	 * @param targets 目标值数组
	 */
	void training(double inputs[], const double targets[]);

	/**
	 * 使用训练好的神经网络进行预测
	 * @param inputs 输入值数组
	 * @param outputs 输出结果数组
	 */
	void predict(double inputs[], double *outputs[]);

	/**
	 * 添加一个新的神经元层到网络中
	 * @param numNeurons 层中神经元的数量
	 */
	void addLayer(int numNeurons);

	/**
	 * 构造函数，初始化神经网络
	 * @param numberInput 输入层神经元数量
	 * @param learningRate 学习率
	 */
	BPNeuronNet(int numberInput, double learningRate);

	/**
	 * 析构函数，释放神经网络资源
	 */
	~BPNeuronNet();
};

