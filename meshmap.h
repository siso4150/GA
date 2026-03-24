#pragma once

#include "config.h"

#include <iostream>
#include <fstream>
#include <istream>
#include <sstream>
#include <vector>

using namespace std;

struct cell{
    bool isRoad;
    double riskVal;
};

class meshmap{
public:
    meshmap(config& config);
    void initRoad();
    void initRisk();


    cell& operator()(int y,int x){
        return map[y][x];
    }
    


private:
    config& cfg;
    vector<vector<cell>> map;
};