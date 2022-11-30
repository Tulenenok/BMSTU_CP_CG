//
// Created by Nataliia Gurova on 28.11.2022.
//

#ifndef C_VERSION_LINK_H
#define C_VERSION_LINK_H

#include "../../server/vertex_t.h"
#include <string>
#include "../3d_objects/cube.h"

class Link
{
public:
    Link() {};
    Link(vertex_t f, vertex_t t);
    void print();
    double get_len();

    vertex_t from;
    vertex_t to;
};

#endif //C_VERSION_LINK_H
