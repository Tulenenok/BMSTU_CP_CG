//
// Created by Nataliia Gurova on 26.11.2022.
//

#ifndef C_VERSION_HANDLE_BUTTONS_H
#define C_VERSION_HANDLE_BUTTONS_H

#include "../connect/handle_buttons.h"
#include "../server/screen_t.h"
#include "../server/triangle_t.h"
#include "../server/light_source.h"
#include "../model/fractals/preset_settings.h"

#include <vector>

class Handler
{
public:
    Handler() : polygons(), light_sources() {};

    int load_figure(screen_t *screen_matrix, preset_setting_t& preset);

    int scale(screen_t *screen_matrix, double kx, double ky, double kz);
    int push(screen_t *screen_matrix, double dx, double dy, double dz);
    int rotate(screen_t *screen_matrix, double ax, double ay, double az);

    int add_light_source(screen_t *screen_matrix, double x, double y, double z);

    int clean_handler();

    void push_polygons(std::vector<triangle_t*>);

private:
    std::vector<triangle_t*> polygons;
    std::vector<light_source_t*> light_sources;
};

#endif //C_VERSION_HANDLE_BUTTONS_H
