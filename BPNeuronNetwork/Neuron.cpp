#include"pch.h"
#include"NeuronUtils.h"
#include"Neuron.h"

/**
 * 重置神经元的状态。
 * 将激活值和误差设置为-1，并随机初始化权重。
 */
void Neuron::reset() {
	activation = -1;
	error = -1;
	for (int i = 0; i < numInputPerNerous; i++) {
		weight[i] = randomClamped();
	}
}

/**
 * 构造一个神经元对象。
 * @param numInputPerNerous 每个神经元的输入数量。
 * 初始化权重和动量，并为权重和动量分配内存。
 */
Neuron::Neuron(const int numInputPerNerous) :numInputPerNerous(numInputPerNerous) {
	weight = new double[numInputPerNerous + 1];//多1个作为 bias
	for (int i = 0; i <= numInputPerNerous; i++) {
		weight[i] = randomClamped();
	}
	momentum = new double[numInputPerNerous + 1];
	for (int i = 0; i <= numInputPerNerous; i++) {
		momentum[i] = 0;
	}
}

/**
 * 移动构造函数。
 * @param n 被移动的神经元对象。
 * 通过移动语义构造一个神经元，同时确保被移动对象不再拥有资源。
 */
Neuron::Neuron(Neuron&& n) noexcept :numInputPerNerous(n.numInputPerNerous), activation(n.activation), error(n.error), weight(n.weight) {
	weight = nullptr;
}

/**
 * 析构函数。
 * 释放神经元所拥有的资源。
 */
Neuron::~Neuron() {
	_delete(weight);
}
