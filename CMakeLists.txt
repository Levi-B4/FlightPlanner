cmake_minimum_required(VERSION 3.16)

project(FlightPlanner LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# input files
set (input01 "data/sample01-flight-data.txt")
set (input02 "data/sample01-req-flights.txt")
set (input03 "data/sample02-flight-data.txt")
set (input04 "data/sample02-req-flights.txt")
set (test01  "data/sample01-output-target.txt")
set (test02  "data/sample02-output-target.txt")

# Copy data files to build dir
foreach(file IN LISTS input01 input02 input03 input04 test01 test02)
    configure_file(${file} ${file} COPYONLY)
endforeach()

add_executable(FlightPlanner
    main.cpp
    flightplanner.h flightplanner.cpp

    DataStructures/DSAdjList/dsadjlist.h
    DataStructures/DSDoublyLL/dsdoublyll.h
    DataStructures/DSDoublyLL/dsnode.h
    DataStructures/DSStack/dsstack.h
    DataStructures/DSString/dsstring.h DataStructures/DSString/dsstring.cpp
    DataStructures/DSVector/dsvector.h

    DataStructures/catch.hpp DataStructures/test.cpp
)

include(GNUInstallDirs)
install(TARGETS FlightPlanner
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
