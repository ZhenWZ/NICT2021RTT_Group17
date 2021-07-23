# 基于ART-Pi和RT-Thread的智能门禁检测助手

# 1. 项目说明
口罩识别二分类模型，识别图片中的人是否佩戴口罩。
基于神经网络实现口罩识别。
模型训练完成后，使用RT-AK框架，将模型一键部署到RT-Thread系统中。

# 2. 元件
- Art-Pi 开发板
- 多媒体拓展板

# 3. 训练Model

## 3.1 环境
- Tensorflow==2.4.0
- OpenCV-Python==4.5.1
- matplotlib==3.3.3

## 3.2 数据集
- Face Mask Lite Dataset, <https://www.kaggle.com/prasoonkottarathil/face-mask-lite-dataset>
- COVID Face Mask Detection Dataset, <https://www.kaggle.com/prithwirajmitra/covid-face-mask-detection-dataset>
- With/Without Mask, <https://www.kaggle.com/niharika41298/withwithout-mask>
- Face Mask Detection, <https://www.kaggle.com/andrewmvd/face-mask-detection>
- Face Mask Detection ~12K Images Dataset, <https://www.kaggle.com/ashishjangra27/face-mask-12k-images-dataset>

## 3.3 网络结构

- 两层卷积 + 一层全连接

![model](https://user-images.githubusercontent.com/48997918/126664710-692b93d4-696b-4bf1-98d8-d134d9d4f42c.png)


## 3.4 训练模型 & 验证模型

- 训练模型

![training](https://user-images.githubusercontent.com/48997918/126664723-b9e23965-ee89-411a-853a-e34bb0b62929.png)


- 验证训练模型的准确率

![evaluate](https://user-images.githubusercontent.com/48997918/126664763-96c984d4-bd6e-4ced-9597-06ab6552f4ac.png)


# 4. 运行结果


## 感谢名单
- Derekduke
- lebhoryi
