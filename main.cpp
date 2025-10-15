#include "DataStructures/DSString/dsstring.h"

#include "flightplanner.h"

int main(int argc, char* argv[])
{
    if(argc != 4){
        std::cout << "Error: There were " << argc << " arguments given instead of 4." << std::endl;
        return -1;
    }

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
