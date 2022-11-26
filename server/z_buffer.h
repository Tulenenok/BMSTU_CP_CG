//
// Created by Nataliia Gurova on 26.11.2022.
//

#ifndef C_VERSION_Z_BUFFER_H
#define C_VERSION_Z_BUFFER_H

#include <vector>

#include "screen_properties_t.h"
#include "color_t.h"
#include "triangle_t.h"
#include "screen_t.h"

void z_buffer_render(screen_t *screen, std::vector<triangle_t*> triangles);
void complete_process_level(screen_t *screen, std::vector<triangle_t*> triangles, int y);
void process_level(triangle_t *triangle, screen_t *screen, int y, double *depth_arr);

#endif //C_VERSION_Z_BUFFER_H
