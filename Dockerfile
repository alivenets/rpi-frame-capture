FROM ubuntu:20.04

ENV TZ=Europe/Berlin
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update && apt-get install -y sudo git cmake build-essential

RUN git clone --progress --verbose https://github.com/raspberrypi/tools.git --depth=1 pitools

RUN cd pitools && ./sysidk --install pkg/scripts-bin.tgz

ENV PATH=/pitools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian-x64/bin:${PATH}
ENV BCM_ALLOW_ROOT=yes

RUN git clone --progress --verbose https://github.com/raspberrypi/userland
RUN cd userland && mkdir build && cd build && cmake .. -DCMAKE_TOOLCHAIN_FILE=$(pwd)/../makefiles/cmake/toolchains/arm-linux-gnueabihf.cmake -DCMAKE_INSTALL_PREFIX=/usr && make -j4 && sudo make install

ENTRYPOINT /bin/bash