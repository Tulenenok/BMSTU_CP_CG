//
// Created by Nataliia Gurova on 26.11.2022.
//

#include <cstdlib>
#include <iostream>
#include "screen_t.h"

screen_t *allocate_screen_t(screen_properties_t *screen) {
    auto *matrix = (screen_t*) malloc(sizeof(screen_t));
    matrix->height = screen->height;
    matrix->width = screen->width;

    matrix->color = (color_t**) malloc(sizeof(color_t *) * screen->width);
    matrix->change = (bool**) malloc(sizeof(bool *) * screen->width);

    for (int i = 0; i < screen->height; i++) {
        matrix->color[i] = (color_t *) calloc(screen->height, sizeof(color_t));
        matrix->change[i] = (bool *) calloc(screen->height, sizeof(bool));
    }

    matrix->default_color = {255, 255, 255};

    set_whole_change_false(matrix);

    return matrix;
}

void free_screen_t(screen_t *matrix) {
    for (int i = 0; i < matrix->height; i++) {
        free(matrix->color[i]);
        free(matrix->change[i]);
    }

    free(matrix->color);
    free(matrix->change);

    free(matrix);
}

void color_pixel(screen_t *matrix, color_t *color, int x, int y) {
    if (x < 0 || x >= matrix->width || y < 0 || y >= matrix->height) {
        std::cout << "[DBG] [[ERROR]] OUT OF ARRAY" << std::endl;
    } else {
        matrix->color[x][y].r = color->r;
        matrix->color[x][y].g = color->g;
        matrix->color[x][y].b = color->b;

        matrix->change[x][y] = true;
    }
}

void color_pixel(screen_t *matrix, int r, int g, int b, int x, int y) {
    if (x < 0 || x >= matrix->width || y < 0 || y >= matrix->height) {
        std::cout << "[DBG] [[ERROR]] OUT OF ARRAY" << std::endl;
    } else {
        matrix->color[x][y].r = r;
        matrix->color[x][y].g = g;
        matrix->color[x][y].b = b;

        matrix->change[x][y] = true;
    }
}

void set_whole_change_true(screen_t *matrix) {
    for (int x = 0; x < matrix->width; x++) {
        for (int y = 0; y < matrix->height; y++) {
            matrix->change[x][y] = true;
        }
    }
}

void set_whole_change_false(screen_t *matrix) {
    for (int x = 0; x < matrix->width; x++) {
        for (int y = 0; y < matrix->height; y++) {
            matrix->change[x][y] = false;
        }
    }
}

void fill_screen(screen_t *matrix, color_t *color) {
    for (int x = 0; x < matrix->width; x++) {
        for (int y = 0; y < matrix->height; y++) {
            color_pixel(matrix, color, x, y);
        }
    }
}

void set_default_color(screen_t *matrix, color_t *color) {
    matrix->default_color.r = color->r;
    matrix->default_color.g = color->g;
    matrix->default_color.b = color->b;
}

void reset_screen(screen_t *matrix) {
    fill_screen(matrix, &matrix->default_color);
}
