all: fbcat

fbcat: fbcat.c
	gcc -o $@ $< `pkg-config --libs --cflags ecore`

clean:
	rm -f fbcat
