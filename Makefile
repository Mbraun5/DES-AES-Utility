.PHONY: clean all

HEADERS_DIR=./include
SRC_DIR=./src
OBJ_DIR=./obj

all: $(OBJ_DIR) cipher

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

cipher: $(OBJ_DIR)/cipher.o $(OBJ_DIR)/DES.o $(OBJ_DIR)/AES.o
	g++ $(OBJ_DIR)/cipher.o $(OBJ_DIR)/DES.o $(OBJ_DIR)/AES.o -o cipher -lcrypto

$(OBJ_DIR)/cipher.o: $(SRC_DIR)/cipher.cpp
	g++ -g -c $(SRC_DIR)/cipher.cpp -o $(OBJ_DIR)/cipher.o

$(OBJ_DIR)/DES.o: $(SRC_DIR)/DES.cpp $(HEADERS_DIR)/DES.h
	g++ -g -c $(SRC_DIR)/DES.cpp -o $(OBJ_DIR)/DES.o

$(OBJ_DIR)/AES.o: $(SRC_DIR)/AES.cpp $(HEADERS_DIR)/AES.h
	g++ -g -c $(SRC_DIR)/AES.cpp -o $(OBJ_DIR)/AES.o

clean:
	rm -rf $(OBJ_DIR) cipher
