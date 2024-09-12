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
#include "Reaf.h"

#include <Stage.h>
#include "BackGround.h"
#include "fade/Fade.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene : public StageSelect {

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

	void ChackAllCollisions();

public:

	void SceneReset();

	bool isSceneEnd_ = false;

	bool IsSceneEnd() { return isSceneEnd_; }
	SceneType NextScene() { return SceneType::kResult; }

	bool isSceneEnd2_ = false;

	bool IsSceneEnd2() { return isSceneEnd2_; }
	SceneType NextScene2() { return SceneType::kTitle; }

	void BGMReset();

	void BGMStop();

private:
	// 画像の初期化
	void TextureInitialize();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	// ワールドトランスフォーム
	WorldTransform worldTransform_;
	// ビュープロジェクション
	ViewProjection viewProjection_;

	// スピードアップの画像
	Sprite* textureSpeedUP_;
	bool isSpeedUP;

	// スピードダウンの画像
	Sprite* textureSpeedDown_;
	bool isSpeedDown;

	// ゲームオーバーの画像
	Sprite* textureGameOver_;

	// Speed画像の表示時間
	float speedUPTextureTimer;
	float speedDownTextureTimer;

	float speed;

	std::unique_ptr<Model> modelChain_;
	std::unique_ptr<Chain> chain_;

	std::unique_ptr<Model> modelSpike1_;
	std::unique_ptr<Model> modelSpike2_;
	std::unique_ptr<Model> modelSpike3_;
	std::unique_ptr<Model> modelSpike4_;
	std::unique_ptr<Model> modelGoalObj_;
	std::unique_ptr<Spike> spike_;

	std::unique_ptr<Model> modelReaf_;
	std::unique_ptr<Reaf> reaf_;

	Vector3 spikePos[22];
	float hit[22];
	float playerRadius = 2.0f;
	float spikeRadius = 5.0f;
	float spikeCollisionRadius = 9.0f;
	bool gameOverFlag = false;
	bool grazeFlag = false;

	bool coolTimeDrawFlag = false;
	int coolTimeDrawCount = 0;
	bool hitCoolTimeFlag = false;
	int hitCoolTime = 0;

	std::unique_ptr<Model> modelPlayer_[5];
	std::unique_ptr<Player> player_;

	// 背景3Dモデル
	std::unique_ptr<Model> backGroundModel_ = nullptr;
	// 背景
	std::unique_ptr<BackGround> backGround_;

	// 時間
	std::unique_ptr<Timer> timer_;

	// ハートの画像
	Sprite* textureHeart_[3];
	Vector2 heartSize_;

	// BGM
	uint32_t gameBGMHandle_;
	uint32_t playGameBGM_;
	bool isGameBGM_;

	// SE
	uint32_t chainHandle_;
	uint32_t playChain_;
	bool isChain_;
	bool isSound;

	uint32_t damageHandle_;
	uint32_t playDamage_;
	bool isDamage_;
	bool isHit;

	uint32_t speedUPHandle_;
	uint32_t playSpeedUP_;
	bool isSpeedUP_;

	// フェード
	std::unique_ptr<Fade> fade_;
	bool fadeTimerFlag_;
	const float kFadeTimer_ = 1.657f * 60.0f;
	float fadeTimer_ = kFadeTimer_;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
