shell = comet.c
shell_script = comet

comet_source = $(shell find comet_source/ -type f -name '*.c')
comet_object = $(patsubst %.c, %.o, $(comet_source))

tests_source = $(shell find comet_tests/ -type f -name '*.c')
tests_script = $(patsubst %.c, %, $(tests_source))

CC = gcc
CC_FLAGS = -O3 -Wall -Wextra -Wpedantic -fshort-enums 
CC_FLAGS += -Wl,--gc-sections -fdata-sections -ffunction-sections 
CC_FLAGS += -Wfatal-errors -std=c99 -fearly-inlining 

default: all

.PHONY: clean clean_comet clean_tests clean_all

clean_all: clean clean_comet clean_tests

clean:
	rm -rf $(target)
	
clean_comet:
	rm -rf $(comet_object)
	
clean_tests:
	rm -rf $(tests_script)

$(comet_object): %.o: %.c
	$(CC) $(CC_FLAGS) -c $< -o $@

$(shell): $(comet_object)
	$(CC) $(CC_FLAGS) $(comet_object) $(shell) -o $(shell_script) 

build: $(comet_object)
	$(CC) $(CC_FLAGS) $(comet_object) $(shell) -o $(shell_script) 

tests: clean_all $(comet_object) $(tests_script)

$(tests_script): %: %.c
	$(CC) $(CC_FLAGS) $(comet_object) $< -o $@
	./$@
	
all: clean build

