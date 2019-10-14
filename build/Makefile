CC = ../gbdk-n/bin/gbdk-n-compile.sh
LD = ../gbdk-n/bin/gbdk-n-link.sh
MAKER = ../gbdk-n/bin/gbdk-n-make-rom.sh

SDCCFLAGS = -I ../include

vpath %.c ../src

ROM = game.gb

# RELS = player.rel mapmap.rel mapset.rel player_sprites.rel main.rel
RELS = breakoutset.rel breakoutmap.rel breakout.rel paddle.rel ball.rel
RELS += collision.rel direction.rel

IHX = main.ihx

game: $(ROM)

$(ROM): $(IHX)
	$(MAKER) $^ $@

$(IHX): $(RELS)
	$(LD) $^ -o $@

%.rel: %.c
	$(CC) $(SDCCFLAGS) $^

.PHONY: clean

clean:
	$(RM) $(ROM) $(IHX:.ihx=.*) $(RELS:.rel=.*)
