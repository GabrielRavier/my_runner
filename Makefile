##
## EPITECH PROJECT, 2020
## myhunter
## File description:
## Makefile for this project
##

# We use `override` to enable setting part of CFLAGS on the command line
# This makes the compiler generate dependency files, which will solve any header-related dependency problems we could have had
override CFLAGS += -MMD -MP -MF $@.d

# We need to be able to include the libmy include files
override CFLAGS += -Iinclude

# We need to be able to link to libmy, and link to it
override LDFLAGS += -Llib $(CFLAGS)

.PHONY: all clean fclean re libmy tests_run

.PREVIOUS: obj/%.o

BINARY_NAME := my_runner

all: $(BINARY_NAME)

# Sources for this project
SOURCE_FILES := main game/change_music game/create/create game/create/window game/create/font game/create/map game/create/sound game/create/sprite game/create/state_play game/create/text game/create/texture game/create/view game/destroy game/draw game/handle/key game/main_loop game/player/player game/player/do_animation_and_foot_sound game/player/apply_velocity game/object/building_bottom game/object/hallway_top/hallway_top game/object/hallway_top/make_next_hallway_part game/object_vector game/set/mode game/update/update game/update/title game/update/play/play game/update/play/sequence/sequence game/update/play/sequence/get game/is_jumping parse_argv random text_utils top_score

OBJECT_FILES := $(addprefix obj/, $(addsuffix .o, $(SOURCE_FILES)))

$(BINARY_NAME): libmy $(OBJECT_FILES)
	$(CC) $(LDFLAGS) -o $@ $(OBJECT_FILES) -lmy -lcsfml-window -lcsfml-graphics -lcsfml-system -lcsfml-audio -lm

obj/%.o: src/%.c libmy
	@mkdir --parents obj/game/create
	@mkdir --parents obj/game/draw
	@mkdir --parents obj/game/handle
	@mkdir --parents obj/game/object/hallway_top
	@mkdir --parents obj/game/set
	@mkdir --parents obj/game/update/play/sequence
	@mkdir --parents obj/game/player
	$(CC) -c $< -o $@ $(CFLAGS)

# Just build the entire libmy when we need these headers
libmy:
	$(MAKE) --directory=lib/my

# Include dependencies for the object files
include $(wildcard obj/*.d)

# Remove all object files
clean:
	rm --recursive --force obj
	$(MAKE) --directory=lib/my clean

# Remove all object, binary and other produced files
fclean: clean
	rm --force $(BINARY_NAME)
	$(MAKE) --directory=lib/my fclean

# "Remakes" the project. This rule is shit and won't work properly with parallel make, but it's not like I'm using this target, and neither is Marvin using parallel Make (afaik)
re: clean all
	$(MAKE) --directory=lib/my re

tests_run:
	$(MAKE) --directory=lib/my tests_binary
	rm -rf obj/
	$(MAKE) CFLAGS="$(CFLAGS) --coverage"
	./lib/my/tests_binary
