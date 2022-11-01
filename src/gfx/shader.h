/* date = October 30th 2022 2:28 pm */

#ifndef SHADER_H
#define SHADER_H

#define SHADER_UNIFORM_FUNC(func_name, type) func void func_name(Shader shader, char* name, type val)

typedef struct
{
    uint handle, vertexShader, fragmentShader;
} Shader;

func int
CompileShader(M_Arena* arena, const char* path, GLenum type); // NOTE(Cel): Called by CreateShader.

func Shader
CreateShader(M_Arena* arena, const char* VSPath, const char* FSPath);

func void
BindShader(Shader shader);

func void
DestroyShader(Shader shader);

SHADER_UNIFORM_FUNC(ShaderUniformBool, bool);
SHADER_UNIFORM_FUNC(ShaderUniformInt, int);
SHADER_UNIFORM_FUNC(ShaderUniformF32, f32);

#endif //SHADER_H
