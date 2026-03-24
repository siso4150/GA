#pragma once

#include "config.h"
#include "meshmap.h"
#include "Individual.h"

#include <vector>
#include <random>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

class GeneticPool{

public:
    GeneticPool(config&,meshmap&);
    void initGeneticPool();
    
    //遺伝的オペレータ
    Individual selectionTornament();
    vector<point> crossover(const Individual&,const Individual&);
    void mutation();

    void initialPopulation();//集団の初期化
    vector<point> generateRandomRoute(); //初期解の作成関数

    void evaluatePopulation();//集団の適応度を評価

    void saveBestIndividual();

    void run();//実行関数

private:
    config& cfg;
    meshmap& mp;

    vector<Individual> population;
    vector<Individual> bestIndividualHistory;//各世代の最良個体の履歴

    vector<point> getValidNeighbors(point);
    int calculateManhattanDistance(point currentPoint) {
        return std::abs(currentPoint.x - cfg.goalX) + std::abs(currentPoint.y - cfg.goalY);
    }

    void exportBestRoute(string&);

    vector<int> dx = {0,1,1,1,0,-1,-1,-1};
    vector<int> dy = {-1,-1,0,1,1,1,0,-1};

};