//
// Created by Nataliia Gurova on 26.11.2022.
//

#ifndef C_VERSION_SHADING_H
#define C_VERSION_SHADING_H

#define EPS 1e-3

#include <vector>
#include "triangle_t.h"
#include "light_source.h"

void linear_shading(triangle_t *triangle, std::vector<light_source_t*> &light_sources);

#endif //C_VERSION_SHADING_H
