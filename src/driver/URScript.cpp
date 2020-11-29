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

QString URScript::loadMovelScript(double *poses, double a, double v) {
//Example command: movel(p[0.2,0.3,0.5,0,0,3.14],a=1.2, v=0.25, t=0, r=0)
    QString data = "movel(p[";
    for (int i = 0; i < 6; ++i) {
        data += QString::number(poses[i]);
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
