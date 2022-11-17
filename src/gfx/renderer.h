/* date = November 14th 2022 8:57 pm */

#ifndef RENDERER_H
#define RENDERER_H

#define DEFAULT_VERTEX_SHADER_PATH "res/shaders/vertexShader.vs"
#define DEFAULT_FRAGMENT_SHADER_PATH "res/shaders/fragmentShader.fs"

typedef struct
{
    Window* window;
    Shader shader;
    
    VAO quadVAO;
} Renderer;

func Renderer
CreateRenderer(Window* window);

func void
BeginRender(Renderer renderer);

func void
EndRender(Renderer renderer);

#endif //RENDERER_H
