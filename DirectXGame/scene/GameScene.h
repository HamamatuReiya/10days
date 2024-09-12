#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Chain.h"
#include "Spike.h"
#include "Scene.h"
#include "Player.h"
#include "Timer.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

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
	SceneType NextScene() { return SceneType::kResult; }

	void BGMReset();

	void BGMStop();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	// ワールドトランスフォーム
	WorldTransform worldTransform_;
	// ビュープロジェクション
	ViewProjection viewProjection_;

	float speed;

	std::unique_ptr<Model> modelChain_;
	std::unique_ptr<Chain> chain_;

	std::unique_ptr<Model> modelSpike1_;
	std::unique_ptr<Model> modelSpike2_;
	std::unique_ptr<Spike> spike_;

	std::unique_ptr<Model> modelPlayer_[5];
	std::unique_ptr<Player> player_;

	// 時間
	std::unique_ptr<Timer> timer_;

	// BGM
	uint32_t gameBGMHandle_;
	uint32_t playGameBGM_;
	bool isGameBGM_;

	// SE
	uint32_t chainHandle_;
	uint32_t playChain_;
	bool isChain_;
	bool isSound;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
