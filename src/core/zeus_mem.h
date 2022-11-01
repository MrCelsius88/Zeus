/* date = October 30th 2022 6:49 pm */

#ifndef ZEUS_MEM_H
#define ZEUS_MEM_H

typedef struct
{
    u8* buff;
    size_t length, offset;
} M_Arena;

func uintptr_t
AlignForward(uintptr_t ptr, size_t align);

func void
M_ArenaInit(M_Arena* arena, void* backBuffer, size_t backBufferSize);

func void*
M_ArenaAlloc(M_Arena* arena, size_t size);

func void*
M_ArenaReset(M_Arena* arena);

#endif //ZEUS_MEM_H
