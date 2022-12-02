//
// Created by Ilya Malyshev on 30.11.2022.
//

#include "sphere.h"
#include "../../server/triangle_vector.h"
#include "../../server/triangle_t.h"
#include "../../server/color_t.h"
#include <cmath>
#include <iostream>

#define COUNT_ITERATIONS 1

Sphere::Sphere(VertexSphere center, float radius, unsigned iteration) {
    pos = center;
    init(radius, iteration);
}

void Sphere::init(float radius, unsigned iteration) {
    float r = radius;
    unsigned triangles = 2 << (2 + 2 * iteration);  // 2^3 получается всего 8 базовых треугольников, если не входить в рекурсию, иначе 2^(3 + 2n)
    count = triangles * 3;                  // кол-во вершин
//    vertex = new VertexSphere[count];

    VertexSphere v0, v1, v2;    // Вершины базовых треугольников
    for (int i = 0; i < 8; i++) {
        // Инициализация вершин базовых треугольников
        switch (i) {
            case 0: v0 = { pos.x - r, pos.y, pos.z + r };   v1 = { pos.x + r, pos.y, pos.z + r };   v2 = { pos.x, pos.y + r, pos.z };       break;
            case 1: v0 = { pos.x - r, pos.y, pos.z + r };   v1 = { pos.x, pos.y - r, pos.z };       v2 = { pos.x + r, pos.y, pos.z + r };   break;
            case 2: v0 = { pos.x + r, pos.y, pos.z + r };   v1 = { pos.x + r, pos.y, pos.z - r };   v2 = { pos.x, pos.y + r, pos.z };       break;
            case 3: v0 = { pos.x + r, pos.y, pos.z + r };   v1 = { pos.x, pos.y - r, pos.z };       v2 = { pos.x + r, pos.y, pos.z - r };   break;
            case 4: v0 = { pos.x + r, pos.y, pos.z - r };   v1 = { pos.x - r, pos.y, pos.z - r };   v2 = { pos.x, pos.y + r, pos.z };       break;
            case 5: v0 = { pos.x + r, pos.y, pos.z - r };   v1 = { pos.x, pos.y - r, pos.z };       v2 = { pos.x - r, pos.y, pos.z - r };   break;
            case 6: v0 = { pos.x - r, pos.y, pos.z - r };   v1 = { pos.x - r, pos.y, pos.z + r };   v2 = { pos.x, pos.y + r, pos.z };       break;
            case 7: v0 = { pos.x - r, pos.y, pos.z - r };   v1 = { pos.x, pos.y - r, pos.z };       v2 = { pos.x - r, pos.y, pos.z + r };   break;
        }
        recur(vertex, v0, v1, v2, iteration);
    }
    for (int i = 0; i < count; i++) vertex[i] = normal(vertex[i], radius);
}

// Нормализация вершин - подгоняем длину до радиуса
VertexSphere Sphere::normal(VertexSphere vert, float lenght) {
    VertexSphere dist = vert - pos;
    float hypotenuse = sqrt(dist.x * dist.x + dist.y * dist.y + dist.z * dist.z);
    dist *= VertexSphere(lenght / hypotenuse);
    return pos + dist;
}

// Получение координат середины отрезка
VertexSphere Sphere::middle(VertexSphere p1, VertexSphere p2) {
    return p1 + ((p2 - p1) / VertexSphere(2.0f));
}

// Рекурсия, разбиение треугольников на более мелкие
//void Sphere::recur(VertexSphere *vout, VertexSphere vin0, VertexSphere vin1, VertexSphere vin2, unsigned iteration) {
void Sphere::recur(std::vector<VertexSphere> &vout, VertexSphere vin0, VertexSphere vin1, VertexSphere vin2, unsigned iteration) {
//    static int n = 0;
    if (iteration) {
        VertexSphere m1, m2, m3, v0, v1, v2;
        // Середины отрезков
        m1 = middle(vin0, vin1);
        m2 = middle(vin1, vin2);
        m3 = middle(vin2, vin0);
        iteration--;

        for (int i = 0; i < 4; i++) {   // в одном базовом треугольнике 4 меньших
            switch (i) {
                case 0: v0 = { vin0.x, vin0.y, vin0.z };    v1 = { m1.x, m1.y, m1.z };          v2 = { m3.x, m3.y, m3.z };          break;
                case 1: v0 = { m1.x, m1.y, m1.z };          v1 = { vin1.x, vin1.y, vin1.z };    v2 = { m2.x, m2.y, m2.z };          break;
                case 2: v0 = { m3.x, m3.y, m3.z };          v1 = { m1.x, m1.y, m1.z };          v2 = { m2.x, m2.y, m2.z };          break;
                case 3: v0 = { m3.x, m3.y, m3.z };          v1 = { m2.x, m2.y, m2.z };          v2 = { vin2.x, vin2.y, vin2.z };    break;
            }
            recur(vout, v0, v1, v2, iteration);
        }
    }
    else {
        // Если конечная рекурсия возвращаем начальные вершины
        vout.push_back({ vin0.x, vin0.y, vin0.z });
        vout.push_back({ vin1.x, vin1.y, vin1.z });
        vout.push_back({ vin2.x, vin2.y, vin2.z });
//        vout[n++] = { vin0.x, vin0.y, vin0.z };
//        vout[n++] = { vin1.x, vin1.y, vin1.z };
//        vout[n++] = { vin2.x, vin2.y, vin2.z };
    }
}

//const VertexSphere* Sphere::getVertex() {
const std::vector<VertexSphere> Sphere::getVertex() {
//    if (!vertex) std::cout << "SPHERE::getVertex:: returned nullptr!\n";
    return vertex;
}

void add_sphere(std::vector<triangle_t*>& triangles, double x, double y, double z, double a, color_t *color, int iters) {
    Sphere s(VertexSphere(x, y, z), a, iters);
//    s.pos.x = x;
//    s.pos.y = y;
//    s.pos.z = z;
//
//    s.init(a, 4);

    auto length = s.size();
//    const VertexSphere *vertexes = s.getVertex();
    auto vertexes = s.getVertex();

    for (int i = 0; i < length / 3; i++) {
        triangle_t *t = allocate_triangle_t();
        set_vertex_by_index(t, 0, vertexes[3 * i].x, vertexes[3 * i].y, vertexes[3 * i].z);
        set_vertex_by_index(t, 1, vertexes[3 * i + 1].x, vertexes[3 * i + 1].y, vertexes[3 * i + 1].z);
        set_vertex_by_index(t, 2, vertexes[3 * i + 2].x, vertexes[3 * i + 2].y, vertexes[3 * i + 2].z);
        calculate_center(t);
        set_color(t, color);
        predict_normal(t);

        double k = (t->center[0] - x) * t->perpendicular[0] + (t->center[1] - y) * t->perpendicular[1] + (t->center[2] - z) * t->perpendicular[2];

        if (k < -1e5) {
            for (int j = 0; j < 3; j++) {
                t->perpendicular[j] *= -1;
            }
        }

        group_add(triangles, t);
    }

    std::cout << "udubsdin " << triangles.size() << std::endl;
    for (int i = 0; i < triangles.size(); i++) {
        std::cout << triangles[i]->initial_vertexes[0][0] << " " << triangles[i]->initial_vertexes[0][0] << " " << triangles[i]->initial_vertexes[0][0] << std::endl;
    }
}

void add_sphere(std::vector<triangle_t*>& triangles, sphere_t &sphere, int iters)
{
    add_sphere(triangles, sphere.x, sphere.y, sphere.z, sphere.a, &(sphere.color), iters);
}

