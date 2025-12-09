#include "BarUp.h"
#include "../../Manager/ResourceManager.h"
#include "../../Utility/AsoUtility.h"
#include "../Collider/ColliderModel.h"
#include "../Collider/ColliderBase.h"

BarUp::BarUp(void)
{
	time_ = 0;
	TimeState(TIME_STATE::START);

}

void BarUp::Update(void)
{
	TimeState(timeState_);

	const float rotSpeed = AsoUtility::Deg2RadF(-65.5f);
	speed_ -= rotSpeed;

	transform_.quaRotLocal = Quaternion::Mult(transform_.quaRot,
		Quaternion::Euler(0, AsoUtility::Deg2RadF(speed_), AsoUtility::Deg2RadF(0)));
	transform_.Update();

	// ★★★ ここでコライダーを更新する（超重要） ★★★
	for (auto& col : ownColliders_)
	{
		col.second->Update();   // ColliderModel なら内部で MV1RefreshCollInfo などを行う
	}

	time_++;

}

void BarUp::Release(void)
{
}

void BarUp::TimeState(TIME_STATE timeState)
{
	timeState_ = timeState;
	switch (timeState_)
	{
	case BarUp::TIME_STATE::START:
		UpdateStart();
		break;
	case BarUp::TIME_STATE::HALF:
		UpdateHalf();
		break;
	case BarUp::TIME_STATE::FINAL:
		UpdateFinal();
		break;
	}
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

	transform_.pos = { 0.0f,120.0f,0.0f };

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

void BarUp::UpdateStart(void)
{
	const float rotSpeed = AsoUtility::Deg2RadF(50.0f);
	speed_ -= rotSpeed;

	if (time_ > 1000) { timeState_ = TIME_STATE::HALF; time_ = 0; }
}

void BarUp::UpdateHalf(void)
{
	const float rotSpeed = AsoUtility::Deg2RadF(200.0f);
	speed_ += rotSpeed;

	if (time_ > 900) { timeState_ = TIME_STATE::FINAL; time_ = 0; }

}

void BarUp::UpdateFinal(void)
{
	const float rotSpeed = AsoUtility::Deg2RadF(30.0f);
	speed_ -= rotSpeed;

	if (time_ > 1500) { timeState_ = TIME_STATE::START; time_ = 0; }
}
