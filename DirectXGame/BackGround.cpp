#include "BackGround.h"

void BackGround::Initialize(Model* model) {
	model_ = model;
	worldTransform_.Initialize();
    worldTransform_.scale_ = {16.0f, 1.0f, 25.0f};
	worldTransform_.rotation_ = {10.0f, 0.0f, 0.0f};
	worldTransform_.translation_ = {0.0f, 20.0f, 0.0f};
}

void BackGround::Update() {
	// 行列の更新
	worldTransform_.UpdateMatrix();
}

void BackGround::Draw(const ViewProjection& viewProjection) { 
	model_->Draw(worldTransform_, viewProjection); 
}
