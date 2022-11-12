#include "zeus.h"

global M_Arena testArena;

func void 
framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

func void
ProcessInput(GLFWwindow* window)
{
    // Input processing code goes here.
    
}

int main(int argc, char** argv)
{
    // TODO(Cel): We will create a custom renderer and abstraction, this is just temporary
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, APP_NAME, 0, 0);
    if (window == NULL)
    {
        LOGERR("Failed to create GLFW window!", 0);
        glfwTerminate();
        return 1;
    }
    glfwMakeContextCurrent(window);
    
    // NOTE(Cel): Initialize GLAD before trying to call OpenGL Functions
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        LOGERR("Failed to initialize GLAD", 0);
        return 1;
    }
    
    // TODO(Cel): Add aspect ratio correction macros in app.h or in custom renderer file
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT); 
    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glEnable(GL_DEPTH_TEST);
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
    
    // TODO(Cel): Temporary Memory Arena, ill pull this out later (JUST FOR TESTING)
    u8* backBuff = malloc(4096);
    M_ArenaInit(&testArena, (void*)backBuff, 4096);
    
    //~ NOTE(Cel): TEST OPENGL CODE
    VAO cubeVAO = CreateVAO();
    BindVAO(cubeVAO);
    
    VBO cubeVBO = CreateVBO(GL_ARRAY_BUFFER, false, sizeof(verticies), verticies);
    BindVBO(cubeVBO);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    Shader shader = CreateShader(&testArena, "res/shaders/vertexShader.vs", "res/shaders/fragmentShader.fs");
    //~ COORDINATE SYSTEMS
    Mat4 model = HMM_Rotate(-55.f, HMM_Vec3(1.f, 0.f, 0.f));
    Mat4 view = HMM_Translate(HMM_Vec3(0.f, 0.f, -3.f));
    Mat4 projection = HMM_Perspective(45.f, 800.f / 600.f, 0.1f, 100.f);
    
    //~ TEXTURE LOADING
    glActiveTexture(GL_TEXTURE0);
    Texture tex1 = CreateTexture("res/sprites/test_img.jpg");
    glActiveTexture(GL_TEXTURE1);
    Texture tex2 = CreateTexture("res/sprites/test_img2.png");
    
    BindShader(shader);
    ShaderUniformInt(shader, "Texture", 0);
    ShaderUniformInt(shader, "Texture2", 1);
    ShaderUniformF32(shader, "mixVal", 0.2);
    
    //~ NOTE(Cel): END TEST OPENGL CODE 
    
    while (!glfwWindowShouldClose(window))
    {
        //~ PROCESS INPUT
        ProcessInput(window);
        
        //~ UPDATE
        model = HMM_Rotate((float)glfwGetTime() * 50.f, HMM_Vec3(0.5f, 1.f, 0.f));
        
        BindShader(shader);
        ShaderUniformMat4(shader, "model", model);
        ShaderUniformMat4(shader, "view", view);
        ShaderUniformMat4(shader, "projection", projection);
        
        //~ RENDER
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        BindShader(shader);
        
        BindVAO(cubeVAO);
        for (int i = 0; i < 10; ++i)
        {
            Mat4 model = HMM_Translate(cubePositions[i]);
            f32 angle = 20.f * (i + 1 ) * (float)glfwGetTime();
            model = HMM_MultiplyMat4(model, HMM_Rotate(angle, HMM_Vec3(1.f, 0.3f, 0.5f)));
            ShaderUniformMat4(shader, "model", model);
            
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        
        //~ CHECK EVENTS & SWAP BUFFERS
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    
    glfwTerminate();
    return 0;
}