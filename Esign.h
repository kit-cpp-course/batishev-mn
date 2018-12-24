#pragma once
#include <boost/random.hpp>
#include "ECpoint.h"
#include "Ecurve.h"
#include "hash3411.h"
#include <string>
#include <vector>

using namespace random;
typedef uint8_t byte;

//Создание подписи по ГОСТ Р34.10-2001
class Esign
{
private:
	std::string tobinarystr(cpp_int);
	cpp_int strtoint(std::string);
	cpp_int GeneratePrivateKey();
	ECpoint GeneratePublicKey(cpp_int);
	std::string s4tohex(std::string);
public:
	Ecurve curve;
	ECpoint P, Q;
	cpp_int d;

	Esign();
	Esign(const Ecurve &, const ECpoint &);

	std::string tohex(std::string);

	std::string GenerateSign(std::vector<byte>);
	std::string GenerateSign(std::string);
	bool VerifySign(std::string, std::string);
	bool VerifySign(std::string , std::vector<byte>);
};

