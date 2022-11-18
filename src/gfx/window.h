/* date = November 15th 2022 4:39 pm */

#ifndef WINDOW_H
#define WINDOW_H

// TODO(Cel): Support for multiple windows? Idk if I want/need this yet

typedef struct
{
    GLFWwindow* handle;
    uint width, height;
} Window;

func Window
CreateWindow(const char* title, uint width, uint height);

func void
UpdateWindow(Window* window);

func bool
WindowShouldClose(Window window);

func void
DestroyWindow(Window window);

#endif //WINDOW_H
