#include"pch.h"
#include"BPNeuronNet.h"

// Sigmoid激活函数，用于神经元的激活值计算
// activation: 输入值
// response: 激活函数的响应调整因子
double BPNeuronNet::sigmoidActive(const double activation, const double response) {
	return 1.0 / (1.0 + exp(-activation * response));
}

// Hyperbolic tangent激活函数，用于神经元的激活值计算
// activation: 输入值
double tanhActive(const double activation) {
	return (exp(activation) - exp(-activation)) / (exp(activation) + exp(-activation));
}

// ReLU激活函数，用于神经元的激活值计算
// activation: 输入值
double reluActive(const double activation) {
	return std::max(0.0, activation);
}

// Hyperbolic tangent激活函数的导数，用于反向传播计算
// x: 输入值
double tanhbackactive(const double x) {
	return 1 - pow(tanhActive(x), 2);
}

// ReLU激活函数的导数，用于反向传播计算
// x: 输入值
double reluBackActive(const double x) {
	if (x > 0)
		return 1;
	else if (x <= 0);
		return 0;
}

// Sigmoid激活函数的导数，用于反向传播计算
// x: 输入值
// response: 激活函数的响应调整因子
double BPNeuronNet::backActive(const double x,const double response) {
	return sigmoidActive(x, response)*sigmoidActive(1 - x, response);
}

// 更新神经层的神经元，根据输入值计算激活值
// nl: 待更新的神经层
// inputs: 输入值数组
void BPNeuronNet::updateNeuronLayer(NeuronLayer& nl, const double inputs[])const {
	const int numNerous = nl.size;
	const int numInputPerNerous = nl.inputPerNeuron;

	for (int i = 0; i < numNerous; i++) {
		double* curWeight = nl.neurons[i].weight;
		double netInput = 0;

		int k;
		for (k = 0; k < numInputPerNerous; k++) {
			netInput += curWeight[k] * inputs[k];
		}
		netInput += curWeight[k];
		nl.neurons[i].activation = sigmoidActive(netInput, ACTIVE_RESPONSE);
		//nl.neurons[i].activation = reluActive(netInput);
		//nl.neurons[i].activation = tanhActive(netInput);
	}
}

// 训练神经层，更新权重和动量
// nl: 待训练的神经层
// preActivations: 前一神经层的激活值
// preErrorArr: 前一神经层的误差数组
void BPNeuronNet::trainNeuronLayer(NeuronLayer& nl, const double preActivations[], double preErrorArr[])const {
	// 获取当前神经层的信息
	const int numNeurous = nl.size;
	const int numInputPerNeurous = nl.inputPerNeuron;
	Neuron* neuronArr = nl.neurons;
	// 遍历所有神经元
	for (int i = 0; i < numNeurous; i++) {
		// 更新前一层的误差和当前神经元的权重及动量：
		// 获取当前神经元的权重数组。
		// 计算当前神经元的误差，误差值通过激活函数的导数调整。
		double* curWeight = neuronArr[i].weight;
		const double error = neuronArr[i].error * backActive(neuronArr[i].activation,ACTIVE_RESPONSE);
		//const double error = neuronArr[i].error*reluBackActive(neuronArr[i].activation);
		//const double error = neuronArr[i].error*tanhbackactive(neuronArr[i].activation);
		//更新前一层的误差和当前神经元的权重及动量：
		int j;
		for (j = 0; j < numInputPerNeurous; j++) {
			if (preErrorArr) {
				preErrorArr[j] += curWeight[j] * error;
			}
			neuronArr[i].momentum[j] = 0.2*neuronArr[i].momentum[j] + error * learningRate * preActivations[j];//���¶���
			neuronArr[i].weight[j] += neuronArr[i].momentum[j];
		}
		neuronArr[i].weight[j] += error * learningRate;
	}
}

// 根据输入和目标值进行神经网络的前向传播和误差计算
// inputs: 输入值数组
// targets: 目标值数组
void BPNeuronNet::trainUpdate(const double inputs[], const double targets[]) {
	//前向传播：
	// 使用 updateNeuronLayer 函数更新每一层的神经元激活值。
	// 将当前层的激活值作为下一层的输入。
	for (int i = 0; i <= numHiddenLayer; i++) {
		updateNeuronLayer(neuronLayers[i], inputs);
		inputs = neuronLayers[i].getActivation();
	}
	// 获取输出层：
	NeuronLayer& outLayer = neuronLayers[numHiddenLayer];
	double * outActivation = outLayer.getActivation();
	const int numNeurons = outLayer.size; 
	//误差计算：初始化误差累积和 errorSum。
	//遍历输出层的所有神经元，计算每个神经元的误差（目标值减去实际输出值）。
	//	将误差存储在神经元的 error 属性中。
	//	计算误差的平方并累加到 errorSum。
	errorSum = 0;
	for (int i = 0; i < numNeurons; i++) {
		const double err = targets[i] - outActivation[i];
		outLayer.neurons[i].error = err;
		errorSum += err * err;
	}
}

// 获取神经网络的总误差
// 返回: 总误差值
double BPNeuronNet::getError()const {
	return errorSum;
}

// 进行一次完整的训练过程，包括前向传播和反向传播
// inputs: 输入值数组
// targets: 目标值数组
void BPNeuronNet::training(double inputs[], const double targets[]) {
	double * preOutActivations = nullptr; //前一次的激活
	double * preError = nullptr; //前一层的误差
	// 更新权重和偏置，前向传播
	trainUpdate(inputs, targets);
	// 反向传播
	for (int i = numHiddenLayer; i >= 0; i--) {
		// 当前层
		NeuronLayer& curLayer = neuronLayers[i];
		// 处理隐藏层和输入层
		//如果当前层不是输入层，则获取前一层的激活值和误差，并将前一层的误差数组清零。
		// 如果当前层是输入层，则将前一层的激活值指向输入数据，且没有前一层误差。
		if (i > 0) {
			NeuronLayer& preLayer = neuronLayers[i - 1];
			preOutActivations = preLayer.getActivation();
			preError = preLayer.getError();
			memset(preError, 0, preLayer.size * sizeof(double));
		}
		else {
			preOutActivations = inputs;
			preError = nullptr;
		}
		//使用前一层的激活值和误差训练当前层。更新当前层的权重和偏置。
		trainNeuronLayer(curLayer, preOutActivations, preError);
	}
}

// 使用训练好的神经网络进行预测
// inputs: 输入值数组
// outputs: 输出值数组的指针
void BPNeuronNet::predict(double inputs[], double* outputs[]) {
	for (int i = 0; i <= numHiddenLayer; i++) {
		updateNeuronLayer(neuronLayers[i], inputs);
		inputs = neuronLayers[i].getActivation();
	}
	*outputs = neuronLayers[numHiddenLayer].getActivation();
}

// 添加一个隐藏层到神经网络
// num: 隐藏层的神经元数量
void BPNeuronNet::addLayer(const int num) {
	int inputNum = !neuronLayers.empty() ? neuronLayers[numHiddenLayer].size : numInput;

	void * raw = operator new[](num * sizeof(Neuron));
	Neuron * neurons = static_cast<Neuron*>(raw);
	for (int i = 0; i < num; i++) {
		new (&neurons[i])Neuron(inputNum);
	}
	neuronLayers.emplace_back(inputNum, neurons, num);
	numHiddenLayer = neuronLayers.empty() ? 0 : neuronLayers.size() - 1;
}

// BPNeuronNet类的构造函数
// numberInput: 输入层的神经元数量
// learningRate: 学习率
BPNeuronNet::BPNeuronNet(const int numberInput, const double learningRate) :numInput(numberInput), numHiddenLayer(0), learningRate(learningRate) {

}

// BPNeuronNet类的析构函数
BPNeuronNet::~BPNeuronNet() = default;
