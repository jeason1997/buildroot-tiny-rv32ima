all : images

buildroot.tar.gz :
	wget https://buildroot.org/downloads/buildroot-2024.05.tar.gz
	mv buildroot-2024.05.tar.gz buildroot.tar.gz

buildroot : buildroot.tar.gz
	tar -xvf buildroot.tar.gz
	mv buildroot-2024.05 buildroot
	make -C buildroot BR2_EXTERNAL=../buildroot_overlay/ tinyrv32ima_defconfig

linux_toolchain : buildroot
	make -C buildroot
	touch linux_toolchain

goodies: linux_toolchain
	make -C goodies/hello_linux deploy
	make -C goodies/coremark deploy
	make -C goodies/c4 deploy
	make -C goodies/duktape deploy 

everything : goodies
	make -C buildroot

images : everything
	mkdir -p images
	cp buildroot/output/images/Image images/
	cp buildroot/output/images/rootfs.ext2 images/rootfs

clean:
	make -C goodies/hello_linux clean
	make -C goodies/coremark clean
	make -C goodies/c4 clean
	make -C goodies/duktape clean 
	rm -rf images linux_toolchain buildroot *.tar.gz
