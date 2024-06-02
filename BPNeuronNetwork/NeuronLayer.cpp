#include"pch.h"
#include"NeuronUtils.h"
#include"NeuronLayer.h"

// 重置神经层中所有神经元的状态
void NeuronLayer::reset() const {
	for (int i = 0; i < size; i++) {
		neurons[i].reset();
	}
}

// 获取神经层的激活值数组
double* NeuronLayer::getActivation()const {
	const int size = this->size;
	for (int i = 0; i < size; i++) {
		activation[i] = neurons[i].activation;
	}
	return activation;
}

// 获取神经层的误差值数组
double* NeuronLayer::getError()const {
	const int size = this->size;
	for (int i = 0; i < size; i++) {
		error[i] = neurons[i].error;
	}
	return error;
}

// 构造函数：初始化神经层，分配激活值和误差值数组
NeuronLayer::NeuronLayer(const int inputPerNeuron, Neuron* neurons, const int size) :activation(new double[size]), error(new double[size]), size(size), inputPerNeuron(inputPerNeuron), neurons(neurons) {
}

// 拷贝构造函数：复制另一个神经层的状态
NeuronLayer::NeuronLayer(const NeuronLayer& nl) {
	this->inputPerNeuron = nl.inputPerNeuron;
	this->neurons = nl.neurons;
	this->size = nl.size;
	this->activation = nl.activation;
	this->error = nl.error;
}

// 移动构造函数：通过转移所有权构造神经层
NeuronLayer::NeuronLayer(NeuronLayer&& nl)noexcept :activation(nl.activation), error(nl.error), size(nl.size), inputPerNeuron(nl.inputPerNeuron), neurons(nl.neurons) {
	nl.activation = nullptr;
	nl.error = nullptr;
	nl.neurons = nullptr;
}

// 析构函数：释放神经层分配的激活值和误差值数组
NeuronLayer::~NeuronLayer() {
	_delete(error);
	_delete(activation);
}
