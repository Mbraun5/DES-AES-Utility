#ifndef AES_H
#define AES_H

#include <stdio.h>
#include <stdlib.h>
#include <openssl/aes.h>
#include <string.h>
#include <string>
#include "CipherInterface.h"
#include <ctype.h>

using namespace std;

/** 
 * Implements a AES cipher
 */
class AES: public CipherInterface
{
	/* The public members */
	public:
		
		/**
		 * The default constructor
	 	 */
		AES(){}
			
		/**
		 * Sets the key to use
		 * @param key - the key to use
		 * @return - True if the key is valid and False otherwise
		 */
		virtual bool setKey(const unsigned char* key);

		/**	
		 * Encrypts a plaintext string
		 * @param plainText - the plaintext string
		 * @return - the encrypted ciphertext string
		 */
		virtual unsigned char* encrypt(const unsigned char* plainText);

		/**
		 * Decrypts a string of cipherText
		 * @param ciphertext - the cipherText
		 * @return - the plaintext
		 */
		virtual unsigned char* decrypt(const unsigned char* cipherText);
	
			
	/* The protected members */
	protected:

		/**
		 * Converts a character into a hexidecimal integer
		 * @param character - the character to convert
		 * @return - the converted character, or 'z' on error
		 */
		unsigned char charToHex(const char& character);

		/**
		 * Converts two characters into a hex integers
		 * and then inserts the integers into the higher
		 * and lower bits of the byte
		 */
		unsigned char twoCharToHexByte(const unsigned char* twoChars);

		/* The 128-bit, user-defined encryption key */
		unsigned char aes_key[16];

		/* The key structure used by the AES library */
		AES_KEY key;
};


#endif
