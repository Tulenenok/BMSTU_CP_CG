#ifndef C_VERSION_PRESET_SETTINGS_H
#define C_VERSION_PRESET_SETTINGS_H

#include "Params.h"
#include "../../server/color_t.h"
#include "consts.h"

typedef struct{
    Params params;
    color_t color;
    int count_cubes;
} preset_setting_t;

preset_setting_t get_spiral();
preset_setting_t get_fern();
preset_setting_t get_ivy();
preset_setting_t get_verbena();

#endif //C_VERSION_PRESET_SETTINGS_H
