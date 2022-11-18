/* date = November 17th 2022 8:34 pm */

#ifndef CAMERA_H
#define CAMERA_H

typedef enum
{
    CAMERA_ORTHOGRAPHIC,
    CAMERA_PERSPECTIVE,
} CameraType;

typedef struct
{
    CameraType camType;
    
    Vec3 pos, dir, up;
    f32 fov, clipNear, clipFar;
} Camera;

#endif //CAMERA_H
