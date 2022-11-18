func Renderer
CreateRenderer(Window* window)
{
    Renderer out;
    out.window = window;
    out.shader = CreateShader(DEFAULT_VERTEX_SHADER_PATH, DEFAULT_FRAGMENT_SHADER_PATH);
    
    VBO vbo;
    f32 buffer[] = 
    {
        // Pos          // Tex
        0.f, 1.f, 0.f,  0.f, 1.f,
        1.f, 0.f, 0.f,  1.f, 0.f,
        0.f, 0.f, 0.f,  0.f, 0.f,
        
        0.f, 1.f, 0.f,  0.f, 1.f, 
        1.f, 1.f, 0.f,  1.f, 1.f,
        1.f, 0.f, 0.f,  1.f, 0.f,
    };
    
    out.quadVAO = CreateVAO();
    vbo = CreateVBO(GL_ARRAY_BUFFER, false, sizeof(buffer), buffer);
    VAOAttribute(out.quadVAO, vbo, 0, 3, GL_FLOAT, 5 * sizeof(f32), 0);
    VAOAttribute(out.quadVAO, vbo, 1, 2, GL_FLOAT, 5 * sizeof(f32), 3 * sizeof(f32));
    
    return out;
}

func void
BeginRender(Renderer renderer)
{
    // NOTE(Cel): Just clear to black, if I ever want to change, ill add more functionality.
    glClearColor(1.f, 1.f, 1.f, 1.0f); 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    
    BindShader(renderer.shader);
}

func void
RenderQuadTexture(Renderer renderer, Texture texture, Vec3 pos, Vec2 size, f32 rotate)
{
    BindShader(renderer.shader);
    
    Mat4 model = HMM_Translate(pos);
    model = HMM_MultiplyMat4(model, HMM_Translate(HMM_Vec3(0.5f * size.X, 0.5f * size.Y, 0.f)));
    model = HMM_MultiplyMat4(model, HMM_Rotate(rotate, HMM_Vec3(0.f, 0.f, 1.f)));
    model = HMM_MultiplyMat4(model, HMM_Translate(HMM_Vec3(-0.5f * size.X, -0.5f * size.Y, 0.f)));
    model = HMM_MultiplyMat4(model, HMM_Scale(HMM_Vec3(size.X, size.Y, 1.f)));
    
    ShaderUniformMat4(renderer.shader, "model", model);
    
    BindVAO(renderer.quadVAO);
    BindTexture(texture);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

func void
EndRender(Renderer renderer)
{
    glfwSwapBuffers(renderer.window->handle);
}