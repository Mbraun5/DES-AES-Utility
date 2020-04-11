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
	for(int idx=1; idx<32; idx+=2) {
		/* Convert the key if the character is valid */
		if((this->aes_key[idx/2] = twoCharToHexByte(keyArray + idx)) == 'z')
			return false;
	}

	/* Print the key */
	fprintf(stdout, "AES KEY: ");
	for(int idx=0; idx<16; idx++)
		fprintf(stdout, "%x", this->aes_key[idx]);
	fprintf(stdout, "\n");	
	
	/* If first index is set to 0x00, then user passed in ENC */
	if (keyArray[0] == 0x00){
		if (AES_set_encrypt_key(this->aes_key, 128, &this->key) != 0) {
			fprintf(stderr, "AES_set_encrypt_key() failed!\n");
			return false;
		}
	}
	/* Otherwise, DEC */
	else {
		if (AES_set_decrypt_key(this->aes_key, 128, &this->key) != 0) {
			fprintf(stderr, "AES_set_decrypt_key() failed!\n");
			return false;
		}
	}

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

/**
 * Converts a character into a hexidecimal integer
 * @param character - the character to convert
 * @return - the converted character, or 'z' on error
 */
unsigned char DES::charToHex(const char& character)
{
	/* Is the first digit 0-9 ? */	
	if(character >= '0' && character <= '9')	
		/* Convert the character to hex */
		return character - '0';
	/* It the first digit a letter 'a' - 'f'? */
	else if(character >= 'a' && character <= 'f')
		/* Conver the cgaracter to hex */
		return (character - 97) + 10;	
	/* Invalid character */
	else return 'z';
}

unsigned char AES::twoCharToHexByte(const unsigned char* twoChars)
{
	/* The byte */
	unsigned char singleByte;
	
	/* The second character */
	unsigned char secondChar;

	/* Convert the first character */
	if((singleByte = charToHex(twoChars[0])) == 'z') 
	{
		/* Invalid digit */
		return 'z';
	}
	
	/* Move the newly inserted nibble from the
	 * lower to upper nibble.
	 */
	singleByte = (singleByte << 4);
	
	/* Conver the second character */
	if((secondChar = charToHex(twoChars[1])) == 'z')
		return 'z'; 
	
	/* Insert the second value into the lower nibble */	
	singleByte |= secondChar;

	return singleByte;
}

