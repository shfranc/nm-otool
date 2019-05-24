#include "ft_nm.h"

void        *is_in_file(t_bin_file *file, void *dest, size_t size)
{
    void       *max;

    max = dest + size;
    if (dest >= file->ptr && max <= file->end)
        return (dest);
    return (NULL);
}