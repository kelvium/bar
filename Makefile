CC      := clang
CFLAGS  := -c -fstack-protector-strong -O0 -g -Wall -Wextra -Wpedantic
LDFLAGS := -O0 -fuse-ld=lld
        
OBJ     := main.o
TARGET  := bar

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJ) $(TARGET)
