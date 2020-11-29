//
// Created by li on 2020/11/30.
//

#include "URScript.h"

URScript::~URScript() {

}

URScript::URScript() {

}

QString URScript::loadMovejScript(double *joints, double a, double v) {
    //Example command: movej([0,1.57,-1.57,3.14,-1.57,1.57],a=1.4, v=1.05, t=0, r=0)
    QString data = "movej([";
    for (int i = 0; i < 6; ++i) {
        data += QString::number(joints[i]);
        if (i < 5) {
            data += ",";
        }
    }
    data += "],a=";
    data += QString::number(a);
    data += ", v=";
    data += QString::number(v);
    data += ", t=0, r=0)";
    return data;
}