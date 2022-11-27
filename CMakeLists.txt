cmake_minimum_required(VERSION 3.23)
project(c_version)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(c_version main.cpp ui/mainwindow.cpp ui/mainwindow.h ui/mainwindow.ui connect/handle_buttons.cpp connect/handle_buttons.h server/color_t.cpp server/color_t.h server/triangle_t.cpp server/triangle_t.h server/vertex_t.cpp server/vertex_t.h server/triangle_vector.cpp server/triangle_vector.h server/screen_properties_t.cpp server/screen_properties_t.h server/screen_t.cpp server/screen_t.h server/shading.cpp server/shading.h server/z_buffer.cpp server/z_buffer.h tests/server_test.cpp tests/server_test.h tests/all_tests.h tests/model_test.cpp tests/model_test.h model/3d_objects/cube.cpp model/3d_objects/cube.h model/fractals/Params.h model/fractals/Params.cpp model/fractals/Rules.cpp model/fractals/Rules.h server/light_source.cpp server/light_source.h model/fractals/Fractal.cpp model/fractals/Fractal.h model/fractals/Link.cpp model/fractals/Link.h)
target_link_libraries(c_version
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )

