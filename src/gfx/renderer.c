func void
BeginRender(Window window)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

func void
EndRender(Window window)
{
    glfwPollEvents();
    glfwSwapBuffers(window.handle);
}