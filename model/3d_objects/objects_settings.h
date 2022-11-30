//
// Created by Nataliia Gurova on 01.12.2022.
//

#ifndef C_VERSION_OBJECTS_SETTINGS_H
#define C_VERSION_OBJECTS_SETTINGS_H

#include "cube.h"

typedef union {
    cube_t cube;
} object_setting_t;

typedef struct
{
    int type_obj;
    object_setting_t params;
} object_t;

#endif //C_VERSION_OBJECTS_SETTINGS_H
