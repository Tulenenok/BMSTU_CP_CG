//
// Created by Nataliia Gurova on 26.11.2022.
//

#include "vertex_t.h"

void copy_vertex(const vertex_t src, vertex_t dst)
{
    dst[0] = src[0];
    dst[1] = src[1];
    dst[2] = src[2];
}
