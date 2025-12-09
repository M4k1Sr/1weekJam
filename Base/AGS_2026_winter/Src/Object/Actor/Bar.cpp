#include "Bar.h"
#include "../../Manager/ResourceManager.h"
#include "../../Utility/AsoUtility.h"
#include "../Collider/ColliderModel.h"
#include "../Collider/ColliderBase.h"

Bar::Bar(void)
{
	speed_ = 180.0f;
}

void Bar::Update(void)
{
	const float rotSpeed = AsoUtility::Deg2RadF(95.5f);
	speed_ -= rotSpeed;

	transform_.quaRotLocal = Quaternion::Mult(
		transform_.quaRot,
		Quaternion::Euler(0, AsoUtility::Deg2RadF(speed_), 0));

	transform_.Update();

	// ★★★ ここでコライダーを更新する（超重要） ★★★
	for (auto& col : ownColliders_)
	{
		col.second->Update();   // ColliderModel なら内部で MV1RefreshCollInfo などを行う
	}
}



void Bar::Release(void)
{
}

void Bar::InitLoad(void)
{
	transform_.SetModel(resMng_.LoadModelDuplicate(
		ResourceManager::SRC::BarDown));
}

void Bar::InitTransform(void)
{
	static float SIZE = 0.1f;
	transform_.scl = { SIZE,SIZE,SIZE };
	transform_.quaRot = Quaternion::Identity();
	transform_.quaRotLocal = Quaternion::Identity();

	transform_.pos = { 0.0f,-80.0f,0.0f };

	transform_.Update();

}

void Bar::InitCollider(void)
{
	transform_.Update();
	// DxLib側の衝突情報セットアップ
	MV1SetupCollInfo(transform_.modelId);
	// モデルのコライダ
	ColliderModel* colModel =
		new ColliderModel(ColliderBase::TAG::STAGE, &transform_);
	ownColliders_.emplace(static_cast<int>(COLLIDER_TYPE::MODEL), colModel);
}

void Bar::InitAnimation(void)
{
}

void Bar::InitPost(void)
{
}
