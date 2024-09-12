#include <Model.h>
#include "WorldTransform.h"

class Chain {
public:
	void Initialize(Model* model);

	void Update(float speed);

	void Draw(ViewProjection& viewProjection);

	void Reset();

private:

	static const int chainNumber_ = 12;
	// ワールド変換データ
	WorldTransform worldTransformChain1_[chainNumber_];

	WorldTransform worldTransformChain2_[chainNumber_];

	WorldTransform worldTransformLeftChain1_[chainNumber_];

	WorldTransform worldTransformLeftChain2_[chainNumber_];

	WorldTransform worldTransformRightChain1_[chainNumber_];

	WorldTransform worldTransformRightChain2_[chainNumber_];

	WorldTransform worldTransformStart_[2];

	// モデル
	Model* model_ = nullptr;



	};