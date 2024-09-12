#include "ResultScene.h"
#include "TextureManager.h"
#include <cassert>

void ResultScene::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	// 画像の初期化
	TextureInitialize();

	// SE
	gameClearHandle_ = audio_->LoadWave("SE/clear.mp3");
	isClear = true;

}

void ResultScene::Update() {
	textureDeleteTime += 1;
	if (input_->TriggerKey(DIK_SPACE)) {
		isSceneEnd_ = true;
	}

	// SE
	if (isClear == true) {
		isGameClear_ = audio_->PlayWave(gameClearHandle_, false, 0.5);
		isClear = false;
	}

}

void ResultScene::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	textureBackground_->Draw();

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
	
	if (textureDeleteTime % 10 != 0) {
		textureGameClear_->Draw();
	}

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void ResultScene::SceneReset() { 
	isSceneEnd_ = false; 
	textureDeleteTime = 0;
	isClear = true;
}

void ResultScene::TextureInitialize() {
	// ゲームクリアの画像
	uint32_t GameClearHandle;
	GameClearHandle = TextureManager::Load("GameClear.png");

	textureGameClear_ = Sprite::Create(GameClearHandle, {350.0f, 300.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});

	//背景
	uint32_t BackgroundHandle;
	BackgroundHandle = TextureManager::Load("background.png");

	textureBackground_ = Sprite::Create(BackgroundHandle, {0.0f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
}
