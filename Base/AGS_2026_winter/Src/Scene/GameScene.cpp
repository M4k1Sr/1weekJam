#include "GameScene.h"
#include "../Manager/Camera.h"
#include "../Object/Grid.h"
#include "../Object/Actor/Stage.h"
#include "../Object/Actor/ActorBase.h"
#include "../Manager/SceneManager.h"
#include "../Object/Actor/Charactor/CharactorBase.h"
#include "../Object/Actor/Charactor/Player.h"
#include "../Object/Actor/Bar.h"
#include "../Object/Actor/BarUp.h"
#include "../Sound/AudioManager.h"
#include "../Manager/InputManager.h"

GameScene::GameScene(void)
	: timeLimit_(LIMIT_TIME)
	, elapsedTime_(0.0f)
	, isTimeLimitActive_(false)
{
}

GameScene::~GameScene(void)
{
}

void GameScene::Init(void)
{

	grid_ = new Grid();
	stage_ = new Stage();
	stage_->Init();
	player_ = new Player();
	player_->Init();
	bar_ = new Bar();
	bar_->Init();
	barUp_ = new BarUp();
	barUp_->Init();
	// ステージモデルのコライダーをプレイヤーに登録
	const ColliderBase* stageCollider =
		stage_->GetOwnCollider(static_cast<int>(Stage::COLLIDER_TYPE::MODEL));
	const ColliderBase* barCollider =
		bar_->GetOwnCollider(static_cast<int>(Bar::COLLIDER_TYPE::MODEL));
	const ColliderBase* barUpCollider =
		barUp_->GetOwnCollider(static_cast<int>(BarUp::COLLIDER_TYPE::MODEL));
	player_->AddHitCollider(stageCollider);
	player_->AddHitCollider(barCollider);
	player_->AddHitCollider(barUpCollider);

	sceMng_.GetCamera()->ChangeMode(Camera::MODE::FOLLOW);
	sceMng_.GetCamera()->SetFollow(&player_->GetTransform());

	StartMission(LIMIT_TIME);

	AudioManager::GetInstance()->LoadSceneSound(LoadScene::GAME);
	AudioManager::GetInstance()->PlayBGM(SoundID::BGM_GAME);
	AudioManager::GetInstance()->SetBgmVolume(150);
}

void GameScene::Update()
{
	// タイムリミット更新
	if (isTimeLimitActive_)
	{
		elapsedTime_ += SceneManager::GetInstance().GetDeltaTime();

		if (elapsedTime_ >= timeLimit_)
		{
			OnTimeUp();
		}
	}

	player_->Update();
	bar_->Update();
	barUp_->Update();

	//エネミーHP0になったらゲームクリアシーン遷移
	if (player_->GetDead())
	{
		//ゲームオーバーシーンに遷移する
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAMEOVER);
		//DxLib_End();
		//exit(0);  // ゲームを完全に終了する
	}

	if (elapsedTime_ > LIMIT_TIME)
	{
		//ゲームクリアシーンに遷移する
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_ID::GAMECLEAR);
	}
}

void GameScene::Draw(void)
{

	if (isTimeLimitActive_)
	{
		float remaining = GetRemainingTime();
		int min = static_cast<int>(remaining) / 60;
		int sec = static_cast<int>(remaining) % 60;

		// 残り時間表示
		DrawFormatString(10, 10, GetColor(255, 255, 255),
			"Time: %02d:%02d", min, sec);
	}

	stage_->Draw();
	player_->Draw();
	bar_->Draw();
	barUp_->Draw();
}

void GameScene::Release(void)
{
	player_->Release();
}

void GameScene::StartMission(float limitSeconds)
{
	timeLimit_ = limitSeconds;
	elapsedTime_ = 0.0f;
	isTimeLimitActive_ = true;
}

float GameScene::GetRemainingTime() const
{
	if (!isTimeLimitActive_) return 0.0f;
	return timeLimit_ - elapsedTime_;
}

void GameScene::OnTimeUp()
{
	isTimeLimitActive_ = false;

	// ゲームオーバー処理
	DrawString(400, 300, "こりゃだめじゃ!", GetColor(255, 0, 0));
}

