//
// Created by Ilya Malyshev on 29.11.2022.
//

#ifndef C_VERSION_TRIANGLE_PRISM_H
#define C_VERSION_TRIANGLE_PRISM_H

#include <vector>
#include "../../server/triangle_t.h"

void add_cube(std::vector<triangle_t*>& triangles, double x, int y, int z, int a, color_t *color);

#endif //C_VERSION_TRIANGLE_PRISM_H
