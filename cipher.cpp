#include <string>
#include "CipherInterface.h"
#include "DES.h"
#include "AES.h"

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
	if ((argc == 2 && strcmp(argv[1], "help") == 0 || argc != 6)) {
		print_usage();
		exit(-1);
	}
	else {
		if (strcmp(argv[1],"DES") == 0) { CipherInterface* cipher = new DES(); }
		else if (strcmp(argv[1], "AES") == 0) { CipherInterface* cipher = new AES(); }
		else {
			fprintf(stderr, "Invalid <CIPHER NAME>. run ./cipher help for help.\n");
			exit(-1);
		}
	}

	/* Error checks */
	if(!cipher)
	{
		fprintf(stderr, "ERROR [%s %s %d]: could not allocate memory\n",	
		__FILE__, __FUNCTION__, __LINE__);
		exit(-1);
	}
	
	/* Set the encryption key
	 * A valid key comprises 16 hexidecimal
	 * characters. Below is one example.
	 * Your program should take input from
	 * command line.
	 */
	cipher->setKey((unsigned char*)"0123456789abcdef");
	
	/* Perform encryption */
	//string cipherText = cipher->encrypt("hello world");
	
	/* Perform decryption */
	//cipher->decrypt(cipherText);	
	
	return 0;
}

void print_usage() {
	fprintf(stderr, "ERROR! Invalid parameter count!\n"
		"Usage: ./cipher <CIPHER NAME> <KEY> <ENC/DEC> <INPUT FILE> <OUTPUT FILE>\n"
			"\t<CIPHER NAME> - The name of the cipher. One of DES/AES\n"
			"\t<KEY> - The encryption key to use. 16 chars in length exactly\n"
			"\t<ENC/DEC> - One of ENC or DEC, denoting encryption or decryption respectively\n"
			"\t<INPUT FILE> - Name of the input file you would like encrypted/decrypted\n"
			"\t<OUTPUT FILE> - Name of the output file you want content written to\n"
	);	
}