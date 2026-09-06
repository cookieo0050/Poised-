#pragma once

struct GLFWwindow;

class Engine
{
public:
	bool Initialize(const char* title, int width, int height);
	void Update();
	void Run();
	void Shutdown();

protected:
	virtual void OnUpdate(float deltaTime) = 0;
	virtual void OnRender() = 0;

private:
	struct GLFWwindow* m_window = nullptr;
	bool m_isRunning = false;
	float m_lastFrameTime = 0.0f;
};