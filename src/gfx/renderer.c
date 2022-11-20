func Renderer
CreateRenderer(Window* window)
{
    Renderer out;
    out.window = window;
    out.shader = CreateShader(DEFAULT_VERTEX_SHADER_PATH, DEFAULT_FRAGMENT_SHADER_PATH);
    
    out.quadVAO = CreateVAO();
    BindVAO(out.quadVAO);
    out.quadVBO = CreateVBO(GL_ARRAY_BUFFER, false);
    
    // NOTE(Cel): Setup a default projection and view matrix
    out.projections.view = HMM_Mat4d(1.f);
    out.projections.projection = HMM_Orthographic(0.f, window->width, 0.f, window->height, -1.f, 1.f);
    
    return out;
}

func void
RendererUseCamera(Renderer* renderer, Camera* camera)
{
    renderer->camera = camera;
    if (camera != NULL)
    {
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
    else
    { 
        // NOTE(Cel): Revert back to default projection and view
        renderer->projections.view = HMM_Mat4d(1.f);
        renderer->projections.projection = HMM_Orthographic(0.f, renderer->window->width, 0.f, renderer->window->height, -1.f, 1.f);
    }
}

func void
BeginRender(Renderer renderer)
{
    // NOTE(Cel): Just clear to black, if I ever want to change, ill add more functionality.
    glClearColor(1.f, 1.f, 1.f, 1.0f); 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    BindShader(renderer.shader);
}

func void
RenderQuadTexture(Renderer renderer, Texture texture, Vec4 texCoords, Vec3 pos, Vec2 size, f32 rotate)
{
    BindShader(renderer.shader);
    ShaderUniformMat4(renderer.shader, "view", renderer.projections.view);
    ShaderUniformMat4(renderer.shader, "projection", renderer.projections.projection);
    ShaderUniformTexture2D(renderer.shader, "Texture", texture);
    
    f32 buffer[] = 
    {
        // Pos          // Tex
        1.f, 0.f, 0.f,  texCoords.Z, texCoords.W,
        0.f, 0.f, 0.f,  texCoords.X, texCoords.W,
        0.f, 1.f, 0.f,  texCoords.X, texCoords.Y,
        
        1.f, 0.f, 0.f,  texCoords.Z, texCoords.W, 
        0.f, 1.f, 0.f,  texCoords.X, texCoords.Y,
        1.f, 1.f, 0.f,  texCoords.Z, texCoords.Y,
    };
    VBOBuffer(renderer.quadVBO, sizeof(buffer), buffer);
    VAOAttribute(renderer.quadVAO, renderer.quadVBO, 0, 3, GL_FLOAT, 5 * sizeof(f32), 0);
    VAOAttribute(renderer.quadVAO, renderer.quadVBO, 1, 2, GL_FLOAT, 5 * sizeof(f32), 3 * sizeof(f32));
    
    Mat4 model = HMM_Translate(pos);
    model = HMM_MultiplyMat4(model, HMM_Translate(HMM_Vec3(0.5f * size.X, 0.5f * size.Y, 0.f)));
    model = HMM_MultiplyMat4(model, HMM_Rotate(rotate, HMM_Vec3(0.f, 0.f, 1.f)));
    model = HMM_MultiplyMat4(model, HMM_Translate(HMM_Vec3(-0.5f * size.X, -0.5f * size.Y, 0.f)));
    model = HMM_MultiplyMat4(model, HMM_Scale(HMM_Vec3(size.X, size.Y, 1.f)));
    
    ShaderUniformMat4(renderer.shader, "model", model);
    
    BindVAO(renderer.quadVAO);
    BindVBO(renderer.quadVBO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

func void
EndRender(Renderer renderer)
{
    glfwSwapBuffers(renderer.window->handle);
}