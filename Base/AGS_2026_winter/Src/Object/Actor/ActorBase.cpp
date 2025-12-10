#include "../../Manager/ResourceManager.h"
#include "../../Manager/SceneManager.h"
#include "ActorBase.h"
#include "../Collider/ColliderBase.h"

ActorBase::ActorBase(void)
	: 
	resMng_(ResourceManager::GetInstance()),
	scnMng_(SceneManager::GetInstance()),
	transform_()
{
	
}

ActorBase::~ActorBase(void)
{
}

void ActorBase::Init(void)
{

	// リソースロード
	InitLoad();

	// Transform初期化
	InitTransform();

	// 衝突判定の初期化
	InitCollider();

	// アニメーションの初期化
	InitAnimation();

	// 初期化後の個別処理
	InitPost();
}

void ActorBase::Draw(void)
{

	if (transform_.modelId != -1)
	{
		MV1DrawModel(transform_.modelId);
	}

#ifdef _DEBUG
	// 所有しているコライダの描画
	for (const auto& own : ownColliders_)
	{
		own.second->Draw();
	}
#endif // _DEBUG


}

void ActorBase::Release(void)
{
	transform_.Release();
	ownColliders_.clear(); 
}



const Transform& ActorBase::GetTransform(void) const
{
	return transform_;
}

const ColliderBase* ActorBase::GetOwnCollider(int key) const
{
	auto it = ownColliders_.find(key);
	if (it == ownColliders_.end()) {
		return nullptr;
	}
	return it->second.get();  // ← ここ重要！
}


void ActorBase::AddHitCollider(const ColliderBase* hitCollider)
{
	for (const auto& c : hitColliders_)
	{
		if (c == hitCollider)
		{
			return;
		}
	}
	hitColliders_.emplace_back(hitCollider);
}

void ActorBase::ClearHitCollider(void)
{
	hitColliders_.clear();
}

bool ActorBase::GetDead(void) const
{
	return isDead_;
}

void ActorBase::SetDead(bool isDie)
{
	isDead_ = isDie;
}

