OUT=fbcat.real

all: $(OUT)

$(OUT): fbcat.c
	gcc -o $@ $< $(CFLAGS) `pkg-config --libs --cflags elementary` $(LDFLAGS)

clean:
	rm -f $(OUT)
