#include "zeus.h"

int main(int argc, char** argv)
{
    Window window = CreateWindow(APP_NAME, HMM_Vec2(WINDOW_WIDTH, WINDOW_HEIGHT));
    // These are a lot of verticies 
    float verticies[] =
    {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    
    Vec3 cubePositions[] = 
    {
        HMM_Vec3( 0.0f,  0.0f,  0.0f), 
        HMM_Vec3( 2.0f,  5.0f, -15.0f), 
        HMM_Vec3(-1.5f, -2.2f, -2.5f),  
        HMM_Vec3(-3.8f, -2.0f, -12.3f),  
        HMM_Vec3( 2.4f, -0.4f, -3.5f),  
        HMM_Vec3(-1.7f,  3.0f, -7.5f),  
        HMM_Vec3( 1.3f, -2.0f, -2.5f),  
        HMM_Vec3( 1.5f,  2.0f, -2.5f), 
        HMM_Vec3( 1.5f,  0.2f, -1.5f), 
        HMM_Vec3(-1.3f,  1.0f, -1.5f)  
    };
    
    Renderer renderer = CreateRenderer(&window);
    
    //~ COORDINATE SYSTEMS
    Mat4 view = HMM_Translate(HMM_Vec3(0.f, 0.f, -3.f));
    Mat4 projection = HMM_Perspective(45.f, 800.f / 600.f, 0.1f, 100.f);
    
    //~ TEXTURE LOADING
    Texture tex1 = CreateTexture("res/sprites/test_img2.png");
    
    //~ NOTE(Cel): END TEST OPENGL CODE 
    
    while (!WindowShouldClose(window))
    {
        //~ PROCESS INPUT
        
        //~ UPDATE
        BindShader(renderer.shader);
        ShaderUniformMat4(renderer.shader, "view", view);
        ShaderUniformMat4(renderer.shader, "projection", projection);
        
        //~ RENDER
        BeginRender(renderer);
        
        RenderQuadTexture(renderer, tex1, HMM_Vec3(0.f, 0.f, 0.f), HMM_Vec2(1.f, 1.f), 0);
        
        EndRender(renderer);
        
        UpdateWindow(&window);
    }
    
    glfwTerminate();
    return 0;
}