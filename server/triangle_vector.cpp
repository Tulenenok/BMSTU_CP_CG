//
// Created by Nataliia Gurova on 26.11.2022.
//

#include <vector>

#include "triangle_vector.h"
#include "triangle_t.h"

void group_reset_processed_vertexes(std::vector<triangle_t*> triangles) {
    for (int i = 0; i < triangles.size(); i++) {
        reset_processed_vertexes(triangles[i]);
    }
}

void group_reset_processed_color(std::vector<triangle_t*> triangles) {
    for (int i = 0; i < triangles.size(); i++) {
        reset_processed_color(triangles[i]);
    }
}

void group_center(std::vector<triangle_t*> triangles, vertex_t center) {
    int mins[3];
    int maxs[3];

    if (triangles.empty()) {
        for (int i = 0; i < 3; i++) {
            mins[i] = 0;
            maxs[i] = 0;
        }
    } else {
        for (int i = 0; i < 3; i++) {
            mins[i] = triangles[0]->processed_vertexes[0][i];
            maxs[i] = triangles[0]->processed_vertexes[0][i];
        }
    }

    for (int i = 0; i < triangles.size(); i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                mins[k] = mins[k] > triangles[i]->processed_vertexes[j][k] ? triangles[i]->processed_vertexes[j][k] : mins[k];
                maxs[k] = maxs[k] < triangles[i]->processed_vertexes[j][k] ? triangles[i]->processed_vertexes[j][k] : maxs[k];
            }
        }
    }

    for (int i = 0; i < 3; i++) {
        center[i] = (mins[i] + maxs[i]) / 2;
    }
}

void group_push(std::vector<triangle_t*> triangles, int dx, int dy, int dz) {
    for (int i = 0; i < triangles.size(); i++) {
        push(triangles[i], dx, dy, dz);
    }
}

void group_scale(std::vector<triangle_t*> triangles, vertex_t center, double dx, double dy, double dz) {
    for (int i = 0; i < triangles.size(); i++) {
        scale(triangles[i], center, dx, dy, dz);
    }
}

void group_rotate(std::vector<triangle_t*> triangles, vertex_t center, double dx, double dy, double dz) {
    for (int i = 0; i < triangles.size(); i++) {
        rotate(triangles[i], center, dx, dy, dz);
    }
}

