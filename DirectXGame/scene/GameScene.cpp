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
	modelSpike3_.reset(Model::CreateFromOBJ("FakeSpike", true));
	modelSpike4_.reset(Model::CreateFromOBJ("FakeSpikeBody", true));
	modelGoalObj_.reset(Model::CreateFromOBJ("GoalObj", true));
	spike_->Initialize(modelSpike1_.get(), modelSpike2_.get(), modelSpike3_.get(), modelGoalObj_.get(), modelSpike4_.get());
	
	player_ = std::make_unique<Player>();
	modelPlayer_[0].reset(Model::CreateFromOBJ("Player01", true));
	modelPlayer_[1].reset(Model::CreateFromOBJ("Player02", true));
	modelPlayer_[2].reset(Model::CreateFromOBJ("Player03", true));
	modelPlayer_[3].reset(Model::CreateFromOBJ("Player04", true));
	modelPlayer_[4].reset(Model::CreateFromOBJ("Player05", true));
	player_->Initialize(modelPlayer_[0].get(), modelPlayer_[1].get(), modelPlayer_[2].get(), modelPlayer_[3].get(), modelPlayer_[4].get());

	// テクスチャの初期化
	TextureInitialize();

	// 背景の生成
	backGround_ = std::make_unique<BackGround>();
	// 3Dモデルの生成
	backGroundModel_.reset(Model::CreateFromOBJ("background", true));
	// 背景の初期化
	backGround_->Initialize(backGroundModel_.get());

	reaf_=std::make_unique<Reaf>();
	modelReaf_.reset(Model::CreateFromOBJ("Leaf", true));
	reaf_->Initialize(modelReaf_.get());

	// 時間
	timer_ = std::make_unique<Timer>();
	timer_->Initialize();

	// フェードの生成
	fade_ = std::make_unique<Fade>();
	// フェードの初期化
	fade_->Initialize();
	// フェードインの開始
	fade_->FadeInStart();

	// BGM
	gameBGMHandle_ = audio_->LoadWave("BGM/gameplay.mp3");

	// SE
	chainHandle_ = audio_->LoadWave("SE/chain.mp3");
	isSound = false;

	damageHandle_ = audio_->LoadWave("SE/damage.mp3");
	isHit = false;

	speedUPHandle_ = audio_->LoadWave("SE/SpeedUP.mp3");

	// 画像の表示時間
	speedUPTextureTimer = 120.0f;
	speedDownTextureTimer = 120.0f;
}

void GameScene::Update() { 
	switch (stageNo) {
	case Stage::kStage1:
		if (gameOverFlag == false) {
			chain_->Update(speed);

			player_->Update();
			if (spike_->GetCollisionFlag() == true) {
				ChackAllCollisions();
			}
			// 時間更新
			timer_->Update();
			// ステージ１の関数
			spike_->Update(speed);
		}
		break;
	case Stage::kStage2:
		if (gameOverFlag == false) {
			chain_->Update(speed);
			player_->Wind();
			player_->Update();
			if (spike_->GetCollisionFlag() == true) {
				ChackAllCollisions();
			}
			// 時間更新
			timer_->Update();
			// ステージ2の関数
			if (player_->GetWindFlag() == true) {
				if (player_->GetWindPattern() == 0) {
					reaf_->SetRightFlag(true);

				} else if (player_->GetWindPattern() == 1) {
					reaf_->SetLeftFlag(true);
				}
				reaf_->Update();
			} else {
				reaf_->SetLeftFlag(false);
				reaf_->SetRightFlag(false);
			}
			reaf_->UpdateMat();
			spike_->Update2(speed);
			
		}
		break;
	case Stage::kStage3:
		if (gameOverFlag == false) {
			chain_->Update(speed);

			player_->Update();
			if (spike_->GetCollisionFlag() == true) {
				ChackAllCollisions();
			}
			// 時間更新
			timer_->Update();
			// ステージ3の関数
			spike_->Update3(speed);
		}
		break;
	default:
		break;
	}

	//speed += 0.0005f;
	if (speed > 1.0f) {
		speed = 1.0f;
	}
	// SE
	if (isSound == false) {
		//playChain_ = audio_->PlayWave(chainHandle_, true, 1.0);
		isSound = true;
	}

	if (isHit == true) {
		//isDamage_ = audio_->PlayWave(damageHandle_, false, 1.0);
		isHit = false;
	}
	

	// シーン移動
#ifdef _DEBUG
	if (input_->TriggerKey(DIK_SPACE)) {
		if (gameOverFlag == false) {
			isSceneEnd_ = true;
		} 
	}
#endif // DEBUG

	if (input_->TriggerKey(DIK_SPACE) && gameOverFlag == true) {
		// フェードアウトスタート
		fadeTimerFlag_ = true;
		fade_->FadeOutStart();
	}
	// フェード開始
	if (fadeTimerFlag_ == true) {
		fadeTimer_--;
	}
	if (fadeTimer_ <= 0) {
		isSceneEnd2_ = true;
	}

	//体力の表示の処理
	for (int i = 0; i < player_->GetLife(); i++) {
		heartSize_ = textureHeart_[i]->GetSize();
		heartSize_ = {50.0f, 50.0f};
		textureHeart_[i]->SetSize(heartSize_);
	}

	
	

	if (isSpeedUP == true) {
		speedUPTextureTimer -= 1.0f;
		if (speedUPTextureTimer < 0.0f) {
			speedUPTextureTimer = 120.0f;
			isSpeedUP = false;
		}
	} 
	if (isSpeedDown == true) {
		speedDownTextureTimer -= 1.0f;
		if (speedDownTextureTimer < 0.0f) {
			speedDownTextureTimer = 120.0f;
			isSpeedDown = false;
		}
	}

	// 背景更新
	backGround_->Update();
	// フェードの更新
	fade_->Update();
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
	/// </summary>

	chain_->Draw(viewProjection_);
	if (coolTimeDrawCount <= 5) {
		player_->Draw(viewProjection_);
	}
	spike_->Draw(viewProjection_);
	
	// 背景描画
	backGround_->Draw(viewProjection_);

	if (spike_->GetStage2Flag() == true) {
		reaf_->Draw(viewProjection_);
	}
	
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

	//体力の表示
	for (int i = 0; i < player_->GetLife(); i++) {
		textureHeart_[i]->Draw();
	}

	// スピードアップ
	if (isSpeedUP == true) {
		textureSpeedUP_->Draw();
	}
	// スピードダウン
	if (isSpeedDown == true) {
		textureSpeedDown_->Draw();
	}
	// ゲームオーバー
	if (gameOverFlag == true) {
		textureGameOver_->Draw();
	}

	// フェードの描画
	fade_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::SceneReset() { 
	player_->Reset();
	chain_->Reset();
	spike_->Reset();
	reaf_->Reset();
	timer_->Reset(); 
	speed = 0.2f;
	isSceneEnd_ = false;
	isSceneEnd2_ = false;
	//audio_->StopWave(playChain_);
	isSound = false;
	speedUPTextureTimer = 120.0f;
	speedDownTextureTimer = 120.0f;
	isSpeedUP = false;
	isSpeedDown = false;

	fade_->FadeReset();
	fadeTimerFlag_ = false;
	fadeTimer_ = kFadeTimer_;

	 gameOverFlag = false;
	 grazeFlag = false;

	 coolTimeDrawFlag = false;
	coolTimeDrawCount = 0;
	 hitCoolTimeFlag = false;
	hitCoolTime = 0;

}

void GameScene::BGMReset() { 
	//playGameBGM_ = audio_->PlayWave(gameBGMHandle_, true, 0.5);
}

void GameScene::BGMStop() { 
	//audio_->StopWave(playGameBGM_);
}

void GameScene::TextureInitialize() {
	uint32_t heartHandle[3];
	for (int i = 0; i < player_->GetLife(); i++) {
		heartHandle[i] = TextureManager::Load("heart.png");
		textureHeart_[i] = Sprite::Create(heartHandle[i], {i * 55.0f + 10, 10.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	}

	// スピードアップの画像
	uint32_t SpeedUpHandle;
	SpeedUpHandle = TextureManager::Load("SpeedUP.png");

	textureSpeedUP_ = Sprite::Create(SpeedUpHandle, {500.0f, 50.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});

	// スピードダウンの画像
	uint32_t SpeedDownHandle;
	SpeedDownHandle = TextureManager::Load("SpeedDown.png");

	textureSpeedDown_ = Sprite::Create(SpeedDownHandle, {500.0f, 100.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});

	// ゲームオーバーの画像
	uint32_t GameOverHandle;
	GameOverHandle = TextureManager::Load("GameOver.png");

	textureGameOver_ = Sprite::Create(GameOverHandle, {500.0f, 400.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
}

void GameScene::ChackAllCollisions() { 
	Vector3 playerPos = player_->GetWorldPosition();
	spikePos[0] = spike_->GetWorldPosition1();
	spikePos[1] = spike_->GetWorldPosition2();
	spikePos[2] = spike_->GetWorldPosition3();
	spikePos[3] = spike_->GetWorldPosition4();
	spikePos[4] = spike_->GetWorldPosition5();
	spikePos[5] = spike_->GetWorldPosition6();
	spikePos[6] = spike_->GetWorldPosition7();
	spikePos[7] = spike_->GetWorldPosition8();
	spikePos[8] = spike_->GetWorldPosition9();
	spikePos[9] = spike_->GetWorldPosition10();
	spikePos[10] = spike_->GetWorldPosition11();
	spikePos[11] = spike_->GetWorldPosition12();
	spikePos[12] = spike_->GetWorldPosition13();
	spikePos[13] = spike_->GetWorldPosition14();
	spikePos[14] = spike_->GetWorldPosition15();
	spikePos[15] = spike_->GetWorldPosition16();
	spikePos[16] = spike_->GetWorldPosition17();
	spikePos[17] = spike_->GetWorldPosition18();
	spikePos[18] = spike_->GetWorldPosition19();
	spikePos[19] = spike_->GetWorldPosition20();
	spikePos[20] = spike_->GetWorldPosition21();
	spikePos[21] = spike_->GetWorldPosition22();

	Vector3 goalPos = spike_->GetWorldPosition99();

	for (int i = 0; i < 22; i++) {
		hit[i] = (spikePos[i].x - playerPos.x) * (spikePos[i].x - playerPos.x) + (spikePos[i].y - playerPos.y) * (spikePos[i].y - playerPos.y) + (spikePos[i].z - playerPos.z) * (spikePos[i].z - playerPos.z);
	}

	float radius = (playerRadius + spikeRadius) * (playerRadius + spikeRadius);
	float graze = (playerRadius + spikeCollisionRadius) * (playerRadius + spikeCollisionRadius);

	if (hitCoolTimeFlag == true) {
		hitCoolTime++;
		coolTimeDrawCount++;
		if (coolTimeDrawCount >= 10) {
			coolTimeDrawCount = 0;
		}
		speed = 0.2f;
		isSpeedDown = true;
		if (hitCoolTime >= 120) {
			hitCoolTime = 0;
			hitCoolTimeFlag = false;
			coolTimeDrawFlag = false;
		}
	}

	if (player_->GetLife() < 0) {
		gameOverFlag = true;
	}

	if (playerPos.y <= goalPos.y+10.0f) {
		//フェードアウトスタート
		fadeTimerFlag_ = true;
		fade_->FadeOutStart();
	}
	//フェード開始
	if (fadeTimerFlag_ == true) {
		fadeTimer_--;
	}
	if (fadeTimer_ <= 0) {
		isSceneEnd_ = true;
	}

	for (int i = 0; i < 22; i++) {
		if (hitCoolTimeFlag == false) {
			if (hit[i] <= radius) {
				hitCoolTimeFlag = true;
				coolTimeDrawFlag = true;
				player_->Oncollision();
				isHit = true;
			}
		}

		if (hit[i] <= graze && grazeFlag == false) {
			if (player_->GetGrazeFlag() == true) {
				grazeFlag = true;
				speed += 0.04f;
				//isSpeedUP_ = audio_->PlayWave(speedUPHandle_, false, 0.5);
				isSpeedUP = true;
			}
		}
	}

	if (player_->GetGrazeFlag() == false) {
		grazeFlag = false;
	}

}
