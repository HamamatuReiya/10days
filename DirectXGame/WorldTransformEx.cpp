#include "MT.h"
#include "WorldTransform.h"
#include <math.h>

void WorldTransform::UpdateMatrix() {

	matWorld_ = MakeAffineMatrix(scale_, rotation_, translation_);

	// 親があれば親のワールド行列を掛ける
	if (parent_) {

		matWorld_ = Multiply(matWorld_, parent_->matWorld_);
	}

	TransferMatrix();
};