//
// Created by Nataliia Gurova on 27.11.2022.
//

#include "cube.h"

#include "../../server/triangle_t.h"
#include "../../server/triangle_vector.h"


void add_cube(std::vector<triangle_t*>& triangles, int x, int y, int z, int a, color_t *color) {

//    Нижняя грань
    triangle_t *tr1 = allocate_triangle_t();
    set_vertex_by_index(tr1, 0, x - a, y - a, z - a);
    set_vertex_by_index(tr1, 1, x - a, y - a, z + a);
    set_vertex_by_index(tr1, 2, x + a, y - a, z - a);
    set_color(tr1, color);
    calculate_center(tr1);
    set_perpendicular(tr1, 0, -1, 0);
    group_add(triangles, tr1);

    triangle_t *tr2 = allocate_triangle_t();
    set_vertex_by_index(tr2, 0, x + a, y - a, z + a);
    set_vertex_by_index(tr2, 1, x - a, y - a, z + a);
    set_vertex_by_index(tr2, 2, x + a, y - a, z - a);
    set_color(tr2, color);
    calculate_center(tr2);
    set_perpendicular(tr2, 0, -1, 0);
    group_add(triangles, tr2);

//    Верхняя грань
    triangle_t *tr3 = allocate_triangle_t();
    set_vertex_by_index(tr3, 0, x - a, y + a, z - a);
    set_vertex_by_index(tr3, 1, x - a, y + a, z + a);
    set_vertex_by_index(tr3, 2, x + a, y + a, z - a);
    set_color(tr3, color);
    calculate_center(tr3);
    set_perpendicular(tr3, 0, 1, 0);
    group_add(triangles, tr3);

    triangle_t *tr4 = allocate_triangle_t();
    set_vertex_by_index(tr4, 0, x + a, y + a, z + a);
    set_vertex_by_index(tr4, 1, x - a, y + a, z + a);
    set_vertex_by_index(tr4, 2, x + a, y + a, z - a);
    set_color(tr4, color);
    calculate_center(tr4);
    set_perpendicular(tr4, 0, 1, 0);
    group_add(triangles, tr4);

//    Левая грань
    triangle_t *tr5 = allocate_triangle_t();
    set_vertex_by_index(tr5, 0, x - a, y - a, z - a);
    set_vertex_by_index(tr5, 1, x - a, y - a, z + a);
    set_vertex_by_index(tr5, 2, x - a, y + a, z - a);
    set_color(tr5, color);
    calculate_center(tr5);
    set_perpendicular(tr5, -1, 0, 0);
    group_add(triangles, tr5);

    triangle_t *tr6 = allocate_triangle_t();
    set_vertex_by_index(tr6, 0, x - a, y + a, z + a);
    set_vertex_by_index(tr6, 1, x - a, y - a, z + a);
    set_vertex_by_index(tr6, 2, x - a, y + a, z - a);
    set_color(tr6, color);
    calculate_center(tr6);
    set_perpendicular(tr6, -1, 0, 0);
    group_add(triangles, tr6);

//    Правая грань
    triangle_t *tr7 = allocate_triangle_t();
    set_vertex_by_index(tr7, 0, x + a, y - a, z - a);
    set_vertex_by_index(tr7, 1, x + a, y - a, z + a);
    set_vertex_by_index(tr7, 2, x + a, y + a, z - a);
    set_color(tr7, color);
    calculate_center(tr7);
    set_perpendicular(tr7, 1, 0, 0);
    group_add(triangles, tr7);

    triangle_t *tr8 = allocate_triangle_t();
    set_vertex_by_index(tr8, 0, x + a, y + a, z + a);
    set_vertex_by_index(tr8, 1, x + a, y - a, z + a);
    set_vertex_by_index(tr8, 2, x + a, y + a, z - a);
    set_color(tr8, color);
    calculate_center(tr8);
    set_perpendicular(tr8, 1, 0, 0);
    group_add(triangles, tr8);

//    Ближняя грань
    triangle_t *tr9 = allocate_triangle_t();
    set_vertex_by_index(tr9, 0, x - a, y - a, z - a);
    set_vertex_by_index(tr9, 1, x - a, y + a, z - a);
    set_vertex_by_index(tr9, 2, x + a, y - a, z - a);
    set_color(tr9, color);
    calculate_center(tr9);
    set_perpendicular(tr9, 0, 0, -1);
    group_add(triangles, tr9);

    triangle_t *tr10 = allocate_triangle_t();
    set_vertex_by_index(tr10, 0, x + a, y + a, z - a);
    set_vertex_by_index(tr10, 1, x - a, y + a, z - a);
    set_vertex_by_index(tr10, 2, x + a, y - a, z - a);
    set_color(tr10, color);
    calculate_center(tr10);
    set_perpendicular(tr10, 0, 0, -1);
    group_add(triangles, tr10);

//    Дальняя грань
    triangle_t *tr11 = allocate_triangle_t();
    set_vertex_by_index(tr11, 0, x - a, y - a, z + a);
    set_vertex_by_index(tr11, 1, x - a, y + a, z + a);
    set_vertex_by_index(tr11, 2, x + a, y - a, z + a);
    set_color(tr11, color);
    calculate_center(tr11);
    set_perpendicular(tr11, 0, 0, 1);
    group_add(triangles, tr11);

    triangle_t *tr12 = allocate_triangle_t();
    set_vertex_by_index(tr12, 0, x + a, y + a, z + a);
    set_vertex_by_index(tr12, 1, x - a, y + a, z + a);
    set_vertex_by_index(tr12, 2, x + a, y - a, z + a);
    set_color(tr12, color);
    calculate_center(tr12);
    set_perpendicular(tr12, 0, 0, 1);
    group_add(triangles, tr12);

}
