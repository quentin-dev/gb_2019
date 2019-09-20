CC = ../gbdk-n/bin/gbdk-n-compile.sh
LD = ../gbdk-n/bin/gbdk-n-link.sh
MAKER = ../gbdk-n/bin/gbdk-n-make-rom.sh

SDCCFLAGS = -I../include

vpath %.c ../src

ROM = game.gb

RELS = tileset.rel tilemap.rel main.rel
IHXS = main.ihx

game: $(ROM)

$(ROM): $(IHXS)
	$(MAKER) $^ $@

$(IHXS): $(RELS)
	$(LD) $^ -o $@

%.rel: %.c
	$(CC) $(SDCCFLAGS) $^

clean:
	$(RM) $(ROM) $(RELS) $(IHXS) main.* tileset.* tilemap.*
