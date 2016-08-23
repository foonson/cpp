
linux: visudo
linux: usermod stevecheng -a -G wheel
linux: yum install gcc gcc-c++ kernel-devel
linux: mount -r /dev/cdrom /media/vbaddin
linux: yum install dkms bzip2 tmux tmux-powerline
linux: lsmod
linux: sudo modprobe vboxadd
linux: tty
linux: uname -r
git:   git clone https://github.com/zeromq/libzmq
