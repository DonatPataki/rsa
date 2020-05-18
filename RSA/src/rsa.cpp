#include "rsa.h"

unsigned long long rsa::fastMod(unsigned long long base, unsigned long long exp, unsigned long long mod)
{
	unsigned long long result;
	for (result = 1; exp; exp >>= 1)
	{
		if (exp & 1)
			result = (result * base) % mod;
		base = (base * base) % mod;
	}
	return result;
}

long long rsa::extendedEuc(unsigned long long a, unsigned long long b, long long x, long long y)
{
	while (b != 0)
	{
		unsigned long long uTemp = a;
		a = b;
		b = uTemp % b;
		long long sTemp = x;
		x = y;
		y = sTemp - y * (uTemp / a);
	}

	return x;
}

unsigned long long rsa::gcd(unsigned long long a, unsigned long long b)
{
	while (b != 0)
	{
		unsigned long long uTemp = a;
		a = b;
		b = uTemp % b;
	}

	return a;
}

rsa::rsa(unsigned long long p, unsigned long long q)
	:p(p), q(q)
{
	n = p * q;
	phi = (p - 1) * (q - 1);
	std::srand(std::time(nullptr));
	e = std::rand() % (phi / 200) + (phi / 5000);
	while (e < phi)
	{
		if (gcd(phi, e) == 1)
			break;
		e++;
	}
	{
		long long temp = extendedEuc(phi, e);
		while (temp < 0)
			temp += phi;
		d = temp;
	}
}

rsa::rsa(pkey publicKey)
	:p(0), q(0), n(publicKey.n), phi(0), e(publicKey.e), d(0)
{
}

unsigned long long rsa::encrypt(unsigned long long message)
{
	return fastMod(message, e, n);
}

unsigned long long rsa::decrypt(unsigned long long encryptedMessage)
{
	return fastMod(encryptedMessage, d, n);
}

pkey rsa::getPublicKey()
{
	pkey publicKey(n, e);
	return publicKey;
}
