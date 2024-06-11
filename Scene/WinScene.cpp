#include <functional>
#include <string>
#include <fstream>

#include "Engine/GameEngine.hpp"
#include "Engine/IScene.hpp"
#include "PlayScene.hpp"
#include "Engine/AudioHelper.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "Engine/Point.hpp"
#include "WinScene.hpp"
#include "Engine/LOG.hpp"

PlayScene* WinScene::getPlayScene() {
	return dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"));
}

void WinScene::Initialize() {
	ticks = 0;
	written=false;
	int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
	int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
	int halfW = w / 2;
	int halfH = h / 2;

	AddNewObject(new Engine::Image("win/benjamin-sad.png", halfW, halfH+70, 0, 0, 0.5, 0.5));
	AddNewObject(new Engine::Image("win/square.png", halfW, halfH * 1 / 2, 0, 0, 0.5, 0.5));
	AddNewObject(new Engine::Label("You Win!", "pirulen.ttf", 48, halfW, halfH / 4 -10, 255, 255, 255, 255, 0.5, 0.5));
	Engine::ImageButton* btn;
	btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 200, halfH * 7 / 4 - 50, 400, 100);
	btn->SetOnClickCallback(std::bind(&WinScene::BackOnClick, this, 2));
	AddNewControlObject(btn);
	AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));
	AddNewObject(new Engine::Label(name, "pirulen.ttf", 30, halfW, halfH * 1 / 2, 255, 255, 255, 255, 0.5, 0.5));
	bgmId = AudioHelper::PlayAudio("win.wav");
}
void WinScene::Terminate() {
	IScene::Terminate();
	AudioHelper::StopBGM(bgmId);
}
void WinScene::Update(float deltaTime) {
	ticks += deltaTime;
	if (ticks > 4 && ticks < 100 &&
		dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"))->MapId == 2) {
		ticks = 100;
		bgmId = AudioHelper::PlayBGM("happy.ogg");
	}
}
void WinScene::BackOnClick(int stage) {
	// Change to select scene.
	Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}



void WinScene::OnKeyDown(int keyCode) {
	PlayScene* playScene = getPlayScene();
	if (playScene == nullptr) {
		//Engine::LOG(Engine::DEBUGGING) << "Error: playScene is nullptr";
		return;
	}
	//IScene::OnKeyDown(keyCode);
	//Engine::LOG(Engine::DEBUGGING) << keyCode;
	if (keyCode == ALLEGRO_KEY_ENTER) {
		if(!written) {
			std::string filename = "../Resource/scoreboard.txt";
			std::ofstream outfile(filename, std::ios::app);
			std::string score=std::to_string(playScene->GetScore());
			std::string time=playScene->GetTime();
			//Engine::LOG(Engine::DEBUGGING) << getPlayScene()->GetMoney();
			outfile << std::string(name) + " " + score + " " + time << std::endl;
			outfile.flush();
			outfile.close();
			written=true;
			name="";
		}
		Engine::GameEngine::GetInstance().ChangeScene("stage-select");
	}
	else if (keyCode == ALLEGRO_KEY_BACKSPACE) {
		name.pop_back();
		Engine::GameEngine::GetInstance().ChangeScene("win");
	}
	else {
		//if (keyCode >= 32 && keyCode <= 126) {
			//Engine::LOG(Engine::DEBUGGING) << keyCode;
			name += keyCode+'A'-1;
			Engine::GameEngine::GetInstance().ChangeScene("win");
		//}
	}
	/*
	int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
	int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
	int halfW = w / 2;
	int halfH = h / 2;
	AddNewObject(new Engine::Label(name, "pirulen.ttf", 48, halfW, halfH * 1 / 2, 255, 255, 255, 255, 0.5, 0.5));
	*/
	Engine::LOG(Engine::DEBUGGING) << name;
}

/*
void WinScene::OnKeyDown(int keyCode){
	ALLEGRO_EVENT_QUEUE *q = NULL;

		ALLEGRO_EVENT ev;
		al_wait_for_event(q, &ev);
		if (ev.type == ALLEGRO_EVENT_KEY_CHAR) {
			switch (ev.keyboard.keycode) {
				case ALLEGRO_KEY_ENTER:
					Engine::GameEngine::GetInstance().ChangeScene("stage-select");

				break;
				case ALLEGRO_KEY_BACKSPACE:
					if (name.size() > 0) {
						name.pop_back();
					}
				break;

				default:
					std::string newChar = std::to_string(ev.keyboard.unichar);
					name+=newChar;

				break;
			}
			Engine::LOG(Engine::DEBUGGING) << name;
		}

}
*/