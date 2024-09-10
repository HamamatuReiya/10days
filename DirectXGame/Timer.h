#pragma once
#include "Sprite.h"

class Timer {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// リセット
	/// </summary>
	void Reset();

private:
	// 数字の画像の読み込み
	uint32_t numHandle_[10];
	//:画像
	uint32_t colonHandle_;

	//フレームカウント
	int frameCount = 0;

	// 数字の画像
	//秒
	Sprite* textureTimerSeconds_[2];
	//分
	Sprite* textureTimerMinutes_[2];
	//コロン
	Sprite* textureColon;

	int numSeconds[2];
	int numMinutes[2];
};
