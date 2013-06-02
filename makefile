all : chead

chead: source/main.cpp source/headertitle.h source/pipein.h
	mkdir -p bin
	g++ source/main.cpp -o ./bin/chead -Wall

install: chead
	cp ./bin/chead /usr/bin/chead

uninstall:
	rm /usr/bin/chead

clean:
	rm -r ./bin

test: chead
	(cd tests && python Tests.py)
