#include "Spike.h"

void Spike::Initialize(Model* model, Model* model2) { 
	model_ = model;
	model2_ = model2;

	startFlag = false;

	randNumber[0] = {0};
	randNumber[1] = {1};

	worldTransformBase_[0].Initialize();
	worldTransformBase_[1].Initialize();

	for (int i = 0; i < 5; i++) {
		worldTransform1_[i].Initialize();
		worldTransform1_[i].translation_ = {0.0f, 100, -3.0f};
		worldTransform1_[i].scale_ = {5.0f, 5.0f, 5.0f};

		worldTransform2_[i].Initialize();
		worldTransform2_[i].translation_ = {0.0f, 100, -3.0f};
		worldTransform2_[i].scale_ = {5.0f, 5.0f, 5.0f};
	}

	collisionFlag = false;
	collisionCount = 0;

	worldTransformPattern_[0][0].translation_ = {0.0f, 0.0f, -3.0f};
	worldTransformPattern_[0][1].translation_ = {-20.0f, -width, -3.0f};
	worldTransformPattern_[0][2].translation_ = {-20.0f, -width * 2, -3.0f};
	worldTransformPattern_[0][3].translation_ = {20.0f, -width * 3, -3.0f};
	worldTransformPattern_[0][4].translation_ = {0.0f, -width * 4, -3.0f};

	worldTransformPattern_[1][0].translation_ = {-20.0f, 0.0f, -3.0f};
	worldTransformPattern_[1][1].translation_ = {0.0f, -width, -3.0f};
	worldTransformPattern_[1][2].translation_ = {0.0f, -width * 2, -3.0f};
	worldTransformPattern_[1][3].translation_ = {20.0f, -width * 3, -3.0f};
	worldTransformPattern_[1][4].translation_ = {0.0f, -width * 4, -3.0f};

	worldTransformPattern_[2][0].translation_ = {20.0f, 0.0f, -3.0f};
	worldTransformPattern_[2][1].translation_ = {20.0f, -width, -3.0f};
	worldTransformPattern_[2][2].translation_ = {0.0f, -width * 2, -3.0f};
	worldTransformPattern_[2][3].translation_ = {-20.0f, -width * 3, -3.0f};
	worldTransformPattern_[2][4].translation_ = {-20.0f, -width * 4, -3.0f};

	worldTransformPattern_[3][0].translation_ = {0.0f, 0.0f, -3.0f};
	worldTransformPattern_[3][1].translation_ = {20.0f, -width, -3.0f};
	worldTransformPattern_[3][2].translation_ = {0.0f, -width * 2, -3.0f};
	worldTransformPattern_[3][3].translation_ = {20.0f, -width * 3, -3.0f};
	worldTransformPattern_[3][4].translation_ = {-20.0f, -width * 4, -3.0f};

	worldTransformPattern_[4][0].translation_ = {-20.0f, 0.0f, -3.0f};
	worldTransformPattern_[4][1].translation_ = {0.0f, -width, -3.0f};
	worldTransformPattern_[4][2].translation_ = {0.0f, -width * 2, -3.0f};
	worldTransformPattern_[4][3].translation_ = {20.0f, -width * 3, -3.0f};
	worldTransformPattern_[4][4].translation_ = {0.0f, -width * 4, -3.0f};

}

void Spike::Update(float speed) {
	if (collisionFlag == false) {
		collisionCount++;
	}

	if (collisionCount >= 10) {
		collisionFlag = true;
	}

	worldTransformBase_[0].translation_.y += speed;
	worldTransformBase_[1].translation_.y += speed;

	if (worldTransformBase_[0].translation_.y >= width * 6) {
		worldTransformBase_[0].translation_.y = -width * 4;
		randNumber[0] = rand() % 5;
	}

	if (worldTransformBase_[1].translation_.y >= width * 11) {
		worldTransformBase_[1].translation_.y = width;
		randNumber[1] = rand() % 5;
	}

	for (int i = 0; i < 5; i++) {
		worldTransform1_[i].translation_ = Add(worldTransformBase_[0].translation_,worldTransformPattern_[randNumber[0]][i].translation_);
		worldTransform2_[i].translation_ = Add(worldTransformBase_[1].translation_, worldTransformPattern_[randNumber[1]][i].translation_);
		worldTransform2_[i].translation_.y += -width * 5;
	}
	if (startFlag == false) {
		startFlag = true;
		worldTransformBase_[0].translation_.y -=width*5;
		worldTransformBase_[1].translation_.y -= width * 5;
	}
	for (int i = 0; i < 5; i++) {
		worldTransform1_[i].UpdateMatrix();
		worldTransform2_[i].UpdateMatrix();
	}
	worldTransformBase_[0].UpdateMatrix();
	worldTransformBase_[1].UpdateMatrix();
}

void Spike::Draw(ViewProjection& viewProjection) {
	for (int i = 0; i < 5; i++) {
		model_->Draw(worldTransform1_[i], viewProjection);
		model2_->Draw(worldTransform1_[i], viewProjection);

		model_->Draw(worldTransform2_[i], viewProjection);
		model2_->Draw(worldTransform2_[i], viewProjection);
	}
}

Vector3 Spike::GetWorldPosition1() {
	Vector3 worldPos;

		worldPos.x = worldTransform1_[0].matWorld_.m[3][0];
		worldPos.y = worldTransform1_[0].matWorld_.m[3][1];
		worldPos.z = worldTransform1_[0].matWorld_.m[3][2];

		return worldPos;
}

Vector3 Spike::GetWorldPosition2() {
	    Vector3 worldPos;

	    worldPos.x = worldTransform1_[1].matWorld_.m[3][0];
	    worldPos.y = worldTransform1_[1].matWorld_.m[3][1];
	    worldPos.z = worldTransform1_[1].matWorld_.m[3][2];

	    return worldPos;
}
Vector3 Spike::GetWorldPosition3() {
	    Vector3 worldPos;

	    worldPos.x = worldTransform1_[2].matWorld_.m[3][0];
	    worldPos.y = worldTransform1_[2].matWorld_.m[3][1];
	    worldPos.z = worldTransform1_[2].matWorld_.m[3][2];

	    return worldPos;
}
Vector3 Spike::GetWorldPosition4() {
	    Vector3 worldPos;

	    worldPos.x = worldTransform1_[3].matWorld_.m[3][0];
	    worldPos.y = worldTransform1_[3].matWorld_.m[3][1];
	    worldPos.z = worldTransform1_[3].matWorld_.m[3][2];

	    return worldPos;
}
Vector3 Spike::GetWorldPosition5() {
	    Vector3 worldPos;

	    worldPos.x = worldTransform1_[4].matWorld_.m[3][0];
	    worldPos.y = worldTransform1_[4].matWorld_.m[3][1];
	    worldPos.z = worldTransform1_[4].matWorld_.m[3][2];

	    return worldPos;
}
Vector3 Spike::GetWorldPosition6() {
	    Vector3 worldPos;

	    worldPos.x = worldTransform1_[5].matWorld_.m[3][0];
	    worldPos.y = worldTransform1_[5].matWorld_.m[3][1];
	    worldPos.z = worldTransform1_[5].matWorld_.m[3][2];

	    return worldPos;
}
Vector3 Spike::GetWorldPosition7() {
	    Vector3 worldPos;

	    worldPos.x = worldTransform1_[6].matWorld_.m[3][0];
	    worldPos.y = worldTransform1_[6].matWorld_.m[3][1];
	    worldPos.z = worldTransform1_[6].matWorld_.m[3][2];

	    return worldPos;
}
Vector3 Spike::GetWorldPosition8() {
	    Vector3 worldPos;

	    worldPos.x = worldTransform1_[7].matWorld_.m[3][0];
	    worldPos.y = worldTransform1_[7].matWorld_.m[3][1];
	    worldPos.z = worldTransform1_[7].matWorld_.m[3][2];

	    return worldPos;
}
Vector3 Spike::GetWorldPosition9() {
	    Vector3 worldPos;

	    worldPos.x = worldTransform1_[8].matWorld_.m[3][0];
	    worldPos.y = worldTransform1_[8].matWorld_.m[3][1];
	    worldPos.z = worldTransform1_[8].matWorld_.m[3][2];

	    return worldPos;
}
Vector3 Spike::GetWorldPosition10() {
	    Vector3 worldPos;

	    worldPos.x = worldTransform1_[9].matWorld_.m[3][0];
	    worldPos.y = worldTransform1_[9].matWorld_.m[3][1];
	    worldPos.z = worldTransform1_[9].matWorld_.m[3][2];

	    return worldPos;
}
