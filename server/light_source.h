//
// Created by Nataliia Gurova on 27.11.2022.
//

#ifndef C_VERSION_LIGHT_SOURCE_H
#define C_VERSION_LIGHT_SOURCE_H

#include "vertex_t.h"

typedef struct {
    vertex_t vertex;
} light_source_t;

light_source_t *allocate_light_source_t();
void free_light_source_t(light_source_t* ls);
light_source_t *create_light_source_t(int x, int y, int z);

#endif //C_VERSION_LIGHT_SOURCE_H
