//
// Created by Nataliia Gurova on 26.11.2022.
//

#ifndef C_VERSION_HANDLE_BUTTONS_H
#define C_VERSION_HANDLE_BUTTONS_H

typedef enum {
    LOAD,
    DRAW,
    ADD_LIGHT
} cmd_t;

class Handler
{
public:

    int handle_button(cmd_t cmd);

private:
    int load_figure();
    int add_light_source();
};

#endif //C_VERSION_HANDLE_BUTTONS_H
