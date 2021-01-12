#ifndef _RPI_CAPTURE_H
#define _RPI_CAPTURE_H

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

struct _rpi_capture_ctx;
typedef struct _rpi_capture_ctx rpi_capture_ctx_t;

int rpi_capture_library_init();

rpi_capture_ctx_t *rpi_capture_ctx_alloc(int screen);

int rpi_capture_ctx_screenshot(rpi_capture_ctx_t *ctx, unsigned char **image, size_t *len);

int rpi_capture_ctx_release(rpi_capture_ctx_t *ctx);

#ifdef __cplusplus
}
#endif

#endif // _RPI_CAPTURE_H
