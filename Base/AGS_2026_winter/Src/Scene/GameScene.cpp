#include "GameScene.h"
#include "../Manager/Camera.h"
#include "../Object/Grid.h"
#include "../Object/Actor/Stage.h"
#include "../Object/Actor/ActorBase.h"
#include "../Manager/SceneManager.h"
#include "../Object/Actor/Charactor/CharactorBase.h"
#include "../Object/Actor/Charactor/Player.h"

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
	sceMng_.GetCamera()->ChangeMode(Camera::MODE::FOLLOW);
	sceMng_.GetCamera()->SetFollow(&player_->GetTransform());
}

void GameScene::Update(void)
{
	player_->Update();
}

void GameScene::Draw(void)
{
	grid_->Draw();
	stage_->Draw();
	player_->Draw();
}

void GameScene::Release(void)
{
	player_->Release();
}
