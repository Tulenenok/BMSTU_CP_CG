//
// Created by Nataliia Gurova on 27.11.2022.
//
#include "Params.h"
#include <iostream>
#include <utility>

Params::Params(int _x, int _y, int _z, float _alpha, float _delta, float _step, std::string _axiom,
               Rules _rules, int _n, Rules rules) : rules(std::move(rules)) {
    this->x = _x;
    this->y = _y;
    this->z = _z;
    this->alpha = _alpha;
    this->delta = _delta;
    this->step = _step;
    this->axiom = std::move(_axiom);
    this->rules = std::move(_rules);
    this->n = _n;
}

void Params::print() {
    std::cout << "\n";
    std::cout << "N = " << this->n << "\n";
    std::cout << "X = " << this->x << "\n";
    std::cout << "Y = " << this->y << "\n";
    std::cout << "Z = " << this->z << "\n";

    std::cout << "Alpha = " << this->alpha << "\n";
    std::cout << "Delta = " << this->delta << "\n";
    std::cout << "Axiom = " << this->axiom << "\n";

    this->rules.print();
}

