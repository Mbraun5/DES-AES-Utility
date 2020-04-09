#include <string>
#include "CipherInterface.h"
#include "DES.h"
#include "AES.h"
#include <fstream>

using namespace std;

void print_usage();

int main(int argc, char** argv)
{
	/**
	 * TODO: Replace the code below	to SWITCH
	 * between DES and AES and encrypt files. 
	 * DO NOT FORGET TO PAD
	 * THE LAST BLOCK IF NECESSARY.
	 */
	CipherInterface* cipher = NULL;
	ifstream infile;
	ofstream outfile;
	unsigned char* memblock;
	int BUFFER_SIZE;

	/** 
	 * If argument count != 6, not every parameter was added correctly.
	 * If argument count is 2 and the 2nd argument is 'help', omit the 'Invalid parameter count' line
	 */
	if ((argc == 2 && strcmp(argv[1], "help") == 0 || argc != 6)) {
		if (!argv[1] || strcmp(argv[1], "help") != 0) { fprintf(stderr, "ERROR! Invalid parameter count!\n"); }
		print_usage();
		exit(-1);
	}

	/* Set the cipher using flag from 2nd command line argument */
	if (strcmp(argv[1],"DES") == 0) { cipher=new DES(); BUFFER_SIZE=64;}
	else if (strcmp(argv[1], "AES") == 0) { cipher=new AES(); BUFFER_SIZE=128;}
	else {		/* Only DES/AES are supported */
		fprintf(stderr, "Invalid <CIPHER NAME> - must be one of DES/AES. Run ./cipher help for help.\n");
		exit(-1);
	}
	if(!cipher) {  /* Sanity check to make sure cipher was created properly */
		fprintf(stderr, "ERROR [%s %s %d]: could not allocate memory\n",	
		__FILE__, __FUNCTION__, __LINE__);
		exit(-1);
	}

	/** 
	 * Set the encryption/decryption key for the cipher. 
	 * A valid key comprises 16 hexidecimal characters
	 */
	if (cipher->setKey((unsigned char*)argv[2])) {
		fprintf(stderr, "Valid key!\n");
	}
	else {
		fprintf(stderr, "Invalid <KEY> - must be a valid 16-length hexadecimal literal. Run ./cipher help for help.\n");
		exit(-1);
	}

	/* Input file validation */
	infile.open(argv[4], ios::in);
	if (!infile) { /* File path should be absolute or relative to cipher.cpp file */
		fprintf(stderr, "Invalid <INPUT FILE> - must be a valid local file path. Run ./cipher help for help.\n");
		exit(-1);
	}
	/* Output file validation. */
	outfile.open(argv[5], ios::out | ios::trunc);
	if (!outfile) { /* If error is thrown, system is unable to create new file in working directory */
		fprintf(stderr, "Invalid <OUTPUT FILE> and unable to create new file in directory - "
						"must be a valid local file path. Run ./cipher help for help.\n");
		exit(-1);	
	}

	memblock = new unsigned char [BUFFER_SIZE];
	/* Error checks */

	
	/* Perform encryption */
	//string cipherText = cipher->encrypt("hello world");
	
	/* Perform decryption */
	//cipher->decrypt(cipherText);	
	
	return 0;
}

void print_usage() {
	fprintf(stderr,
		"Usage: ./cipher <CIPHER NAME> <KEY> <ENC/DEC> <INPUT FILE> <OUTPUT FILE>\n"
			"\t<CIPHER NAME> - The name of the cipher for encryption/decryption. One of DES/AES\n"
			"\t<KEY> - The encryption key to use. 16 chars in length exactly\n"
			"\t<ENC/DEC> - One of ENC or DEC, denoting encryption or decryption respectively\n"
			"\t<INPUT FILE> - Name of the input file you would like encrypted/decrypted\n"
			"\t<OUTPUT FILE> - Name of the output file you want content written to\n"
	);	
}