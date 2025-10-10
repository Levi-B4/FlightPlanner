#ifndef FLIGHTPLANNER_H
#define FLIGHTPLANNER_H

#include "DataStructures/DSString/dsstring.h"
#include "DataStructures/DSVector/dsvector.h"
#include "DataStructures/DSAdjList/dsadjlist.h"

class FlightPlanner
{
public:
    struct City{
        DSString name;
        DSString airline;
        int time;
        int cost;
    };

    struct Plan{
        DSVector<City> path;
        int totalTime;
        int totalCost;
    };

    /**
     * @brief FlightPlanner - default constructor
     */
    FlightPlanner();

    /**
     * @brief createFlightList - Creates adjacency list using the data from the given file
     * @param dataFile - file containing flight data
     */
    void createFlightList(const DSString dataFile);

    /**
     * @brief planFlights - outputs the best 3 flight paths for each plan in the given plans file
     * @param plansFile - a ptah to the file containing the flight plans
     * @param outputFile - file to output the best flights
     */
    void planFlights(const DSString plansFile, const DSString outputFile);

private:
    const int LAYOVER_TIME = 43;
    const int LAYOVER_COST = 19;

    const int AIRLINE_CHANGE_TIME = 22;
    const int AIRLINE_CHANGE_COST = 0;

    DSAdjList<City> flights;

    /**
     * @brief cheapestFlightPaths - returns the cheapest 3 flight paths between the given cities
     * @param start - starting city
     * @param end - ending city
     * @return a vector containing the cheapest 3 paths
     */
    DSVector<Plan> cheapestFlightPaths(const DSString start, const DSString end);

    /**
     * @brief fastestFlightPaths - returns the fastest 3 flight paths between the given cities
     * @param start - starting city
     * @param end - ending city
     * @return a vector containing the fastest 3 paths
     */
    DSVector<Plan> fastestFlightPaths(const DSString start, const DSString end);

    /**
     * @brief writeToFile - outputs the given flight paths to the given file
     * @param paths - flight paths to output
     * @param filePath - path to the output file
     */
    void writeToFile(const DSVector<DSVector<Plan>> paths, const DSString filePath) const;
};

#endif // FLIGHTPLANNER_H
