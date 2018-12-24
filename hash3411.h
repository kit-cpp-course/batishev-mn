#pragma once
#include <boost/multiprecision/cpp_int.hpp>
#include <vector>
#include <string>

typedef uint8_t byte;

using namespace boost;
using namespace multiprecision;
using namespace std;

//Класс для вычисления хэша
//Хэш функция Стрибог по ГОСТ 34.11
class hash3411
{
private:
	hash3411() {}
	vector<byte> add_mod512(vector<byte>, vector<byte>);
	vector<byte> add_XOR(vector<byte>, vector<byte>);
	vector<byte> S(vector<byte>);
	vector<byte> P(vector<byte>);
	vector<byte> L(vector<byte>);
	vector<byte> KeySchedule(vector<byte>, int);
	vector<byte> E(vector<byte>, vector<byte>);
	vector<byte> g(vector<byte>, vector<byte>, vector<byte>);
public:
	vector<byte> calculate_Hash(vector<byte>);
	vector<byte> calculate_Hash(string);

	static hash3411& get_Instance() {
		static hash3411 instance;
		return instance;
	}
};

