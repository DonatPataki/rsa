#pragma once

#include <string>
#include <cstdlib>
#include <ctime>

struct pkey {
	unsigned long long n;
	unsigned long long e;
	pkey(unsigned long long n, unsigned long long e)
		:n(n), e(e) {};
};

class rsa
{
private:
	unsigned long long p, q;
	unsigned long long n, phi;
	unsigned long long e;
	unsigned long long d;
	unsigned long long fastMod(unsigned long long number, unsigned long long power, unsigned long long mod);
	long long extendedEuc(unsigned long long a, unsigned long long b, long long x = 0, long long y = 1);
	unsigned long long gcd(unsigned long long a, unsigned long long b);
public:
	rsa(unsigned long long p, unsigned long long q);
	rsa(pkey publicKey);
	unsigned long long encrypt(unsigned long long message);
	unsigned long long decrypt(unsigned long long encryptedMessage);
	pkey getPublicKey();
};