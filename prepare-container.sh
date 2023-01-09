#/bin/bash

set -e

apt update
apt install -y vim libudev-dev

if [ ! -f /usr/lib/x86_64-linux-gnu/libudev.so.1.6.17.orig ]; then
    cp /usr/lib/x86_64-linux-gnu/libudev.so.1.6.17 /usr/lib/x86_64-linux-gnu/libudev.so.1.6.17.orig
fi
make
cp libfakeudev.so /usr/lib/x86_64-linux-gnu/libudev.so.1.6.17
ln -sf /usr/lib/x86_64-linux-gnu/libudev.so.1.6.17 /usr/lib/x86_64-linux-gnu/libudev.so.1
