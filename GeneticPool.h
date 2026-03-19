#pragma once

#include "Individual.h"

#include <vector>

using namespace std;

class GeneticPool{

public:
    GeneticPool();
    void selection();
    void crossover();
    void mutation();

private:
    vector<Individual> gPool;



};