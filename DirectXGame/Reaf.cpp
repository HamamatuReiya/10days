#include "Reaf.h"

void Reaf::Initialize(Model* model) {
	model_ = model;
	for (int i = 0; i < 3; i++) {
		worldTransform_[i].Initialize();
		worldTransform_[i].translation_ = {100, 100, 0};
		worldTransform_[i].scale_ = {3.0f, 3.0f, 3.0f};
	}

	rightFlag = false;
	leftFlag = false;
	posSet = false;
}

void Reaf::Update() {
		if (rightFlag == true) {
			if (posSet == false) {
				posSet = true;
				worldTransform_[0].translation_ = {-50, -20, 6};
			    worldTransform_[1].translation_ = {-60, 0, 6};
			    worldTransform_[2].translation_ = {-70, 20, 6};
			}
		    for (int i = 0; i < 3; i++) {
			    worldTransform_[i].translation_.x += speed;
			    if (worldTransform_[i].translation_.x >= 50) {
				    worldTransform_[i].translation_.x = -50;
			    }
		    }
		} else if (leftFlag == true) {
			if (posSet == false) {
				posSet = true;
			    worldTransform_[0].translation_ = {50, -20, 6};
			    worldTransform_[1].translation_ = {60, 0, 6};
			    worldTransform_[2].translation_ = {70, 20, 6};
			}
		    for (int i = 0; i < 3; i++) {
			    worldTransform_[i].translation_.x -= speed;
			    if (worldTransform_[i].translation_.x<=-50) {
				    worldTransform_[i].translation_.x = 50;
			    }
		    }
	    }
}

void Reaf::UpdateMat() {
	    if (rightFlag == false && leftFlag==false) {

		    posSet = false;
		    for (int i = 0; i < 3; i++) {
			    worldTransform_[i].translation_ = {100.0f, 100.0f, 100.0f};
		    }
	    }
	for (int i = 0; i < 3; i++) {
		worldTransform_[i].UpdateMatrix();
	}
	}

void Reaf::Draw(ViewProjection& viewProjection) {
	for (int i = 0; i < 3; i++) {
		model_->Draw(worldTransform_[i], viewProjection);
	}
}

void Reaf::Reset() {
	rightFlag = false;
	leftFlag = false;
	posSet = false;
	for (int i = 0; i < 3; i++) {
		worldTransform_[i].translation_ = {100.0f, 100.0f, 100.0f};
		worldTransform_[i].UpdateMatrix();
	}
}
