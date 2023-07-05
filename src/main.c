#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/fb.h>

int main(void) {
    int fb = open("/dev/fb0", O_RDWR);

    if (fb == -1) {
        printf("Failed to open framebuffer");
        return 1;
    }

    struct fb_var_screeninfo screeninfo;
    if (ioctl(fb, FBIOGET_VSCREENINFO, &screeninfo) == -1) {
        printf("Failed to read screen information");
        return 1;
    }

    printf("Framebuffer dimensions: %d %d\n", screeninfo.xres, screeninfo.yres);
    close(fb);

    printf("Hello, RG35XX C \n");
}
