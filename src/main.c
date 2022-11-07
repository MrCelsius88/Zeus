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
    u8* backBuff = malloc(512);
    M_ArenaInit(&testArena, (void*)backBuff, 512);
    
    //~ NOTE(Cel): TEST OPENGL CODE 
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
    
    //~ IMAGE LOADING
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // TODO(Cel): Determine if we want interpolation in the long run.
    
    int width, height, nChannels;
    u8* data = stbi_load("res/sprites/test_img.jpg", &width, &height, &nChannels, 0);
    assert(data);
    uint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
    
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
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(rectArrObj);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        
        //~ CHECK EVENTS & SWAP BUFFERS
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    
    glfwTerminate();
    return 0;
}