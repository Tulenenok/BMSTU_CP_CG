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
            rotate_matrix(180, 'U', &tmp.HLU);

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
