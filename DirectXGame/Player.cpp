#include "Player.h"

void Player::Initialize(Model* model, Model* model2, Model* model3, Model* model4, Model* model5) {
	model_[0] = model;
	model_[1] = model2;
	model_[2] = model3;
	model_[3] = model4;
	model_[4] = model5;
	worldTransform_.Initialize();
	worldTransform_.scale_ = {2.0f, 2.0f, 2.0f};
	worldTransform_.rotation_ = {0.0f, 1.6f, 0.3f};
	worldTransform_.translation_ = {0.0f, 0.0f, -2.5f};
}

void Player::Update() { worldTransform_.UpdateMatrix(); }

void Player::Draw(ViewProjection& viewProjection) {
	model_[0]->Draw(worldTransform_, viewProjection);
	model_[1]->Draw(worldTransform_, viewProjection);
	model_[2]->Draw(worldTransform_, viewProjection);
	model_[3]->Draw(worldTransform_, viewProjection);
	model_[4]->Draw(worldTransform_, viewProjection);
}
