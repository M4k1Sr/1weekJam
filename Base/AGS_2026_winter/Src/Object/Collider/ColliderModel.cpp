#include "ColliderModel.h"
#include "../Common/Transform.h"

ColliderModel::ColliderModel(TAG tag, const Transform* follow)
	:
	ColliderBase(SHAPE::MODEL, tag, follow)
{
}

ColliderModel::~ColliderModel(void)
{
}

void ColliderModel::AddExcludeFrameIds(const std::string& name)
{
	// フレーム数を取得
	int num = MV1GetFrameNum(follow_->modelId);
	for (int i = 0; i < num; i++)
	{
		// フレーム名称を取得
		std::string frameName = MV1GetFrameName(follow_->modelId, i);
		if (frameName.find(name) != std::string::npos)
		{
			// 除外フレームに追加
			excludeFrameIds_.push_back(i);
		}
	}
}

void ColliderModel::Update()
{
	// Transform のワールド行列をモデルに反映
	MV1SetMatrix(follow_->modelId, follow_->GetWorldMatrix());

	// モデルの衝突情報を最新の状態に更新
	MV1RefreshCollInfo(follow_->modelId);
}


void ColliderModel::ClearExcludeFrame(void)
{
	excludeFrameIds_.clear();
}

bool ColliderModel::IsExcludeFrame(int frameIdx) const
{
	// 除外判定
	if (std::find(
		excludeFrameIds_.begin(),
		excludeFrameIds_.end(),
		frameIdx) != excludeFrameIds_.end())
	{
		// 除外に該当する
		return true;
	}
	return false;

}
