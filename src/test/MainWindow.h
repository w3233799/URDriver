//
// Created by wt on 2020/11/29.
//

#ifndef URDRIVERCPP_MAINWINDOW_H
#define URDRIVERCPP_MAINWINDOW_H

#include <math.h>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QFormLayout>
#include <QWidget>
#include "URDriver.h"

class MainWindow : public QWidget {
    //角度转弧度
    double DEGREETORADIUS = M_PI / 180;
    //ip输入框
    QLineEdit *ipEdit;
    //端口输入框
    QLineEdit *portEdit;

    //连接状态
    QLabel *statusLabel;

    //连接机械臂按钮
    QPushButton *connectBtn;
    QPushButton *disConnectBtn;

    //movej的每一个关节输入
    QLineEdit *joint1Edit;
    QLineEdit *joint2Edit;
    QLineEdit *joint3Edit;
    QLineEdit *joint4Edit;
    QLineEdit *joint5Edit;
    QLineEdit *joint6Edit;

    //movej
    QPushButton *movejBtn;

    //movel输入
    QLineEdit *xEdit;
    QLineEdit *yEdit;
    QLineEdit *zEdit;
    QLineEdit *rxEdit;
    QLineEdit *ryEdit;
    QLineEdit *rzEdit;

    //movel
    QPushButton *movelBtn;
public:
    MainWindow(QWidget *parent = Q_NULLPTR);

    ~MainWindow();

    //初始化ui界面
    void initUI();

    //设置机器人连接状态的回调函数
    void setCallBack();

    //处理信号和槽函数
    void signalAndSlot();

    // movej函数
    void movej();

    // movel函数
    void movel();

};


#endif //URDRIVERCPP_MAINWINDOW_H