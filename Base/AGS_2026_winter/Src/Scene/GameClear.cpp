#include <DxLib.h>
#include "../Application.h"
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Utility/AsoUtility.h"
#include "GameClear.h"

GameClear::GameClear(void)
{
}

GameClear::~GameClear(void)
{
}

void GameClear::Init(void)
{
	imgGameClear_ = LoadGraph((Application::PATH_IMAGE + "YouWin.png").c_str());
	imgBack_ = LoadGraph((Application::PATH_IMAGE + "WinBack.png").c_str());


	// カメラ設定を追加
	VECTOR cameraPos = VGet(0.0f, 100.0f, -300.0f);  // カメラ位置
	VECTOR targetPos = VGet(0.0f, 50.0f, 0.0f);       // 注視点
	SetCameraPositionAndTarget_UpVecY(cameraPos, targetPos);
}

void GameClear::Update(void)
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
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::TITLE);
	}
}

void GameClear::Draw(void)
{
	DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y / 2, 1.0f, 0.0f, imgBack_, true);

	DrawRotaGraph(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y / 2, 1.0f, 0.0f, imgGameClear_, true);

}

void GameClear::Release(void)
{
	DeleteGraph(imgGameClear_);
	DeleteGraph(imgBack_);

}