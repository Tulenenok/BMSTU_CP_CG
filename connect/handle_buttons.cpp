#include <iostream>
#include "handle_buttons.h"
#include "../server/z_buffer.h"
#include "../server/triangle_vector.h"
#include "../model/3d_objects/cube.h"

static int ijk = 0;

int Handler::load_figure(screen_t *screen_matrix)
{
    color_t color = {0, 0, 255};
    add_cube(polygons, 300 + ijk, 300 + ijk, 0, 3, &color);
    ijk = 30;
    std::cout << polygons.size();
    return 0;
}

int Handler::scale(screen_t *screen_matrix, double kx, double ky, double kz)
{

    vertex_t center;
    group_center(polygons, center);
    group_scale(polygons, center,  kx, ky , kz);

    return 0;
}

#define PI 3.141592

int Handler::rotate(screen_t *screen_matrix, double ax, double ay, double az) {

    vertex_t center;
    group_center(polygons, center);
    group_rotate(polygons, center,  ax * PI / 180, ay * PI / 180 , az * PI / 180);

    std::cout << "rotate " << polygons.size() << "\n";

    return 0;
}

int Handler::push(screen_t *screen_matrix, double dx, double dy, double dz) {
    group_push(polygons, (int)dx, (int)dy , (int)dz);

    return 0;
}

int Handler::add_light_source(screen_t *screen_matrix, double x, double y, double z) {
    auto new_ls = create_light_source_t((int)x, (int)y, (int)z);
    light_sources.push_back(new_ls);

    render(screen_matrix);
    return 0;
}

void Handler::render(screen_t *screen_matrix)
{
    group_shading(polygons, light_sources);
    z_buffer_render(screen_matrix, polygons);
}
