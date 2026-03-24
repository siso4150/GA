#include "GeneticPool.h"
#include "Individual.h"
#include "meshmap.h"
#include "config.h"
#include "json.hpp"

#include <iostream>

using namespace std;
using json = nlohmann::json;

int main(int argc, char* argv[]){
    
    //ハイパーパラメータのロード
    config config;
    string config_file = "config_json/sample.json";

    if(argc >= 2){//コマンドラインにjsonが指定されている時
        config_file = argv[1];
    }

    //ファイルの読み込み
    ifstream f(config_file);
    if (!f.is_open()) {
        cerr << "Error: Failed to open " << config_file << endl;
        return 1;
    }

    cout << config_file << "を読み込み";
    //jsonのパース
    json data = json::parse(f);

    //各データの代入
    config.maxPopulation = data["maxPopulation"].get<int>();
    config.maxGeneration = data["maxGeneration"].get<int>();
    config.tournamentSize = data["tornamentSize"].get<int>();
    config.mutationP = data["mutationP"].get<double>();

    config.maxH = data["maxH"].get<int>();
    config.maxW = data["maxW"].get<int>();
    
    config.startX = data["startX"].get<int>();
    config.startY = data["startY"].get<int>();
    config.goalX = data["goalX"].get<int>();
    config.goalY = data["goalY"].get<int>();

    config.mapCsv = data["mapCsv"].get<string>();
    config.somCsv = data["somCsv"].get<string>();

    cout  << "、設定完了" << endl;

    meshmap meshmap(config);
    cout << "meshmapクラスの初期化完了" << endl;

    GeneticPool gPool(config,meshmap);
    cout << "GeneticPoolクラスの初期化完了" << endl;

    cout << "初期化終了,実行可能" << endl;
    
    gPool.run();

    return 0;

}