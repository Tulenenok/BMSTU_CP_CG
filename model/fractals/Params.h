//
// Created by Nataliia Gurova on 27.11.2022.
//

#ifndef C_VERSION_PARAMS_H
#define C_VERSION_PARAMS_H

#include <map>
#include <vector>
#include <string>

#include "Rules.h"
#include "../../server/vertex_t.h"

typedef std::vector<std::vector<double>> mat_t;

class Params
{
public:
    Params() {};
    Params(int _x, int _y, int _z, float _alpha, float _delta, float _step, std::string _axiom, Rules &_rules, int _n);
    void print();
    void print_hlu();

    std::string calculate();  // рассчет итоговой формулы фрактала

    int n;
    vertex_t p;
    float alpha;
    float delta;
    float step;
    std::string axiom;
    Rules rules;

    std::vector<char> consts;

    mat_t HLU = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
};

//Params get_params_from_file(char *filename);

#endif //C_VERSION_PARAMS_H
