#ifndef FLIGHTPLANNER_H
#define FLIGHTPLANNER_H

#include "DataStructures/DSString/dsstring.h"
#include "DataStructures/DSVector/dsvector.h"
#include "DataStructures/DSAdjList/dsadjlist.h"

class FlightPlanner
{
public:
    struct Flight{
        Flight(){}
        Flight(DSString city1, DSString city2, DSString airline, int cost, int time) :
            city1(city1), city2(city2), airline(airline), cost(cost), time(time){}

        DSString city1;
        DSString city2;
        DSString airline;
        int cost;
        int time;
    };

    struct Plan{
        Plan(){};

        Plan(DSDoublyLL<DSString> path, int cost, int time) :
            path(path), cost(cost), time(time){}

        DSDoublyLL<DSString> path;
        int cost;
        int time;
    };

    /**
     * @brief FlightPlanner - default constructor
     */
    FlightPlanner();

    /**
     * @brief createFlightList - Creates adjacency list using the data from the given file
     * @param dataPath - file containing flight data
     */
    void createFlightList(const DSString dataPath);

    /**
     * @brief planFlights - outputs the best 3 flight paths for each plan in the given plans file
     * @param plansPath- a ptah to the file containing the flight plans
     * @param outputPath - file to output the best flights
     */
    void planFlights(const DSString plansPath, const DSString outputPath);

private:
    const int LAYOVER_TIME = 43;
    const int LAYOVER_COST = 19;

    const int AIRLINE_CHANGE_TIME = 22;
    const int AIRLINE_CHANGE_COST = 0;

    const int NUM_PLANS_SAVED = 3;

    DSAdjList<DSString> flightMap;
    DSDoublyLL<Flight> flights;

    /**
     * @brief cheapestFlightPaths - returns the cheapest 3 flight paths between the given cities
     * @param start - starting city
     * @param end - ending city
     * @return a vector containing the cheapest 3 paths
     */
    DSVector<Plan> cheapestFlightPaths(const DSString start, const DSString end, DSVector<Plan>& plans, DSDoublyLL<DSString> visited = {});

    /**
     * @brief fastestFlightPaths - returns the fastest 3 flight paths between the given cities
     * @param start - starting city
     * @param end - ending city
     * @return a vector containing the fastest 3 paths
     */
    DSVector<Plan> fastestFlightPaths(const DSString start, const DSString end, DSVector<Plan>& plans, DSDoublyLL<DSString> visited = {});

    /**
     * @brief writeToFile - outputs the given flight paths to the given file
     * @param paths - flight paths to output
     * @param filePath - path to the output file
     */
    void writePlans(const DSVector<Plan> paths, std::ofstream& outputFile) const;

    int stringToInt(DSString str);

    Flight minPath(DSVector<Flight> flights, DSString airline, char comparer) const;

    DSString pathToString(const DSDoublyLL<DSString> path) const;

    Plan pathToPlan(const DSDoublyLL<DSString> path, const char priority) const;
};

#endif // FLIGHTPLANNER_H
