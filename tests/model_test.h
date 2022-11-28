//
// Created by Nataliia Gurova on 27.11.2022.
//

#ifndef C_VERSION_MODEL_TEST_H
#define C_VERSION_MODEL_TEST_H

#include "../server/screen_t.h"

void test_rules();
void test_params();
void test_calculate_rule();
void test_params_copy();
void test_fractal();

void test_cube(screen_t *screen);
void test_rotate_cube(screen_t *screen);
void test_scale_cube(screen_t *screen);
void test_push_cube(screen_t *screen);
void test_light(screen_t *screen);

#endif //C_VERSION_MODEL_TEST_H
