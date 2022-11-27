//
// Created by Nataliia Gurova on 27.11.2022.
//

#ifndef C_VERSION_PARAMS_H
#define C_VERSION_PARAMS_H

#include <map>
#include <vector>
#include <string>

#include "Rules.h"

class Params
{
public:
    Params() {};
    Params(int _x, int _y, int _z, float _alpha, float _delta, float _step, std::string _axiom, Rules &_rules, int _n);
    void print();

    int n;
    int x;
    int y;
    int z;
    float alpha;
    float delta;
    float step;
    std::string axiom;
    Rules rules;
};


#endif //C_VERSION_PARAMS_H
