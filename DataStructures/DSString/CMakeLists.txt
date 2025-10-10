cmake_minimum_required(VERSION 3.5)

project(DSString LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(DSString main.cpp
    dsstring.h dsstring.cpp
    catch.hpp
    test.cpp)

include(GNUInstallDirs)
install(TARGETS DSString
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
