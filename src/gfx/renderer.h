/* date = November 14th 2022 8:57 pm */

#ifndef RENDERER_H
#define RENDERER_H

#define DEFAULT_VERTEX_SHADER_PATH "res/shaders/vertexShader.vs"
#define DEFAULT_FRAGMENT_SHADER_PATH "res/shaders/fragmentShader.fs"

typedef struct
{
    Mat4 view, projection;
} Projections;

typedef struct
{
    Window* window;
    Camera* camera;
    
    Shader shader;
    VAO quadVAO;
    VBO quadVBO;
    
    Projections projections;
} Renderer;

func Renderer
CreateRenderer(Window* window);

func void
RendererUseCamera(Renderer* renderer, Camera* camera);

func void
BeginRender(Renderer renderer);

func void
RenderQuadTexture(Renderer renderer, Texture texture, Vec4 texCoords, Vec3 pos, Vec2 size, f32 rotate);

func void
EndRender(Renderer renderer);

#endif //RENDERER_H
