//
// Created by li on 2020/11/30.
//

#include "Utils.h"
#include <math.h>
#include <memory.h>

void reverseByte(char *p, int size) {
    if (size == 4) {
        //0001
        char tmp = p[0];//*p
        p[0] = p[3];//*(p+3)
        p[3] = tmp;

        tmp = p[1];
        p[1] = p[2];
        p[2] = tmp;
    } else if (size == 8) {
        //10000000
        char tmp = p[0];
        p[0] = p[7];
        p[7] = tmp;


        tmp = p[1];
        p[1] = p[6];
        p[6] = tmp;

        tmp = p[2];
        p[2] = p[5];
        p[5] = tmp;

        tmp = p[3];
        p[3] = p[4];
        p[4] = tmp;
    }
}

bool isClosed(URData &urData, Instruction &targetIns) {
    //保存当前数据
    double curData[6];
    //目标数据
    double targetData[6];
    memcpy(targetData, targetIns.data, 6 * sizeof(double));
    //获取移动类型
    MOVETYPE type = targetIns.type;
    //判断类型
    if (type == MOVETYPE::MOVEJ) {
        memcpy(curData, urData.q_actual, 6 * sizeof(double));
    } else if (type == MOVETYPE::MOVEL) {
        memcpy(curData, urData.Tool_vector_actual, 6 * sizeof(double));
    }
    //误差
    double result = errorDistance(type, targetData, curData);
    qDebug()<<"误差:"<<result<<endl;
    return result < 0.07;
}

//x y z rx ry rz 3.14  -3.14
double errorDistance(MOVETYPE type, double *targetData, double *curData) {
    double result = 0;
    if (type == MOVETYPE::MOVEL) {
        for (int i = 0; i < 6; ++i) {
            if (i >= 3) {
                result += pow((abs(curData[i]) - abs(targetData[i]))/5.0, 2);
            } else {
                result += pow(curData[i] - targetData[i], 2);
            }
        }
    } else if (type == MOVETYPE::MOVEJ) {
        for (int i = 0; i < 6; ++i) {
            result += pow(curData[i] - targetData[i], 2);
        }
    }

    result = sqrt(result);
    return result;
}