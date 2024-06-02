#pragma once
#include<vector>

/**
 * @brief 神经元类
 *
 * 该类代表一个神经网络中的神经元，包括其激活值、误差值、权重和动量。
 * 支持神经元的重置、移动构造函数和析构函数等功能。
 */
class Neuron
{
public:
    /// 每个神经元接收的输入数量
    int numInputPerNerous;

    /// 当前神经元的激活值
    double activation = 0;

    /// 当前神经元的误差值
    double error = 0;

    /// 神经元的权重指针
    double* weight;

    /// 神经元的动量指针
    double* momentum;

    /**
     * @brief 重置神经元的状态
     *
     * 该函数用于重置神经元的激活值、误差值、权重和动量到初始状态。
     */
    void reset();

    /**
     * @brief 移动构造函数
     *
     * 通过移动语义构造一个神经元对象，接管来自另一个神经元对象的资源。
     * @param n 被移动的神经元对象
     */
    Neuron(Neuron&& n) noexcept;

    /**
     * @brief 显式构造函数
     *
     * 通过指定神经元接收的输入数量来构造神经元对象，并初始化权重和动量数组。
     * @param numInputPerNeuron 每个神经元接收的输入数量
     */
    explicit Neuron(int numInputPerNeuron);

    /// 析构函数
    ~Neuron();
};
