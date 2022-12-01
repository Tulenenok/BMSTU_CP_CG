//
// Created by Ilya Malyshev on 30.11.2022.
//

#ifndef C_VERSION_SPHERE_H
#define C_VERSION_SPHERE_H

#include <vector>
#include "../../server/triangle_t.h"
#include "../../server/color_t.h"

void add_sphere(std::vector<triangle_t*>& triangles, double x, double y, double z, double r, color_t *color);

struct VertexSphere {
    float x, y, z;

    VertexSphere() : x(0.0f), y(0.0f), z(0.0f) {};
    VertexSphere(float a) : x(a), y(a), z(a) {};
    VertexSphere(float a, float b, float c) : x(a), y(b), z(c) {};

    VertexSphere operator- (const VertexSphere &obj) {
        return { x - obj.x, y - obj.y, z - obj.z };
    }
    VertexSphere operator+ (const VertexSphere &obj) {
        return { x + obj.x, y + obj.y, z + obj.z };
    }
    VertexSphere operator* (const VertexSphere &obj) {
        return { x * obj.x, y * obj.y, z * obj.z };
    }
    VertexSphere operator*= (const VertexSphere &obj) {
        x *= obj.x;
        y *= obj.y;
        z *= obj.z;
        return *this;
    }
    VertexSphere operator/ (const VertexSphere &obj) {
        return { x / obj.x, y / obj.y, z / obj.z };
    }
};


class Sphere {
public:
    Sphere() : pos({ 0.0f, 0.0f, 0.0f }), count(0), vertex(nullptr) {};
    Sphere(VertexSphere center, float radius, unsigned iteration = 4);
    ~Sphere() { if(vertex) delete[] vertex; }

    void init(float radius, unsigned iteration = 4);    // Инициализация вершин
    const VertexSphere* getVertex();                    // Получить вершины
    unsigned size() { return count; };                  // Размер (в вершинах)

    VertexSphere pos;       // Позиция центра
    unsigned count;         // Кол-во вершин
    VertexSphere *vertex;   // Массив вершин

    VertexSphere middle(VertexSphere p1, VertexSphere p2);
    VertexSphere normal(VertexSphere posVert, float lenght);
    void recur(VertexSphere *vout, VertexSphere vin0, VertexSphere vin1, VertexSphere vin2, unsigned iter);
};


#endif //C_VERSION_SPHERE_H