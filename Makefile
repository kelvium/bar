CC      := clang
CFLAGS  := -c -fstack-protector-strong -O2 -g -Wall -Wextra -Wpedantic
LDFLAGS := -O2 -fuse-ld=lld -lasound
        
OBJ     := main.o basic.o alsa.o
TARGET  := bar

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJ) $(TARGET)
