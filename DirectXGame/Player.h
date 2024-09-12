#pragma once
#include <Model.h>
#include "WorldTransform.h"
#include "MT.h"
#include "Input.h"

class Player {
public:
	void Initialize(Model* model, Model* model2, Model* model3, Model* model4, Model* model5);

	void Update();

	void Draw(ViewProjection& viewProjection);

	Vector3 GetWorldPosition();

	void Oncollision();

	bool GetGrazeFlag() { return GrazeFlag; }

	int GetLife() { return life; }

private:
	WorldTransform worldTransform_;

	Input* input_ = nullptr;

	int life = 3;

	bool startFlag = false;
	bool leftMoveFlag = false;
	bool rightMoveFlag = false;
	bool senterStopFlag = true;
	bool GrazeFlag = false;

	int count = 0;
	float widthSpeed;

	// モデル
	Model* model_[5] = {nullptr};
};
