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
};


#endif //URDRIVERCPP_URDRIVER_H