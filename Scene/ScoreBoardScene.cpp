#include <allegro5/allegro_audio.h>
#include <memory>
#include "ScoreBoardScene.h"
#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>
#include <fstream>
#include <map>
#include <sstream>
#include <Engine/LOG.hpp>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "PlayScene.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "UI/Component/Slider.hpp"
#include "Scene/StartScene.h"

void ScoreBoardScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    rank.clear();
    ReadScoreBoard();
    Engine::ImageButton* btn;

    AddNewObject(new Engine::Label("ScoreBoard", "pirulen.ttf", 70, halfW, halfH / 6 + 30, 90, 250, 140, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 200, halfH * 3 / 2 - 50,
                                  400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreBoardScene::BackOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("back", "pirulen.ttf", 48, halfW, halfH * 3 / 2, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW * 1 / 3 - 200, halfH * 3 / 2 - 50,
                                  400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreBoardScene::prevOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("prev page", "pirulen.ttf", 48, halfW * 1 / 3, halfH * 3 / 2, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW * 5 / 3 - 200, halfH * 3 / 2 - 50,
                                  400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreBoardScene::nextOnClick, this, 1));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("next page", "pirulen.ttf", 48, halfW * 5 / 3, halfH * 3 / 2, 0, 0, 0, 255, 0.5, 0.5));

}

void ScoreBoardScene::BackOnClick(int stage) {
    Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}

void ScoreBoardScene::prevOnClick(int stage) {
    if(cnt>=8) cnt-=8;
    Engine::GameEngine::GetInstance().ChangeScene("scoreboard-scene");
}

void ScoreBoardScene::nextOnClick(int stage) {
    if(cnt+8<rank.size()) cnt+=8;
    Engine::GameEngine::GetInstance().ChangeScene("scoreboard-scene");

}

void ScoreBoardScene::ReadScoreBoard() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;

    std::string filename = std::string("../Resource/scoreboard.txt");

    std::string name, date;
    int score;
    //std::string datetime;
    std::ifstream fin(filename);
    std::string line;

    while (std::getline(fin, line)) {
        std::stringstream ss(line);
        ss >> name >> score;
        std::getline(ss >> std::ws, date);
        rank.insert({score, std::make_tuple(name, date)});
        //Engine::LOG(Engine::DEBUGGING) << date;
    }
    fin.close();
    int i=1;
    for(auto it = rank.rbegin(); it != rank.rend(); it++){

        if(i==9 || cnt+i-1>=rank.size()) break;
        auto tmp=it;
        for(int j=0; j<cnt; j++) tmp=next(tmp);
        std::string output_name = std::string(std::get<0>(tmp->second));
        std::string output_score = std::to_string(tmp->first);
        std::string output_date = std::string(std::get<1>(tmp->second));
        //Engine::LOG(Engine::DEBUGGING) << output_date;
        AddNewObject(new Engine::Label( output_name,"pirulen.ttf", 40, halfW, halfH / 6 + 50 + 50*i, 180, 255, 180, 255, 0.5, 0.5));
        AddNewObject(new Engine::Label( output_score,"pirulen.ttf", 40, halfW+250, halfH / 6 + 50 + 50*i, 180, 255, 180, 255, 0.5, 0.5));
        AddNewObject(new Engine::Label( output_date,"pirulen.ttf", 15, halfW-330, halfH / 6 + 50 + 50*i, 180, 255, 180, 255, 0.5, 0.5));
        i++;
    }

    /*
    while (fin >> name >> score) {
        //Engine::LOG(Engine::DEBUGGING) << date;
        rank.insert({score, name});
    }
    fin.close();
    //Engine::LOG(Engine::DEBUGGING) << rank.size();
    int i=1;
    for(auto it = rank.rbegin(); it != rank.rend(); it++){

        if(i==9 || cnt+i-1>=rank.size()) break;
        auto tmp=it;
        for(int j=0; j<cnt; j++) tmp=next(tmp);
        std::string output_name = std::string(tmp->second);
        std::string output_score = std::to_string(tmp->first);
        AddNewObject(new Engine::Label( output_name,"pirulen.ttf", 40, halfW, halfH / 6 + 50 + 50*i, 180, 255, 180, 255, 0.5, 0.5));
        AddNewObject(new Engine::Label( output_score,"pirulen.ttf", 40, halfW+250, halfH / 6 + 50 + 50*i, 180, 255, 180, 255, 0.5, 0.5));
        i++;

    }
*/
/*
    for(auto it = rank.rbegin(); it != rank.rend(); it++) {

        if(i%9==0) {
            i=1;
        }

        std::string output_name = std::string(it->second);
        std::string output_score = std::to_string(it->first);
        AddNewObject(new Engine::Label( output_name,"pirulen.ttf", 40, halfW, halfH / 6 + 50 + 50*i, 180, 255, 180, 255, 0.5, 0.5));
        AddNewObject(new Engine::Label( output_score,"pirulen.ttf", 40, halfW+250, halfH / 6 + 50 + 50*i, 180, 255, 180, 255, 0.5, 0.5));
        i++;
    }
*/
}

