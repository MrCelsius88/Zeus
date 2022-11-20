/* date = October 24th 2022 5:12 pm */

#ifndef ZEUS_H
#define ZEUS_H

//~ NON-ENGINE RELATED

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define HANDMADE_MATH
#include "../lib/HandmadeMath.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb_image.h"

#include "../lib/glad/include/glad/glad.h"
#include "../lib/glad/src/glad.c"
#include <GLFW/glfw3.h>

#include "utils.h"

//~ HEADERS

// MEMORY MANAGEMENT
#include "core/zeus_mem.h"
// GRAPHICS
#include "gfx/texture.h"
#include "gfx/shader.h"
#include "gfx/vertexObjects.h"
#include "gfx/window.h"
#include "gfx/camera.h"
#include "gfx/renderer.h"
// APP SETTINGS
#include "app.h"

//~ IMPLEMENTATION (now we can seperate implementation into a lib if we wanted.)

// MEMORY MANAGEMENT
#include "core/zeus_mem.c"
// GRAPHICS
#include "gfx/texture.c"
#include "gfx/shader.c"
#include "gfx/vertexObjects.c"
#include "gfx/window.c"
#include "gfx/camera.c"
#include "gfx/renderer.c"

// TODO(Cel): Find a better place for this, if needed.
func void
ZeusClose(void) // Used for cleanup
{
    glfwTerminate();
}

#endif //ZEUS_H

