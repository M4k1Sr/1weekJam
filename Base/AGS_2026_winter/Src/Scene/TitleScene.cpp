#include "TitleScene.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Application.h"
#include <DxLib.h>

TitleScene::TitleScene(void)
{
}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Init(void)
{
	titleImg_ = LoadGraph((Application::PATH_IMAGE + "Title2.png").c_str());
	backImg_ = LoadGraph((Application::PATH_IMAGE + "BackGraund2.png").c_str());
	pushImg_ = LoadGraph((Application::PATH_IMAGE + "Push2.png").c_str());
}

void TitleScene::Update(void)
{
	//ÉVÅ[ÉìëJà⁄
	InputManager& ins = InputManager::GetInstance();

	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAME);
	}

	
	count++;
	if (count % 70 < 30)
	{
		pushAlive_ = true;
	}
	else
	{
		pushAlive_ = false;
	}
}

void TitleScene::Draw(void)
{

	DrawGraph(0, 0,backImg_, true);
	DrawGraph(Application::SCREEN_SIZE_X/4 - 30 ,0,titleImg_,true);
	if (pushAlive_)
	{
		DrawGraph(Application::SCREEN_SIZE_X / 3 + 70, Application::SCREEN_SIZE_Y / 2 + 50, pushImg_, true);
	}
	

	
}

void TitleScene::Release(void)
{
	DeleteGraph(titleImg_);
	DeleteGraph(backImg_);
	DeleteGraph(pushImg_);
}
