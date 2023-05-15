CC           := clang
CCFLAGS      := --std=c2x -O3 -Wall -Wextra
INCLUDE_DIRS := ./includes/
OBJDIR       := build
SRCDIR       := src
BIN          := $(OBJDIR)/main

INCLUDE_FLAGS ?= $(foreach D,$(INCLUDE_DIRS), -I$(D))
OBJS          ?= $(patsubst src/%.c, $(OBJDIR)/%.o, $(wildcard $(SRCDIR)/*.c))
DEPENDS       ?= $(patsubst src/%.c, $(OBJDIR)/%.d, $(wildcard $(SRCDIR)/*.c))

.PHONY: clean all

all: Makefile $(OBJDIR) $(OBJS) $(BIN)

$(BIN): $(OBJS)
	$(CC) $^ -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CCFLAGS) ${INCLUDE_FLAGS} -MMD -MP -c $< -o $@

-include $(DEPENDS)

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	$(info removing the $(OBJDIR) directory...)
	@rm -rf $(OBJDIR)
