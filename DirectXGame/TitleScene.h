#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Scene.h"

#include "fade/Fade.h"
#include "Timer.h"

class TitleScene {
public:
	/// <summary>
	/// コンストクラタ
	/// </summary>
	TitleScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TitleScene();

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

public:
	void SceneReset();

	bool isSceneEnd_ = false;

	bool IsSceneEnd() { return isSceneEnd_; }
	SceneType NextScene() { return SceneType::kGamePlay; }

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	// ワールドトランスフォーム
	WorldTransform worldTransform_;
	// ビュープロジェクション
	ViewProjection viewProjection_;

	// タイトル画像
	Sprite* textureTitle_;
	uint32_t titleHandle_;

	// 時間
	std::unique_ptr<Timer> timer_;
	const int kFrameCount = 0;
	int frameCount = kFrameCount;
	//確認フラグ
	bool st = false;

	// フェード
	std::unique_ptr<Fade> fade_;
	bool fadeTimerFlag_;
	const float kFadeTimer_ = 1.657f * 60.0f;
	float fadeTimer_ = kFadeTimer_;
};
