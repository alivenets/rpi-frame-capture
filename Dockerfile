FROM tttapa/rpi-cross:aarch64-rpi3-linux-gnu

RUN ./userland.sh

ENTRYPOINT /bin/bash