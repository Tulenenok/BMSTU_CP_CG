//
// Created by Nataliia Gurova on 27.11.2022.
//

#ifndef C_VERSION_PARAMS_T_H
#define C_VERSION_PARAMS_T_H

#include <map>
#include <string>

typedef struct {
    int x;
    int y;
    int z;
    float alpha;
    float delta;
    float step;
    std::string axiom;
    int count_rules;
    std::map<std::string, std::string> rules;
    int n;
} params_t;

params_t *init_params(int x, int y, int z, float alpha, float delta, float step,
                      std::string axiom, std::map<std::string, std::string> rules, int n);

//void init_rules(std::vector<std::string> from, std::vector<std::string> to);

//void print_params(params_t *params);

void free_params(params_t *params);

#endif //C_VERSION_PARAMS_T_H
