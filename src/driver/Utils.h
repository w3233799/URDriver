//
// Created by li on 2020/11/30.
//

#ifndef URDRIVER_LI_UTILS_H
#define URDRIVER_LI_UTILS_H

#include "data.h"
#include <QDebug>
void reverseByte(char *p,int size);

//判断是否足够接近
bool isClosed(URData &urData, Instruction &targetIns);
//判断距离
double errorDistance(MOVETYPE type,double *targetData,double *curData);
#endif //URDRIVER_LI_UTILS_H
