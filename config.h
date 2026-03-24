#pragma once

#include <string>

using namespace std;
struct config{

    int maxPopulation;

    int maxGeneration;

    int tournamentSize;

    double mutationP;

    int maxH;
    int maxW;

    int startX;
    int startY;
    int goalX;
    int goalY;

    string mapCsv;//道路のcsv
    string somCsv;//SOMのcsv
};