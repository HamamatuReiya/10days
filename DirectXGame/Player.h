#pragma once
#include <Model.h>
#include "WorldTransform.h"
#include "MT.h"

class Player {
public:
	void Initialize(Model* model, Model* model2, Model* model3, Model* model4, Model* model5);

	void Update();

	void Draw(ViewProjection& viewProjection);

private:
	WorldTransform worldTransform_;

	bool startFlag = false;

	// モデル
	Model* model_[5] = {nullptr};
};
