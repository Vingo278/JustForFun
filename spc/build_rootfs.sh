#/bin/bash
#解压ubuntu-base-16.04.3-base-amd64.tar.gz生成rootfs镜像

ROOTFS_PACKET=ubuntu-base-16.04.3-base-amd64.tar.gz
ROOTFS_PACKET_URL=http://cdimage.ubuntu.com/ubuntu-base/releases/16.04/release/ubuntu-base-16.04.3-base-amd64.tar.gz
mkdir -p ./rootfs
if [ ! -f $ROOTFS_PACKET ]; then
    wget $ROOTFS_PACKET_URL
fi
tar -xpf ubuntu-base-16.04.3-base-amd64.tar.gz -C rootfs
