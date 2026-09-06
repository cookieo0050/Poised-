#include "pch.h"
#include "Engine.h"

#include <imgui.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

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
	fprintf(stdout, "OpenGL %d.%d initialized, YAY :D\n", GLVersion.major, GLVersion.minor);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	ImGui::StyleColorsDark();

	if (!ImGui_ImplGlfw_InitForOpenGL(m_window, true) || !ImGui_ImplOpenGL3_Init("#version 330"))
	{
		fprintf(stderr, "Failed to initialize Dear ImGui, This is so tisim\n");
		Shutdown();
		return false;
	}

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

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		OnRender();
		OnImGui();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		Update();
		glfwSwapBuffers(m_window);
	}
}

void Engine::Shutdown()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	if (m_window)
	{
		glfwDestroyWindow(m_window);
		m_window = nullptr;
	}
	glfwTerminate();
	m_isRunning = false;
}