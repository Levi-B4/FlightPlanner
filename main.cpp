#define CATCH_CONFIG_RUNNER
#define CATCH_CONFIG_NO_POSIX_SIGNALS

#include "DataStructures/DSString/dsstring.h"

#include "flightplanner.h"
#include "DataStructures/catch.hpp"


// runs test.cpp using catch2 lib
int runCatchTests(int argc, char* argv[]){
    return Catch::Session().run(argc, argv);
}

int main(int argc, char* argv[])
{
    if(argc == 1){
        std::cout << "Running tests..." << std::endl;
        return runCatchTests(argc, argv);
    } else if(argc != 4){
        std::cerr << "3 parameters were expected, but " << argc - 1 << " were given." << std::endl;
        return -1;
    } else {
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
