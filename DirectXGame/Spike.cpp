#include "Spike.h"

void Spike::Initialize(Model* model, Model* model2, Model* model3, Model* model4, Model* model5) { 
	model_ = model;
	model2_ = model2;
	model3_ = model3;
	model4_ = model4;
	model5_ = model5;

	startFlag = false;

	randNumber[0] = {0};
	randNumber[1] = {1};

	worldTransformBase_[0].Initialize();
	worldTransformBase_[1].Initialize();
	worldTransformBase_[2].Initialize();

	worldTransformBase_[2].translation_ = {0, -250, -4};
	worldTransformBase_[2].rotation_ = {0, 1.56f, 0};
	worldTransformBase_[2].scale_ = {3.0, 4.0, 3.0};

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

	stage3Flag = false;

	for (int i = 0; i < 7; i++) {
		worldTransform1_3_[i].Initialize();
		worldTransform1_3_[i].translation_ = {0.0f, 100, -3.0f};
		worldTransform1_3_[i].scale_ = {5.0f, 5.0f, 5.0f};

		worldTransform2_3_[i].Initialize();
		worldTransform2_3_[i].translation_ = {0.0f, 100, -3.0f};
		worldTransform2_3_[i].scale_ = {5.0f, 5.0f, 5.0f};
	}

	randNumber3[0] = {0};
	randNumber3[1] = {1};

	//ステージ１
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

	//ステージ２
	worldTransformPattern_[5][0].translation_ = {0.0f, -width, -3.0f};
	worldTransformPattern_[5][1].translation_ = {-20.0f, -width, -3.0f};
	worldTransformPattern_[5][2].translation_ = {0.0f, -width * 2, -3.0f};
	worldTransformPattern_[5][3].translation_ = {20.0f, -width * 4, -3.0f};
	worldTransformPattern_[5][4].translation_ = {-20.0f, -width * 4, -3.0f};

	worldTransformPattern_[6][0].translation_ = {-20.0f, 0.0f, -3.0f};
	worldTransformPattern_[6][1].translation_ = {20.0f, -width, -3.0f};
	worldTransformPattern_[6][2].translation_ = {-20.0f, -width * 2, -3.0f};
	worldTransformPattern_[6][3].translation_ = {20.0f, -width * 3, -3.0f};
	worldTransformPattern_[6][4].translation_ = {0.0f, -width * 4, -3.0f};

	worldTransformPattern_[7][0].translation_ = {20.0f, -width, -3.0f};
	worldTransformPattern_[7][1].translation_ = {-20.0f, -width, -3.0f};
	worldTransformPattern_[7][2].translation_ = {20.0f, -width * 2, -3.0f};
	worldTransformPattern_[7][3].translation_ = {-20.0f, -width * 3, -3.0f};
	worldTransformPattern_[7][4].translation_ = {0.0f, -width * 4, -3.0f};

	worldTransformPattern_[8][0].translation_ = {20.0f, 0.0f, -3.0f};
	worldTransformPattern_[8][1].translation_ = {0.0f, -width, -3.0f};
	worldTransformPattern_[8][2].translation_ = {0.0f, -width * 2, -3.0f};
	worldTransformPattern_[8][3].translation_ = {-20.0f, -width * 4, -3.0f};
	worldTransformPattern_[8][4].translation_ = {0.0f, -width * 4, -3.0f};

	worldTransformPattern_[9][0].translation_ = {-20.0f, 0.0f, -3.0f};
	worldTransformPattern_[9][1].translation_ = {-20.0f, -width, -3.0f};
	worldTransformPattern_[9][2].translation_ = {0.0f, -width * 2, -3.0f};
	worldTransformPattern_[9][3].translation_ = {20.0f, -width * 3, -3.0f};
	worldTransformPattern_[9][4].translation_ = {0.0f, -width * 4, -3.0f};

	//ステージ３
	worldTransformPattern_3_[0][0].translation_ = {-20.0f, 0.0f, -3.0f};
	worldTransformPattern_3_[0][1].translation_ = {-20.0f, -width, -3.0f};
	worldTransformPattern_3_[0][2].translation_ = {0.0f, -width * 2, -3.0f};
	worldTransformPattern_3_[0][3].translation_ = {20.0f, -width * 3, -3.0f};
	worldTransformPattern_3_[0][4].translation_ = {0.0f, -width * 4, -3.0f};
	worldTransformPattern_3_[0][5].translation_ = {-20.0f, 0.0f, -3.0f};
	worldTransformPattern_3_[0][6].translation_ = {-20.0f, -width, -3.0f};

	worldTransformPattern_3_[1][0].translation_ = {-20.0f, 0.0f, -3.0f};
	worldTransformPattern_3_[1][1].translation_ = {-20.0f, -width, -3.0f};
	worldTransformPattern_3_[1][2].translation_ = {0.0f, -width * 2, -3.0f};
	worldTransformPattern_3_[1][3].translation_ = {20.0f, -width * 3, -3.0f};
	worldTransformPattern_3_[1][4].translation_ = {0.0f, -width * 4, -3.0f};
	worldTransformPattern_3_[1][5].translation_ = {-20.0f, 0.0f, -3.0f};
	worldTransformPattern_3_[1][6].translation_ = {-120.0f, -width, -3.0f};

	worldTransformPattern_3_[2][0].translation_ = {-20.0f, 0.0f, -3.0f};
	worldTransformPattern_3_[2][1].translation_ = {-20.0f, -width, -3.0f};
	worldTransformPattern_3_[2][2].translation_ = {0.0f, -width * 2, -3.0f};
	worldTransformPattern_3_[2][3].translation_ = {20.0f, -width * 3, -3.0f};
	worldTransformPattern_3_[2][4].translation_ = {0.0f, -width * 4, -3.0f};
	worldTransformPattern_3_[2][5].translation_ = {-20.0f, 0.0f, -3.0f};
	worldTransformPattern_3_[2][6].translation_ = {-120.0f, -width, -3.0f};

	worldTransformPattern_3_[3][0].translation_ = {-20.0f, 0.0f, -3.0f};
	worldTransformPattern_3_[3][1].translation_ = {-20.0f, -width, -3.0f};
	worldTransformPattern_3_[3][2].translation_ = {0.0f, -width * 2, -3.0f};
	worldTransformPattern_3_[3][3].translation_ = {20.0f, -width * 3, -3.0f};
	worldTransformPattern_3_[3][4].translation_ = {0.0f, -width * 4, -3.0f};
	worldTransformPattern_3_[3][5].translation_ = {-20.0f, 0.0f, -3.0f};
	worldTransformPattern_3_[3][6].translation_ = {-20.0f, -width, -3.0f};

	worldTransformPattern_3_[4][0].translation_ = {-20.0f, 0.0f, -3.0f};
	worldTransformPattern_3_[4][1].translation_ = {-20.0f, -width, -3.0f};
	worldTransformPattern_3_[4][2].translation_ = {0.0f, -width * 2, -3.0f};
	worldTransformPattern_3_[4][3].translation_ = {20.0f, -width * 3, -3.0f};
	worldTransformPattern_3_[4][4].translation_ = {0.0f, -width * 4, -3.0f};
	worldTransformPattern_3_[4][5].translation_ = {-20.0f, 0.0f, -3.0f};
	worldTransformPattern_3_[4][6].translation_ = {-20.0f, -width, -3.0f};

}

void Spike::Update(float speed) {
	stage3Flag = false;
	if (collisionFlag == false) {
		collisionCount++;
	}

	if (collisionCount >= 10) {
		collisionFlag = true;
	}

	worldTransformBase_[0].translation_.y += speed;
	worldTransformBase_[1].translation_.y += speed;

	if (popObjCount <= 20) {
		if (worldTransformBase_[0].translation_.y >= width * 6) {
			worldTransformBase_[0].translation_.y = -width * 4;
			randNumber[0] = rand() % 5;
			popObjCount++;
		}

		if (worldTransformBase_[1].translation_.y >= width * 11) {
			worldTransformBase_[1].translation_.y = width;
			randNumber[1] = rand() % 5;
			popObjCount++;
		}
	} else {
		worldTransformBase_[2].translation_.y += speed;
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
	worldTransformBase_[2].UpdateMatrix();
}

void Spike::Update2(float speed) {
	stage3Flag = false;
	if (collisionFlag == false) {
		collisionCount++;
	}

	if (collisionCount >= 10) {
		collisionFlag = true;
	}

	worldTransformBase_[0].translation_.y += speed;
	worldTransformBase_[1].translation_.y += speed;

	if (popObjCount <= 20) {
		if (worldTransformBase_[0].translation_.y >= width * 6) {
			worldTransformBase_[0].translation_.y = -width * 4;
			randNumber[0] = rand() % 5 + 5;
			popObjCount++;
		}

		if (worldTransformBase_[1].translation_.y >= width * 11) {
			worldTransformBase_[1].translation_.y = width;
			randNumber[1] = rand() % 5 + 5;
			popObjCount++;
		}
	} else {
		worldTransformBase_[2].translation_.y += speed;
	}

	for (int i = 0; i < 5; i++) {
		worldTransform1_[i].translation_ = Add(worldTransformBase_[0].translation_, worldTransformPattern_[randNumber3[0]][i].translation_);
		worldTransform2_[i].translation_ = Add(worldTransformBase_[1].translation_, worldTransformPattern_[randNumber3[1]][i].translation_);
		worldTransform2_[i].translation_.y += -width * 5;
	}
	if (startFlag == false) {
		startFlag = true;
		worldTransformBase_[0].translation_.y -= width * 5;
		worldTransformBase_[1].translation_.y -= width * 5;
	}
	for (int i = 0; i < 5; i++) {
		worldTransform1_[i].UpdateMatrix();
		worldTransform2_[i].UpdateMatrix();
	}
	worldTransformBase_[0].UpdateMatrix();
	worldTransformBase_[1].UpdateMatrix();
	worldTransformBase_[2].UpdateMatrix();
}

void Spike::Update3(float speed) {
	stage3Flag = true;
	if (collisionFlag == false) {
		collisionCount++;
	}

	if (collisionCount >= 10) {
		collisionFlag = true;
	}

	worldTransformBase_[0].translation_.y += speed;
	worldTransformBase_[1].translation_.y += speed;

	if (popObjCount <= 20) {
		if (worldTransformBase_[0].translation_.y >= width * 6) {
			worldTransformBase_[0].translation_.y = -width * 4;
			randNumber3[0] = rand() % 5 + 10;
			popObjCount++;
		}

		if (worldTransformBase_[1].translation_.y >= width * 11) {
			worldTransformBase_[1].translation_.y = width;
			randNumber3[1] = rand() % 5 + 10;
			popObjCount++;
		}
	} else {
		worldTransformBase_[2].translation_.y += speed;
	}

	for (int i = 0; i < 7; i++) {
		worldTransform1_3_[i].translation_ = Add(worldTransformBase_[0].translation_, worldTransformPattern_[randNumber[0]][i].translation_);
		worldTransform2_3_[i].translation_ = Add(worldTransformBase_[1].translation_, worldTransformPattern_[randNumber[1]][i].translation_);
		worldTransform2_3_[i].translation_.y += -width * 5;
	}
	if (startFlag == false) {
		startFlag = true;
		worldTransformBase_[0].translation_.y -= width * 5;
		worldTransformBase_[1].translation_.y -= width * 5;
	}
	for (int i = 0; i < 7; i++) {
		worldTransform1_3_[i].UpdateMatrix();
		worldTransform2_3_[i].UpdateMatrix();
	}
	worldTransformBase_[0].UpdateMatrix();
	worldTransformBase_[1].UpdateMatrix();
	worldTransformBase_[2].UpdateMatrix();
}

void Spike::Draw(ViewProjection& viewProjection) {
	if (stage3Flag == false) {
		for (int i = 0; i < 5; i++) {
			model_->Draw(worldTransform1_[i], viewProjection);
			model2_->Draw(worldTransform1_[i], viewProjection);

			model_->Draw(worldTransform2_[i], viewProjection);
			model2_->Draw(worldTransform2_[i], viewProjection);
		}
	} else if (stage3Flag == true) {
		for (int i = 0; i < 6; i++) {
			model_->Draw(worldTransform1_3_[i], viewProjection);
			model2_->Draw(worldTransform1_3_[i], viewProjection);

			model_->Draw(worldTransform2_3_[i], viewProjection);
			model2_->Draw(worldTransform2_3_[i], viewProjection);
		}
		model3_->Draw(worldTransform1_3_[6], viewProjection);
		model5_->Draw(worldTransform1_3_[6], viewProjection);

		model3_->Draw(worldTransform2_3_[6], viewProjection);
		model5_->Draw(worldTransform2_3_[6], viewProjection);
	}

	model4_->Draw(worldTransformBase_[2], viewProjection);



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

	    worldPos.x = worldTransform2_[0].matWorld_.m[3][0];
	    worldPos.y = worldTransform2_[0].matWorld_.m[3][1];
	    worldPos.z = worldTransform2_[0].matWorld_.m[3][2];

	    return worldPos;
}
Vector3 Spike::GetWorldPosition7() {
	    Vector3 worldPos;

	    worldPos.x = worldTransform2_[1].matWorld_.m[3][0];
	    worldPos.y = worldTransform2_[1].matWorld_.m[3][1];
	    worldPos.z = worldTransform2_[1].matWorld_.m[3][2];

	    return worldPos;
}
Vector3 Spike::GetWorldPosition8() {
	    Vector3 worldPos;

	    worldPos.x = worldTransform2_[2].matWorld_.m[3][0];
	    worldPos.y = worldTransform2_[2].matWorld_.m[3][1];
	    worldPos.z = worldTransform2_[2].matWorld_.m[3][2];

	    return worldPos;
}
Vector3 Spike::GetWorldPosition9() {
	    Vector3 worldPos;

	    worldPos.x = worldTransform2_[3].matWorld_.m[3][0];
	    worldPos.y = worldTransform2_[3].matWorld_.m[3][1];
	    worldPos.z = worldTransform2_[3].matWorld_.m[3][2];

	    return worldPos;
}
Vector3 Spike::GetWorldPosition10() {
	    Vector3 worldPos;

	    worldPos.x = worldTransform2_[4].matWorld_.m[3][0];
	    worldPos.y = worldTransform2_[4].matWorld_.m[3][1];
	    worldPos.z = worldTransform2_[4].matWorld_.m[3][2];

	    return worldPos;
}

Vector3 Spike::GetWorldPosition99() {
	    Vector3 worldPos;

	    worldPos.x = worldTransformBase_[2].matWorld_.m[3][0];
	    worldPos.y = worldTransformBase_[2].matWorld_.m[3][1];
	    worldPos.z = worldTransformBase_[2].matWorld_.m[3][2];

	    return worldPos;
}
