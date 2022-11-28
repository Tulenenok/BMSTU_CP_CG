//
// Created by Ilya Malyshev on 28.11.2022.
//

#ifndef C_VERSION_CHANGE_FACTOR_T_H
#define C_VERSION_CHANGE_FACTOR_T_H

typedef struct {
    double rotate_factor[3];
    double scale_factor[3];
    int push_factor[3];
} change_factor_t;

change_factor_t *allocate_change_factor_t();
void reset_change_factor_t(change_factor_t* dst);
void free_change_factor_t(change_factor_t* dst);

void increment_scale_factor(change_factor_t *dst, double x, double y, double z);
void increment_rotate_factor(change_factor_t *dst, double x, double y, double z);
void increment_push_factor(change_factor_t *dst, int x, int y, int z);

#endif //C_VERSION_CHANGE_FACTOR_T_H
