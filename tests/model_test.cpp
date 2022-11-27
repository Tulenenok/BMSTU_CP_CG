//
// Created by Nataliia Gurova on 27.11.2022.
//

#include "model_test.h"
#include <iostream>
#include <vector>
#include "server_test.h"
#include "../server/triangle_t.h"
#include "../server/z_buffer.h"
#include "../model/3d_objects/cube.h"
#include "../server/triangle_vector.h"
#include <math.h>

void test_params() {
//    params_t *params = init_params(1, 1, 1, 30, 30, 5, "aaa", )
}

void test_cube(screen_t *screen) {
    std::vector<triangle_t*> cube;
    color_t color = {0, 0, 255};
    add_cube(cube, 300, 300, 0, 100, &color);

    z_buffer_render(screen, cube);
}

void test_rotate_cube(screen_t *screen) {
    std::vector<triangle_t*> cube;
    color_t color = {0, 0, 255};
    add_cube(cube, 300, 300, 0, 100, &color);

    vertex_t center;
    group_center(cube, center);
    group_rotate(cube, center, 0, 30 * 3.141592 / 180, 0);

    z_buffer_render(screen, cube);
}

void test_scale_cube(screen_t *screen) {
    std::vector<triangle_t*> cube;
    color_t color = {0, 0, 255};
    add_cube(cube, 300, 300, 0, 100, &color);

    vertex_t center;
    group_center(cube, center);
    group_scale(cube, center, -2, 1, 0.5);

    z_buffer_render(screen, cube);
}

void test_push_cube(screen_t *screen) {
    std::vector<triangle_t*> cube;
    color_t color = {0, 0, 255};
    add_cube(cube, 300, 300, 0, 100, &color);

    vertex_t center;
    group_center(cube, center);
    group_push(cube, 100, -100, 100);

    z_buffer_render(screen, cube);
}
