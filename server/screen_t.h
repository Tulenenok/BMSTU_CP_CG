//
// Created by Nataliia Gurova on 26.11.2022.
//

#ifndef C_VERSION_SCREEN_T_H
#define C_VERSION_SCREEN_T_H

#include "color_t.h"
#include "screen_properties_t.h"

typedef struct {
    color_t **color;
    bool **change;
    int width;
    int height;
} screen_t;

screen_t *allocate_screen_t(screen_properties_t *screen);
void free_screen_t(screen_t *matrix);
void color_pixel(screen_t *matrix, color_t *color, int x, int y);
void color_pixel(screen_t *matrix, int r, int g, int b, int x, int y);
void set_whole_change_true(screen_t *matrix);
void set_whole_change_false(screen_t *matrix);
void set_default_color(screen_t *matrix, color_t *color);

#endif //C_VERSION_SCREEN_T_H
