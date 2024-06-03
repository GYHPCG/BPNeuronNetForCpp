# BPNeuronNetForCpp
## 项目介绍
这个项目是个人的贵州大学2024年春季机器学习课期末项目，主要实现了一个BP神经网络，并利用c++纯手写(没有调用任何机器学习库)从零开始实现了一个简单的BP神经网络，采用[MINIST](http://yann.lecun.com/exdb/mnist/) 数据集进行训练。然后对于训练得到的BP神经网络，采用OpenCV窗口用鼠标进行手写数字，然后预测出手写数字的结果。

## 项目结构
![Bp.drawio](https://cdn.jsdelivr.net/gh/GYHPCG/my_picgo/picture/Bp.drawio.png)

## 运行环境
- Visual Studio 2022
- OpenCV 4.5.5
- c++ version >= c++11  
在项目中使用的时候，首先需要下载OpenCV,然后需要将OpenCV的库文件添加到项目中，并且将OpenCV的库文件添加到链接器中等，具体看查看[VS2022永久配置OpenCV开发环境](https://blog.csdn.net/m0_47917394/article/details/122349918)。
1. 下载OpenCV
2. 将OpenCV的库文件添加到项目中
3. 将OpenCV的库文件添加到链接器中
4. 编译
5. 运行
## 运行结果
1. 训练结果
![image-20240603110002704](https://cdn.jsdelivr.net/gh/GYHPCG/my_picgo/picture/image-20240603110002704.png)
2. OpenCV窗口用鼠标进行手写数字，然后预测出手写数字的结果
![image-20240603110054092](https://cdn.jsdelivr.net/gh/GYHPCG/my_picgo/picture/image-20240603110054092.png)
