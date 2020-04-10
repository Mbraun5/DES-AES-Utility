#include <string>
#include "CipherInterface.h"
#include "DES.h"
#include "AES.h"
#include <stdio.h>

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
	FILE* infile;
	FILE* outfile;
	unsigned char* pblock; 
	unsigned char* nblock;
	int BUFFER_SIZE;
	bool encrypt;

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

	if (strcmp(argv[3], "ENC") == 0) { encrypt = true; }
	else if (strcmp(argv[3], "DEC") == 0) { encrypt = false; }
	else {
		fprintf(stderr, "Invalid <ENC/DEC> - must be one of ENC/DEC, denoting whether to encrypt or decrypt respectively. Run ./cipher help for help.\n");
		exit(-1);
	}

	/** 
	 * Set the encryption/decryption key for the cipher. 
	 * A valid key comprises 16 hexidecimal characters
	 */
	if (!cipher->setKey((unsigned char*)argv[2])) {
		fprintf(stderr, "Invalid <KEY> - must be a valid 16-length hexadecimal literal. Run ./cipher help for help.\n");
		exit(-1);
	}

	/* Input file validation */
	infile = fopen(argv[4], "rb");
	if (infile == NULL) { /* File path should be absolute or relative to cipher.cpp file */
		fprintf(stderr, "Invalid <INPUT FILE> - must be a valid local file path. Run ./cipher help for help.\n");
		exit(-1);
	}
	/* Output file validation. */
	outfile = fopen(argv[5], "wb+");
	if (outfile == NULL) { /* If error is thrown, system is unable to create new file in working directory */
		fprintf(stderr, "Invalid <OUTPUT FILE> and unable to create new file in directory - "
						"must be a valid local file path. Run ./cipher help for help.\n");
		exit(-1);	
	}

	pblock = new unsigned char [BUFFER_SIZE];
	nblock = new unsigned char [BUFFER_SIZE];
	int bytes;
	while (!feof(infile)) {
			bytes = fread(pblock, sizeof(unsigned char), BUFFER_SIZE, infile);

			if (encrypt) { nblock = cipher->encrypt(pblock); }
			else { nblock = cipher->decrypt(pblock); }

			if (fwrite(nblock, sizeof(unsigned char), bytes, outfile) != bytes) {
				fprintf(stderr, "Did not write correct amount of lines to new file.\n");
				exit(-1);
			}

			memset(pblock, '\0', BUFFER_SIZE);
			memset(nblock, '\0', BUFFER_SIZE);
	}

	
	/* Perform encryption */
	//string cipherText = cipher->encrypt("hello world");
	
	/* Perform decryption */
	//cipher->decrypt(cipherText);

	fclose(infile);
	fclose(outfile);
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