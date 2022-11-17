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