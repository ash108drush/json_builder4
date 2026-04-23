cmake_minimum_required(VERSION 3.16)

project(json_builder4 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(json_builder4 main.cpp)

include(GNUInstallDirs)
install(TARGETS json_builder4
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
