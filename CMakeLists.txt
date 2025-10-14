cmake_minimum_required(VERSION 3.16)

project(FlightPlanner LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# input files
set (input01 "data/sample01-flight-data.txt")
set (input02 "data/sample01-req-flights.txt")

# Copy data files to build dir
foreach(file IN LISTS input01 input02)
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
)

include(GNUInstallDirs)
install(TARGETS FlightPlanner
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
