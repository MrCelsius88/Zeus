func VAO
CreateVAO()
{
    VAO out;
    glGenVertexArrays(1, &out.handle);
    
    return out;
}

func void
BindVAO(VAO vao)
{
    glBindVertexArray(vao.handle);
}

func void
VAOAttribute(VAO currentVAO, VBO buffer, GLuint index, GLint size, GLenum type, GLsizei stride, size_t offset)
{
    BindVAO(currentVAO);
    BindVBO(buffer);
    
    glVertexAttribPointer(index, size, type, GL_FALSE, stride, (void*)offset);
    glEnableVertexAttribArray(index);
}

func void
DestroyVAO(VAO vao)
{
    glDeleteVertexArrays(1, &vao.handle);
}

func VBO
CreateVBO(GLenum type, bool dynamic)
{
    VBO out = { .type = type, .dynamic = dynamic };
    glGenBuffers(1, &out.handle);
    
    return out;
}

func void
VBOBuffer(VBO vbo, size_t dataSize, void* data)
{
    glBindBuffer(vbo.type, vbo.handle);
    glBufferData(vbo.type, dataSize, data, vbo.dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}

func void
BindVBO(VBO vbo)
{
    glBindBuffer(vbo.type, vbo.handle);
}

func void
DestroyVBO(VBO vbo)
{
    glDeleteBuffers(1, &vbo.handle);
}