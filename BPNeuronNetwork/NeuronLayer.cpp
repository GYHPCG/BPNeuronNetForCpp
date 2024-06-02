#include"pch.h"
#include"NeuronUtils.h"
#include"NeuronLayer.h"

// �����񾭲���������Ԫ��״̬
void NeuronLayer::reset() const {
	for (int i = 0; i < size; i++) {
		neurons[i].reset();
	}
}

// ��ȡ�񾭲�ļ���ֵ����
double* NeuronLayer::getActivation()const {
	const int size = this->size;
	for (int i = 0; i < size; i++) {
		activation[i] = neurons[i].activation;
	}
	return activation;
}

// ��ȡ�񾭲�����ֵ����
double* NeuronLayer::getError()const {
	const int size = this->size;
	for (int i = 0; i < size; i++) {
		error[i] = neurons[i].error;
	}
	return error;
}

// ���캯������ʼ���񾭲㣬���伤��ֵ�����ֵ����
NeuronLayer::NeuronLayer(const int inputPerNeuron, Neuron* neurons, const int size) :activation(new double[size]), error(new double[size]), size(size), inputPerNeuron(inputPerNeuron), neurons(neurons) {
}

// �������캯����������һ���񾭲��״̬
NeuronLayer::NeuronLayer(const NeuronLayer& nl) {
	this->inputPerNeuron = nl.inputPerNeuron;
	this->neurons = nl.neurons;
	this->size = nl.size;
	this->activation = nl.activation;
	this->error = nl.error;
}

// �ƶ����캯����ͨ��ת������Ȩ�����񾭲�
NeuronLayer::NeuronLayer(NeuronLayer&& nl)noexcept :activation(nl.activation), error(nl.error), size(nl.size), inputPerNeuron(nl.inputPerNeuron), neurons(nl.neurons) {
	nl.activation = nullptr;
	nl.error = nullptr;
	nl.neurons = nullptr;
}

// �����������ͷ��񾭲����ļ���ֵ�����ֵ����
NeuronLayer::~NeuronLayer() {
	_delete(error);
	_delete(activation);
}
