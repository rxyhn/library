CC = gcc
CFLAGS = -Wall
LDFLAGS =
OBJFILES = main.o src/library.o src/login.o lib/book.o lib/user.o lib/common.o
TARGET = lms

all: $(TARGET)

$(TARGET) : $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) *~