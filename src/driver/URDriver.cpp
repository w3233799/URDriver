//
// Created by wt on 2020/11/29.
//

#include "URDriver.h"

//初始化静态属性
shared_ptr<URDriver> URDriver::instance = shared_ptr<URDriver>(new URDriver);


URDriver::URDriver() {
    //设置函数指针为空
    connectCallBack=NULL;
//绑定连接信号
    QObject::connect(&socket,&QTcpSocket::connected,[this]{
        if(connectCallBack==NULL)return ;
        this->connectCallBack();
    });
//绑定断开连接信号
    QObject::connect(&socket,&QTcpSocket::disconnected,[this]{
        this->disConnectCallBack();
    });

}

URDriver::~URDriver() {
    cout<<"析构函数"<<endl;
}


shared_ptr<URDriver>URDriver::getInstance() {
    return instance;
}

void URDriver::connectToRobot(QString ip, int port) {
    socket.connectToHost(ip,port);
}

void URDriver::setconnectCallBack(function<void ()>  connectCallBack) {
    this->connectCallBack=connectCallBack;
}

void URDriver::disConnectToRobot() {
    socket.disconnectFromHost();
}

void URDriver::setdisConnectCallBack(function<void()> disConnectCallBack) {
    this->disConnectCallBack=disConnectCallBack;
}
