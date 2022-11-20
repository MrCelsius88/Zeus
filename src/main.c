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
    cam.fov = 60.f;
    cam.clipNear = 0.1f;
    cam.clipFar = 100.f;
    
    //Texture tex1 = CreateTexture("res/sprites/test_img2.png");
    Texture texAtlas = CreateTexture("/home/giannib/dev/DungeonMaster/res/sprites/0x72_DungeonTilesetII_v1.4/0x72_DungeonTilesetII_v1.4.png");
    V4 texRect = GetInnerTexcoords(texAtlas, HMM_Vec4(128, 100, 16, 28));
    
    while (!WindowShouldClose(window))
    {
        //~ PROCESS INPUT
        
        //~ UPDATE
        
        //~ RENDER
        BeginRender(renderer);
        {
            //RendererUseCamera(&renderer, &cam);
            
            RenderQuadTexture(renderer, texAtlas, texRect, HMM_Vec3(0.f, 0.f, 0.f), HMM_Vec2(160.f, 280.f), 0);
        }
        EndRender(renderer);
        
        UpdateWindow(&window);
    }
    
    ZeusClose();
    return 0;
}