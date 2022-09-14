CC      := clang
CFLAGS  := -c -fstack-protector-strong -O2 -g -Wall -Wextra -Wpedantic
LDFLAGS := -O2 -fuse-ld=lld
        
OBJ     := main.o meminfo.o date.o disk.o
TARGET  := bar

.PHONY: all
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJ) $(TARGET)
