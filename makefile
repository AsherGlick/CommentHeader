all : chead

chead: source/main.cpp source/headertitle.h source/pipein.h
	mkdir -p bin
	g++ source/main.cpp -o ./bin/chead -Wall -std=c++0x

install: chead
	cp ./bin/chead /usr/bin/chead
	install -g 0 -o 0 -m 0644 documentation/chead.1 /usr/share/man/man1/
	gzip /usr/share/man/man1/chead.1

uninstall:
	rm /usr/bin/chead

clean:
	rm -r ./bin

test: chead
	(cd tests && python Tests.py)
