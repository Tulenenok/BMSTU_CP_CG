//
// Created by Nataliia Gurova on 26.11.2022.
//

#include <cmath>
#include <iostream>
#include <thread>
#include "z_buffer.h"

//Фунуция работает не с изначальными координатами вершин, а с измененными!!!
//Функция работает не с изначальным светом, а с измененным
void process_level(triangle_t *triangle, screen_t *screen, int y, double *depth_arr) {

    int max_x_ind = ind_of_max_of_axis(triangle, 0);
    int min_x_ind = ind_of_min_of_axis(triangle, 0);

    int max_y_ind = ind_of_max_of_axis(triangle, 1);
    int min_y_ind = ind_of_min_of_axis(triangle, 1);
    int mid_y_ind = ind_of_mid_of_axis(triangle, 1);

    double ymax = triangle->processed_vertexes[max_y_ind][1];
    double ymin = triangle->processed_vertexes[min_y_ind][1];
    double ymid = triangle->processed_vertexes[mid_y_ind][1];
    double xmax = triangle->processed_vertexes[max_y_ind][0];
    double xmin = triangle->processed_vertexes[min_y_ind][0];
    double xmid = triangle->processed_vertexes[mid_y_ind][0];
    double zmax = triangle->processed_vertexes[max_y_ind][2];
    double zmin = triangle->processed_vertexes[min_y_ind][2];
    double zmid = triangle->processed_vertexes[mid_y_ind][2];

//  Если треугольник целиком выше или ниже уровня
    if (y < triangle->processed_vertexes[min_y_ind][1] || y > triangle->processed_vertexes[max_y_ind][1]) {
//        std::cout << "y" << y << "pos 1" << std::endl;
        return;
    }

//   Если треугольник выраждается в точку или линию - пропускаем этот треугольник
    if (max_x_ind == min_x_ind || max_y_ind == min_y_ind) {
//        std::cout << "y" << y << "pos 2" << std::endl;
        return;
    }

    if ((y == triangle->processed_vertexes[max_y_ind][1] || y == triangle->processed_vertexes[min_y_ind][1]) && count_value_with_axis(triangle, 1, y) == 1) {
        int y_ind = index_with_axis(triangle, 1, y);
        int x = ceil(triangle->processed_vertexes[y_ind][0]);
        int z = ceil(triangle->processed_vertexes[y_ind][2]);

        if (x >= 0 && x < screen->width) {
            if (depth_arr[x] > z) {
                depth_arr[x] = z;
                color_pixel(screen, &(triangle->processed_color), x, y);
            }
        }

//        std::cout << "y" << y << "pos 3" << std::endl;
        return;
    }

    double start_x;
    double finish_x;
    double start_z;
    double finish_z;

//    if (y > ymid && fabs(ymin - ymid) > 1e-6 && fabs(ymin - ymax) > 1e-6) {
    if (y > ymid) {

//        std::cout << y << " higher" << std::endl;

//      Этот блок одинаков для каждой ветки
        double d_ya = ymax - ymin;
        double d_xa = xmax - xmin;
        double d_za = zmax - zmin;
        start_x = xmin + d_xa * (y - ymin) / d_ya;
        start_z = zmin + d_za * (y - ymin) / d_ya;

        double d_yb = ymax - ymid;
        double d_xb = xmax - xmid;
        double d_zb = zmax - zmid;
        finish_x = xmid + d_xb * (y - ymid) / d_yb;
        finish_z = zmid + d_zb * (y - ymid) / d_yb;

//    } else if (fabs(ymax - ymid) > 1e-6 && fabs(ymin - ymax) > 1e-6) {
    } else if (y < ymid) {

//        std::cout << y << " lower" << std::endl;

//      Этот блок одинаков для каждой ветки
        double d_ya = ymax - ymin;
        double d_xa = xmax - xmin;
        double d_za = zmax - zmin;
        start_x = xmin + d_xa * (y - ymin) / d_ya;
        start_z = zmin + d_za * (y - ymin) / d_ya;

//        double d_yb = ymax - ymid;
//        double d_xb = xmax - xmid;
//        double d_zb = zmax - zmid;
//        finish_x = xmid + d_xb * (y - ymid) / d_yb;
//        finish_z = xmid + d_zb * (y - ymid) / d_yb;
        double d_yb = ymid - ymin;
        double d_xb = xmid - xmin;
        double d_zb = zmid - zmin;
        finish_x = xmin + d_xb * (y - ymin) / d_yb;
        finish_z = zmin + d_zb * (y - ymin) / d_yb;

    } else {
//        std::cout << y << " equal" << std::endl;

//      Этот блок одинаков для каждой ветки
        double d_ya = ymax - ymin;
        double d_xa = xmax - xmin;
        double d_za = zmax - zmin;
        start_x = xmin + d_xa * (y - ymin) / d_ya;
        start_z = zmin + d_za * (y - ymin) / d_ya;

        finish_x = xmid;
        finish_z = zmid;
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
//        std::cout << "y" << y << "pos 5" << std::endl;
        return;
    }

    double dz = (finish_z - start_z) / (finish_x - start_x);

    for (int x = ceil(start_x - 1); x < ceil(finish_x + 1); x++) {
        if (x >= 0 && x < screen->width) {
            double z = start_z + dz * (x - start_x);

//            if (triangle->processed_color.r > 200) {
//                std::cout << "[DBG][ERROR]" << z << "\n";
//            }

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
            depth_array[i] = 1e33;
        }

        for (int i = 0; i < triangles.size(); i++) {
            process_level(triangles[i], screen, y, depth_array);
        }

        for (int x = 0; x < screen->width; x++) {
            if (not screen->change[x][y] && depth_array[x] == INT_MAX) {
                color_pixel(screen, &(screen->default_color), x, y);
            }
        }

        free(depth_array);
    }
}

void z_buffer_render(screen_t *screen, std::vector<triangle_t*> triangles)
{
    for (int y = screen->height - 1; y >= 0; y--){
        complete_process_level(screen, triangles, y);
    }

}

void threaded_z_buffer_render(screen_t *screen, const std::vector<triangle_t*> triangles)
{
    std::vector<std::thread> threads;

    auto cores_count = std::thread::hardware_concurrency(); //Узнаем к-во ядер
    int n = cores_count - 1;
    std::cout << n << std::endl;

//    std::thread t1([]() {
//        complete_process_level((screen, triangles, y));
//    });
    int y;
    for (int i = 0; i < screen->height / n + 1; i++) {
//        std::vector<std::thread> threads;

        for (int k = 0; k < n; k++) {
            y = n * i + k;
            if ( y < screen->height ) {
                threads.push_back(std::thread(complete_process_level, screen, triangles, y));
            }
        }

        for (int k = 0; k < threads.size(); k++) {
            threads[k].join();
        }

        threads.clear();
    }

}
