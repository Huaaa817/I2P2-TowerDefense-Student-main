#ifndef SCOREBOARDSCENE_H
#define SCOREBOARDSCENE_H

#include <allegro5/allegro_audio.h>
#include <memory>
#include <map>
#include "Engine/IScene.hpp"

class ScoreBoardScene final : public Engine::IScene {
public:
    int cnt=0;
    int currentPage=0;
    //std::multimap <int, std::string> rank;
    std::multimap <int, std::tuple<std::string, std::string>>rank;

    void Initialize() override;
    void BackOnClick(int stage);
    void prevOnClick(int stage);
    void nextOnClick(int stage);
    void ReadScoreBoard();
    void ShowPage(std::map <int, std::string> rank, int currentPage) ;
};
#endif //SCOREBOARDSCENE_H
