#pragma once
#include "signature.h"
#include <boost/random.hpp>
#include "ECpoint.h"
#include "Ecurve.h"
#include <string>
#include <vector>

using namespace random;
typedef uint8_t byte;

class Esign: public signature {
private:
	//Метод конвертирующий число в строку бит
	std::string tobinarystr(cpp_int);
	//Метод конвертирующий строку бит в число
	cpp_int strtoint(std::string);
	//Метод генерации закрытого ключа
	cpp_int GeneratePrivateKey();
	//Метод создания открытого ключа по закрытому
	ECpoint GeneratePublicKey(cpp_int);
	//Эллиптическая кривая
	Ecurve curve;
	//Q - публичный ключ
	//Р - точка кривой
	ECpoint P, Q;
	//d - закрытый ключ
	cpp_int d;
public:

	Esign();
	Esign(const Ecurve &, const ECpoint &);

	//Перегружаем виртуальный метод родительского класса для генерации подписи
	void generate(std::vector<byte>);
	//Метод провверки подписи
	bool VerifySign(std::string, std::vector<byte>);
};

