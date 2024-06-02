#pragma once
#include<vector>
#include"Neuron.h"

/* ��������� */
class NeuronLayer
{
	/* ����ֵ���飬���ڴ洢��Ԫ�ļ���ֵ */
	double * activation;
	/* �����ݶ����飬���ڴ洢��Ԫ�Ĵ����ݶ� */
	double * error;

public:
	/* ��Ԫ���� */
	int size;
	/* ÿ����Ԫ���������� */
	int inputPerNeuron;
	/* ��Ԫָ�����飬�洢���ڵ���Ԫ���� */
	Neuron* neurons;

	/**
	 * ���캯������ʼ���������
	 * @param inputPerNeuron ÿ����Ԫ����������
	 * @param neurons ��Ԫ����
	 * @param size ��Ԫ����
	 */
	NeuronLayer(int inputPerNeuron, Neuron* neurons, int size);

	/**
	 * ���ƹ��캯�������ڴ���һ�������������ĸ���
	 * @param nl ��������������
	 */
	NeuronLayer(const NeuronLayer& nl);

	/**
	 * �ƶ����캯�������ڸ�Ч��ת����Դ����Ȩ
	 * @param nl ��������������ת������Ȩ������Ч
	 */
	NeuronLayer(NeuronLayer&& nl)noexcept;

	/* ���������������ͷ���Դ */
	~NeuronLayer();

	/**
	 * ������Ԫ��ļ���ֵ�ʹ����ݶ�
	 */
	void reset() const;

	/**
	 * ��ȡ��Ԫ��ļ���ֵ����
	 * @return ����ֵ�����ָ��
	 */
	double* getActivation() const;

	/**
	 * ��ȡ��Ԫ��Ĵ����ݶ�����
	 * @return �����ݶ������ָ��
	 */
	double* getError() const;

};
