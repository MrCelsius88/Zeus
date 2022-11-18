#include "zeus.h"

int main(int argc, char** argv)
{
    Window window = CreateWindow(APP_NAME, WINDOW_WIDTH, WINDOW_HEIGHT);
    Renderer renderer = CreateRenderer(&window);
    
    Camera cam;
    cam.camType = CAMERA_PERSPECTIVE;
    cam.pos = HMM_Vec3(0.f, 2.f, 3.f);
    cam.dir = HMM_Vec3(0.f, 0.f, 0.f);
    cam.up = HMM_Vec3(0.f, 1.f, 0.f);
    cam.fov = 45.f;
    cam.clipNear = 0.1f;
    cam.clipFar = 100.f;
    
    //~ COORDINATE SYSTEMS
    Mat4 view = HMM_Translate(HMM_Vec3(0.f, 10.f, -3.f));
    Mat4 projection = HMM_Perspective(45.f, 800.f / 600.f, 0.1f, 100.f);
    
    //~ TEXTURE LOADING
    Texture tex1 = CreateTexture("res/sprites/test_img2.png");
    
    //~ NOTE(Cel): END TEST OPENGL CODE 
    
    while (!WindowShouldClose(window))
    {
        //~ PROCESS INPUT
        
        //~ UPDATE
        
        //~ RENDER
        BeginRender(renderer);
        {
            RendererUseCamera(&renderer, &cam);
            
            RenderQuadTexture(renderer, tex1, HMM_Vec3(0.f, 0.f, 0.f), HMM_Vec2(1.f, 1.f), 0);
        }
        EndRender(renderer);
        
        UpdateWindow(&window);
    }
    
    glfwTerminate();
    return 0;
}