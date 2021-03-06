//
// Created by wt on 2020/11/29.
//

#ifndef URDRIVERCPP_URDRIVER_H
#define URDRIVERCPP_URDRIVER_H

#include <iostream>
#include <QString>
#include <QTcpSocket>
#include <memory>
#include <functional>
#include <QDebug>
#include <URScript.h>
#include "data.h"
#include "Utils.h"
#include <queue>
using namespace std;

class URDriver {
private:
    //1.私有化构造方法
    URDriver();

    URDriver(const URDriver &);

    URDriver operator=(const URDriver &);

    //2.静态变量保存当前对象实例
    static shared_ptr<URDriver> instance;

    //QTCPScoket实例
    QTcpSocket socket;

    // 接收连接函数的对象
    function<void ()>  connectCallBack;// 函数指针

    // 接收断开连接函数的对象
    function<void ()>  disConnectCallBack;// 函数指针

    // 字符串拼接的工具类创建对象
    URScript urScript;

    //保存当前状态
//    double Program_state=0;
    //保存指令队列
    queue<Instruction> instructionQueue;
    //目标指令
    Instruction targetInstruction;
    //是否第一次
    bool isFirst = true;


public:

    ~URDriver();

    //3.公有方法获取对象实例
    static shared_ptr<URDriver> getInstance();

    //连接机械臂
    void connectToRobot(QString ip, int port);

    //断开连接机械臂
    void disConnectToRobot();

    //接收连接状态的回调函数
    void setconnectCallBack(function<void ()>  connectCallBack);

    //接收断开连接状态的回调函数
    void setdisConnectCallBack(function<void ()>  disConnectCallBack);

    //movej移动
    void movej(double *joints,double a=1.2,double v=1.05);

    //movel移动
    void movel(double *poses,double a=1.25,double v=0.25);

    void parseRobotData(QByteArray &data, URData &urData);

    //决定是否执行下一条指令
    void decideExcuteNextInstruction(URData &urData);
    //执行指令
    void excuteNextInstruction();
    //更新指令
    void updateTargetInstruction(Instruction &instruction);
};


#endif //URDRIVERCPP_URDRIVER_H