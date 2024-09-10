#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();

	speed = 0.2f;

	chain_ = std::make_unique<Chain>();
	modelChain_.reset(Model::CreateFromOBJ("Chain", true));
	chain_->Initialize(modelChain_.get());

	spike_ = std::make_unique<Spike>();
	modelSpike1_.reset(Model::CreateFromOBJ("Spike01", true));
	modelSpike2_.reset(Model::CreateFromOBJ("Spike02", true));
	spike_->Initialize(modelSpike1_.get(), modelSpike2_.get());
	
	player_ = std::make_unique<Player>();
	modelPlayer_[0].reset(Model::CreateFromOBJ("Player01", true));
	modelPlayer_[1].reset(Model::CreateFromOBJ("Player02", true));
	modelPlayer_[2].reset(Model::CreateFromOBJ("Player03", true));
	modelPlayer_[3].reset(Model::CreateFromOBJ("Player04", true));
	modelPlayer_[4].reset(Model::CreateFromOBJ("Player05", true));
	player_->Initialize(modelPlayer_[0].get(), modelPlayer_[1].get(), modelPlayer_[2].get(), modelPlayer_[3].get(), modelPlayer_[4].get());

	// 時間
	timer_ = std::make_unique<Timer>();
	timer_->Initialize();

	// SE
	chainHandle_ = audio_->LoadWave("SE/chain.mp3");
	isSound = false;
}

void GameScene::Update() { 
	speed += 0.0005f;
	if (speed > 1.0f) {
		speed = 1.0f;
	}
	// SE
	if (isSound == false) {
		/*playChain_ = audio_->PlayWave(chainHandle_, true, 1.0);*/
		isSound = true;
	}

	chain_->Update(speed);
	spike_->Update(speed);
	player_->Update();

	// 時間更新
	timer_->Update();
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	
	chain_->Draw(viewProjection_);
	player_->Draw(viewProjection_);
	spike_->Draw(viewProjection_);
	
	/// </summary>

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	//  時間表示
	timer_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::SceneReset() { 
	timer_->Reset(); 
}
