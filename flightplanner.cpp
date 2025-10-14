#include "flightplanner.h"

#include <fstream>

#include <iostream>

/**
 * @brief FlightPlanner - default constructor
 */
FlightPlanner::FlightPlanner() {}

/**
 * @brief createFlightList - Creates adjacency list using the data from the given file
 * @param dataPath - file containing flight data
 */
void FlightPlanner::createFlightList(const DSString dataPath)
{
    std::ifstream dataFile(dataPath.c_str());

    DSString line;
    int numEdges;

    dataFile >> numEdges;
    dataFile.get();

    const char DELIMITER = '|';
    const int NUM_DELIMITERS = 4;
    int delimiterIndexes[NUM_DELIMITERS];
    Plan plan;
    for(int i = 0; i < numEdges; i++){
        dataFile >> line;

        for(int j = 1; j < NUM_DELIMITERS + 1; j++){
            int index = line.findChar(DELIMITER, j) + 1;
            delimiterIndexes[j - 1] = index;
        }

        struct PH{
            PH(){};

            PH(DSString node1, DSString node2, int cost, int time) :
                node1(node1), node2(node2), cost(cost), time(time){}

            DSString node1 = "";
            DSString node2 = "";

            int cost = 0;
            int time = 0;
        };

        DSVector<PH> weights;

        DSString node1 = line.substring(0, delimiterIndexes[0] - 1);
        DSString node2 = line.substring(delimiterIndexes[0], delimiterIndexes[1] - delimiterIndexes[0] - 1);

        int cost = stringToInt(line.substring(delimiterIndexes[1], delimiterIndexes[2] - delimiterIndexes[1] - 1));

        int time = stringToInt(line.substring(delimiterIndexes[2], delimiterIndexes[3] - delimiterIndexes[2] - 1));

        DSString airline = line.substring(delimiterIndexes[3], line.size() - delimiterIndexes[3]);

        flights.addEdge(node1, node2);

        weights.pushBack(PH(node1, node2, cost, time));
    }

    dataFile.close();
}

/**
 * @brief planFlights - iterate through the given file and find the fastest or cheapest 3 fligt paths for each plan
 * @param plansPath - a ptah to the file containing the flight plans
 * @param outputPath - file to output the best flights
 */
void FlightPlanner::planFlights(const DSString plansPath, const DSString outputPath)
{
    // read plansFile
    std::ifstream plansFile(plansPath.c_str());

    int numPlans;

    plansFile >> numPlans;
    plansFile.get();


    const char DELIMITER = '|';
    const int NUM_DELIMITERS = 2;
    int delimiterIndexes[NUM_DELIMITERS];
    DSString line;
    DSVector<Plan> plans;
    for(int i = 0; i < numPlans; i++){
        plansFile >> line;

        for(int j = 1; j < NUM_DELIMITERS + 1; j++){
            int index = line.findChar(DELIMITER, j) + 1;
            delimiterIndexes[j - 1] = index;
        }

        DSString node1 = line.substring(0, delimiterIndexes[0] - 1);
        DSString node2 = line.substring(delimiterIndexes[0], delimiterIndexes[1] - delimiterIndexes[0] - 1);
        char comparer = line[line.size() - 1];

        Plan current;
        if(comparer == 'T'){
            fastestFlightPaths(node1, node2);
        } else{
            cheapestFlightPaths(node1, node2);
        }
    }
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

    std::cout << "Finding cheapest paths between " << start << " and " << end << std::endl;

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

    std::cout << "Finding fastest paths between " << start << " and " << end << std::endl;

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

int FlightPlanner::stringToInt(DSString str){
    int total = 0;
    for(int i = str.size() - 1; i >= 0; i--){
        char c = str[i];

        if(c < '0' or c > '9'){
            std::cout << "Throwing an error, cant convert non digit to int" << std::endl;
            return 0; //TODO: add exception
        }

        int tens = 1;
        for(int j = 0; j < i; j++){
            tens *= 10;
        }

        total += tens * (str[i] - '0');
    }

    return total;
}
