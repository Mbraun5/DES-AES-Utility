#include "AES.h"

/**
 * Sets the key to use
 * @param key - the first byte of this represents whether
 * to encrypt or to decrypt. 00 means encrypt and any other
 * value to decrypt.  Then come the bytes of the 128-bit key
 * (should be 16 of them).
 * @return - True if the key is valid and False otherwise
 */
bool AES::setKey(const unsigned char* keyArray)
{
	/* Copy over valid bytes to key array */
	for (int i=0; i<17; i++){
		this->key[i] = keyArray[i+1];
	}
	
	/* If first index is set to 0x00, then user passed in ENC */
	if (keyArray[0] == 0x00){
		if (AES_set_encrypt_key(this->key, 128, &this->aes_key) != 0) {
			fprintf(stderr, "AES_set_encrypt_key() failed!\n");
			return false;
		}
	}
	/* Otherwise, DEC */
	else {
		if (AES_set_decrypt_key(this->key, 128, &this->aes_key) != 0) {
			fprintf(stderr, "AES_set_decrypt_key() failed!\n");
			return false;
		}
	}

	/* If key was valid, print the key the user passed in */
	fprintf(stdout, "AES PRE-KEY: ");
	for(int keyIndex = 0; keyIndex < 16; ++keyIndex)
		fprintf(stdout, "%c", this->key[keyIndex]);
	fprintf(stdout, "\n");

	return true;	
}

/**	
 * Encrypts a plaintext string
 * @param plaintext - the plaintext string
 * @return - the encrypted ciphertext string
 */
unsigned char* AES::encrypt(const unsigned char* plainText)
{
	/* Create output buffer */
	unsigned char* bytes = new unsigned char[16];
	memset(bytes, 0, 16);
	
	/* Encrypt file using AES key */
	AES_ecb_encrypt(plainText, bytes, &this->aes_key, AES_ENCRYPT);

	return bytes;
}

/**
 * Decrypts a string of ciphertext
 * @param cipherText - the ciphertext
 * @return - the plaintext
 */
unsigned char* AES::decrypt(const unsigned char* cipherText)
{
	/* Create output buffer */
	unsigned char* bytes = new unsigned char[16];
	memset(bytes, 0, 16);

	/* Decrypt file using AES key */
	AES_ecb_encrypt(cipherText, bytes, &this->aes_key, AES_DECRYPT);

	return bytes;
}



