//
// Created by Nataliia Gurova on 27.11.2022.
//

#include "params_t.h"
#include <utility>
#include <stdio.h>
#include <iostream>
#include <vector>

params_t *init_params(int x, int y, int z, float alpha, float delta, float step,
                      std::string axiom, std::map<std::string, std::string> rules, int n)
{
    auto *params = (params_t *)calloc(1, sizeof(params_t));

    params->x = x;
    params->y = y;
    params->z = z;
    params->alpha = alpha;
    params->delta = delta;
    params->step = step;
    params->axiom = std::move(axiom);
    params->rules = std::move(rules);
    params->n = n;

    return params;
}


//void init_rules(std::vector<std::string> from, std::vector<std::string> to) {
//    std::cout << 1;
//}

//void print_params(params_t *params){
//    printf("x = %d, y = %d, z = %d, alpha = %f, delta = %f\n",
//           params->x, params->y, params->z, params->alpha, params->delta);
//    std::cout << "Axiom = " << params->axiom << "\n";
//
//    auto it = (params->rules).begin();
//    for (int i = 0; it != params->rules.end(); it++, i++) {
//        std::cout << i << ") Ключ " << it->first << ", значение " << it->second << std::endl;
//    }
//
//    std::cout << "N = " << params->n;
//
//}

void free_params(params_t *params)
{
    free(params);
}
