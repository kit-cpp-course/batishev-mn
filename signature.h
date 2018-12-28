#pragma once
#include <string>
#include <vector>

typedef uint8_t byte;

//Абстрактный класс подписи
class signature {
protected:
	//Сама подпись
	std::string sign;
	//Преобразует битовую строку из 4 символов в шестнадцатиричную цифру
	std::string s4tohex(std::string str) const  {
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

public:
	//Виртуальный метод генерации подписи
	//Принимает на вход последовательность байт
	virtual void generate(std::vector<byte>) = 0;

	//Метод возвращающий подпись подписи
	std::string get_sign() const {
		return sign;
	}

	//Приводит строку к шестнадцатиричному виду
	std::string tohex() const {
		if (sign.size() % 4 != 0) { 
			throw("Wrong size!");
		}
		std::string res = "0x";
		for (int i = 0; i < sign.size()/4; i++) {
			res += s4tohex(sign.substr(4 * i, 4));
		}
		return res;
	}
};