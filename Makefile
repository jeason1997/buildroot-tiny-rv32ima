all : images

buildroot.tar.gz :
	wget https://buildroot.org/downloads/buildroot-2024.05.tar.gz
	mv buildroot-2024.05.tar.gz buildroot.tar.gz

buildroot : buildroot.tar.gz
	tar -xvf buildroot.tar.gz
	mv buildroot-2024.05 buildroot
	# make -C buildroot BR2_EXTERNAL=../buildroot_overlay/ tinyrv32ima_defconfig

linux_toolchain : buildroot
	make -C buildroot
	touch linux_toolchain

goodies: linux_toolchain
	make -C goodies/hibernate deploy
	make -C goodies/hello_linux deploy
	make -C goodies/coremark deploy
	
everything : goodies
	make -C modules install
	make -C buildroot

images/dtb : devicetree/devicetree.dts
	dtc -I dts -O dtb -o $@ $^ -S 2048

devicetree : images/dtb

images : everything
	mkdir -p images
	cp buildroot/output/images/Image images/
	cp buildroot/output/images/rootfs.ext2 images/rootfs
	make devicetree
	echo s > images/stat

run_emu :
	make -C host_emu
	host_emu/mini-rv32ima -f images/Image -B images/rootfs -b images/dtb
	
hibernate : images
	make -C host_emu
	host_emu/mini-rv32ima -f images/Image -B images/rootfs -S images/snap -b images/dtb -X

clean:
	make -C modules clean 
	make -C goodies/hibernate clean
	make -C goodies/hello_linux clean
	make -C goodies/coremark clean
	make -C host_emu clean 
	rm -rf images linux_toolchain buildroot *.tar.gz

