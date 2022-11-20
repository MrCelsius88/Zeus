func Image
LoadImage(const char* path)
{
    //stbi_set_flip_vertically_on_load(true);
    int width, height, nChannels;
    u8* img = stbi_load(path, &width, &height, &nChannels, STBI_rgb_alpha);
    if (img == NULL) { LOGERR("Unable to load image at: %s", path); }
    
    Image out;
    out.data = malloc(width * height * 4); // NOTE(Cel): 4 = rgba
    memcpy(out.data, img, width * height * 4);
    out.width = width;
    out.height = height;
    
    stbi_image_free(img);
    return out;
}

func void
UnloadImage(Image image)
{
    assert(image.data);
    free(image.data);
}

func Texture
CreateTextureFromImage(Image image)
{
    Texture out = { .width = image.width, .height = image.height };
    glGenTextures(1, &out.handle);
    glBindTexture(GL_TEXTURE_2D, out.handle);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // TODO(Cel): Determine if we want interpolation in the long run.
    // NOTE(Cel): We dont for this pixel art game we are making.
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image.width, image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data);
    //glGenerateMipmap(GL_TEXTURE_2D);
    
    return out;
}

func Texture
CreateTexture(const char* path)
{
    Image img = LoadImage(path);
    Texture out = CreateTextureFromImage(img);
    UnloadImage(img);
    
    return out;
}

func void
BindTexture(Texture texture)
{
    glBindTexture(GL_TEXTURE_2D, texture.handle);
}

func void
UnloadTexture(Texture texture)
{
    glDeleteTextures(1, &texture.handle);
}

func Vec4
GetInnerTexcoords(Texture atlas, Vec4 rect)
{
    f32 texWidth = atlas.width;
    f32 texHeight = atlas.height;
    
    rect.ZW = HMM_AddVec2(rect.XY, rect.ZW);
    rect = HMM_DivideVec4(rect, HMM_Vec4(texWidth, texHeight, texWidth, texHeight));
    
    return rect;
}