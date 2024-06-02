#pragma once
#include<vector>

/**
 * @brief ��Ԫ��
 *
 * �������һ���������е���Ԫ�������伤��ֵ�����ֵ��Ȩ�غͶ�����
 * ֧����Ԫ�����á��ƶ����캯�������������ȹ��ܡ�
 */
class Neuron
{
public:
    /// ÿ����Ԫ���յ���������
    int numInputPerNerous;

    /// ��ǰ��Ԫ�ļ���ֵ
    double activation = 0;

    /// ��ǰ��Ԫ�����ֵ
    double error = 0;

    /// ��Ԫ��Ȩ��ָ��
    double* weight;

    /// ��Ԫ�Ķ���ָ��
    double* momentum;

    /**
     * @brief ������Ԫ��״̬
     *
     * �ú�������������Ԫ�ļ���ֵ�����ֵ��Ȩ�غͶ�������ʼ״̬��
     */
    void reset();

    /**
     * @brief �ƶ����캯��
     *
     * ͨ���ƶ����幹��һ����Ԫ���󣬽ӹ�������һ����Ԫ�������Դ��
     * @param n ���ƶ�����Ԫ����
     */
    Neuron(Neuron&& n) noexcept;

    /**
     * @brief ��ʽ���캯��
     *
     * ͨ��ָ����Ԫ���յ�����������������Ԫ���󣬲���ʼ��Ȩ�غͶ������顣
     * @param numInputPerNeuron ÿ����Ԫ���յ���������
     */
    explicit Neuron(int numInputPerNeuron);

    /// ��������
    ~Neuron();
};
