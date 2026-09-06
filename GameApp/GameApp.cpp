#include <glad/glad.h>
#include <imgui.h>
#include "Engine.h"

class Maingame : public Engine
{
protected:
    void OnUpdate(float deltaTime) override
    {
        (void)deltaTime;
    }
    void OnRender() override
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }
    void OnImGui() override
    {
        ImGui::ShowDemoWindow();
    }
};

int main()
{
    Maingame gameApp;
    if (!gameApp.Initialize("Window", 800, 600))
    {
        return -1;
    }
    gameApp.Run();
    gameApp.Shutdown();
    return 0;
}
