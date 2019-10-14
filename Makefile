game:
	make -C build -j4

lib:
	make -C gbdk-n

all: lib game

.PHONY: clean

check:
	make -C build check

clean:
	make -C build clean
