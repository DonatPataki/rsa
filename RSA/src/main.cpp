#include <iostream>

#include "rsa.h"

int main()
{
	rsa bob(49171, 59221);
	rsa alice(bob.getPublicKey());

	unsigned long long m = 2545454552;
	std::cout << "message: " << m << std::endl;
	unsigned long long encryptedM = alice.encrypt(m);
	std::cout << "encrypted message: " << encryptedM << std::endl;

	unsigned long long decryptedM = bob.decrypt(encryptedM);
	std::cout << "decrypted message: " <<  decryptedM << std::endl;
}