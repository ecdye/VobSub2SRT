.PHONY: all clean distclean documentation install uninstall

all: build
	$(MAKE) -C build

clean: build
	$(MAKE) -C build clean

distclean:
	rm -rf build/

documentation: build
	$(MAKE) -C build documentation

install: build
	$(MAKE) -C build install

uninstall: build
	$(MAKE) -C build uninstall

build:
	@echo "Please run ./configure (with appropriate parameters)!"
	@exit 1
