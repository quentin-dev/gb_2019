game:
	make -C build -j4

lib:
	make -C gbdk-n

all: lib game

.PHONY: clean

clean:
	make -C build clean
