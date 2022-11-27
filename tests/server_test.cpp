//
// Created by Nataliia Gurova on 26.11.2022.
//

#include <iostream>
#include <vector>
#include "server_test.h"
#include "../server/triangle_t.h"
#include "../server/z_buffer.h"


int server_test_set_default_color(screen_t *screen)
{
    color_t color = {150, 200, 90};
    fill_screen(screen, &color);

    return 0;
}

int server_test_draw_triangle(screen_t *screen)
{
    std::vector<triangle_t*> triangles;
    triangle_t *tr1 = allocate_triangle_t();

    set_vertex_by_index(tr1, 0, 0, 0, -100);
    set_vertex_by_index(tr1, 1, 350, 50, 0);
    set_vertex_by_index(tr1, 2, 700, 100, 200);

    color_t color = {100, 50, 100};
    set_color(tr1, &color);
    triangles.push_back(tr1);

    z_buffer_render(screen, triangles);

    return 0;
}


triangle_t *create_triangle(int x1, int y1, int z1,
                            int x2, int y2, int z2,
                            int x3, int y3, int z3,
                            color_t c)
{
    triangle_t *tr = allocate_triangle_t();

    set_vertex_by_index(tr, 0, x1, y1, z1);
    set_vertex_by_index(tr, 1, x2, y2, z2);
    set_vertex_by_index(tr, 2, x3, y3, z3);

    set_color(tr, &c);
    return tr;
}


int server_test_draw_2_triangle(screen_t *screen)
{
    std::vector<triangle_t*> triangles;
    color_t c1 = {100, 50, 100};
    color_t c2 = {0, 200, 100};
    color_t c3 = {0, 0, 255};

    triangle_t *t2 = create_triangle(0, 0, 0,
                                     720, 0, 0,
                                     0, 720, 0, c1);

    triangle_t *t1 = create_triangle(300, 0, -100,
                                     0, 300, -100,
                                     720, 720, 200, c2);

    triangle_t *t3 = create_triangle(400, 0, -50,
                                     0, 400, -50,
                                     720, 600, 150, c3);

    triangles.push_back(t1);
    triangles.push_back(t2);
    triangles.push_back(t3);
    z_buffer_render(screen, triangles);

    return 0;
}