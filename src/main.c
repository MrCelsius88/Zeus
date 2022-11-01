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
    float triangle1[] = 
    {
        // Position            // Colors
        0.5f, -0.5f, 0.0f,    1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,
        0.0f, 0.5f, 0.0f,     0.0f, 0.0f, 1.0f
    };
    
    // TODO(Cel): Temporary Memory Arena, ill pull this out later (JUST FOR TESTING)
    u8* backBuff = malloc(512);
    M_ArenaInit(&testArena, (void*)backBuff, 512);
    
    //~ NOTE(Cel): TEST OPENGL CODE 
    uint triangle1ArrObj;
    glGenVertexArrays(1, &triangle1ArrObj);
    glBindVertexArray(triangle1ArrObj);
    
    uint triangle1BuffObj;
    glGenBuffers(1, &triangle1BuffObj);
    glBindBuffer(GL_ARRAY_BUFFER, triangle1BuffObj);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle1), triangle1, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
    // TODO(Cel): Figure out why relative paths aren't working.
    Shader shader = CreateShader(&testArena, "res/shaders/vertexShader.vs", "res/shaders/fragmentShader.fs");
    
    //~ NOTE(Cel): END TEST OPENGL CODE 
    
    while (!glfwWindowShouldClose(window))
    {
        //~ PROCESS INPUT
        ProcessInput(window);
        //~ UPDATE
        
        //~ RENDER
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        BindShader(shader);
        
        glBindVertexArray(triangle1ArrObj);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        //~ CHECK EVENTS & SWAP BUFFERS
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    
    glfwTerminate();
    return 0;
}