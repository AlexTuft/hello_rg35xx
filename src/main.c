#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/fb.h>

int main(void) {
    int fb = open("/dev/fb1", O_RDWR);

    if (fb == -1) {
        printf("Failed to open framebuffer\n");
        return 1;
    }

    struct fb_var_screeninfo screeninfo;
    if (ioctl(fb, FBIOGET_VSCREENINFO, &screeninfo) == -1) {
        printf("Failed to read screen information\n");
        return 1;
    }

    printf("Framebuffer =======================\n");
    printf(" width: %d\n", screeninfo.xres);
    printf(" height: %d\n", screeninfo.yres);
    printf(" bpp: %d\n", screeninfo.bits_per_pixel);
    
    size_t screensize = screeninfo.xres * screeninfo.yres * screeninfo.bits_per_pixel / 8;
    uint8_t* buffer = mmap(NULL, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fb, 0);

    if (buffer == MAP_FAILED) {
        printf("Failed to map framebuffer\n");
        close(fb);
        return 1;
    }

    for (int i = 0; i < screensize; i++) {
        *(buffer + (i * 4)) = 0xFF;
        *(buffer + (i * 4) + 1) = 0x00;
        *(buffer + (i * 4) + 2) = 0x00;
        *(buffer + (i * 4) + 3) = 0x00;
    }

    munmap(buffer, screensize);
    close(fb);

    printf("Hello, RG35XX C \n");
}
