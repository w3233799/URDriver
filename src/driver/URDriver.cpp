//
// Created by wt on 2020/11/29.
//

#include "URDriver.h"

//初始化静态属性
shared_ptr<URDriver> URDriver::instance = shared_ptr<URDriver>(new URDriver);


URDriver::URDriver() {
    //设置函数指针为空
    connectCallBack = NULL;
//绑定连接信号
    QObject::connect(&socket, &QTcpSocket::connected, [this] {
        if (connectCallBack == NULL)return;
        this->connectCallBack();
    });
//绑定断开连接信号
    QObject::connect(&socket, &QTcpSocket::disconnected, [this] {
        this->disConnectCallBack();
    });

}

URDriver::~URDriver() {
    cout << "析构函数" << endl;
}


shared_ptr<URDriver> URDriver::getInstance() {
    return instance;
}

void URDriver::connectToRobot(QString ip, int port) {
    socket.connectToHost(ip, port);
}

void URDriver::setconnectCallBack(function<void()> connectCallBack) {
    this->connectCallBack = connectCallBack;
}

void URDriver::disConnectToRobot() {
    socket.disconnectFromHost();
}

void URDriver::setdisConnectCallBack(function<void()> disConnectCallBack) {
    this->disConnectCallBack = disConnectCallBack;
}

void URDriver::movej(double *joints, double a, double v) {
//    cout << "joints: ";
//    for (int i=0;i<6;++i) {
//        cout <<"   "<< joints[i];
//    }cout<<endl;
//   拼接字符串发给机械臂的上位机，这时采取创建一个拼接字符串的工具类，方便以后的更改
    QString data=urScript.loadMovejScript(joints, a, v);
    //通过socket发送给UR的上位机
    socket.write(data.toUtf8());
}

void URDriver::movel(double *poses, double a, double v) {
    cout << "joints: ";
    for (int i=0;i<6;++i) {
        cout <<"   "<< poses[i];
    }cout<<endl;
//   拼接字符串发给机械臂的上位机，这时采取创建一个拼接字符串的工具类，方便以后的更改
    QString data=urScript.loadMovelScript(poses, a, v);
    //通过socket发送给UR的上位机
    socket.write(data.toUtf8());
}
