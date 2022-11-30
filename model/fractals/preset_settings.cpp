//
// Created by Nataliia Gurova on 30.11.2022.
//

#include "preset_settings.h"

preset_setting_t get_spiral()
{
    preset_setting_t spiral;

    Rules rules({'A'}, {"A-^A"});
    Params params(SPIRAL_X, SPIRAL_Y, SPIRAL_Z,
                  SPIRAL_ALPHA, -12, SPIRAL_STEP, "A", rules, 8);

    spiral.params = params;
    spiral.color = {230,168,215};
    spiral.count_cubes = 3;

    return spiral;
}

preset_setting_t get_fern()
{
    preset_setting_t fern;

    Rules rules({'A', 'C', 'D'},
                {R"([++++++++++++++EC]B^+B[--------------ED]B+BA)", R"([---------EE][+++++++++EE]B__+C)",
                 "[---------EE][+++++++++EE]B__-D"});
    Params params(FERN_X, FERN_Y, FERN_Z,
                  FERN_ALPHA, 4, FERN_STEP, "EEEA", rules, 10);

    fern.params = params;
    fern.color = {200,255,0};
    fern.count_cubes = 3;

    return fern;
}

preset_setting_t get_ivy()
{
    preset_setting_t ivy;

    Rules rules({'A'}, {"/A[++A]-|A[--A]+//A"});
    Params params(IVY_X, IVY_Y, IVY_Z,
                  IVY_ALPHA, -18, IVY_STEP, "--A", rules, 4);

    ivy.params = params;
    ivy.color = {200,255,0};
    ivy.count_cubes = 3;

    return ivy;
}

preset_setting_t get_verbena()
{
    preset_setting_t verbena;

    Rules rules({'A', 'B'}, {R"(B[+A]||||[+A]||||[+A]||||BA)", "BB"});
    Params params(VERBENA_X, VERBENA_Y, VERBENA_Z,
                  VERBENA_ALPHA, 30, VERBENA_STEP, "A", rules, 4);

    verbena.params = params;
    verbena.color = {200,255,0};
    verbena.count_cubes = 3;

    return verbena;
}