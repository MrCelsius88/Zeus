/* date = November 11th 2022 9:13 pm */

#ifndef VERTEX_OBJECTS_H
#define VERTEX_OBJECTS_H

typedef struct
{
    uint handle;
} VAO;

typedef struct
{
    uint handle;
    GLenum type;
    bool dynamic;
} VBO;

func VAO
CreateVAO();

func void
BindVAO(VAO vao);

func void
VAOAttribute(VAO currentVAO, VBO buffer, GLuint index, GLint size, GLenum type, GLsizei stride, size_t offset);

func void
DestroyVAO(VAO vao);

func VBO
CreateVBO(GLenum type, bool dynamic, size_t dataSize, void* data);

func void
BindVBO(VBO vbo);

func void
DestroyVBO(VBO vbo);

#endif //VERTEX_OBJECTS_H
