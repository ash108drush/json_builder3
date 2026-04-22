cmake_minimum_required(VERSION 3.16)

project(json_builder3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(json_builder3 main.cpp
    json.cpp json.h json_builder.cpp json_builder.h)

include(GNUInstallDirs)
install(TARGETS json_builder3
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
