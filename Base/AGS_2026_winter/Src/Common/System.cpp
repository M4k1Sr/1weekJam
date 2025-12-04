//#include "System.h"
//#include "../../Manager/SceneManager.h"
//
//System::System(STAGE stage)
//{
//	stage_ = stage;
//	killEnemyNum_ = 0;
//}
//
//System::~System()
//{
//}
//
//void System::Init(void)
//{
//
//	timer_ = GetNowCount();
//	killEnemyNum_ = 0;
//	coolTimeRightPos_ = 300;
//	Cr_ = GetColor(0, 255, 0);
//	stock_ = 3;
//	stockImage_ = LoadGraph((Application::PATH_IMAGE + "stock1.png").c_str());
//	stockImage2P_ = LoadGraph((Application::PATH_IMAGE + "stock2.png").c_str());
//	player1Wins_ = 0;
//	player2Wins_ = 0;
//	maxWins_ = 3;
//	winNum_ = -1;
//	isWin_ = false;
//	Winer_ = 0;
//	roundWinners_ = {
//		Winner::NONE, Winner::NONE, Winner::NONE
//	};
//}
//
//void System::ImageInit(void)
//{
//	stockImage_ = LoadGraph((Application::PATH_IMAGE + "stock1.png").c_str());
//	stockImage2P_ = LoadGraph((Application::PATH_IMAGE + "stock2.png").c_str());
//}
//
//void System::Update(void)
//{
//
//
//
//	coolTimeRightPos_++;
//
//	//クールタイムバーの色変更
//	if (300 <= coolTimeRightPos_)
//	{
//		coolTimeRightPos_ = 300;
//		Cr_ = GetColor(0, 255, 0);
//	}
//	else
//	{
//		Cr_ = GetColor(255, 0, 0);
//	}
//
//
//	if (SceneManager::playMode_ == PLAY_MODE::MULTI)
//	{
//
//		if (player1Wins_ == 2)
//		{
//			Winer_ = 0;
//			SceneManager::GetInstance().ChangeScene(
//				SceneManager::SCENE_ID::RESULT);
//			
//		}
//		else if (player2Wins_ == 2)
//		{
//			Winer_ = 1;
//			SceneManager::GetInstance().ChangeScene(
//				SceneManager::SCENE_ID::RESULT);
//		}
//	}
//}
//
//void System::Draw(STAGE stage)
//{
//	stage_ = stage;
//
//	SetFontSize(45);
//	switch (stage_)
//	{
//	case STAGE::STAGE1:
//		break;
//	case STAGE::STAGE2:
//		break;
//	case STAGE::STAGE3:
//		break;
//	case STAGE::STAGE4:
//		break;
//	case STAGE::STAGE5:
//		break;
//	case STAGE::STAGE_M1:
//
//		for (int i = 0; i < maxWins_; ++i)
//		{
//			int x = WIN_UI_START_X + (WIN_UI_SIZE + WIN_UI_MARGIN) * i;
//
//			// 枠を描画
//			DrawBox(x, WIN_UI_START_Y, x + WIN_UI_SIZE, WIN_UI_START_Y + WIN_UI_SIZE, GetColor(255, 255, 255), false);
//
//			// 枠内中央に「1」「2」「3」を描画
//			DrawFormatString(x + WIN_UI_SIZE / 3, WIN_UI_START_Y + WIN_UI_SIZE / 3-13, GetColor(255, 255, 255), "%d", i + 1);
//
//			// 勝利数に応じてアイコンを描画
//		/*	if (i < player1Wins_)
//			{
//				DrawRotaGraphF(
//					x + WIN_UI_SIZE / 2,
//					WIN_UI_START_Y + WIN_UI_SIZE / 4,
//					1.0f, 0.0, stockImage_, true);
//			}
//			if (i < player2Wins_)
//			{
//				DrawRotaGraphF(
//					x + WIN_UI_SIZE / 2,
//					WIN_UI_START_Y + WIN_UI_SIZE / 4,
//					1.0f, 0.0, stockImage2P_, true);
//			}*/
//
//			// ラウンド勝者に応じて描画
//			switch (roundWinners_[i])
//			{
//			case Winner::PLAYER1:
//				DrawGraphF(x + WIN_UI_SIZE / 2-20, WIN_UI_START_Y + WIN_UI_SIZE / 4, stockImage_, true);
//				isWin_ = false;
//				break;
//			case Winner::PLAYER2:
//				DrawGraphF(x + WIN_UI_SIZE / 2-20, WIN_UI_START_Y + WIN_UI_SIZE / 4, stockImage2P_, true);
//				isWin_ = false;
//				break;
//			case Winner::NONE:
//			default:
//				// 何も描かない
//				break;
//			}
//		}
//		
//		
//		break;
//	default:
//		break;
//	}
//
//	if (SceneManager::GetInstance().GetSceneID() == SceneManager::SCENE_ID::MISSION)
//	{
//		//残機の描画
//		DrawRotaGraphF(
//			Application::SCREEN_SIZE_X / 2 - 80,
//			Application::SCREEN_SIZE_Y /1.5,
//			2.0f, 0.0, stockImage_, true);
//  		DrawFormatString(Application::SCREEN_SIZE_X / 2, Application::SCREEN_SIZE_Y / 1.6+10, 0xffffff, "×  %d", stock_);
//	}
//	
//	
//	
//	///*DrawFormatString(0, 0, 0x000000, "P1:%d", score_.x);
//	//DrawFormatString(Application::SCREEN_SIZE_X - GetDrawStringWidth("P2:%d", 5), 0, 0x000000, "P2:%d", score_.y);*/
//	/*DrawBox(0, 0, coolTimeRightPos_, 30, Cr_, true);*/
//	
//	SetFontSize(20);
//
//}
//
//void System::Release(void)
//{
//	DeleteGraph(stockImage_);
//	DeleteGraph(stockImage2P_);
//	stockImage_ = -1;
//	stockImage2P_ = -1;
//	timer_ = 0;
//	nowCount_ = 0;
//	killEnemyNum_ = 0;
//	coolTimeRightPos_ = 0;
//	Cr_ = 0;
//	stage_ = STAGE::MAX_STAGE;
//}
//
//int System::GetTime(void)
//{
//	return nowCount_;
//}
//
//int System::GetCount(void)
//{
//	return killEnemyNum_;
//}
//
//void System::SetCount(int count)
//{
//	killEnemyNum_ += count;
//}
//
//void System::SetCoolTime(int time)
//{
//	coolTimeRightPos_ = time;
//}
//
//int System::GetCoolTime(void)
//{
//	return coolTimeRightPos_;
//}
//
//void System::SetStock(int stock)
//{
//	stock_ = stock;
//}
//
//int System::GetStock(void) const
//{
//	return stock_;
//}
//
//void System::SetWin1P(int win1p)
//{
//	player1Wins_ += win1p;
//	roundWinners_[winNum_] = Winner::PLAYER1;
//}
//
//void System::SetWin2P(int win2p)
//{
//	player2Wins_+= win2p;
//	roundWinners_[winNum_] = Winner::PLAYER2;
//}
//
//int System::GetWins(void)
//{
//	return winNum_;
//}
//
//void System::SetWins(int win)
//{
//	winNum_ += win;
//	isWin_ = true;
//}
//
//int System::GetWinNum(void)
//{
//	return Winer_;
//}
//

