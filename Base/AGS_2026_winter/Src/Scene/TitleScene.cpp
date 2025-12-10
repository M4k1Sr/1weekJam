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
	auto& ins = InputManager::GetInstance();

	// シーン遷移の入力判定
	bool isSceneChangeInput = false;

	// キーボード操作
	bool isSceneChangeKeyboard = ins.IsTrgDown(KEY_INPUT_SPACE);

	// ゲームパッド操作
	bool isSceneChangePad = false;
	if (GetJoypadNum() > 0)
	{
		// 接続されているゲームパッド１の情報を取得
		InputManager::JOYPAD_IN_STATE padState =
			ins.GetJPadInputState(InputManager::JOYPAD_NO::PAD1);

		// どのボタンでシーン遷移するか選んで（例：STARTボタン）		
		isSceneChangePad = ins.IsPadBtnNew(InputManager::JOYPAD_NO::PAD1,
			InputManager::JOYPAD_BTN::DOWN);  // Aボタン（DOWN）
	}

	// どちらかが押されたらシーン遷移
	if (isSceneChangeKeyboard || isSceneChangePad)
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
