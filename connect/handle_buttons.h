//
// Created by Nataliia Gurova on 26.11.2022.
//

#ifndef C_VERSION_HANDLE_BUTTONS_H
#define C_VERSION_HANDLE_BUTTONS_H

enum cmd_t {
    LOAD,
    DRAW,
    ADD_LIGHT
};

int handleButton(cmd_t command);

#endif //C_VERSION_HANDLE_BUTTONS_H
