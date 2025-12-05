#include "Stage.h"
#include "../../Manager/ResourceManager.h"
#include "../../Utility/AsoUtility.h"
#include "../Collider/ColliderModel.h"
#include "../Collider/ColliderBase.h"

Stage::Stage(void)
{
}

void Stage::Update(void)
{
}

void Stage::Release(void)
{
}

void Stage::InitLoad(void)
{
	transform_.SetModel(resMng_.LoadModelDuplicate(
		ResourceManager::SRC::MAIN_STAGE));
}

void Stage::InitTransform(void)
{
	transform_.scl = {1.0f,1.0f,1.0f};
	transform_.quaRot = Quaternion::Identity();
	transform_.quaRotLocal = Quaternion::Identity();

	transform_.pos = { 0.0f,-100.0f,0.0f };

	transform_.Update();
}

void Stage::InitCollider(void)
{
	transform_.Update();
	// DxLib側の衝突情報セットアップ
	MV1SetupCollInfo(transform_.modelId);
	// モデルのコライダ
	ColliderModel* colModel =
		new ColliderModel(ColliderBase::TAG::STAGE, &transform_);
	for (const std::string& name : EXCLUDE_FRAME_NAMES)
	{
		colModel->AddExcludeFrameIds(name);
	}
	ownColliders_.emplace(static_cast<int>(COLLIDER_TYPE::MODEL), colModel);
}

void Stage::InitAnimation(void)
{
}

void Stage::InitPost(void)
{

}
