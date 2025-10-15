#define CATCH_CONFIG_RUNNER
#define CATCH_CONFIG_NO_POSIX_SIGNALS

#include "DataStructures/DSString/dsstring.h"

#include "flightplanner.h"
#include "DataStructures/catch.hpp"

// Test flag
#define TEST false

// runs test.cpp using catch2 lib
int runCatchTests(int argc, char* argv[]){
    return Catch::Session().run(argc, argv);
}

int main(int argc, char* argv[])
{
    if(TEST){
        return runCatchTests(argc, argv);
    } else{
        std::cout << "Welcome to the flight planner!" << std::endl;

        DSString dataPath = argv[1];
        DSString plansPath = argv[2];
        DSString outputPath = argv[3];

        FlightPlanner flights = FlightPlanner();

        flights.createFlightList(dataPath);
        flights.planFlights(plansPath, outputPath);

        std::cout << "You can find the data in \"" << outputPath << "\", goodbye!" << std::endl;

        return 0;
    }
}
