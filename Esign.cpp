#include "Esign.h"

Esign::Esign() : curve(), P(), Q(), d(){}

Esign::Esign(const Ecurve &nc, const ECpoint &np) : curve(nc), P(np), Q(), d(){}

//Генератор приватного ключа
cpp_int Esign::GeneratePrivateKey() {
	mt19937 mt(time(0));
	uniform_int_distribution<cpp_int> ui(1, curve.m/curve.h - 1);
	return ui(mt);
}

//Генератор публичного ключа по приватному
ECpoint Esign::GeneratePublicKey(cpp_int nd) {
	return P.multiply(nd);
}

//Принимает чило, возвращает его бинарное представление, дополненое нулями до 256 символов 
std::string Esign::tobinarystr(cpp_int num) {
	std::vector<unsigned char> numv;
	export_bits(num, std::back_inserter(numv), 1);
	std::string res = "";
	for (size_t i = 0; i < numv.size(); i++) {
		res += (int)numv[i] + '0';
	}
	if (res.size() < 256) {
		do {
			res = "0" + res;
		} while (res.size() < 256);
	}
	return res;
}

//Востанавливает число из его бинарного представления 
cpp_int Esign::strtoint(std::string bi) {
	std::vector<byte> num(bi.size());
	for (size_t i = 0; i < bi.size(); i++) {
		if ((bi[i] != '0') && (bi[i] != '1')) throw("Not binary string!");
		num[i] = bi[i] - '0';
	}
	cpp_int res;
	import_bits(res, num.begin(), num.end(), 1);
	return res;
}

//Преобразует битовую строку из 4 символов в шестнадцатиричную цифру
std::string Esign::s4tohex(std::string str) {
	if (str.size() != 4) throw("Wrong string!");
	if (str == "0000") return "0";
	if (str == "0001") return "1";
	if (str == "0010") return "2";
	if (str == "0011") return "3";
	if (str == "0100") return "4";
	if (str == "0101") return "5";
	if (str == "0110") return "6";
	if (str == "0111") return "7";
	if (str == "1000") return "8";
	if (str == "1001") return "9";
	if (str == "1010") return "a";
	if (str == "1011") return "b";
	if (str == "1100") return "c";
	if (str == "1101") return "d";
	if (str == "1110") return "e";
	if (str == "1111") return "f";
	throw("Wrong string!");
}

//Преобразует бинарную строку к шестнадцатиричному виду
std::string Esign::tohex(std::string sg) {
	if (sg.size() != 512) throw("Wrong size!");
	std::string res = "0x";
	for (int i = 0; i < 128; i++) {
		res += s4tohex(sg.substr(4*i, 4));
	}
	return res;
}

//Генерирует подпись по последовательности байт
std::string Esign::GenerateSign(std::vector<byte> h) {
	d = GeneratePrivateKey();
	//d = cpp_int("55441196065363246126355624130324183196576709222340016572108097750006097525544");
	Q = GeneratePublicKey(d);
	cpp_int a, q = curve.m/curve.h;
	import_bits(a, h.begin(), h.end());
	cpp_int e = a % q;
	if (e == 0) e = 1;
	//e = cpp_int("20798893674476452017134061561508270130637142515379653289952617252661468872421");
	mt19937 mt(time(0));
	uniform_int_distribution<cpp_int> ui(1, q - 1);
	cpp_int k, r, s;
	//k = cpp_int("53854137677348463731403841147996619241504003434302020712960838528893196233395");
	do {
		k = ui(mt);
		r = P.multiply(k).x % q;
		s = (r * d + k * e) % q;
	} while ((k == 0) || (s == 0));
	return tobinarystr(r) + tobinarystr(s);
}

//Подпись сообщения
std::string Esign::GenerateSign(std::string message) {
	//Хэшируем сообщение и подписываем его
	return GenerateSign(hash3411::get_Instance().calculate_Hash(message));
}

//Проверка подписи по последовательности байт
bool Esign::VerifySign(std::string sign, std::vector<byte> h) {
	if (sign.size() != 512) return false;
	cpp_int r, s;
	try {
		r = strtoint(sign.substr(0, 256));
		s = strtoint(sign.substr(256, 256));
	}
	catch (...) {
		return 0;
	}
	cpp_int a, q = curve.m / curve.h;
	if ((r > q) || (s > q)) 
		return false;
	import_bits(a, h.begin(), h.end());
	cpp_int e = a % q;
	//e = cpp_int("20798893674476452017134061561508270130637142515379653289952617252661468872421");
	if (e == 0) e = 1;
	cpp_int v = cpp_int(powm(e, q - 2, q)) % q;
	cpp_int z1 = (s * v) % q, z2 = q + (-r * v) % q;
	cpp_int R = ((P.multiply(z1) + Q.multiply(z2)).x) % q;
	return R == r;
}

//Проверка подписи по сообщению
bool Esign::VerifySign(std::string sign, std::string message) {
	//Хэшируем сообщение и проверяем подпись
	return VerifySign(sign, hash3411::get_Instance().calculate_Hash(message));
}