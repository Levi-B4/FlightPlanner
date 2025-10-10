#include "DataStructures/DSString/dsstring.h"

#include "flightplanner.h"

int main(int argc, char* argv[])
{
    DSString dataPath = argv[1];
    DSString plansPath = argv[2];
    DSString outputPath = argv[3];

    FlightPlanner flights = FlightPlanner();

    flights.createFlightList(dataPath);
    flights.planFlights(plansPath, outputPath);

    return 0;
}
