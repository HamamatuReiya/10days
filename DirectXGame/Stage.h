#pragma once
enum Stage {
	kStage1,
	kStage2,
	kStage3
};

class StageSelect {
protected:
	static int stageNo;

public:
	int GetStageNo();

};
