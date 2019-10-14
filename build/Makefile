CC = ../gbdk-n/bin/gbdk-n-compile.sh
LD = ../gbdk-n/bin/gbdk-n-link.sh
MAKER = ../gbdk-n/bin/gbdk-n-make-rom.sh

SDCCFLAGS = -I ../include

vpath %.c ../src
vpath %.c ../tests

TEST_CC = gcc
TEST_CFLAGS = -I ../include -Wall -Wextra -Werror -std=c99 -pedantic
TEST_LD_FLAGS = -lcriterion

TEST_OBJS = test_direction.o direction.o

TESTS = test_direction

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

check: $(TESTS)
	for t in $(TESTS); do \
		echo "Running $$t"; \
		./$$t; \
	done;

test_%: test_%.o %.o
	$(TEST_CC) -o $@ $^ $(TEST_LD_FLAGS)

%.o: %.c
	$(TEST_CC) $(TEST_CFLAGS) -c $^

.PHONY: clean

clean:
	$(RM) $(ROM) $(IHX:.ihx=.*) $(RELS:.rel=.*) $(TESTS) $(TEST_OBJS) 