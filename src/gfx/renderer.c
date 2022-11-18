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
    
    // NOTE(Cel): Setup a default projection and view matrix
    out.projections.view = HMM_Mat4d(1.f);
    
    // TODO(Cel): Figure out if it should go
    // 0.f, window->height
    // or
    // window->height, 0.f
    // The latter makes (0, 0) the top left of the screen, if we
    // do this I want to make sure that we can also replicate it
    // with a perspective camera. If we can't lets just leave it at
    // this.
    out.projections.projection = HMM_Orthographic(0.f, window->width, 0.f, window->height, -1.f, 1.f);
    
    return out;
}

func void
RendererUseCamera(Renderer* renderer, Camera* camera)
{
    if (camera != NULL || renderer->camera != camera)
    { 
        renderer->camera = camera;
    }
    
    // NOTE(Cel): Now we implement the camera
    BindShader(renderer->shader);
    renderer->projections.view = HMM_LookAt(camera->pos, camera->dir, camera->up);
    if (camera->camType == CAMERA_PERSPECTIVE)
    {
        renderer->projections.projection = HMM_Perspective(camera->fov, renderer->window->width / renderer->window->height, camera->clipNear, camera->clipFar);
    }
    else if (camera->camType == CAMERA_ORTHOGRAPHIC)
    {
        renderer->projections.projection = HMM_Orthographic(0.f, renderer->window->width, 0.f, renderer->window->height, camera->clipNear, camera->clipFar);
    }
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
    ShaderUniformMat4(renderer.shader, "view", renderer.projections.view);
    ShaderUniformMat4(renderer.shader, "projection", renderer.projections.projection);
    
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