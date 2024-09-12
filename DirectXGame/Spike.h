#pragma once
#include <Model.h>
#include "WorldTransform.h"
#include "MT.h"
#include "Time.h"

class Spike {
public:
	void Initialize(Model* model, Model* model2, Model* model4);

	void Update(float speed);

	void Update2(float speed);

	void Update3(float speed);

	void Draw(ViewProjection& viewProjection);

	Vector3 GetWorldPosition1();
	Vector3 GetWorldPosition2();
	Vector3 GetWorldPosition3();
	Vector3 GetWorldPosition4();
	Vector3 GetWorldPosition5();
	Vector3 GetWorldPosition6();
	Vector3 GetWorldPosition7();
	Vector3 GetWorldPosition8();
	Vector3 GetWorldPosition9();
	Vector3 GetWorldPosition10();

	Vector3 GetWorldPosition99();

	bool GetCollisionFlag() { return collisionFlag; }

private:

	WorldTransform worldTransform1_[5];
	WorldTransform worldTransform2_[5];

	WorldTransform worldTransformBase_[3];

	WorldTransform worldTransformPattern_[10][5];

	float width = 25.0f;

	bool startFlag = false;

	int randNumber[2] = {0};

	int collisionCount;
	bool collisionFlag;

	int popObjCount = 0;


	// モデル
	Model* model_ = nullptr;

	Model* model2_ = nullptr;

	Model* model3_ = nullptr;

	Model* model4_ = nullptr;
};
