#pragma once
#include<queue>
#include<thread>
#include<string>
#include<mutex>

/* �������࣬�������ն���ʾ���� */
class ProgressBar
{
public:
	/* ������ֵ */
	int max;
	/* ��ǰ����ֵ */
	int curProgress = 0;
	/* ������ʱ�洢����ֵ�Ķ��� */
	int currentValue = 0;
	std::queue<int> upgradeQueue;
	/* �����߳��Ƿ�ֹͣ�ı�־ */
	bool stopThread = false;
	/* �����̶߳��� */
	std::thread * printThread{};
	/* �������������̰߳�ȫ�Ĳ��� */
	std::mutex mtx;

	/* ���½���ֵ */
	void updateValue(int value);

	/* ���캯������ʼ�������Ⱥͽ�������ǩ */
	ProgressBar(int max, const std::string& label);

	/* ���캯������ʼ�������� */
	explicit ProgressBar(int max);

	/* �������������أ����ڵ������� */
	ProgressBar& operator++();

	/* �ӷ����������أ��������������� */
	ProgressBar& operator+=(int max);

	/* ��ʾ������ */
	void show();

	/* ֹͣ�����߳� */
	void shutDown();

	/* ���ý������������µ������Ⱥͱ�ǩ */
	void reset(int max, const std::string& label);

	/* ����������������Դ�ͷź��̵߳�ֹͣ */
	~ProgressBar();


	/* �����̺߳��������ڸ��º���ʾ���� */
	static void* progressThread(void *__this);
};
