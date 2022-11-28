//
// Created by Ilya Malyshev on 28.11.2022.
//

#include <cstdlib>
#include "change_factor_t.h"

change_factor_t *allocate_change_factor_t() {
    auto res = (change_factor_t*) calloc(1, sizeof(change_factor_t));

    reset_change_factor_t(res);

    return res;
}

void reset_change_factor_t(change_factor_t* dst) {
    for (int i = 0; i < 3; i++) {
        dst->push_factor[i] = 0;
        dst->rotate_factor[i] = 0.0;
        dst->scale_factor[i] = 1;
    }
}

void free_change_factor_t(change_factor_t* dst) {
    free(dst);
}

void increment_scale_factor(change_factor_t *dst, double x, double y, double z) {
    dst->scale_factor[0] *= x;
    dst->scale_factor[1] *= y;
    dst->scale_factor[2] *= z;
}

void increment_rotate_factor(change_factor_t *dst, double x, double y, double z) {
    dst->rotate_factor[0] += x;
    dst->rotate_factor[1] += y;
    dst->rotate_factor[2] += z;
}

void increment_push_factor(change_factor_t *dst, int x, int y, int z) {
    dst->push_factor[0] += x;
    dst->push_factor[1] += y;
    dst->push_factor[2] += z;
}
