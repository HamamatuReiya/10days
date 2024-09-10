#pragma once
#include <Model.h>
#include "WorldTransform.h"
#include "MT.h"
#include "Time.h"

class Spike {
public:
	void Initialize(Model* model ,Model* model2);

	void Update(float speed);

	void Draw(ViewProjection& viewProjection);

private:

	WorldTransform worldTransform1_[5];
	WorldTransform worldTransform2_[5];

	WorldTransform worldTransformBase_[2];

	WorldTransform worldTransformPattern_[10][5];

	float width = 25.0f;

	bool startFlag = false;

	int randNumber[2] = {0};

	// モデル
	Model* model_ = nullptr;

	Model* model2_ = nullptr;

};
