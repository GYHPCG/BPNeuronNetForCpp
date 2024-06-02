#include"pch.h"
#include"NeuronUtils.h"
#include"Neuron.h"

/**
 * ������Ԫ��״̬��
 * ������ֵ���������Ϊ-1���������ʼ��Ȩ�ء�
 */
void Neuron::reset() {
	activation = -1;
	error = -1;
	for (int i = 0; i < numInputPerNerous; i++) {
		weight[i] = randomClamped();
	}
}

/**
 * ����һ����Ԫ����
 * @param numInputPerNerous ÿ����Ԫ������������
 * ��ʼ��Ȩ�غͶ�������ΪȨ�غͶ��������ڴ档
 */
Neuron::Neuron(const int numInputPerNerous) :numInputPerNerous(numInputPerNerous) {
	weight = new double[numInputPerNerous + 1];//��1����Ϊ bias
	for (int i = 0; i <= numInputPerNerous; i++) {
		weight[i] = randomClamped();
	}
	momentum = new double[numInputPerNerous + 1];
	for (int i = 0; i <= numInputPerNerous; i++) {
		momentum[i] = 0;
	}
}

/**
 * �ƶ����캯����
 * @param n ���ƶ�����Ԫ����
 * ͨ���ƶ����幹��һ����Ԫ��ͬʱȷ�����ƶ�������ӵ����Դ��
 */
Neuron::Neuron(Neuron&& n) noexcept :numInputPerNerous(n.numInputPerNerous), activation(n.activation), error(n.error), weight(n.weight) {
	weight = nullptr;
}

/**
 * ����������
 * �ͷ���Ԫ��ӵ�е���Դ��
 */
Neuron::~Neuron() {
	_delete(weight);
}
