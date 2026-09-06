#include "pch.h"
#include "Engine.h"

#include <cstdio>

bool Engine::Initialize(const char* title, int width, int height)
{
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW, This is so tisim\n");
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (!m_window)
	{
		fprintf(stderr, "Failed to create GLFW window, This is so tisim\n");
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(m_window);
	glfwSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		fprintf(stderr, "Failed to initialize GLAD, So You done something wrong you chud!\n");
		Shutdown();
		return false;
	}
	if (GLVersion.major < 3 || (GLVersion.major == 3 && GLVersion.minor < 3))
	{
		fprintf(stderr, "OpenGL 3.3 or higher is required (got %d.%d), This is so tisim\n", GLVersion.major, GLVersion.minor);
		Shutdown();
		return false;
	}
	fprintf(stdout, "OpenGL %d.%d initialized, This is so tisim\n", GLVersion.major, GLVersion.minor);

	m_isRunning = true;
	m_lastFrameTime = 0.0f;
	return true;
}

void Engine::Update()
{
	glfwPollEvents();
}

void Engine::Run()
{
	while (m_isRunning && !glfwWindowShouldClose(m_window))
	{
		float currentTime = (float)glfwGetTime();
		float deltaTime = m_lastFrameTime == 0.0f ? 0.0f : currentTime - m_lastFrameTime;
		m_lastFrameTime = currentTime;

		OnUpdate(deltaTime);
		OnRender();

		Update();
		glfwSwapBuffers(m_window);
	}
}

void Engine::Shutdown()
{
	if (m_window)
	{
		glfwDestroyWindow(m_window);
		m_window = nullptr;
	}
	glfwTerminate();
	m_isRunning = false;
}