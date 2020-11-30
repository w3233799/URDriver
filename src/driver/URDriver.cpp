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
        if(disConnectCallBack==NULL)return;
        this->disConnectCallBack();
    });
//绑定接收解析数据 解析成URdata的数据结构
    QObject::connect(&socket, &QTcpSocket::readyRead, [this] {
        //读取机械臂返回的消息
        QByteArray data = socket.readAll();
        //URData数据
        URData urData;
        //解析机械臂返回的数据  解析成结构体URData
        parseRobotData(data,urData);
        //判断是否需要执行一条新的指令
        decideExcuteNextInstruction(urData);
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
    //判断当前状态
//    if(Program_state==2){
//        return;
//    }
//    //拼接脚本字符串
//    QString data = urScript.loadMovejScript(joints,a,v);
//    qDebug()<<"发送指令:"<<data<<endl;
//    //发送给机器人上位机
//    socket.write(data.toUtf8());
    //构建指令
    Instruction instruction;
    instruction.type = MOVETYPE::MOVEJ;
    memcpy(instruction.data,joints,6*sizeof(double ));
    instruction.a = a;
    instruction.v = v;
    //添加一条指令
    instructionQueue.push(instruction);
}

void URDriver::movel(double *poses, double a, double v) {
    //判断状态
//    if(Program_state==2){
//        return;
//    }
    //拼接脚本字符串
//    QString data = urScript.loadMovelScript(pose,a,v);
//    qDebug()<<"发送指令:"<<data<<endl;
//    //发送给机器人上位机
//    socket.write(data.toUtf8());
    //构建指令
    Instruction instruction;
    instruction.type = MOVETYPE::MOVEL;
    memcpy(instruction.data,poses,6*sizeof(double ));
    instruction.a = a;
    instruction.v = v;
    //添加一条指令
    instructionQueue.push(instruction);
}

void URDriver::parseRobotData(QByteArray &data, URData &urData) {
    //定义字节数组 拷贝data数据到字节数组中
    char newData[data.size()];
    // 将原数据拷贝到字节数组中
    memcpy(newData, data.data(), data.size());
    // 解析数据之前需要将数据的地址位交换,显示前四个size字节地址位交换
    reverseByte(newData, 4);
    //解析msgSize 拷贝前4字节到结构体
    memcpy(((char*)(&urData)),newData,4);
    //从第5个字节开始  每8个字节交换 ox12+1108-8  1100
    for (char* p= newData+4; p < newData+data.size()-8; p+=8) {
        reverseByte(p, 8);
    }
    //拷贝到结构体中double 0x01 + 1 0x09 sizeof()
    memcpy(((char*)(&urData))+8,newData+4,data.size()-4);
}

void URDriver::decideExcuteNextInstruction(URData &urData) {
    //如果第一次  直接执行
    if(isFirst){
        //执行指令
        excuteNextInstruction();
        return;
    }
    //如果不是第一次 需要判断是否接近目标
    if(isClosed(urData,targetInstruction)) {
        excuteNextInstruction();
    }
}

void URDriver::excuteNextInstruction() {
    //是否有指令
    if(instructionQueue.empty()){
        return;
    }
    //取出队列中第一个指令
    Instruction instruction = instructionQueue.front();
    //组合脚本
    QString data;
    if(instruction.type==MOVETYPE::MOVEJ){
        data = urScript.loadMovejScript(instruction.data,instruction.a,instruction.v);
    }else if(instruction.type==MOVETYPE::MOVEL){
        data = urScript.loadMovelScript(instruction.data,instruction.a,instruction.v);
    }
    //socket发送
    socket.write(data.toUtf8());
    //更新目标
    updateTargetInstruction(instruction);
    //删除
    instructionQueue.pop();
    //改变标记
    isFirst = false;
}

void URDriver::updateTargetInstruction(Instruction &instruction) {
    targetInstruction.type = instruction.type;
    memcpy(targetInstruction.data,instruction.data,6*sizeof(double));
    targetInstruction.a = instruction.a;
    targetInstruction.v = instruction.v;
}