# Declare configuration block start

OUT_DIR     = out
EXECUTABLE  = speller

# Compiler flags, i.e first standard, debug level and gdb support
# Warnings as errors
# and sanitize options
# and sanitize options

CFLAGS      = -O0 -std=c11 -ggdb3 \
              -Wall -Werror -Wextra -Wno-sign-compare -Wno-unused-parameter \
              -Wno-unused-variable -Wshadow \
              -fsanitize=signed-integer-overflow -fsanitize=undefined

# Libraries required for GCC compilation. Sometimes clang appends it by default,
# but usually no.

LIBS        = -lubsan

# Sources

SRCS        = dictionary.c speller.c

# We use a hack here with path mangling
# https://stackoverflow.com/questions/5178125/how-to-place-object-files-in-separate-subdirectory

OBJS        = $(patsubst %,$(OUT_DIR)/%,$(SRCS:.c=.o))

# Declare configuration block end

# all target - runs all targets, useful as convention and to clean first
# This becomes the default target if plain "make" is invoked

all: clean directories speller

# clean target - wipes the output directory we declared in the configuration block

clean:
	rm -rf $(OUT_DIR)

# speller target - take $OBJS (.c source names renamed to .o)

speller: directories $(OBJS)
	$(CC) $(LDFLAGS) -o $(OUT_DIR)/$(EXECUTABLE) $(OBJS) $(LIBS)

# create output directory

directories:
	mkdir -p $(OUT_DIR)

$(OUT_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

# Declare phony targets (ie "dummy" targets which produce
# no file output

# https://www.gnu.org/software/make/manual/html_node/Phony-Targets.html

.PHONY: all clean
