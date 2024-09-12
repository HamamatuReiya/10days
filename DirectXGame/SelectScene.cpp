#include "SelectScene.h"
#include <TextureManager.h>

SelectScene::SelectScene() {}

SelectScene::~SelectScene() {}

void SelectScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	//テクスチャの初期化
	TextureInitialize();

	//カーソルのスピード
	cursorSpeed_ = {30, 0};

	// フェードの生成
	fade_ = std::make_unique<Fade>();
	// フェードの初期化
	fade_->Initialize();
	// フェードインの開始
	fade_->FadeInStart();
}

void SelectScene::Update() { 
	
	//ステージカウントが最大ステージ数いないの時、場面が切り替わっていない時
	if (stageCount_ >= 0 || stageCount_ <= kMaxStage_ && fadeTimerFlag_ == false) {
		//ステージ選択
		if (input_->TriggerKey(DIK_RIGHT)) {
			stageCount_ += 1;
		} 
		else if (input_->TriggerKey(DIK_LEFT)) {
			stageCount_ -= 1;
		}
		//決定
		if (input_->TriggerKey(DIK_SPACE)) {
			//フェードを開始するフラグ
			fadeTimerFlag_ = true;
			//フェードアウトを始めるフラグ
			fade_->FadeOutStart();
		}
	}
	//フェードが開始したとき
	if (fadeTimerFlag_ == true) {
		fadeTimer_--;
	}
	if (fadeTimer_ <= 0) {
		isSceneEnd_ = true;
	}

	//カーソルの画像の移動用
	textureCursor_->SetPosition(cursorPos_);

	// ステージ選択
	StageSelect();
	// フェードの更新
	fade_->Update();
}

void SelectScene::Draw() {
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

	textureNumber_[0]->Draw();
	textureNumber_[1]->Draw();
	textureNumber_[2]->Draw();
	//textureNumber_[3]->Draw();

	textureCursor_->Draw();

	textureText_->Draw();

	// フェードの描画
	fade_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void SelectScene::TextureInitialize() {
	// 数字の画像
	uint32_t numHandle[4];
	numHandle[0] = TextureManager::Load("./Resources/number/0.png");
	numHandle[1] = TextureManager::Load("./Resources/number/1.png");
	numHandle[2] = TextureManager::Load("./Resources/number/2.png");
	numHandle[3] = TextureManager::Load("./Resources/number/3.png");

	// 取得した数
	textureNumber_[0] = Sprite::Create(numHandle[0], {50.0f, 330.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	textureNumber_[1] = Sprite::Create(numHandle[1], {313.0f, 330.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	textureNumber_[2] = Sprite::Create(numHandle[2], {600.0f, 330.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	textureNumber_[3] = Sprite::Create(numHandle[3], {853.0f, 330.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});

	// カーソルの画像
	uint32_t cursorHandle;
	cursorHandle = TextureManager::Load("cursor.png");

	textureCursor_ = Sprite::Create(cursorHandle, {50.0f, 1.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});

	// テキストの画像
	uint32_t textHandle;
	textHandle = TextureManager::Load("./Resources/Text.png");

	textureText_ = Sprite::Create(textHandle, {350.0f, 100.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
}

void SelectScene::StageSelect() {
	if (stageCount_ < 0) {
		stageCount_ += 1;
	}
	if (stageCount_ > kMaxStage_) {
		stageCount_ -= 1;
	}

	if (stageCount_ == 0) {
		cursorPos_.x = 50.0f - 30;
		stageNo = Stage::kStage1;
	}

	if (stageCount_ == 1) {
		cursorPos_.x = 313.0f - 30;
		stageNo = Stage::kStage2;
	}

	if (stageCount_ == 2) {
		cursorPos_.x = 600.0f - 30;
		stageNo = Stage::kStage3;
	}
}

void SelectScene::SceneReset() {
	fade_->FadeReset();
	isSceneEnd_ = false;
	fadeTimerFlag_ = false;
	fadeTimer_ = kFadeTimer_;
}