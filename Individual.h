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
    Individual();
    Individual(vector<point> route);

    void setMetrics(double d, double r, double f){dist = d; risk = r; fitness = f;};
    double getFitness() const {return fitness;};
    double getDist() const {return dist;};
    double getRisk() const {return risk;};

    const vector<point>& getRoute() const {return route;};

private:
    vector<point> route;
    double risk;
    double dist;
    double fitness;

};