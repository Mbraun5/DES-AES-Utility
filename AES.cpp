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
	for (int i=0; i<17; i++){
		this->key[i] = keyArray[i+1];
	}
	if (keyArray[0] == 0x00){
		if (AES_set_encrypt_key(this->key, 128, &this->aes_key) != 0) {
			fprintf(stderr, "AES_set_encrypt_key() failed!\n");
			return false
		}
	}
	else {
		if (AES_set_decrypt_key(this->key, 128, &this->aes_key) != 0) {
			fprintf(stderr, "AES_set_decrypt_key() failed!\n");
			return false
		}
	}	
	fprintf(stdout, "DES KEY: ");

	/* Print the key */
	for(int keyIndex = 0; keyIndex < 8; ++keyIndex)
		fprintf(stdout, "%x", this->aes_key[keyIndex]);
	
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
	
	//TODO: 1. Dynamically allocate a block to store the ciphertext.
	//	2. Use AES_ecb_encrypt(...) to encrypt the text (please see the URL in setKey(...)
	//	and the aes.cpp example provided.
	// 	3. Return the pointer to the ciphertext
		
	return NULL;	
}

/**
 * Decrypts a string of ciphertext
 * @param cipherText - the ciphertext
 * @return - the plaintext
 */
unsigned char* AES::decrypt(const unsigned char* cipherText)
{
	
	//TODO: 1. Dynamically allocate a block to store the plaintext.
	//	2. Use AES_ecb_encrypt(...) to decrypt the text (please see the URL in setKey(...)
	//	and the aes.cpp example provided.
	// 	3. Return the pointer to the plaintext
		
	return NULL;
}



