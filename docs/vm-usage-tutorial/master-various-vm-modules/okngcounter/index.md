---
sidebar_position: 9
---
# OK/NG计数方案搭建

import VideoPlayer from '@site/videoPlayer.js'

<VideoPlayer src="https://www.hikrobotics.com/cn2/source/support/video/OK%20NG%E8%AE%A1%E6%95%B0%E6%96%B9%E6%A1%88%E6%90%AD%E5%BB%BA%E6%95%99%E7%A8%8B.mp4"/>

## OKNG计数方案

![](image.png)

## 1. 添加图像源

## 2. 添加圆弧边缘缺陷检测

![](image-9.png)

1. 基本参数

自行绘制ROI,在图像上拖动小圆,圈住被测物

![](image-2.png)

2. 运行参数

    1. 边缘类型:选择最强
    2. 边缘极性:由黑到白

    ![](image-1.png)

    3. 缺陷距离阈值: 10

    ![](image-3.png)

3. 结果显示

为方便查看,文本显示内容设置为:检测结果:{}

![](image-4.png)

光标移动到{}中间,选择模块状态

![](image-5.png)

执行结果

![](image-6.png)

## 3. 添加条件检查工具

![](image-7.png)

点击条件检测工具

1. 基本参数

![](image-8.png)

判断方式设置为全部

添加变量

条件设为1,有效值设为1-1

点击执行

![](image-10.png)

## 4. 添加变量计算

![](image-11.png)

重命名为计数

1. 基本参数

    1. 添加两个变量用于统计检测数和OK数

    ![](image-12.png)

    2. 在表达式项打开计算器图标,分别设置n,OK
    点击链接选择计数的n变量,点击+,点击1
    
    ![](image-13.png)

    点击计数的OK+条件检测结果1的结果(INT)

    ![](image-14.png)

    3. 完成后保存执行,左上方会显示n和ok值

    ![](image-15.png)

## 5. 计算合格率

1. 再添加一个变量计算工具

2. 基本参数

![](image-16.png)

增加NG和Rate变量，NG表达式通过链接选择计数的n-计数的OK,Rate表达式通过链接选择计数的OK/计数的n*100

点击执行,查看到NG数和良率

![](image-17.png)

## 6. 界面设计

![](image-18.png)

打开后编辑界面

1. 拖动图像显示区为如下范围大小

![](image-19.png)

2. 配置图像数据源

![](image-20.png)

3. 配置图形配置

![](image-21.png)

4. 拖动OKNG位置

![](image-22.png)

5. 配置OKNG数据源

![](image-23.png)

6. 添加OK数,NG数,检测数,合格率的文本框

字体大小均设置为24,数据类型设置为int,选择对应数据源,合格率类型设置为float

![](image-24.png)

![](image-25.png)

## 7. 预览界面
点击预览

![](image-26.png)

点击运行按钮

![](image-27.png)

## 8. 重置计数

添加Btn按钮,触发命令类型设置为重置

![](image-28.png)

数据源设置为所有变量计算

![](image-29.png)

点击预览,运行,点击计数清零

![](image-30.png)

点击计数清零后,下次运行重新开始计数

![](image-31.png)








