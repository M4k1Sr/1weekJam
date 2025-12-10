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

	AudioManager::GetInstance()->LoadSceneSound(LoadScene::GAME);
	AudioManager::GetInstance()->PlayBGM(SoundID::BGM_GAME);
	AudioManager::GetInstance()->SetBgmVolume(150);
}

void GameScene::Update(void)
{
	player_->Update();
	bar_->Update();
	barUp_->Update();

}

void GameScene::Draw(void)
{
	grid_->Draw();
	stage_->Draw();
	player_->Draw();
	bar_->Draw();
	barUp_->Draw();
}

void GameScene::Release(void)
{
	player_->Release();
}
