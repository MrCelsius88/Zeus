/* date = November 7th 2022 8:39 pm */

#ifndef TEXTURE_H
#define TEXTURE_H

typedef struct
{
    uint handle;
    int width, height;
} Texture;

typedef struct
{
    u8* data;
    int width, height;
} Image;

func Image
LoadImage(const char* path);

func void
UnloadImage(Image image);

func Texture
CreateTextureFromImage(Image image);

func Texture
CreateTexture(const char* path);

func void
BindTexture(Texture texture);

func void
UnloadTexture(Texture texture);

#endif //TEXTURE_H
