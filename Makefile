game:
	make -C build -j4

lib:
	make -C gbdk-n

.PHONY: clean

clean:
	make -C build clean
