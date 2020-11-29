//
// Created by wt on 2020/11/29.
//

#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    //初始化界面
    initUI();
    // 连接状态的回调函数
    setCallBack();
    //处理信号和槽
    signalAndSlot();
}

MainWindow::~MainWindow() {

}

void MainWindow::initUI() {
    setFixedSize(600, 800);
    //布局
    QFormLayout *layout = new QFormLayout;
    //ip输入框
    ipEdit = new QLineEdit("192.168.0.102");
    //端口输入框
    portEdit = new QLineEdit("30003");

    //连接状态
    statusLabel = new QLabel("未连接");

    //连接机械臂按钮
    connectBtn = new QPushButton("连接机械臂");
    disConnectBtn = new QPushButton("断开连接");

    //movej的每一个关节输入
    joint1Edit = new QLineEdit("-144.98");
    joint2Edit = new QLineEdit("-97.67");
    joint3Edit = new QLineEdit("-102.98");
    joint4Edit = new QLineEdit("-68.95");
    joint5Edit = new QLineEdit("83.07");
    joint6Edit = new QLineEdit("58.15");

    //movej
    movejBtn = new QPushButton("moveJ");

    //movel输入
    xEdit = new QLineEdit("-54.16");
    yEdit = new QLineEdit("-324.52");
    zEdit = new QLineEdit("183.76");
    rxEdit = new QLineEdit("3.1225");
    ryEdit = new QLineEdit("0.5556");
    rzEdit = new QLineEdit("0.2693");

    //movel
    movelBtn = new QPushButton("moveL");

    //添加
    layout->addRow("ip", ipEdit);
    layout->addRow("port", portEdit);
    layout->addRow("连接状态", statusLabel);
    layout->addRow("", connectBtn);
    layout->addRow("", disConnectBtn);

    layout->addRow("关节1:", joint1Edit);
    layout->addRow("关节2:", joint2Edit);
    layout->addRow("关节3:", joint3Edit);
    layout->addRow("关节4:", joint4Edit);
    layout->addRow("关节5:", joint5Edit);
    layout->addRow("关节6:", joint6Edit);

    layout->addRow("", movejBtn);

    layout->addRow("x:", xEdit);
    layout->addRow("y:", yEdit);
    layout->addRow("z:", zEdit);
    layout->addRow("rx:", rxEdit);
    layout->addRow("ry:", ryEdit);
    layout->addRow("rz:", rzEdit);

    layout->addRow("", movelBtn);

    //设置布局
    setLayout(layout);
}

void MainWindow::signalAndSlot() {
//连接按钮
    connect(connectBtn, &QPushButton::clicked, [this]() {
        //获取ip和端口
        QString ip = ipEdit->text();
        int port = portEdit->text().toInt();
        //调用URDriver驱动连接机械臂
        URDriver::getInstance()->connectToRobot(ip, port);
        //
    });
//断开连接按钮
    connect(disConnectBtn, &QPushButton::clicked, [this]() {
        //调用URDriver驱动断开连接机械臂
        URDriver::getInstance()->disConnectToRobot();
    });

}

void MainWindow::setCallBack() {
// 创建URDriver的连接接收回调函数的实例
    URDriver::getInstance()->setconnectCallBack([this] {
         //cout << "回调函数被调用，说明已经连接上了！！" << endl;
        //更新状态信息
        statusLabel->setText("已连接");
    });
// 创建URDriver的断开连接接收回调函数的实例
    URDriver::getInstance()->setdisConnectCallBack([this] {
        cout << "已经断开连接了！！" << endl;
        //更新状态信息
        statusLabel->setText("未连接");
    });
}
