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
    set_default_color(screen, &color);

    return 0;
}

int server_test_draw_triangle(screen_t *screen)
{
    std::vector<triangle_t*> triangles;
    triangle_t *tr1 = allocate_triangle_t();

    set_vertex_by_index(tr1, 0, 0, 0, 0);
    set_vertex_by_index(tr1, 1, 350, 0, 0);
    set_vertex_by_index(tr1, 2, 500, 100, 0);

    color_t color = {100, 50, 100};
    set_color(tr1, &color);
    triangles.push_back(tr1);

    z_buffer_render(screen, triangles);

    return 0;
}