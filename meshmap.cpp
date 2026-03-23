#include "meshmap.h"

meshmap::meshmap(config& config):cfg(config){
    
    //mapのサイズ初期化
    map.resize(cfg.maxH);
    for(int i = 0; i < cfg.maxH; i++){
        map[i].resize(cfg.maxW);
    }

    initRoad();
    initRisk();
}


void meshmap::initRoad(){
    string str_buf;
    string str_conma_buf;
    ifstream ifs_csv(cfg.mapCsv);

    if(!ifs_csv.is_open()){
        cerr << "ファイルがありません" << endl;
        return;
    }

    int h = 0;
    while(getline(ifs_csv,str_buf)){
        istringstream i_stream(str_buf);
        int w = 0;
        while(getline(i_stream, str_conma_buf,',')){
            if(stoi(str_conma_buf) == 1){
                map[h][w].isRoad = true;
            }
            w++;
        }
        h++;
    }
}

void meshmap::initRisk(){
    string str_buf;
    string str_conma_buf;
    ifstream ifs_csv(cfg.somCsv);

    if(!ifs_csv.is_open()){
        cerr << cfg.somCsv <<"のファイルがありません" << endl;
        return;
    }

    int cnt = 0;
    while(getline(ifs_csv,str_buf)){
        
        if(cnt == 0){//１行目はヘッダなので飛ばす
            cnt++;
            continue;
        }

        istringstream i_stream(str_buf);
        int h;
        int w;
        int col = 0;
        double risk = 0;
        while(getline(i_stream, str_conma_buf,',')){
            if(col == 0) h = stoi(str_conma_buf);
            else if(col == 1) w = stoi(str_conma_buf);
            else risk += stod(str_conma_buf); 
            col++;
        }
        map[h][w].riskVal = risk;
    }
}