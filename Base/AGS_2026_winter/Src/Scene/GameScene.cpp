#include "GameScene.h"
#include "../Manager/Camera.h"
#include "../Object/Grid.h"
#include "../Object/Actor/Stage.h"
#include "../Object/Actor/ActorBase.h"
#include "../Manager/SceneManager.h"

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
	sceMng_.GetCamera()->ChangeMode(Camera::MODE::FOLLOW);
	
}

void GameScene::Update(void)
{
}

void GameScene::Draw(void)
{
	grid_->Draw();
	stage_->Draw();
}

void GameScene::Release(void)
{
}
