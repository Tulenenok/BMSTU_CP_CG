//
// Created by Nataliia Gurova on 26.11.2022.
//

#include <cstdlib>
#include <cmath>
#include <iostream>

#include "triangle_t.h"

triangle_t *allocate_triangle_t() {
    auto *res = (triangle_t *) calloc(1, sizeof(triangle_t));
    return res;
}

void print_triangle_t(triangle_t *src) {
    std::cout << "triangle" << std::endl;
    std::cout << "A:   " << src->initial_vertexes[0][0] << " " << src->initial_vertexes[0][1] << " " << src->initial_vertexes[0][2] << std::endl;
    std::cout << "B:   " << src->initial_vertexes[1][0] << " " << src->initial_vertexes[1][1] << " " << src->initial_vertexes[1][2] << std::endl;
    std::cout << "C:   " << src->initial_vertexes[2][0] << " " << src->initial_vertexes[2][1] << " " << src->initial_vertexes[2][2] << std::endl;
    std::cout << "RGB: " << src->initial_color.r << " " << src->initial_color.g << " " << src->initial_color.b << std::endl;
}

void free_triangle_t(triangle_t *src) {
    free(src);
}

//Находит индекс вершины, у которой максимальное значение координаты по определенной оси
//Речь идет об уже преобразованных вершинах
int ind_of_max_of_axis(triangle_t *triangle, int axis) {
    int ind = 0;

    for (int i = 0; i < 3; i++) {
        if (triangle->processed_vertexes[i][axis] > triangle->processed_vertexes[ind][axis]) {
            ind = i;
        }
    }

    return ind;
}

//Находит индекс вершины, у которой минимальное значение координаты по определенной оси
//Речь идет об уже преобразованных вершинах
int ind_of_min_of_axis(triangle_t *triangle, int axis) {
    int ind = 0;

    for (int i = 0; i < 3; i++) {
        if (triangle->processed_vertexes[i][axis] < triangle->processed_vertexes[ind][axis]) {
            ind = i;
        }
    }

    return ind;
}

//Находит индекс вершины, у которой среднее значение координаты по определенной оси
//Речь идет об уже преобразованных вершинах
int ind_of_mid_of_axis(triangle_t *triangle, int axis) {
    int min = ind_of_min_of_axis(triangle, axis);
    int max = ind_of_max_of_axis(triangle, axis);
    int result = -1;
    for (int i = 0; i < 3; i++) {
        if (i != min && i != max) {
            result = i;
        }
    }

    return result;
}

//Находит количество вершин, у которой координата по определенной оси совпадает с заданным значением
//Речь идет об уже преобразованных вершинах
int count_value_with_axis(triangle_t *triangle, int axis, int value) {
    int count = 0;

    for (int i = 0; i < 3; i++) {
        if (triangle->processed_vertexes[i][axis] == value) {
            count++;
        }
    }

    return count;
}

//Находит индекс вершины, у которой координата по определенной оси совпадает с заданным значением
//Речь идет об уже преобразованных вершинах
int index_with_axis(triangle_t *triangle, int axis, int value) {
    for (int i = 0; i < 3; i++) {
        if (triangle->processed_vertexes[i][axis] == value) {
            return i;
        }
    }
    return 0;
}

void set_vertex_by_index(triangle_t *triangle, int ind, int x, int y, int z) {
    triangle->initial_vertexes[ind][0] = x;
    triangle->initial_vertexes[ind][1] = y;
    triangle->initial_vertexes[ind][2] = z;

    triangle->processed_vertexes[ind][0] = x;
    triangle->processed_vertexes[ind][1] = y;
    triangle->processed_vertexes[ind][2] = z;
}

void set_color(triangle_t *triangle, color_t *color) {
    triangle->initial_color.r = color->r;
    triangle->initial_color.g = color->g;
    triangle->initial_color.b = color->b;

    triangle->processed_color.r = color->r;
    triangle->processed_color.g = color->g;
    triangle->processed_color.b = color->b;
}

void set_perpendicular(triangle_t *triangle, int x, int y, int z) {
    triangle->perpendicular[0] = x;
    triangle->perpendicular[1] = y;
    triangle->perpendicular[2] = z;
}

void predict_perpendicular(triangle_t *triangle) {
    double ax = triangle->initial_vertexes[0][0];
    double ay = triangle->initial_vertexes[0][1];
    double az = triangle->initial_vertexes[0][2];

    double bx = triangle->initial_vertexes[1][0];
    double by = triangle->initial_vertexes[1][1];
    double bz = triangle->initial_vertexes[1][2];

    double cx = triangle->initial_vertexes[2][0];
    double cy = triangle->initial_vertexes[2][1];
    double cz = triangle->initial_vertexes[2][2];

    double x_ab = bx - ax;
    double y_ab = by - ay;
    double z_ab = bz - az;

    double x_ac = cx - ax;
    double y_ac = cy - ay;
    double z_ac = cz - az;

    int x_n = (int) (y_ab * z_ac - y_ac * z_ab);
    int y_n = (int) (x_ab * z_ac - x_ac * z_ab);
    int z_n = (int) (x_ab * y_ac - x_ac * y_ab);

    triangle->perpendicular[0] = x_n;
    triangle->perpendicular[1] = y_n;
    triangle->perpendicular[2] = z_n;
}

void calculate_center(triangle_t *triangle) {
    int x = 0;
    int y = 0;
    int z = 0;

    for (int i = 0; i < 3; i++) {
        x += triangle->initial_vertexes[i][0];
        y += triangle->initial_vertexes[i][1];
        z += triangle->initial_vertexes[i][2];
    }

    x /= 3;
    y /= 3;
    z /= 3;

    triangle->center[0] = x;
    triangle->center[1] = y;
    triangle->center[2] = z;
}

void reset_processed_vertexes(triangle_t *triangle) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            triangle->processed_vertexes[i][j] = triangle->initial_vertexes[i][j];
        }
    }
}

void reset_processed_color(triangle_t *triangle) {
    triangle->processed_color.r = triangle->initial_color.r;
    triangle->processed_color.g = triangle->initial_color.g;
    triangle->processed_color.b = triangle->initial_color.b;
}

void push(triangle_t *triangle, int dx, int dy, int dz) {
    for (int i = 0; i < 3; i++) {
        triangle->processed_vertexes[i][0] += dx;
        triangle->processed_vertexes[i][1] += dy;
        triangle->processed_vertexes[i][2] += dz;
    }
}

void scale(triangle_t *triangle, vertex_t center, double dx, double dy, double dz) {
    push(triangle, -center[0], -center[1], -center[2]);

    for (int i = 0; i < 3; i++) {
        triangle->processed_vertexes[i][0] = (int) (triangle->processed_vertexes[i][0] * dx);
        triangle->processed_vertexes[i][1] = (int) (triangle->processed_vertexes[i][1] * dy);
        triangle->processed_vertexes[i][2] = (int) (triangle->processed_vertexes[i][2] * dz);
    }

    push(triangle, center[0], center[1], center[2]);
}

void rotate(triangle_t *triangle, vertex_t center, double dx, double dy, double dz) {
    push(triangle, -center[0], -center[1], -center[2]);


    double x, y, z;
    for (int i = 0; i < 3; i++) {
        x = triangle->processed_vertexes[i][0];
        y = triangle->processed_vertexes[i][1];
        z = triangle->processed_vertexes[i][2];
        triangle->processed_vertexes[i][0] = (int) ((cos(dx) * cos(dz) - sin(dx) * cos(dy) * sin(dz)) * x - (sin(dx) * cos(dz) + cos(dx) * cos(dy) * sin(dz)) * y + sin(dy) * sin(dz) * z);
        triangle->processed_vertexes[i][1] = (int) ((cos(dx) * sin(dz) + sin(dx) * cos(dy) * cos(dz)) * x - (sin(dx) * sin(dz) - cos(dx) * cos(dy) * cos(dz)) * y - sin(dy) * cos(dz) * z);
        triangle->processed_vertexes[i][2] = (int) (sin(dx) * sin(dy) * x + cos(dx) * sin(dy) * y + cos(dy) * z);
    }

    push(triangle, center[0], center[1], center[2]);
}
