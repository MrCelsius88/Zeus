/* date = October 24th 2022 5:12 pm */

#ifndef ZEUS_H
#define ZEUS_H

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

//~ GRAPHICS
#include "gfx/shader.h"
#include "gfx/shader.c"

//~ MEMORY MANAGEMENT
#include "zeus_mem.h"
#include "zeus_mem.c"

#include "app.h"

#endif //ZEUS_H

