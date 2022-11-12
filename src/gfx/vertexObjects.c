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
DestroyVAO(VAO vao)
{
    glDeleteVertexArrays(1, &vao.handle);
}

func VBO
CreateVBO(GLenum type, bool dynamic, size_t dataSize, void* data)
{
    VBO out = 
    {
        .type = type,
        .dynamic = dynamic
    };
    glGenBuffers(1, &out.handle);
    
    glBindBuffer(type, out.handle);
    glBufferData(type, dataSize, data, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
    
    return out;
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