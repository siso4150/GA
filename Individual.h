#pragma once

#include "config.h"
#include "meshmap.h"

#include <vector>

using namespace std;
struct point{
    int x;
    int y;
};

class Individual{

public:
    Individual(config&);
    Individual(config&,vector<point> route);

    void setMetrics(double d, double r, double f){dist = d; risk = r; fitness = f;};
    double getFitness() const {return fitness;};

    const vector<point>& getRoute(){return route;};

private:
    config& cfg;

    vector<point> route;
    double risk;
    double dist;
    double fitness;

};