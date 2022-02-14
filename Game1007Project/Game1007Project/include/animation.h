#pragma once
#include <map>
#include "gameObject.h"
#include "resource.h"
#include "canvas.h"

class Animation : public GOComponent {
public:
	Animation(string atlasName, int layer, int startIdx, int endIdx, int interval);
	void Update();
	void Draw();
	void SetNativeSize();
private:
	int m_deltaTime;
	int m_interval;
	int m_startIdx, m_endIdx;
	int m_currentIdx;
	AtlasResource* m_pResource;
	Canvas* m_pCanvas;
};

/*class Animator : public GOComponent {
public:
	void Update();
	void Draw();
	void SetState(string state);
	void SetAnimationClip(string state, Animation* clip);
private:
	string m_currentState;
	Animation* m_pAnimationClip;
	vector<string, Animation*> m_animationClip;
	Canvas* m_pCanvas;
};*/