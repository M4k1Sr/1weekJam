#include "BarUp.h"
#include "../../Manager/ResourceManager.h"
#include "../../Utility/AsoUtility.h"
#include "../Collider/ColliderModel.h"
#include "../Collider/ColliderBase.h"

BarUp::BarUp(void)
{
	speed_ = 180.0f;
}

void BarUp::Update(void)
{
	const float rotSpeed = AsoUtility::Deg2RadF(-45.5f);
	speed_ -= rotSpeed;

	transform_.quaRotLocal = Quaternion::Mult(transform_.quaRot,
		Quaternion::Euler(0, AsoUtility::Deg2RadF(speed_), AsoUtility::Deg2RadF(0)));
	transform_.Update();
}

void BarUp::Release(void)
{
}

void BarUp::InitLoad(void)
{
	transform_.SetModel(resMng_.LoadModelDuplicate(
		ResourceManager::SRC::BarDown));
}

void BarUp::InitTransform(void)
{
	static float SIZE = 0.1f;
	transform_.scl = { SIZE,SIZE,SIZE };
	transform_.quaRot = Quaternion::Identity();
	transform_.quaRotLocal = Quaternion::Identity();

	transform_.pos = { 0.0f,200.0f,0.0f };

	transform_.Update();

}

void BarUp::InitCollider(void)
{
	transform_.Update();
	// DxLib側の衝突情報セットアップ
	MV1SetupCollInfo(transform_.modelId);
	// モデルのコライダ
	ColliderModel* colModel =
		new ColliderModel(ColliderBase::TAG::STAGE, &transform_);
	ownColliders_.emplace(static_cast<int>(COLLIDER_TYPE::MODEL), colModel);
}

void BarUp::InitAnimation(void)
{
}

void BarUp::InitPost(void)
{
}
