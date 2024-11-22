CC = gcc
CFLAGS = -O3 -g
LDFLAGS = -L. 
LDLIBS = -lppm -lm

TARGET = test mandel
LIB = libppm.so

all: $(TARGET)

$(LIB): ppm.c ppm.h
	$(CC) $(CFLAGS) -fpic -shared $< -o $@

test: main.c $(LIB)
	$(CC) $(CFLAGS) $(LDFLAGS) $< $(LDLIBS) -o $@

mandel: mandel.c $(LIB)
	$(CC) $(CFLAGS) $(LDFLAGS) $< $(LDLIBS) -o $@

clean:
	rm -f $(TARGET) $(LIB)
