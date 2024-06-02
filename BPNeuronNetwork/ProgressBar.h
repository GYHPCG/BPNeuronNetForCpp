#pragma once
#include<queue>
#include<thread>
#include<string>
#include<mutex>

/* 进度条类，用于在终端显示进度 */
class ProgressBar
{
public:
	/* 最大进度值 */
	int max;
	/* 当前进度值 */
	int curProgress = 0;
	/* 用于临时存储进度值的队列 */
	int currentValue = 0;
	std::queue<int> upgradeQueue;
	/* 控制线程是否停止的标志 */
	bool stopThread = false;
	/* 进度线程对象 */
	std::thread * printThread{};
	/* 互斥锁，用于线程安全的操作 */
	std::mutex mtx;

	/* 更新进度值 */
	void updateValue(int value);

	/* 构造函数，初始化最大进度和进度条标签 */
	ProgressBar(int max, const std::string& label);

	/* 构造函数，初始化最大进度 */
	explicit ProgressBar(int max);

	/* 自增操作符重载，用于递增进度 */
	ProgressBar& operator++();

	/* 加法操作符重载，用于增加最大进度 */
	ProgressBar& operator+=(int max);

	/* 显示进度条 */
	void show();

	/* 停止进度线程 */
	void shutDown();

	/* 重置进度条，设置新的最大进度和标签 */
	void reset(int max, const std::string& label);

	/* 析构函数，用于资源释放和线程的停止 */
	~ProgressBar();


	/* 进度线程函数，用于更新和显示进度 */
	static void* progressThread(void *__this);
};
