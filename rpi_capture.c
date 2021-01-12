#include "rpi_capture.h"

#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <bcm_host.h>

struct _rpi_capture_ctx
{
    DISPMANX_DISPLAY_HANDLE_T display;
    DISPMANX_MODEINFO_T info;
    uint32_t vc_image_ptr;
    DISPMANX_RESOURCE_HANDLE_T resource;
    VC_IMAGE_TYPE_T type;
    VC_IMAGE_TRANSFORM_T transform;
};

#define BYTES_PER_PIXEL 4

int rpi_capture_library_init()
{
    bcm_host_init();
    return 0;
}

rpi_capture_ctx_t *rpi_capture_ctx_alloc(int screen)
{
    int ret = 0;

    rpi_capture_ctx_t *ctx = malloc(sizeof(rpi_capture_ctx_t));

    memset(ctx, 0, sizeof(*ctx));
    ctx->display = vc_dispmanx_display_open(screen);

    ret = vc_dispmanx_display_get_info(ctx->display, &ctx->info);
    if (ret < 0) {
        perror("vc_dispmanx_display_get");
        free(ctx);
        return NULL;
    }

    ctx->type = VC_IMAGE_RGBA32;
    ctx->resource = vc_dispmanx_resource_create(ctx->type, ctx->info.width, ctx->info.height, &ctx->vc_image_ptr);
    return ctx;
}

int rpi_capture_ctx_screenshot(rpi_capture_ctx_t *ctx, unsigned char **pImage, size_t *pLen)
{
    VC_RECT_T rect;

    assert(ctx);
    assert(pImage);
    assert(pLen);

    vc_dispmanx_snapshot(ctx->display, ctx->resource, 0 /* DISPMAN_NO_ROTATE */);
    vc_dispmanx_rect_set(&rect, 0, 0, ctx->info.width, ctx->info.height);

    size_t len = ctx->info.width * ctx->info.height * BYTES_PER_PIXEL;

    unsigned char *image = (unsigned char*)malloc(len);
    if (!image) {
        perror("malloc");
        return -ENOMEM;
    }

    vc_dispmanx_resource_read_data(ctx->resource, &rect, image, len);

    *pImage = image;
    *pLen = len;

    return 0;
}

int rpi_capture_ctx_release(rpi_capture_ctx_t *ctx)
{
    int ret = 0;
    assert(ctx);
    ret = vc_dispmanx_resource_delete(ctx->resource);
    assert(ret == 0);
    ret = vc_dispmanx_display_close(ctx->display);
    assert(ret == 0);
    return ret;
}
