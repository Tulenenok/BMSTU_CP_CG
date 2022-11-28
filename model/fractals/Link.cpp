//
// Created by Nataliia Gurova on 28.11.2022.
//

#include "Link.h"
#include <iostream>

Link::Link(vertex_t f, vertex_t t)
{
    copy_vertex(f, from);
    copy_vertex(t, to);
}

void Link::print()
{
    std::cout << "Link:\n";
    std::cout << "v1: (" << from[0] << ", " << from[1] << ", " << from[2] << ")\n";
    std::cout << "v2: (" << to[0] << ", " << to[1] << ", " << to[2] << ")\n";
}
