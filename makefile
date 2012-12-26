all : chead

chead: main.cpp headertitle.h pipein.h
	g++ main.cpp -o chead -Wall

install: chead
	cp chead /usr/bin/chead

uninstall:
	rm /usr/bin/chead

clean:
	rm chead
test: chead
	python unitTest.py
