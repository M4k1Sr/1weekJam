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
	static float SIZE = 0.4f;
	transform_.scl = { SIZE,SIZE,SIZE };
	transform_.quaRot = Quaternion::Identity();
	transform_.quaRotLocal = Quaternion::Identity();

	transform_.pos = { 0.0f,-100.0f,0.0f };

	transform_.Update();
}

void Stage::InitCollider(void)
{

	// モデルのコライダ
	ColliderModel* colModel =
		new ColliderModel(ColliderBase::TAG::STAGE, &transform_);

	// 対象フレーム設定
	for (const std::string& name : TARGET_FRAME_NAMES)
	{
		colModel->AddTargetFrameIds(name);
	}

	ownColliders_.emplace(static_cast<int>(COLLIDER_TYPE::MODEL), colModel);
	// DxLib側の衝突情報セットアップ
	MV1SetupCollInfo(transform_.modelId);
	transform_.Update();
}

void Stage::InitAnimation(void)
{
}

void Stage::InitPost(void)
{

}
