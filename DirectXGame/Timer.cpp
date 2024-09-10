#include "Timer.h"
#include <TextureManager.h>

void Timer::Initialize() {
	// 数字の画像
	numHandle_[0] = TextureManager::Load("./Resources/number/0.png");
	numHandle_[1] = TextureManager::Load("./Resources/number/1.png");
	numHandle_[2] = TextureManager::Load("./Resources/number/2.png");
	numHandle_[3] = TextureManager::Load("./Resources/number/3.png");
	numHandle_[4] = TextureManager::Load("./Resources/number/4.png");
	numHandle_[5] = TextureManager::Load("./Resources/number/5.png");
	numHandle_[6] = TextureManager::Load("./Resources/number/6.png");
	numHandle_[7] = TextureManager::Load("./Resources/number/7.png");
	numHandle_[8] = TextureManager::Load("./Resources/number/8.png");
	numHandle_[9] = TextureManager::Load("./Resources/number/9.png");
	// コロン　画像
	colonHandle_ = TextureManager::Load("./Resources/number/colon.png");

	
    // 取得した数 秒
	for (int i = 0; i < 2; i++) {
		textureTimerSeconds_[i] = Sprite::Create(numHandle_[i], {1150.0f + i * 50.0f, 10.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	}
	// 取得した数 分
	for (int i = 0; i < 2; i++) {
		textureTimerMinutes_[i] = Sprite::Create(numHandle_[i], {1000.0f + i * 50.0f, 10.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
	}

	//コロン　画像
	textureColon = Sprite::Create(colonHandle_, {1100.0f, 10.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f});
}

void Timer::Update() { 
	frameCount++;

	int frame = frameCount / 60;
	int minutes = frame / 60;
	int seconds = frame % 60;

	numMinutes[0] = minutes / 10;
	minutes = minutes % 10;
	numMinutes[1] = minutes;

	numSeconds[0] = seconds / 10;
	seconds = seconds % 10;
	numSeconds[1] = seconds;
	
	//秒
	for (int i = 0; i < 2; i++) {
		textureTimerSeconds_[i]->SetTextureHandle(numHandle_[numSeconds[i]]);
	}
	//分
	for (int i = 0; i < 2; i++) {
		textureTimerMinutes_[i]->SetTextureHandle(numHandle_[numMinutes[i]]);
	}
}

void Timer::Draw() {
	for (int i = 0; i < 2; i++) {
		textureTimerSeconds_[i]->Draw();
	}
	for (int i = 0; i < 2; i++) {
		textureTimerMinutes_[i]->Draw();
	}
	textureColon->Draw();
}

void Timer::Reset() { 
	frameCount = 0;
}
