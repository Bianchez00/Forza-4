TARGET = F4Client
CC = gcc
SRC_DIR = Src
INC_DIR = Inc
CFLAGS = -Wall -Wextra -std=c99
INCLUDES = -I./Inc

SOURCES = $(SRC_DIR)/F4Client.c $(SRC_DIR)/errExit.c $(SRC_DIR)/Shared_memory.c
HEADERS = $(INC_DIR)/errExit.h $(INC_DIR)/shared_memory.h

OBJECTS = $(SOURCES: .c=.o)
INPUT_PARAMS = Pietro X

$(TARGET): $(OBJECT)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCLUDES)-c $< -o $@ -I$(INC_DIR)

run: $(TARGET)
	./$(TARGET) $(INPUT_PARAMS)
clean:
	rm -f $(OBJECTS) $(TARGET)
