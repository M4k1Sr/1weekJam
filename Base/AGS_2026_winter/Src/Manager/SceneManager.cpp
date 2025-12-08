#include "../Common/Fader.h"
#include "SceneManager.h"
#include "../Common/System.h"
#include "../Scene/SceneBase.h"
#include "../Scene/GameScene.h"
#include "../Scene/TitleScene.h"


SceneManager* SceneManager::instance_ = nullptr;

void SceneManager::CreateInstance()
{
	if (instance_ == nullptr)
	{
		instance_ = new SceneManager();
	}
	instance_->Init();
}

SceneManager& SceneManager::GetInstance(void)
{
	return *instance_;
}

void SceneManager::Init(void)
{

	sceneId_ = SCENE_ID::TITLE;
	waitSceneId_ = SCENE_ID::NONE;
	isLoading_ = false;
	loadingTime_ = 0.0f;

	fader_ = new Fader();
	fader_->Init();

	//system_ = new System(selectedStage_);
	//system_->Init();

	//3Dの初期化設定
	Init3D();

	isSceneChanging_ = false;

	// デルタタイム
	preTime_ = std::chrono::system_clock::now();

	// 初期シーンの設定
	DoChangeScene(SCENE_ID::TITLE);

}

void SceneManager::Update(void)
{

	if (scene_ == nullptr)
	{
		return;
	}

	// デルタタイム
	auto nowTime = std::chrono::system_clock::now();
	deltaTime_ = static_cast<float>(
		std::chrono::duration_cast<std::chrono::nanoseconds>(nowTime - preTime_).count() / 1000000000.0);
	preTime_ = nowTime;

	// フェード更新
	fader_->Update();
	if (isSceneChanging_)
	{
		// フェード状態の切替処理
		Fade();
	}
	else
	{
		// 各シーンの更新処理
		scene_->Update();
	}

}

void SceneManager::Draw(void)
{

	// 描画先グラフィック領域の指定
	// (３Ｄ描画で使用するカメラの設定などがリセットされる)
	SetDrawScreen(DX_SCREEN_BACK);

	// 画面を初期化
	ClearDrawScreen();
	
	if (scene_)
	{
		scene_->Draw();
	}

	fader_->Draw();  // フェードを先に描画

	if (isLoading_ && scene_)
	{
		scene_->DrawNowLoading();  // ローディング文字を最後に描画（最前面に表示される）
	}

}

void SceneManager::Release(void)
{

	// シーンの解放
	scene_->Release();
	delete scene_;

	/*system_->Release();
	delete system_;*/

	// フェード機能の解放
	delete fader_;

}

void SceneManager::Init3D(void)
{

	// 背景色設定
	SetBackgroundColor(0, 139, 139);
	// Zバッファを有効にする
	SetUseZBuffer3D(true);
	// Zバッファへの書き込みを有効にする
	SetWriteZBuffer3D(true);
	// バックカリングを有効にする
	SetUseBackCulling(true);
	// ライトの設定
	SetUseLighting(false);
	// ライトの設定
	ChangeLightTypeDir({ 0.5f, -0.5f, 0.5f });


}

void SceneManager::ChangeScene(SCENE_ID nextId)
{

	// フェード処理が終わってからシーンを変える場合もあるため、
	// 遷移先シーンをメンバ変数に保持
	waitSceneId_ = nextId;

	// フェードアウト(暗転)を開始する
	fader_->SetFade(Fader::STATE::FADE_OUT, 0x000000);
	isSceneChanging_ = true;

}

SceneManager::SCENE_ID SceneManager::GetSceneID(void)
{
	return sceneId_;
}

float SceneManager::GetDeltaTime(void) const
{
	/*return 1.0f / 60.0f;*/
	return deltaTime_;
}

STAGE SceneManager::GetNextStage(STAGE current)
{
	int next = static_cast<int>(current) + 1;
	if (next >= static_cast<int>(STAGE::MAX_STAGE))
	{
		return current; // または STAGE::STAGE1 など
	}
	return static_cast<STAGE>(next);
}

SceneManager::SceneManager(void)
{

	sceneId_ = SCENE_ID::NONE;
	waitSceneId_ = SCENE_ID::NONE;

	scene_ = nullptr;
	fader_ = nullptr;

	isSceneChanging_ = false;

	// デルタタイム
	deltaTime_ = 1.0f / 60.0f;

}

SceneManager::~SceneManager(void)
{
	delete instance_;
}

void SceneManager::ResetDeltaTime(void)
{
	deltaTime_ = 0.016f;
	preTime_ = std::chrono::system_clock::now();
}

void SceneManager::DoChangeScene(SCENE_ID sceneId)
{

	// シーンを変更する
	sceneId_ = sceneId;

	// 現在のシーンを解放
	if (scene_ != nullptr)
	{
		scene_->Release();
		delete scene_;
	}

	switch (sceneId_)
	{
	case SCENE_ID::TITLE:
		scene_ = new TitleScene();
		break;
	case SCENE_ID::GAME:
		scene_ = new GameScene();
		break;
	}

	// 各シーンの初期化
	scene_->Init();
	if (sceneId_ == SCENE_ID::TITLE)
	{
		/*system_->Init();*/
	}

	ResetDeltaTime();

	waitSceneId_ = SCENE_ID::NONE;

}

void SceneManager::Fade(void)
{
	Fader::STATE fState = fader_->GetState();

	switch (fState)
	{
	case Fader::STATE::FADE_IN:
		if (fader_->IsEnd())
		{
			fader_->SetFade(Fader::STATE::NONE, 0x000000);
			isSceneChanging_ = false;
		}
		break;

	case Fader::STATE::FADE_OUT:
		if (fader_->IsEnd())
		{
			if (!isLoading_)
			{
				// ローディング開始
				isLoading_ = true;
				loadingTime_ = 0.0f;
			}
			else
			{
				// ローディング待機中
				loadingTime_ += deltaTime_;

				if (loadingTime_ > LOADING_WAIT)
				{
					// 実際のシーン遷移
					DoChangeScene(waitSceneId_);

					// 明転開始
					fader_->SetFade(Fader::STATE::FADE_IN, 0x000000);
					isLoading_ = false;
				}
			}
		}
		break;
	}
}


float SceneManager::GetTotalTime(void) const
{
	return loadingTime_;
}

System* SceneManager::GetSystem(void) const
{
	return system_;
}
