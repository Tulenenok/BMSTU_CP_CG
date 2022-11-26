//
// Created by Nataliia Gurova on 26.11.2022.
//

#include <cmath>
#include "z_buffer.h"

//Фунуция работает не с изначальными координатами вершин, а с измененными!!!
//Функция работает не с изначальным светом, а с измененным
void process_level(triangle_t *triangle, screen_t *screen, int y, double *depth_arr) {

    int max_x_ind = ind_of_max_of_axis(triangle, 0);
    int min_x_ind = ind_of_min_of_axis(triangle, 0);

    int max_y_ind = ind_of_max_of_axis(triangle, 1);
    int min_y_ind = ind_of_min_of_axis(triangle, 1);
    int mid_y_ind = ind_of_mid_of_axis(triangle, 1);

    int ymax = triangle->processed_vertexes[max_y_ind][1];
    int ymin = triangle->processed_vertexes[min_y_ind][1];
    int ymid = triangle->processed_vertexes[mid_y_ind][1];
    int xmax = triangle->processed_vertexes[max_y_ind][0];
    int xmin = triangle->processed_vertexes[min_y_ind][0];
    int xmid = triangle->processed_vertexes[mid_y_ind][0];
    int zmax = triangle->processed_vertexes[max_y_ind][2];
    int zmin = triangle->processed_vertexes[min_y_ind][2];
    int zmid = triangle->processed_vertexes[mid_y_ind][2];

//  Если треугольник целиком выше или ниже уровня
    if (y < triangle->processed_vertexes[min_y_ind][1] || y > triangle->processed_vertexes[max_y_ind][1]) {
        return;
    }

//   Если треугольник выраждается в точку или линию - пропускаем этот треугольник
    if (max_x_ind == min_x_ind || max_y_ind == min_y_ind) {
        return;
    }

    if ((y == triangle->processed_vertexes[max_y_ind][1] || y == triangle->processed_vertexes[min_y_ind][1]) && count_value_with_axis(triangle, 1, y) == 1) {
        int y_ind = index_with_axis(triangle, 1, y);
        int x = triangle->processed_vertexes[y_ind][0];
        int z = triangle->processed_vertexes[y_ind][2];

        if (x >= 0 && x < screen->width) {
            if (depth_arr[x] > z) {
                depth_arr[x] = z;
                color_pixel(screen, &(triangle->processed_color), x, y);
            }
        }

        return;
    }

    double start_x;
    double finish_x;
    double start_z;
    double finish_z;

    if (y > ymid && fabs(ymin - ymid) > 1e-6 && fabs(ymin - ymax) > 1e-6) {

        double d_ya = ymin - ymid;
        double d_xa = xmin - xmid;
        double d_za = zmin - zmid;
        start_x = xmid + d_xa * (y - ymid) / d_ya;
        start_z = zmid + d_za * (y - ymid) / d_ya;

        double d_yb = ymin - ymax;
        double d_xb = xmin - xmax;
        double d_zb = zmin - zmax;
        finish_x = xmax + d_xb * (y - ymax) / d_yb;
        finish_z = zmax + d_zb * (y - ymax) / d_yb;

    } else if (fabs(ymax - ymid) > 1e-6 && fabs(ymin - ymax) > 1e-6) {

        double d_ya = ymax - ymin;
        double d_xa = xmax - xmin;
        double d_za = zmax - zmin;
        start_x = xmin + d_xa * (y - ymin) / d_ya;
        start_z = zmin + d_za * (y - ymin) / d_ya;

        double d_yb = ymax - ymid;
        double d_xb = xmax - xmid;
        double d_zb = zmax - zmid;
        finish_x = xmid + d_xb * (y - ymid) / d_yb;
        finish_z = xmid + d_zb * (y - ymid) / d_yb;

    } else {
        return;
    }

    if (start_x > finish_x) {
        double tmp = start_x;
        start_x = finish_x;
        finish_x = tmp;
        tmp = start_z;
        start_z = finish_z;
        finish_z = tmp;
    }

    if (fabs(finish_x - start_x) < 1e-2) {
        return;
    }

    double dz = (finish_z - start_z) / (finish_x - start_x);

    for (int x = (int) start_x - 1; x < (int) finish_x + 1; x++) {
        if (x >= 0 && x < screen->width) {
            double z = start_z + dz * (x - start_x);

            if (depth_arr[x] > z) {
                depth_arr[x] = z;
                color_pixel(screen, &(triangle->processed_color), x, y);
            }
        }
    }
}

void complete_process_level(screen_t *screen, std::vector<triangle_t*> triangles, int y) {

    if (y < screen->height && y >= 0) {
        auto *depth_array = (double*) malloc(sizeof(double) * screen->width);

        for (int i = 0; i < screen->width; i++) {
            depth_array[i] = INT_MAX;
        }

        for (int i = 0; i < triangles.size(); i++) {
            process_level(triangles[i], screen, y, depth_array);
        }

        free(depth_array);
    }
}

void z_buffer_render(screen_t *screen, std::vector<triangle_t*> triangles) {

    for (int y = screen->height - 1; y >= 0; y--){
        complete_process_level(screen, triangles, y);
    }

}

