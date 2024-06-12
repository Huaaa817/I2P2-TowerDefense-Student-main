

#ifndef SEEDSTORESCENE_H
#define SEEDSTORESCENE_H
#include "Engine/IScene.hpp"

class Plant;
namespace Engine {
    class Group;
    class Image;
    class Label;
    class Sprite;
}  // namespace Engine

class SeedStoreScene final : public Engine::IScene {
protected:
    int money1, money2;
public:
    void Initialize() override;
    void NextOnClick(int stage);
    void BuyOnClick(int player, int money);
    //void OnMouseDown(int button, int mx, int my) override;
    //void OnMouseUp(int button, int mx, int my) override;
    void ReadMoney();//get money

};

#endif //SEEDSTORESCENE_H