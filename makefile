EXEC = cppaudiocapture

CLIB = -I./lib/portaudio/include ./lib/portaudio/lib/.libs/libportaudio.a -lrt -lasound -ljack -pthread -I/lib/pocketsphinx -L. -lpocketsphinx -lm

$(EXEC): VC_Command_Recognition.cpp
	g++ -o $@ $^ $(CLIB)

install-deps:
	mkdir -p lib
	curl https://files.portaudio.com/archives/pa_stable_v190700_20210406.tgz | tar -zx -C lib
	cd lib/portaudio && ./configure && $(MAKE) -j
	cd lib && git clone https://github.com/cmusphinx/pocketsphinx.git
	cd lib/pocketsphinx && cmake -S . -B build && cmake --build build && cmake --build build --target install
.PHONY: install-deps

uninstall-deps: 
	cd lib/portaudio && $(MAKE) uninstall
	rm -rf lib/portaudio
	rm -rf lib/pocketsphinx
.PHONY: uninstall-deps

clean:
	rm -f $(EXEC) 
.PHONY: clean
