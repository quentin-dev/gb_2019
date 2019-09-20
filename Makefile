game:
	make -C build -j4

.PHONY: clean

clean:
	make -C build clean
