my_dir := $(patsubst %/,%,$(dir $(abspath $(lastword $(MAKEFILE_LIST)))))

build_dir := $(my_dir)/build

all:
	mkdir -p $(build_dir)
	cmake -S $(my_dir) -B $(build_dir)
	cmake --build $(build_dir)

run: all
	$(build_dir)/sfml_tut
