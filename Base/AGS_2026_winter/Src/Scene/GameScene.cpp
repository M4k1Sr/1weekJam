#include "GameScene.h"
#include "../Manager/Camera.h"
#include "../Object/Grid.h"

GameScene::GameScene(void)
{
}

GameScene::~GameScene(void)
{
}

void GameScene::Init(void)
{
	camera_ = new Camera();
	camera_->Init();
	grid_ = new Grid();
}

void GameScene::Update(void)
{
}

void GameScene::Draw(void)
{
	camera_->Draw();
	grid_->Draw();
}

void GameScene::Release(void)
{
}
