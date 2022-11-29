//
// Created by Nataliia Gurova on 27.11.2022.
//

#include <cstdlib>
#include "light_source.h"

light_source_t *allocate_light_source_t() {
    auto res = (light_source_t*) malloc(sizeof(light_source_t));

    return res;
}

void free_light_source_t(light_source_t* ls) {
    free(ls);
}

light_source_t *create_light_source_t(double x, double y, double z) {
    auto res = allocate_light_source_t();

    res->vertex[0] = x;
    res->vertex[1] = y;
    res->vertex[2] = z;

    return res;
}
