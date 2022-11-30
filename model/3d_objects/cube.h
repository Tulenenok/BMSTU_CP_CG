//
// Created by Nataliia Gurova on 27.11.2022.
//

#ifndef C_VERSION_CUBE_H
#define C_VERSION_CUBE_H

#include <vector>
#include "../../server/triangle_t.h"

typedef struct
{
    int x;
    int y;
    int z;
    int a;
    color_t color;
} cube_t;

void add_cube(std::vector<triangle_t*>& triangles, int x, int y, int z, int a, color_t *color);

void add_cube_use_struct(std::vector<triangle_t*>& triangles, cube_t cube);

#endif //C_VERSION_CUBE_H
