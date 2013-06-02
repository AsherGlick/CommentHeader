all : chead

chead: main.cpp headertitle.h pipein.h
	mkdir -p bin
	g++ main.cpp -o ./bin/chead -Wall

install: chead
	cp ./bin/chead /usr/bin/chead

uninstall:
	rm /usr/bin/chead

clean:
	rm -r ./bin

test: chead
	python unitTest.py 
