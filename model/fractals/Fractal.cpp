//
// Created by Nataliia Gurova on 28.11.2022.
//

#include "Fractal.h"
#include <iostream>
#include <math.h>

void Fractal::setParams(Params &_params)
{
    this->params = _params;
}

Params Fractal::getParams()
{
    return this->params;
}

void Fractal::calculate()
{
    // В этой функции изменены "стандартные" расшифровки ключей (например, \ это |)

    std::string formula = this->params.calculate();         //  Посчитали итоговую формулу фрактала

    Params tmp = params;
    std::vector<Params> stack;
    bool find_open = false;

    rotate_matrix(params.alpha, 'U', &tmp.HLU);

    for (auto r: formula)
    {
        if (find_open || r == '(' || r == '(')
        {
            find_open = (r != ')');
            continue;
        }

        if (isalpha(r) && std::find(tmp.consts.begin(), tmp.consts.end(), r) == tmp.consts.end())
        {
            vertex_t new_p;
            new_p[0] = round(tmp.p[0] + tmp.step * tmp.HLU[0][0]);
            new_p[1] = round(tmp.p[1] + tmp.step * tmp.HLU[0][1]);
            new_p[2] = round(tmp.p[2] + tmp.step * tmp.HLU[0][2]);

            if (isupper(r))
            {
                Link new_l = {tmp.p, new_p};
                links.push_back(new_l);
            }
            copy_vertex(new_p, tmp.p);
        }
        else if (r == '+')
            rotate_matrix(tmp.delta, 'U', &tmp.HLU);
        else if (r == '-')
            rotate_matrix(-tmp.delta, 'U', &tmp.HLU);
        else if (r == '&' || r == '_')
            rotate_matrix(tmp.delta, 'L', &tmp.HLU);
        else if (r == '^')
            rotate_matrix(-tmp.delta, 'L', &tmp.HLU);
        else if (r == '|')
            rotate_matrix(tmp.delta, 'H', &tmp.HLU);
        else if (r == '/')
            rotate_matrix(-tmp.delta, 'H', &tmp.HLU);
        else if (r == '\\')
            rotate_matrix(180, 'U', &tmp.HLU);              //TODO

        else if (r == '[')
            stack.push_back(tmp);
        else if (r == ']')
        {
            tmp = stack[stack.size() - 1];
            stack.pop_back();
        }
        else if (r == '@')
        {
            tmp.step = tmp.step * 0.8;
        }
    }
}

mat_t Fractal::multiply(mat_t &mat1, mat_t &mat2)
{
    mat_t res = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            for (int k = 0; k < 3; k++)
                res[i][j] += mat1[i][k] * mat2[k][j];

    return res;
}

void Fractal::rotate_matrix(double angle, char cmd, mat_t *hlu)
{
    double r_angle = angle * M_PI / 180;
    double a_cos = cos(r_angle);
    double a_sin = sin(r_angle);

    if (cmd == 'U')
    {
        mat_t tmp_matrix = {{a_cos, a_sin, 0},
                            {-a_sin, a_cos, 0},
                            {0, 0, 1}};
        *hlu = multiply(tmp_matrix, *hlu);
    }
    else if (cmd == 'L')
    {
        mat_t tmp_matrix = {{a_cos, 0, -a_sin},
                            {0, 1, 0},
                            {a_sin, 0, a_cos}};
        *hlu = multiply(tmp_matrix, *hlu);
    }
    else if (cmd == 'H')
    {
        mat_t tmp_matrix = {{1, 0, 0},
                            {0, a_cos, -a_sin},
                            {0, a_sin, a_cos}};
        *hlu = multiply(tmp_matrix, *hlu);
    }
    else
    {
        std::cout << "Отправили неверную букву в функцию Fractal.rotate";
    }
}

void Fractal::print_links()
{
    if (links.empty())
        std::cout << "empty links";

    for(auto l: links)
        l.print();
}

void Fractal::generate_cubes(std::vector<triangle_t *> &polygons)
{
    for (auto link: links)
    {
        double L = link.get_len();
        color_t color = {0, 0, 255};

        //  Общие приращения по всем координатам
        int d_X = link.from[0] - link.to[0];
        int d_Y = link.from[1] - link.to[1];
        int d_Z = link.from[2] - link.to[2];

        double k = 1.0 / (default_n - 1);

        int a;
        if (abs(d_X) >= abs(d_Y) and abs(d_X) >= abs(d_Z))
            a = ceil(k * L / (default_n - 1));
        else if (abs(d_Y) >= abs(d_X) and abs(d_Y) >= abs(d_Z))
            a = ceil(k * L / (default_n - 1));
        else
            a = ceil(k * L / (default_n - 1));

        // Если максимальное приращение по оси X
            // Рассчитываем координаты центров кубов
        int c_x = link.from[0];
        int c_y = link.from[1];
        int c_z = link.from[2];

        for (int i = 0; i < default_n; i++)
        {
            add_cube(polygons, c_x, c_y, c_z, a, &color);
            c_x += round(k * d_X);
            c_y += round(k * d_Y);
            c_z += round(k * d_Z);
        }
    }
}
