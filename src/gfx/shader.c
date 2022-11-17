func int
CompileShader(const char* path, GLenum type)
{
    FILE* shaderSource;
    u32 length;
    char* text;
    
    shaderSource = fopen(path, "rb");
    if (shaderSource == NULL)
    {
        LOGERR("Unable to load shader at: %s", path);
        return -1;
    }
    
    fseek(shaderSource, 0, SEEK_END);
    length = ftell(shaderSource);
    assert(length > 0);
    fseek(shaderSource, 0, SEEK_SET);
    
    text = malloc(length);
    assert(text);
    
    assert(fread(text, 1, length, shaderSource) == length);
    fclose(shaderSource);
    
    uint shader = glCreateShader(type);
    glShaderSource(shader, 1, (const char* const*)&text, &length);
    glCompileShader(shader);
    
    // Check for errors
    int success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        LOGERR("Error Compiling Shader! Error: %s", infoLog);
    }
    
    free(text);
    return shader;
}

func Shader
CreateShader(const char* VSPath, const char* FSPath)
{
    Shader out;
    out.vertexShader = CompileShader(VSPath, GL_VERTEX_SHADER);
    out.fragmentShader = CompileShader(FSPath, GL_FRAGMENT_SHADER);
    out.handle = glCreateProgram();
    
    glAttachShader(out.handle, out.vertexShader);
    glAttachShader(out.handle, out.fragmentShader);
    glLinkProgram(out.handle);
    
    int success = 0;
    glGetProgramiv(out.handle, GL_LINK_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(out.handle, 512, NULL, infoLog);
        LOGERR("Error Linking Shader! Error: %s", infoLog);
    }
    
    return out;
}

func void
BindShader(Shader shader)
{
    glUseProgram(shader.handle);
}

func void
DestroyShader(Shader shader)
{
    glDeleteProgram(shader.handle);
    glDeleteShader(shader.vertexShader);
    glDeleteShader(shader.fragmentShader);
}

SHADER_UNIFORM_FUNC(ShaderUniformBool, bool)
{
    glUniform1i(glGetUniformLocation(shader.handle, name), val);
}
SHADER_UNIFORM_FUNC(ShaderUniformInt, int)
{
    glUniform1i(glGetUniformLocation(shader.handle, name), val);
}
SHADER_UNIFORM_FUNC(ShaderUniformF32, f32)
{
    glUniform1f(glGetUniformLocation(shader.handle, name), val);
}
SHADER_UNIFORM_FUNC(ShaderUniformMat4, Mat4)
{
    glUniformMatrix4fv(glGetUniformLocation(shader.handle, name), 1, GL_FALSE, (f32*)&val);
}