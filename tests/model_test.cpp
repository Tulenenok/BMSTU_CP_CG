//
// Created by Nataliia Gurova on 27.11.2022.
//

#include "model_test.h"
#include <iostream>
#include <vector>
#include "../server/triangle_t.h"
#include "../server/z_buffer.h"
#include "../model/3d_objects/cube.h"
#include "../server/triangle_vector.h"


#include "../model/fractals/Rules.h"
#include "../model/fractals/Params.h"
#include "../model/fractals/Fractal.h"

#define PI 3.141592

void test_rules() {
    Rules rules({'a', 'b', 'c'}, {"a", "b", "c"});
    rules.print();
}

void test_params() {
    Rules rules({'a', 'b', 'c'}, {"a", "b", "c"});
    rules.print();

    Params params(1, 2, 3, 30, 50, 5, "aaa", rules, 3);
    params.print();
}

void test_calculate_rule() {
    Rules rules({'a', 'b', 'c'}, {"ab", "b", "cc"});
    Params params(1, 2, 3, 30, 50, 5, "abc", rules, 2);

    params.print();
    std::cout << params.calculate();
}

void test_params_copy()
{
    Rules rules({'a', 'b', 'c'}, {"ab", "b", "cc"});
    Rules rule2({'a'}, {"ab"});
    Params params(1, 2, 3, 30, 50, 5, "abc", rules, 2);

    std::vector<Params> v1;
    v1.push_back(params);
    params.HLU[0][0] = 10;

    std::cout << v1[0].HLU[0][0];
}

void test_simple_fractal()
{
    Rules rules({'A'}, {"AB"});
    Params params(0, 0, 0, 90, 0, 5, "ABC", rules, 0);
    Fractal fractal;
    fractal.setParams(params);
    params.print();

    std::cout << "\n" << params.calculate();
    fractal.calculate();
    fractal.print_links();
}

void test_fractal_tree()
{
    Rules rules({'A', 'B'}, {R"(B[+A]||||[+A]||||[+A]||||BA)", "BB"});
    Params params(0, 0, 0, 90, 30, 5, "A", rules, 2);
    Fractal fractal;
    fractal.setParams(params);
    params.print();

    std::cout << "\n" << params.calculate();
    fractal.calculate();
    fractal.print_links();
}

void test_fractal_paporotnik()
{
    Rules rules({'A', 'C', 'D'},
                {R"([++++++++++++++EC]B^+B[--------------ED]B+BA)",
                     R"([---------EE][+++++++++EE]B__+C)",
                     "[---------EE][+++++++++EE]B__-D"});
    Params params(0, 0, 0, 90, 4, 10, "EEEA", rules, 12);
    Fractal fractal;
    fractal.setParams(params);
    params.print();

    std::cout << "\n" << params.calculate();
    fractal.calculate();
    fractal.print_links();
}

Fractal test_fractal_show()
{
    Rules rules({'A', 'B'}, {R"(B[+A]||||[+A]||||[+A]||||BA)", "BB"});
    Params params(300, 300, 0, 90, 30, 15, "A", rules, 1);

    Fractal fractal;
    fractal.setParams(params);
    params.print();

    std::cout << "\n" << params.calculate();
    fractal.calculate();
    fractal.print_links();

    return fractal;
}

Fractal test_fractal_show_2()
{
    // Папоротник
    Rules rules({'A', 'C', 'D'},
                {R"([++++++++++++++EC]B^+B[--------------ED]B+BA)",
                 R"([---------EE][+++++++++EE]B__+C)",
                 "[---------EE][+++++++++EE]B__-D"});
    Params params(0, 0, 0, 90, 4, 10, "EEEA", rules, 12);
    Fractal fractal;
    fractal.setParams(params);
    params.print();

    std::cout << "\n" << params.calculate();
    fractal.calculate();
    fractal.print_links();

    return fractal;
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

    double center[3];
    group_center(cube, center);
    group_rotate(cube, center,  30 * 3.141592 / 180, 30 * 3.141592 / 180, 30 * 3.141592 / 180);

    z_buffer_render(screen, cube);
}

void test_scale_cube(screen_t *screen) {
    std::vector<triangle_t*> cube;
    color_t color = {0, 0, 255};
    add_cube(cube, 300, 300, 0, 100, &color);

    double center[3];
    group_center(cube, center);
    group_scale(cube, center, -2, 1, 0.5);

    z_buffer_render(screen, cube);
}

void test_push_cube(screen_t *screen) {
    std::vector<triangle_t*> cube;
    color_t color = {0, 0, 255};
    add_cube(cube, 300, 300, 0, 100, &color);

    double center[3];
    group_center(cube, center);
    group_push(cube, 100, -100, 100);

    z_buffer_render(screen, cube);
}

void test_light(screen_t *screen)
{
    std::vector<triangle_t*> cube;
    color_t color = {0, 0, 255};
    add_cube(cube, 300, 300, 0, 100, &color);

    double center[3];
    group_center(cube, center);
    group_rotate(cube, center,  0, 30 * PI / 180 , 0);

    std::vector<light_source_t*> ls;
    auto new_ls = create_light_source_t(300, 300, -1000);
    ls.push_back(new_ls);

    group_shading(cube, ls);
    z_buffer_render(screen, cube);
}