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
    
    // NOTE(Cel): Alr now for the ULTIMATE OPENGL TEST, rendering a triangle
    float rectangle[] = 
    {
        // Position          // Colors            // Texcoords
        0.5f, 0.5f, 0.0f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,    1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f,   1.0f, 1.0f, 0.0f,    0.0f, 1.0f,
    };
    
    uint indicies[] =
    {
        0, 1, 3, // First Triangle
        1, 2, 3  // Second Triangle
    };
    
    // TODO(Cel): Temporary Memory Arena, ill pull this out later (JUST FOR TESTING)
    u8* backBuff = malloc(4096);
    M_ArenaInit(&testArena, (void*)backBuff, 4096);
    
    //~ NOTE(Cel): TEST OPENGL CODE
    
    // TODO(Cel): Abstract all of this into a VAO and VBO stuct
    uint rectArrObj;
    glGenVertexArrays(1, &rectArrObj);
    glBindVertexArray(rectArrObj);
    
    uint rectVBO;
    glGenBuffers(1, &rectVBO);
    glBindBuffer(GL_ARRAY_BUFFER, rectVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rectangle), rectangle, GL_STATIC_DRAW);
    
    uint rectEBO;
    glGenBuffers(1, &rectEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rectEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
    Shader shader = CreateShader(&testArena, "res/shaders/vertexShader.vs", "res/shaders/fragmentShader.fs");
    
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
        Mat4 trans = HMM_Translate(HMM_Vec3(0.5f, -0.5f, 0.0f));
        trans = HMM_MultiplyMat4(trans, HMM_Rotate((float)glfwGetTime() * 50, HMM_Vec3(0.f, 0.f, 1.f)));
        
        Mat4 trans2 = HMM_Translate(HMM_Vec3(-0.5f, 0.5f, 0.0f));
        trans2 = HMM_MultiplyMat4(trans2, HMM_Scale(HMM_Vec3(fabsf(sinf((float)glfwGetTime())), fabsf(sinf((float)glfwGetTime())), fabsf(sinf((float)glfwGetTime())))));
        
        //~ RENDER
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        BindShader(shader);
        
        glBindVertexArray(rectArrObj);
        
        ShaderUniformMat4(shader, "transform", trans);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        ShaderUniformMat4(shader, "transform", trans2);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        //~ CHECK EVENTS & SWAP BUFFERS
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    
    glfwTerminate();
    return 0;
}