#pragma once
#include<cstdlib>

/**
 * 生成一个介于-0.5到0.5之间的随机小数。
 *
 * @return 一个double类型随机数，范围在-0.5到0.5之间。
 */
inline double randomClamped() {
	return rand() % 1000 * 0.001 - 0.5;
}

/**
 * 生成一个0到1之间的随机小数。
 *
 * @return 一个double类型随机数，范围在0到1之间。
 */
inline double randomFloat() {
	return rand() / (RAND_MAX + 1.0);
}

/**
 * 安全删除指针所指向的数组。
 * 该函数确保在删除数组之前，类型T必须是完全定义的。
 * 这是一个模板函数，适用于任何类型T的指针。
 *
 * @param x 待删除的数组的指针。
 */
template<typename T>
void _delete(T *x) {
	// 使用类型大小来验证类型T是否是完全定义的
	typedef char type_must_be_complete[sizeof(T) ? 1 : -1];
	// 确保上述类型的大小被计算，以避免编译器优化
	(void)sizeof(type_must_be_complete);
	delete[] x;
}
