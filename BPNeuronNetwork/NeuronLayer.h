#pragma once
#include<vector>
#include"Neuron.h"

/* 神经网络层类 */
class NeuronLayer
{
	/* 激活值数组，用于存储神经元的激活值 */
	double * activation;
	/* 错误梯度数组，用于存储神经元的错误梯度 */
	double * error;

public:
	/* 神经元数量 */
	int size;
	/* 每个神经元的输入数量 */
	int inputPerNeuron;
	/* 神经元指针数组，存储层内的神经元对象 */
	Neuron* neurons;

	/**
	 * 构造函数，初始化神经网络层
	 * @param inputPerNeuron 每个神经元的输入数量
	 * @param neurons 神经元数组
	 * @param size 神经元数量
	 */
	NeuronLayer(int inputPerNeuron, Neuron* neurons, int size);

	/**
	 * 复制构造函数，用于创建一个现有神经网络层的副本
	 * @param nl 现有神经网络层对象
	 */
	NeuronLayer(const NeuronLayer& nl);

	/**
	 * 移动构造函数，用于高效地转移资源所有权
	 * @param nl 现有神经网络层对象，转移所有权后不再有效
	 */
	NeuronLayer(NeuronLayer&& nl)noexcept;

	/* 析构函数，用于释放资源 */
	~NeuronLayer();

	/**
	 * 重置神经元层的激活值和错误梯度
	 */
	void reset() const;

	/**
	 * 获取神经元层的激活值数组
	 * @return 激活值数组的指针
	 */
	double* getActivation() const;

	/**
	 * 获取神经元层的错误梯度数组
	 * @return 错误梯度数组的指针
	 */
	double* getError() const;

};
