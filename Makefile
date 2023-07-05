build:
	docker run --rm -v "$(CURDIR)":/root/workspace/src rust-rg35xx make
deploy:
	adb devices > /dev/null
	adb push target/armv7-unknown-linux-gnueabihf/debug/hello_rg35xx /mnt/mmc/Roms/APPS/
