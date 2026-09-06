#include <glad/glad.h>
#include "Engine.h"

class MainGameApp : public Engine
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
};

int main()
{
    MainGameApp gameApp;
    if (!gameApp.Initialize("Window", 800, 600))
    {
        return -1;
    }
    gameApp.Run();
    gameApp.Shutdown();
    return 0;
}
