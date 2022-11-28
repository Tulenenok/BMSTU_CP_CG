//
// Created by Nataliia Gurova on 27.11.2022.
//
#include "Params.h"
#include <iostream>
#include <utility>

Params::Params(int _x, int _y, int _z, float _alpha, float _delta, float _step, std::string _axiom, Rules &_rules, int _n)
{
    this->p[0] = _x;
    this->p[1] = _y;
    this->p[2] = _z;

    this->alpha = _alpha;
    this->delta = _delta;
    this->step = _step;
    this->axiom = std::move(_axiom);
    this->rules = _rules;
    this->n = _n;
}

void Params::print() {
    std::cout << "\n";
    std::cout << "N = " << this->n << "\n";
    std::cout << "X = " << this->p[0] << "\n";
    std::cout << "Y = " << this->p[1] << "\n";
    std::cout << "Z = " << this->p[2] << "\n";
    std::cout << "Step = " << this->step << "\n";

    std::cout << "Alpha = " << this->alpha << "\n";
    std::cout << "Delta = " << this->delta << "\n";
    std::cout << "Axiom = " << this->axiom << "\n";

    this->rules.print();
}

std::string Params::calculate()
{
    std::string result_str = this->axiom;
    for (int i = 0; i < n; ++i)
    {
        std::string tmp_str;
        for (char sym : result_str)
        {
            if (rules.data.count(sym) == 1)
                tmp_str += rules.data.at(sym);
            else
                tmp_str += sym;
        }

        result_str = tmp_str;
    }
    return result_str;
}


//Params get_params_from_file(char *filename)
//{
//    std::cout << "get";
//}