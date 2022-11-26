//
// Created by Nataliia Gurova on 26.11.2022.
//

#ifndef C_VERSION_TRIANGLE_VECTOR_H
#define C_VERSION_TRIANGLE_VECTOR_H

#include "triangle_vector.h"
#include "triangle_t.h"

void group_reset_processed_vertexes(std::vector<triangle_t*> triangles);
void group_reset_processed_color(std::vector<triangle_t*> triangles);
void group_center(std::vector<triangle_t*> triangles, vertex_t center);
void group_push(std::vector<triangle_t*> triangles, int dx, int dy, int dz);
void group_scale(std::vector<triangle_t*> triangles, vertex_t center, double dx, double dy, double dz);
void group_rotate(std::vector<triangle_t*> triangles, vertex_t center, double dx, double dy, double dz);

#endif //C_VERSION_TRIANGLE_VECTOR_H
