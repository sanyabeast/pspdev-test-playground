#include <stdint.h>


namespace GFX{
    void init();
    void clear(uint32_t color);
    void swap_buffers();
    void draw_rect(unsigned int x, unsigned int y, unsigned int w, unsigned int h, uint32_t color);

}

