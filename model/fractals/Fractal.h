//
// Created by Nataliia Gurova on 28.11.2022.
//

#ifndef C_VERSION_FRACTAL_H
#define C_VERSION_FRACTAL_H

#include <vector>
#include "Fractal.h"
#include "Params.h"
#include "Link.h"

class Fractal
{
public:
    Fractal() {};
    void setParams(Params &_params);
    Params getParams();

    void calculate();
    void print_links();

    std::vector<Link> links;
    void generate_cubes(std::vector<triangle_t *> &polygons);
    void generate_spheres(std::vector<triangle_t *> &polygons, int iters);

    color_t color;
    int default_n{3};       //  Дефолное количество кубиков на отрезок

private:
    Params params;
    mat_t multiply(mat_t &mat1, mat_t &mat2);
    void rotate_matrix(double angle, char cmd, mat_t *hlu);
};

#endif //C_VERSION_FRACTAL_H
