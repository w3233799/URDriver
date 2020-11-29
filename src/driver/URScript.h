//
// Created by li on 2020/11/30.
//

#ifndef URDRIVER_LI_URSCRIPT_H
#define URDRIVER_LI_URSCRIPT_H
#include <QString>

class URScript {

public:
    URScript();
    ~URScript();
    QString loadMovejScript(double *joints, double a, double v);

    QString loadMovelScript(double *poses, double a, double v);
};


#endif //URDRIVER_LI_URSCRIPT_H
