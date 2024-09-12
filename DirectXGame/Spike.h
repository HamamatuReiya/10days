#pragma once
#include <Model.h>
#include "WorldTransform.h"
#include "MT.h"
#include "Time.h"

class Spike {
public:
	void Initialize(Model* model, Model* model2, Model* model3, Model* model4, Model* model5);

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
	Vector3 GetWorldPosition11();
	Vector3 GetWorldPosition12();
	Vector3 GetWorldPosition13();
	Vector3 GetWorldPosition14();
	Vector3 GetWorldPosition15();
	Vector3 GetWorldPosition16();

	Vector3 GetWorldPosition99();

	bool GetCollisionFlag() { return collisionFlag; }

private:

	WorldTransform worldTransform1_[5];
	WorldTransform worldTransform2_[5];

	WorldTransform worldTransformBase_[3];

	WorldTransform worldTransformPattern_[15][5];

	WorldTransform worldTransform1_3_[7];
	WorldTransform worldTransform2_3_[7];

	WorldTransform worldTransformPattern_3_[5][7];

	float width = 25.0f;

	bool startFlag = false;

	int randNumber[2] = {0};

	int randNumber3[2] = {0};

	bool stage3Flag = false;

	int collisionCount;
	bool collisionFlag;

	int popObjCount = 0;


	// モデル
	Model* model_ = nullptr;

	Model* model2_ = nullptr;

	Model* model3_ = nullptr;

	Model* model4_ = nullptr;

	Model* model5_ = nullptr;
};
