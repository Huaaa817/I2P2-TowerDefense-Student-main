#ifndef WINSCENE_HPP
#define WINSCENE_HPP
#include <string>
#include <allegro5/allegro_audio.h>
#include "Engine/IScene.hpp"
#include "Engine/Sprite.hpp"


class PlayScene;
class WinScene final : public Engine::IScene {
private:
	float ticks;
	ALLEGRO_SAMPLE_ID bgmId;
protected:
	PlayScene* getPlayScene();
public:
	explicit WinScene() = default;
	void Initialize() override;
	void Terminate() override;
	void Update(float deltaTime) override;
	void BackOnClick(int stage);
	void OnKeyDown(int keyCode) override;
	//virtual void OnKeyDown(int keycode) override;
	std::string name="";
	bool written=false;
};

#endif // WINSCENE_HPP
