func uintptr_t
AlignForward(uintptr_t ptr, size_t align)
{
    assert(PowerOfTwo(align));
    
    uintptr_t p, a, modulo;
    p = ptr;
    a = (uintptr_t)align;
    modulo = p & (a - 1);
    
    if (modulo != 0)
    {
        // NOTE(Cel): If p is not aligned, push the address
        // to the next value which is aligned.
        p += a - modulo;
    }
    
    return p;
}

func void
M_ArenaInit(M_Arena* arena, void* backBuffer, size_t backBufferSize)
{
    arena->buff = (u8*)backBuffer;
    arena->length = backBufferSize;
    arena->offset = 0;
}

func void*
M_ArenaAlloc(M_Arena* arena, size_t size)
{
    size_t align = 2 * sizeof(void*);
    uintptr_t currentPtr = (uintptr_t)arena->buff + (uintptr_t)arena->offset;
    uintptr_t offset = AlignForward(currentPtr, align);
    offset -= (uintptr_t)arena->buff; // Make offset relative
    
    assert(offset + size <= arena->length);
    void* ptr = arena->buff + offset;
    arena->offset = offset + size;
    memset(ptr, 0, size);
    
    return ptr;
}

func void*
M_ArenaReset(M_Arena* arena)
{
    arena->offset = 0;
}

