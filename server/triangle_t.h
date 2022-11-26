//
// Created by Nataliia Gurova on 26.11.2022.
//

#ifndef C_VERSION_TRIANGLE_T_H
#define C_VERSION_TRIANGLE_T_H

#include "color_t.h"
#include "vertex_t.h"

typedef struct {
    vertex_t initial_vertexes[3];
    vertex_t processed_vertexes[3];
    vertex_t perpendicular;
    vertex_t center;
    color_t initial_color;
    color_t processed_color;
    int id; // unused
} triangle_t;

triangle_t *allocate_triangle_t();
void print_triangle_t(triangle_t *src);
void free_triangle_t(triangle_t *src);

int ind_of_max_of_axis(triangle_t *triangle, int axis);
int ind_of_min_of_axis(triangle_t *triangle, int axis);
int ind_of_mid_of_axis(triangle_t *triangle, int axis);
int count_value_with_axis(triangle_t *triangle, int axis, int value);
int index_with_axis(triangle_t *triangle, int axis, int value);

void set_vertex_by_index(triangle_t *triangle, int ind, int x, int y, int z);
void set_color(triangle_t *triangle, color_t *color);
void set_perpendicular(triangle_t *triangle, int x, int y, int z);
void predict_perpendicular(triangle_t *triangle);
void calculate_center(triangle_t *triangle);

void reset_processed_vertexes(triangle_t *triangle);
void reset_processed_color(triangle_t *triangle);
void push(triangle_t *triangle, int dx, int dy, int dz);
void scale(triangle_t *triangle, vertex_t center, double dx, double dy, double dz);
void rotate(triangle_t *triangle, vertex_t center, double dx, double dy, double dz);

#endif //C_VERSION_TRIANGLE_T_H
