#pragma once

#include "config.h"
#include "meshmap.h"
#include "Individual.h"

#include <vector>
#include <random>

using namespace std;

class GeneticPool{

public:
    GeneticPool(config&,meshmap&);
    void initGeneticPool();
    Individual selectionTornament();
    vector<point> crossover(const Individual&,const Individual&);
    void mutation();

    void initialPopulation();//集団の初期化

    vector<point> generateRandomPath(); //初期解の作成関数

    void evaluatePopulation();//集団の適応度を評価

    void run();//実行関数

private:
    config& cfg;
    meshmap& mp;

    vector<Individual> population;

};