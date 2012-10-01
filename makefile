all : chead

chead: main.cpp headertitle.h pipein.h
	g++ main.cpp -o chead -Wall

install: chead
	cp chead /bin/chead

uninstall:
	rm /bin/chead

clean:
	rm chead
test: chead
	python unitTest.py
