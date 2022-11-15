/*
 
Whats up with these private functions?
Well, its impossible for GLFW callback functions to modify whatever our current window struct is.
We solve this by having these functions that keep track of whatever the current window is,
for modification when we poll for events like if the window size changes.

 */


func Window*
_GetCurrentWindow(void)
{
    persist Window window;
    return &window;
}

func void
_SetCurrentWindow(Window window)
{
    Window* currentWindow = _GetCurrentWindow();
    *currentWindow = window;
}

func void 
_framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    
    Window* currentWindow = _GetCurrentWindow();
    currentWindow->dimensions = (Vec2){ width, height };
}

func Window
CreateWindow(const char* title, Vec2 dimensions)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow(dimensions.X, dimensions.Y, title, 0, 0);
    if (window == NULL)
    {
        LOGERR("Failed to create GLFW window!", 0);
        glfwTerminate();
        exit(1);
    }
    glfwMakeContextCurrent(window);
    
    // NOTE(Cel): CALLBACKS
    glfwSetFramebufferSizeCallback(window, _framebuffer_size_callback);
    
    Window out = {.handle = window, .dimensions = dimensions };
    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        LOGERR("Failed to initialize GLAD", 0);
        exit(1);
    }
    
    glEnable(GL_DEPTH_TEST);
    
    return out;
}

func void
PollWindowEvents(Window* window)
{
    _SetCurrentWindow(*window);
    glfwPollEvents();
    *window = *_GetCurrentWindow();
}

func bool
WindowShouldClose(Window window)
{
    return glfwWindowShouldClose(window.handle) ? true : false;
}