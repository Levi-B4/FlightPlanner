cmake_minimum_required(VERSION 3.16)

project(FlightPlanner LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(FlightPlanner
    main.cpp
    flightplanner.h flightplanner.cpp

    DataStructures/DSAdjList/dsadjlist.h
    DataStructures/DSDoublyLL/dsdoublyll.h
    DataStructures/DSDoublyLL/dsnode.h
    DataStructures/DSStack/dsstack.h
    DataStructures/DSString/dsstring.h DataStructures/DSString/dsstring.cpp
    DataStructures/DSVector/dsvector.h
)

include(GNUInstallDirs)
install(TARGETS FlightPlanner
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
