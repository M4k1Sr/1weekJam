//#pragma once
//#include "../../framework.h"
//#include "../../Application.h"
//
//
//class System
//{
//public:
//
//
//	// 勝利数UIの開始位置X座標（画面中央から少し左）
//	static constexpr int WIN_UI_START_X = Application::SCREEN_SIZE_X / 2 - 100;
//
//	// 勝利数UIの開始位置Y座標（画面下から100ピクセル上）
//	static constexpr int WIN_UI_START_Y = Application::SCREEN_SIZE_Y - 100;
//
//	// 勝利数UIの枠サイズ（正方形の1辺の長さ）
//	static constexpr int WIN_UI_SIZE = 60;
//
//	// 勝利数UIの枠間の余白（左右の間隔）
//	static constexpr int WIN_UI_MARGIN = 10;
//
//	// 勝利数の最大値（3本先取なので3）
//	static constexpr int MAX_WINS = 3;
//
//	enum class Winner
//	{
//		NONE,
//		PLAYER1,
//		PLAYER2,
//	};
//
//	std::array<Winner, MAX_WINS> roundWinners_ = {
//		Winner::NONE, Winner::NONE, Winner::NONE
//	};
//
//	System(STAGE stage);
//	~System();
//	void Init(void);
//	void ImageInit(void);
//	void Update(void);
//	void Draw(STAGE stage);
//	void Release(void);
//	//タイマーのゲッター
//	int GetTime(void);
//	//エネミー倒した数のゲッター
//	int GetCount(void);
//	//エネミー倒した数のセッター
//	void SetCount(int count);
//	//追尾弾のクールタイムのセッター
//	void SetCoolTime(int time);
//	//追尾弾のクールタイムのゲッター
//	int GetCoolTime(void);
//	//残機のセッター
//	void SetStock(int stock);
//	//残機のゲッター
//	int GetStock(void) const;
//	//勝利数のセッター
//	void SetWin1P(int win1p);
//	void SetWin2P(int win2p);
//	//勝利数のゲッターセッター
//	int GetWins(void);
//	void SetWins(int win);
//	//勝者のげったー
//	int GetWinNum(void);
//
//private:
//
//	int timer_;			//起動時の時間
//	int nowCount_;		//現在の時間
//	int killEnemyNum_;				//エネミーの倒した数
//	int coolTimeRightPos_;			//クールタイムバーの右端の座標
//	int stock_;			//残機
//	int stockImage_;		//残機の画像ID
//	int stockImage2P_;		//残機の画像ID
//	int player1Wins_;
//	int player2Wins_;
//	int maxWins_;
//	int winNum_;
//	bool isWin_;
//	int Winer_;
//
//	STAGE stage_;		//ステージ情報
//
//	unsigned int Cr_;				//クールタイムバーの色
//
//};

