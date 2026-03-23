#include "GeneticPool.h"
#include "Individual.h"


GeneticPool::GeneticPool(config& config, meshmap& meshmap):cfg(config),mp(meshmap){
   
}


void GeneticPool::initialPopulation(){
    for(int i = 0; i < cfg.maxPopulation;i++){
        vector<point> initialRoute = generateRandomPath();
        population.push_back(Individual(initialRoute));
    }
}

Individual GeneticPool::selectionTornament(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, population.size() - 1);

    int best_index = dist(gen);
    double best_fitness = population[best_index].getFitness();

    // 指定したトーナメントサイズに達するまで比較を繰り返す
    for (int i = 1; i < cfg.tournamentSize; ++i) {
        int random_index = dist(gen);
        double current_fitness = population[random_index].getFitness();

        // 適応度が高い（値が大きい）方を勝者とする
        if (current_fitness > best_fitness) {
            best_index = random_index;
            best_fitness = current_fitness;
        }
    }
}

vector<point> GeneticPool::crossover(const Individual& parent1, const Individual& parent2){
    vector<point> commonPoint;
    vector<point> parentPath1 = parent1.getRoute();
    vector<point> parentPath2 = parent2.getRoute();

    //交叉しているところがあるか探す
    for (size_t i = 1; i < parentPath1.size() - 1; ++i) {
        for (size_t j = 1; j < parentPath2.size() - 1; ++j) {
            if (parentPath1[i].x == parentPath2[j].x && parentPath1[i].y == parentPath2[j].y) {
                commonPoint.push_back(parentPath1[i]);
            }
        }
    }

    //交叉点がないときは、親１をそのまま返す
    if(commonPoint.empty()){
        return parentPath1;
    }

    //先頭の交叉点を選択
    point crossoverPoint = commonPoint.front();
    vector<point> childPath;
    
    //親１の先頭から交叉点までコピー
    for (const auto& point : parentPath1) {
        childPath.push_back(point);
        if (point.x == crossoverPoint.x && point.y == crossoverPoint.y) {
            break;
        }
    }

    //親2の交叉点の次からゴールまでをコピー
    bool isAfterCrossover = false;
    for (const auto& point : parentPath2) {
        if (isAfterCrossover) {
            childPath.push_back(point);
        }
        if (point.x == crossoverPoint.x && point.y == crossoverPoint.y) {
            isAfterCrossover = true;
        }
    }
    
    return childPath;
}

void GeneticPool::mutation(){

}

void GeneticPool::evaluatePopulation(){
    for (auto& individual : population) {
        const vector<point>& route = individual.getRoute();
        double dist = 0.0;
        double risk = 0.0;

        //リスク、距離の計算をする
        for(point p : route){
            risk += mp(p.x,p.y).riskVal;
        }
        dist = route.size();

        double fitness = 1.0 / (dist + risk + 1.0);
        individual.setMetrics(dist,risk,fitness);
    }
}

void GeneticPool::run(){

    //初期解の作成
    initialPopulation();

    //世代ごとのループ
    for(int gen = 0; gen < cfg.maxGeneration; ++gen){

        //集団の適応度の計算
        evaluatePopulation();

        vector<Individual> nextPopulation;
        
        //次世代の生成
        while (nextPopulation.size() < cfg.maxPopulation){
            // 選択
            Individual parent1 = selectionTornament();
            Individual parent2 = selectionTornament();

            // 交叉
            vector<point> childRoute = crossover(parent1,parent2);

            // 突然変異


            //次世代プールに入れる
            nextPopulation.push_back(Individual(childRoute));
        }

    }
}

