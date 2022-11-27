//
// Created by Nataliia Gurova on 26.11.2022.
//

#include <cmath>

#include "shading.h"
#include "color_t.h"
#include "light_source.h"

// У треугольника должен быть определен центр
void linear_shading(triangle_t *triangle, std::vector<light_source_t*> &light_sources) {

    if (light_sources.empty()) {
        triangle->processed_color.r = triangle->initial_color.r;
        triangle->processed_color.g = triangle->initial_color.g;
        triangle->processed_color.b = triangle->initial_color.b;
    }

    double sum_k = 0.0;
    int count = 0;

    double px = triangle->perpendicular[0];
    double py = triangle->perpendicular[1];
    double pz = triangle->perpendicular[2];
    double plength = sqrt(px * px + py * py + pz * pz);
    if (plength > EPS) {
        px /= plength;
        py /= plength;
        pz /= plength;
    }

    double x, y, z, length, k;

    for (int ls_ind = 0; ls_ind < light_sources.size(); ls_ind++) {
        x = light_sources[ls_ind]->vertex[0] - triangle->center[0];
        y = light_sources[ls_ind]->vertex[1] - triangle->center[1];
        z = light_sources[ls_ind]->vertex[2] - triangle->center[2];

        length = sqrt(x * x + y * y + z * z);

        if (length > EPS) {
            x /= length;
            y /= length;
            z /= length;
        }

        k = px * x + py * y + pz * z;

        if (k > 0) {
            sum_k += px * x + py * y + pz * z;
            count++;
        }
    }

    if (count > 0) {
        sum_k /= count;
    }

    int r = (int) (triangle->initial_color.r * sum_k);
    int g = (int) (triangle->initial_color.g * sum_k);
    int b = (int) (triangle->initial_color.b * sum_k);

    r = r < 0 ? 0 : r > 255 ? 255 : r;
    g = g < 0 ? 0 : g > 255 ? 255 : g;
    b = b < 0 ? 0 : b > 255 ? 255 : b;

    triangle->processed_color.r = r;
    triangle->processed_color.g = g;
    triangle->processed_color.b = b;
}
