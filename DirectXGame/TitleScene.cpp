#include "TitleScene.h"
#include <TextureManager.h>

TitleScene::TitleScene() {}

TitleScene::~TitleScene() {}

void TitleScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	titleHandle_ = TextureManager::Load("title.png");
	textureTitle_ = Sprite::Create(titleHandle_, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});

	// フェードの生成
	fade_ = std::make_unique<Fade>();
	// フェードの初期化
	fade_->Initialize();
	// フェードインの開始
	fade_->FadeInStart();

	// BGM
	//titleBGMHandle_ = audio_->LoadWave("BGM/title.mp3");
	//playTitleBGM_ = audio_->PlayWave(titleBGMHandle_, true, 0.5);

	// SE
	//systemHandle_ = audio_->LoadWave("SE/system.mp3");
	isClick = false;
}

void TitleScene::Update() {
	// SE
	if (isClick == true) {
		//playSystem_ = audio_->PlayWave(systemHandle_, false, 1.0);
		isClick = false;
	}

	// シーン移動
	if (input_->TriggerKey(DIK_SPACE)&& fadeTimerFlag_ == false) {
		fadeTimerFlag_ = true;
		isClick = true;
		fade_->FadeOutStart();
	}
	if (fadeTimerFlag_ == true) {
		fadeTimer_--;
	}
	if (fadeTimer_ <= 0) {
		isSceneEnd_ = true;
	}
	// フェードの更新
	fade_->Update();
}

void TitleScene::Draw() {
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

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	//タイトルの画像
	textureTitle_->Draw();
	
	// フェードの描画
	fade_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void TitleScene::SceneReset() { 
	isSceneEnd_ = false;

	fade_->FadeReset(); 
	fadeTimerFlag_ = false;
	fadeTimer_ = kFadeTimer_;
}

void TitleScene::BGMReset() { 
	//playTitleBGM_ = audio_->PlayWave(titleBGMHandle_, true, 0.5);
}

void TitleScene::BGMStop() {
	//audio_->StopWave(playTitleBGM_);
}
