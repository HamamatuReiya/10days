#include "Chain.h"

void Chain::Initialize(Model* model) {
	model_ = model;
	worldTransformStart_[0].Initialize();
	worldTransformStart_[1].Initialize();

	for (int i = 0; i < chainNumber_; i++) {
		worldTransformChain1_[i].Initialize();
		worldTransformChain1_[i].scale_ = {1.0f, 1.0f, 1.0f};
		worldTransformChain1_[i].rotation_ = {0.0f, 0.0f, 0.0f};
		worldTransformChain1_[i].translation_ = {0.0f, 0.0f, 0.0f};

		worldTransformChain2_[i].Initialize();
		worldTransformChain2_[i].scale_ = {1.0f, 1.0f, 1.0f};
		worldTransformChain2_[i].rotation_ = {0.0f, 0.0f, 0.0f};
		worldTransformChain2_[i].translation_ = {0.0f, 0.0f, 0.0f};

		worldTransformLeftChain1_[i].Initialize();
		worldTransformLeftChain1_[i].scale_ = {1.0f, 1.0f, 1.0f};
		worldTransformLeftChain1_[i].rotation_ = {0.0f, 0.0f, 0.0f};
		worldTransformLeftChain1_[i].translation_ = {0.0f, 0.0f, 0.0f};

		worldTransformLeftChain2_[i].Initialize();
		worldTransformLeftChain2_[i].scale_ = {1.0f, 1.0f, 1.0f};
		worldTransformLeftChain2_[i].rotation_ = {0.0f, 0.0f, 0.0f};
		worldTransformLeftChain2_[i].translation_ = {0.0f, 0.0f, 0.0f};

		worldTransformRightChain1_[i].Initialize();
		worldTransformRightChain1_[i].scale_ = {1.0f, 1.0f, 1.0f};
		worldTransformRightChain1_[i].rotation_ = {0.0f, 0.0f, 0.0f};
		worldTransformRightChain1_[i].translation_ = {0.0f, 0.0f, 0.0f};

		worldTransformRightChain2_[i].Initialize();
		worldTransformRightChain2_[i].scale_ = {1.0f, 1.0f, 1.0f};
		worldTransformRightChain2_[i].rotation_ = {0.0f, 0.0f, 0.0f};
		worldTransformRightChain2_[i].translation_ = {0.0f, 0.0f, 0.0f};
	}
}

void Chain::Update(float speed) {
	for (int i = 0; i < chainNumber_; i++) {
		worldTransformChain1_[i].translation_ = {0.0f, worldTransformStart_[0].translation_.y - 4.4f * i, 0.0f};
		worldTransformChain2_[i].translation_ = {0.0f, worldTransformStart_[1].translation_.y + float(-4.4 * i) + float(-4.4f * chainNumber_), 0.0f};

		worldTransformLeftChain1_[i].translation_ = {-20.0f, worldTransformStart_[0].translation_.y - 4.4f * i, 0.0f};
		worldTransformLeftChain2_[i].translation_ = {-20.0f, worldTransformStart_[1].translation_.y + float(-4.4 * i) + float(-4.4f * chainNumber_), 0.0f};

		worldTransformRightChain1_[i].translation_ = {20.0f, worldTransformStart_[0].translation_.y - 4.4f * i, 0.0f};
		worldTransformRightChain2_[i].translation_ = {20.0f, worldTransformStart_[1].translation_.y + float(-4.4 * i) + float(-4.4f * chainNumber_), 0.0f};
	}

	if (worldTransformStart_[0].translation_.y >= 4.4f * (chainNumber_+ 5)) {
		worldTransformStart_[0].translation_.y += float(-4.4f * chainNumber_ * 2);
	}

	if (worldTransformStart_[1].translation_.y >= 4.4f * (chainNumber_ * 2) + 19) {
		worldTransformStart_[1].translation_.y += float(-4.4f * chainNumber_ * 2);
	}

	worldTransformStart_[0].translation_.y += speed;
	worldTransformStart_[1].translation_.y += speed;

	for (int i = 0; i < chainNumber_; i++) {
		worldTransformChain1_[i].UpdateMatrix();
		worldTransformChain2_[i].UpdateMatrix();

		worldTransformLeftChain1_[i].UpdateMatrix();
		worldTransformLeftChain2_[i].UpdateMatrix();

		worldTransformRightChain1_[i].UpdateMatrix();
		worldTransformRightChain2_[i].UpdateMatrix();
	}
	worldTransformStart_[0].UpdateMatrix();
	worldTransformStart_[1].UpdateMatrix();
	}

void Chain::Draw(ViewProjection& viewProjection) {
	for (int i = 0; i < chainNumber_; i++) {
		model_->Draw(worldTransformChain1_[i], viewProjection);
		model_->Draw(worldTransformChain2_[i], viewProjection);

		model_->Draw(worldTransformLeftChain1_[i], viewProjection);
		model_->Draw(worldTransformLeftChain2_[i], viewProjection);

		model_->Draw(worldTransformRightChain1_[i], viewProjection);
		model_->Draw(worldTransformRightChain2_[i], viewProjection);
	}
}

void Chain::Reset() {
	worldTransformStart_[0].Initialize();
	worldTransformStart_[1].Initialize();

	worldTransformStart_[0].translation_ = {0.0f, 0.0f, 0.0f};
	worldTransformStart_[1].translation_ = {0.0f, 0.0f, 0.0f};

	for (int i = 0; i < chainNumber_; i++) {
		worldTransformChain1_[i].Initialize();
		worldTransformChain1_[i].scale_ = {1.0f, 1.0f, 1.0f};
		worldTransformChain1_[i].rotation_ = {0.0f, 0.0f, 0.0f};
		worldTransformChain1_[i].translation_ = {0.0f, 0.0f, 0.0f};

		worldTransformChain2_[i].Initialize();
		worldTransformChain2_[i].scale_ = {1.0f, 1.0f, 1.0f};
		worldTransformChain2_[i].rotation_ = {0.0f, 0.0f, 0.0f};
		worldTransformChain2_[i].translation_ = {0.0f, 0.0f, 0.0f};

		worldTransformLeftChain1_[i].Initialize();
		worldTransformLeftChain1_[i].scale_ = {1.0f, 1.0f, 1.0f};
		worldTransformLeftChain1_[i].rotation_ = {0.0f, 0.0f, 0.0f};
		worldTransformLeftChain1_[i].translation_ = {0.0f, 0.0f, 0.0f};

		worldTransformLeftChain2_[i].Initialize();
		worldTransformLeftChain2_[i].scale_ = {1.0f, 1.0f, 1.0f};
		worldTransformLeftChain2_[i].rotation_ = {0.0f, 0.0f, 0.0f};
		worldTransformLeftChain2_[i].translation_ = {0.0f, 0.0f, 0.0f};

		worldTransformRightChain1_[i].Initialize();
		worldTransformRightChain1_[i].scale_ = {1.0f, 1.0f, 1.0f};
		worldTransformRightChain1_[i].rotation_ = {0.0f, 0.0f, 0.0f};
		worldTransformRightChain1_[i].translation_ = {0.0f, 0.0f, 0.0f};

		worldTransformRightChain2_[i].Initialize();
		worldTransformRightChain2_[i].scale_ = {1.0f, 1.0f, 1.0f};
		worldTransformRightChain2_[i].rotation_ = {0.0f, 0.0f, 0.0f};
		worldTransformRightChain2_[i].translation_ = {0.0f, 0.0f, 0.0f};

	}

}
