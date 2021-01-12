#include "rpi_capture.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    rpi_capture_ctx_t *ctx = NULL;
 
    rpi_capture_library_init();
 
    ctx = rpi_capture_ctx_alloc(0);

    unsigned char *image = NULL;
    size_t len = 0;
    rpi_capture_ctx_screenshot(ctx, &image, &len);

    FILE *fp = fopen("test.bin", "w");
    fwrite(image, 1, len, fp);
    fclose(fp);

    free(image);
    rpi_capture_ctx_release(ctx);
    free(ctx);
}
