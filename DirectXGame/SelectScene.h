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
#include "Stage.h"

class SelectScene : public StageSelect {
public:
	/// <summary>
	/// コンストクラタ
	/// </summary>
	SelectScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~SelectScene();

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

	//
	bool IsSceneEnd() { return isSceneEnd_; }
	SceneType NextScene() { return SceneType::kGamePlay; }

private:
	// 画像の初期化
	void TextureInitialize();

	// ステージ選択
	void StageSelect();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	// シーンを終わらせる変数
	bool isSceneEnd_ = false;

	// 数字の画像
	Sprite* textureNumber_[10];

	// テキストの画像
	Sprite* textureText_;

	// 矢印 カーソル
	Sprite* textureCursor_;
	Vector2 cursorPos_ = {0, 350};
	Vector2 cursorSpeed_ = {0, 0};
	int stageCount_ = 0;
	const int kMaxStage_ = 3;

	// フェード
	std::unique_ptr<Fade> fade_;
	bool fadeTimerFlag_ = false;
	const float kFadeTimer_ = 1.657f * 60.0f;
	float fadeTimer_ = kFadeTimer_;
};
