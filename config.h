#pragma once

struct config{
    double crossoverP;
    
    double muationP;

    int maxPopulation;

    int maxGeneration;

    int tournamentSize;

    int maxH;
    int maxW;

    string mapCsv;//道路のcsv
    string somCsv;//SOMのcsv

    


};