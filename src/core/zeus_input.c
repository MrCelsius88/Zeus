func bool
GetKeyDown(Window window, int key)
{
    if (glfwGetKey(window.handle, key) == GLFW_PRESS)
        return true;
    
    return false;
}

func bool
GetKeyUp(Window window, int key)
{
    if (glfwGetKey(window.handle, key) == GLFW_RELEASE)
        return true;
    
    return false;
}