#include "GeneticPool.h"
#include "Individual.h"


GeneticPool::GeneticPool(config& config, meshmap& meshmap):cfg(config),mp(meshmap){
   
}


void GeneticPool::initialPopulation(){
    for(int i = 0; i < cfg.maxPopulation;i++){
        vector<point> initialRoute = generateRandomPath();
        population.push_back(Individual(cfg,initialRoute));
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

void GeneticPool::crossover(){

}

void GeneticPool::mutation(){

}

void GeneticPool::evaluatePopulation(){
    for (auto& individual : population) {
        const vector<point>& path = individual.getRoute();
        double dist = 0.0;
        double risk = 0.0;

        //計算をする

        //

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
        while (nextPopulation.size() < cfg. maxPopulation){
            // 選択
            Individual parent1 = selectionTornament();
            Individual parent2 = selectionTornament();

        }

    }
}

