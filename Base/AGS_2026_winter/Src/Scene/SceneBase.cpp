#include "SceneBase.h"
#include "../Manager/SceneManager.h"


SceneBase::SceneBase(void)
{
}

SceneBase::~SceneBase(void)
{
}

void SceneBase::Init(void)
{


}

void SceneBase::Update(void)
{
}

void SceneBase::Draw(void)
{
}

void SceneBase::Release(void)
{
}

void SceneBase::DrawNowLoading(void)
{

	if(!isCommonInitialized_)
	{
		loadFont_ = CreateFontToHandle("Arial", LOAD_FONT_SIZE, 0, DX_FONTTYPE_ANTIALIASING);
		if (loadFont_ == -1)
		{
			loadFont_ = CreateFontToHandle("Arial", LOAD_FONT_SIZE, 0, DX_FONTTYPE_NORMAL);
		}
		if (loadFont_ == -1)
		{
			loadFont_ = CreateFontToHandle("ÇlÇr ÉSÉVÉbÉN", LOAD_FONT_SIZE, 0, DX_FONTTYPE_ANTIALIASING);
		}
		if (loadFont_ == -1)
		{
			loadFont_ = CreateFontToHandle("ÇlÇr ÉSÉVÉbÉN", LOAD_FONT_SIZE, 0, DX_FONTTYPE_NORMAL);
		}

		if (loadFont_ == -1)
		{
			printfDx("ÉtÉHÉìÉgê∂ê¨é∏îs\n");
		}
		isCommonInitialized_ = true;
	}
	

	auto time = SceneManager::GetInstance().GetTotalTime();
	int count = static_cast<int>(time / COMMA_TIME) % (COMMA_MAX_NUM + 1); 
	std::string loadStr = "Now Loading";
	loadStr.append(count, '.');

	DrawStringToHandle(LOADING_STRING_POS_X, LOADING_STRING_POS_Y, loadStr.c_str(), 0xffffff, loadFont_);
}

