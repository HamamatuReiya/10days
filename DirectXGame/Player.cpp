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
	worldTransform_.translation_ = {0.0f, 8.0f, -2.5f};
	input_ = Input::GetInstance();
	widthSpeed = 1.0f;
}

void Player::Update() { 
	if (input_->TriggerKey(DIK_LEFT)) {
		if (leftMoveFlag == false && rightMoveFlag == false) {
			leftMoveFlag = true;
			GrazeFlag = true;
		}
	}
	if (input_->TriggerKey(DIK_RIGHT)) {
			if (leftMoveFlag == false && rightMoveFlag == false) {
				rightMoveFlag = true;
			    GrazeFlag = true;
			}
	}

	if (GrazeFlag == true) {
		    count++;
		    if (count >= 10) {
			    count = 0;
			    GrazeFlag = false;
			}
	}

	if (leftMoveFlag == true) {
		worldTransform_.translation_.x -= widthSpeed;
	}
	else if (rightMoveFlag == true) {
		worldTransform_.translation_.x += widthSpeed;
	}

	if (worldTransform_.translation_.x <= -20.0f) {
		worldTransform_.translation_.x = -20.0f;
		leftMoveFlag = false;
		senterStopFlag = false;
	}

	if (worldTransform_.translation_.x >= 20.0f) {
		worldTransform_.translation_.x = 20.0f;
		rightMoveFlag = false;
		senterStopFlag = false;
	}

	if (rightMoveFlag == true && senterStopFlag==false) {
		if (worldTransform_.translation_.x >= 0) {
			worldTransform_.translation_.x = 0;
			senterStopFlag = true;
			rightMoveFlag = false;
		}
	}
	
	if (leftMoveFlag == true && senterStopFlag == false) {
		if (worldTransform_.translation_.x <= 0) {
			worldTransform_.translation_.x = 0;
			senterStopFlag = true;
			leftMoveFlag = false;
		}
	}

	worldTransform_.UpdateMatrix();
}

void Player::Draw(ViewProjection& viewProjection) {
	model_[0]->Draw(worldTransform_, viewProjection);
	model_[1]->Draw(worldTransform_, viewProjection);
	model_[2]->Draw(worldTransform_, viewProjection);
	model_[3]->Draw(worldTransform_, viewProjection);
	model_[4]->Draw(worldTransform_, viewProjection);
}

Vector3 Player::GetWorldPosition() {
	Vector3 worldPos;

	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Player::Oncollision() { life -= 1; }

void Player::Wind() { 
	windCount++; 
	if (windPattern >= 2) {
		windPattern = 0;
	}
		if (windCount >= 1500) {
		windFlag = true;
		windTime++;
		if (windPattern == 0) {
			if (leftMoveFlag == false && rightMoveFlag == false) {
				if (input_->TriggerKey(DIK_LEFT)) {
					widthSpeed = 0.5f;
				}
				if (input_->TriggerKey(DIK_RIGHT)) {
					widthSpeed = 1.6f;
				}
			}
		} else {
			if (leftMoveFlag == false && rightMoveFlag == false) {
				if (input_->TriggerKey(DIK_LEFT)) {
					widthSpeed = 1.5f;
				}
				if (input_->TriggerKey(DIK_RIGHT)) {
					widthSpeed = 0.6f;
				}
			}
		}
		if (windTime >= 600) {
			windCount = 0;
			windTime = 0;
			windFlag = false;
			widthSpeed = 1.0f;
			windPattern += 1;
		}
	}
}

void Player::Reset() {
	worldTransform_.Initialize();
	worldTransform_.scale_ = {2.0f, 2.0f, 2.0f};
	worldTransform_.rotation_ = {0.0f, 1.6f, 0.3f};
	worldTransform_.translation_ = {0.0f, 8.0f, -2.5f};
	widthSpeed = 1.0f;
	life = 3;
	 startFlag = false;
	 leftMoveFlag = false;
	 rightMoveFlag = false;
	 senterStopFlag = true;
	 GrazeFlag = false;

	windCount = 0;
	windFlag = false;
	windTime = 0;
	windPattern = 0;

	count = 0;
	widthSpeed;
}

