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
    for(int i = 0; i < numEdges; i++){
        dataFile >> line;

        for(int j = 1; j < NUM_DELIMITERS + 1; j++){
            int index = line.findChar(DELIMITER, j) + 1;
            delimiterIndexes[j - 1] = index;
        }

        DSString node1 = line.substring(0, delimiterIndexes[0] - 1);
        DSString node2 = line.substring(delimiterIndexes[0], delimiterIndexes[1] - delimiterIndexes[0] - 1);

        int cost = stringToInt(line.substring(delimiterIndexes[1], delimiterIndexes[2] - delimiterIndexes[1] - 1));
        int time = stringToInt(line.substring(delimiterIndexes[2], delimiterIndexes[3] - delimiterIndexes[2] - 1));

        DSString airline = line.substring(delimiterIndexes[3], line.size() - delimiterIndexes[3]);

        flightMap.addEdge(node1, node2);

        flights.pushBack(Flight(node1, node2, airline, cost, time));
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
    std::ifstream plansFile(plansPath.c_str());
    std::ofstream outputFile(outputPath.c_str());

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
        DSVector<Plan> plans;
        outputFile << "Flight " << i << ": " << node1 << ", " << node2;
        if(comparer == 'T'){
            outputFile << " (Time)" << std::endl;
            plans = fastestFlightPaths(node1, node2, plans);
        } else{
            outputFile << " (Cost)" << std::endl;
            plans = cheapestFlightPaths(node1, node2, plans);
        }

        writePlans(plans, outputFile);
        outputFile << std::endl;
    }

    plansFile.close();
    outputFile.close();
}

/**
 * @brief cheapestFlightPaths - iterates through all possible paths and outputs the fastest 3
 * @param start - starting city
 * @param end - ending city
 * @return a vector containing the cheapest 3 paths
 */
DSVector<FlightPlanner::Plan> FlightPlanner::cheapestFlightPaths(const DSString start, const DSString end, DSVector<Plan>& plans, DSDoublyLL<DSString> visited)
{
    visited.pushBack(start);

    DSDoublyLL<DSString> nodes = flightMap.GetConnectedNodes(start);

    for(DSString& node : nodes){
        if(visited.contains(node)){
            continue;
        }

        if(node == end){
            if(plans.getNumIndexes() < NUM_PLANS_SAVED){
                plans.pushBack(pathToPlan(visited + end, 'C'));
            } else {
                Plan current = pathToPlan(visited + end, 'C');
                for(int i = 0; i < NUM_PLANS_SAVED; i++){
                    if(current.cost < plans[i].cost){
                        Plan temp = current;
                        current = plans[i];
                        plans[i] = temp;
                    }
                }
            }
        } else {
            fastestFlightPaths(node, end, plans, visited);
        }
    }

    return plans;
}

/**
 * @brief fastestFlightPaths - iterates through all possible paths and outputs the fastest 3
 * @param start - starting city
 * @param end - ending city
 * @return a vector containing the fastest 3 paths
 */
DSVector<FlightPlanner::Plan> FlightPlanner::fastestFlightPaths(const DSString start, const DSString end, DSVector<Plan>& plans, DSDoublyLL<DSString> visited)
{
    visited.pushBack(start);

    DSDoublyLL<DSString> nodes = flightMap.GetConnectedNodes(start);

    for(DSString& node : nodes){
        if(visited.contains(node)){
            continue;
        }

        if(node == end){
            if(plans.getNumIndexes() < NUM_PLANS_SAVED){
                plans.pushBack(pathToPlan(visited + end, 'T'));
            } else {
                Plan current = pathToPlan(visited + end, 'T');
                for(int i = 0; i < NUM_PLANS_SAVED; i++){
                    if(current.time < plans[i].time){
                        Plan temp = current;
                        current = plans[i];
                        plans[i] = temp;
                    }
                }
            }
        } else {
            fastestFlightPaths(node, end, plans, visited);
        }
    }

    return plans;
}

/**
 * @brief writeToFile - outputs the given flight paths to the given file
 * @param paths - flight paths to output
 * @param filePath - path to the output file
 */
void FlightPlanner::writePlans(const DSVector<Plan> plans, std::ofstream& outputFile) const
{
    for(int i = 0; i < plans.getNumIndexes(); i++){
        Plan currentPlan = plans[i];
        outputFile << "Path " << i << ": " << pathToString(currentPlan.path);
        outputFile << ". Time: " << currentPlan.time;
        outputFile << " Cost: " << currentPlan.cost << std::endl;
    }
}

int FlightPlanner::stringToInt(DSString str){
    int total = 0;
    for(int i = 0; i < str.size(); i++){
        char c = str[i];

        if(c < '0' or c > '9'){
            std::cout << "Throwing an error, cant convert non digit to int" << std::endl;
            return 0; //TODO: add exception
        }

        int tens = 1;
        for(int j = i; j < str.size() - 1; j++){
            tens *= 10;
        }

        total += tens * (str[i] - '0');
    }

    return total;
}

DSString FlightPlanner::pathToString(const DSDoublyLL<DSString> path) const{
    if(path.getNumIndexes() == 0){
        return "";
    }

    DSString output = "";
    DSString Start = path[0];
    DSString end = path[path.size() - 1];

    for(int i = 0; i < path.getNumIndexes() - 1; i++){
        output += path[i] += " -> ";
    }

    output += end;

    return output;
}

FlightPlanner::Plan FlightPlanner::pathToPlan(const DSDoublyLL<DSString> path, const char priority) const{
    Plan output;

    int time = 0;
    int cost = 0;

    DSString lastAirline = "";

    for(int i = 0; i < path.getNumIndexes() - 1; i++){
        DSString city1 = path[i];
        DSString city2 = path[i+1];

        DSVector<Flight> possibleFlights;

        //add looking for airline and comparing the penalty with not switching
        for(int j = 0; j < flights.getNumIndexes(); j++){
            Flight flight = flights[j];
            if(flight.city1 == city1 && flight.city2 == city2 ||
                    flight.city1 == city2 && flight.city2 == city1){
                possibleFlights.pushBack(flight);
                break;
            }
        }

        Flight chosenPath;
        chosenPath = minPath(possibleFlights, lastAirline, priority);

        lastAirline = chosenPath.airline;

        time += chosenPath.time;
        cost += chosenPath.cost;
    }

    // layover addition
    time += (path.getNumIndexes() - 2) * LAYOVER_TIME;
    cost += (path.getNumIndexes() - 2) * LAYOVER_COST;

    output = Plan(path, cost, time);

    return output;
}

FlightPlanner::Flight FlightPlanner::minPath(DSVector<Flight> testFlights, DSString airline, char comparer) const{
    Flight output;
    int min = -1;
    for(int i = 0; i < testFlights.getNumIndexes(); i++){
        Flight current = testFlights[i];
        Flight currentTotal = current;
        if(airline == "" || airline == current.airline){
            currentTotal.time = current.time;
            currentTotal.cost = current.cost;
        } else {
            currentTotal.time = current.time + AIRLINE_CHANGE_TIME;
            currentTotal.cost = current.cost + AIRLINE_CHANGE_COST;
        }

        int compareInt = -1;
        if(comparer == 'T'){
            compareInt = currentTotal.time;
        } else {
            compareInt = currentTotal.cost;
        }

        if(compareInt < min || min == -1){
            min = compareInt;
            output = currentTotal;
        }
    }

    return output;
}
