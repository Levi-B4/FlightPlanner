#include "flightplanner.h"

/**
 * @brief FlightPlanner - default constructor
 */
FlightPlanner::FlightPlanner() {}

/**
 * @brief createFlightList - Creates adjacency list using the data from the given file
 * @param dataFile - file containing flight data
 */
void FlightPlanner::createFlightList(const DSString dataFile)
{
    //set flights adjacency list
}

/**
 * @brief planFlights - iterate through the given file and find the fastest or cheapest 3 fligt paths for each plan
 * @param plansFile - a ptah to the file containing the flight plans
 * @param outputFile - file to output the best flights
 */
void FlightPlanner::planFlights(const DSString plansFile, const DSString outputFile)
{
    // read plansFile

    // call cheapestFlightPaths or fastestFlightPaths for each line

    // call writeToFile
}

/**
 * @brief cheapestFlightPaths - iterates through all possible paths and outputs the fastest 3
 * @param start - starting city
 * @param end - ending city
 * @return a vector containing the cheapest 3 paths
 */
DSVector<FlightPlanner::Plan> FlightPlanner::cheapestFlightPaths(const DSString start, const DSString end)
{
    // try all paths between start and end and output a list of the top 3 cheapest fligts

    return DSVector<Plan>();
}

/**
 * @brief fastestFlightPaths - iterates through all possible paths and outputs the fastest 3
 * @param start - starting city
 * @param end - ending city
 * @return a vector containing the fastest 3 paths
 */
DSVector<FlightPlanner::Plan> FlightPlanner::fastestFlightPaths(const DSString start, const DSString end)
{
    // try all paths between start and end and output a list of the top 3 fastest fligts

    return DSVector<Plan>();
}

/**
 * @brief writeToFile - outputs the given flight paths to the given file
 * @param paths - flight paths to output
 * @param filePath - path to the output file
 */
void FlightPlanner::writeToFile(const DSVector<DSVector<Plan>> plans, const DSString path) const
{
    // write plans to file
}
