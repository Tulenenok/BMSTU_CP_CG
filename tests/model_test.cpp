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

#define PI 3.141592

void test_params(screen_t *screen) {
//    rules_t *rules = init_rules({"a", "b", "c"}, {"a", "b", "c"});
//    print_rules(rules);
//    free_rules(rules);
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
    group_rotate(cube, center,  30 * 3.141592 / 180, 30 * 3.141592 / 180, 30 * 3.141592 / 180);

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

void test_light(screen_t *screen)
{
    std::vector<triangle_t*> cube;
    color_t color = {0, 0, 255};
    add_cube(cube, 300, 300, 0, 100, &color);

    vertex_t center;
    group_center(cube, center);
    group_rotate(cube, center,  0, 30 * PI / 180 , 0);

    std::vector<light_source_t*> ls;
    auto new_ls = create_light_source_t(300, 300, -1000);
    ls.push_back(new_ls);

    group_shading(cube, ls);
    z_buffer_render(screen, cube);
}