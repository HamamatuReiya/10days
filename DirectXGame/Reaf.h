#pragma once
#include <Model.h>
#include "WorldTransform.h"
class Reaf {
public:
	void Initialize(Model* model);

	void Update();

	void UpdateMat();

	void Draw(ViewProjection& viewProjection);

	void SetRightFlag(bool right) { rightFlag = right; };
	void SetLeftFlag(bool left) { leftFlag = left; };

	void Reset();

private:
	WorldTransform worldTransform_[3];

	bool rightFlag = false;

	bool leftFlag = false;

	bool posSet = false;

	float speed = 3.0f;

	Model* model_ = nullptr;
};
