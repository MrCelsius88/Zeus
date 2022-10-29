#include "zeus.h"

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = 
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

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
    float verticies[] = 
    {
        // 0 on z axis so that it looks 2D
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };
    
    //~ NOTE(Cel): TEST OPENGL CODE 
    uint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    
    uint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    uint vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    // NOTE(Cel): Check for errors in shader compilation
    int sucess;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &sucess);
    if (!sucess)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        LOGERR("Error compiling vertex shader! ERROR: %s", infoLog);
    }
    
    uint fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &sucess);
    if (!sucess)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        LOGERR("Error compiling fragment shader! ERROR: %s", infoLog);
    }
    
    uint shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &sucess);
    if (!sucess)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        LOGERR("Error linking shader! ERROR: %s", infoLog);
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    //~ NOTE(Cel): END TEST OPENGL CODE 
    
    while (!glfwWindowShouldClose(window))
    {
        //~ PROCESS INPUT
        ProcessInput(window);
        //~ UPDATE
        
        //~ RENDER
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        //~ CHECK EVENTS & SWAP BUFFERS
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}