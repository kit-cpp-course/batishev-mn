#include "hash3411.h"

//Сложение по модулю 2^512
vector<byte> hash3411::add_mod512(vector<byte> a, vector<byte> b) {
	vector<byte> res;
	res.resize(64, 0);
	while (a.size() < 64) a.insert(a.begin(), 0x00);
	while (b.size() < 64) b.insert(b.begin(), 0x00);
	unsigned int t = 0;
	for (int i = 63; i >= 0; i--) {
		t = a[i] + b[i] + (t >> 8);
		res[i] = t & 0xff;
	}
	return res;
}

//XOR двух векторов
vector<byte> hash3411::add_XOR(vector<byte> a, vector<byte> b) {
	vector<byte> res;
	res.resize(64);
	for (size_t i = 0; i < 64; i++) {
		res[i] = a[i] ^ b[i];
	}
	return res;
}

//Функция подстановки
vector<byte> hash3411::S(vector<byte> a) {
	for (size_t i = 0; i < a.size(); i++) {
		a[i] = Pi[a[i]];
	}
	return a;
}

//Функция перестановки
vector<byte> hash3411::P(vector<byte> a) {
	if (a.size() != 64) throw("Wrong size!");
	vector<byte> res(64);
	for (size_t i = 0; i < a.size(); i++) {
		res[i] = a[Tau[i]];
	}
	return res;
}

//Умножение на бинарную матрицу
vector<byte> hash3411::L(vector<byte> a) {
	vector<byte> res;
	for (int i = 0; i < 8; i++) {
		unsigned long long int t = 0;
		vector<byte> temp;
		temp.insert(temp.end(), a.begin() + 8 * i, a.begin() + 8 * (i + 1));
		cpp_int x;
		import_bits(x, temp.begin(), temp.end(), 8);
		vector<bool> temp_bits;
		export_bits(x, back_inserter(temp_bits), 1);
		while (temp_bits.size() < 64) temp_bits.insert(temp_bits.begin(), 0);
		for (int j = 0; j < 64; j++) {
			if (temp_bits[j]) {
				t = t ^ A[j];
			}
		}
		vector<byte> ResPart;
		x = cpp_int(t);
		export_bits(x, back_inserter(ResPart), 8);
		while (ResPart.size() < 8) ResPart.insert(ResPart.begin(), 0x00);
		res.insert(res.end(), ResPart.begin(), ResPart.end());
	}
	return res;
}

//Функция формирования временного ключа
vector<byte> hash3411::KeySchedule(vector<byte> K, int i) {
	K = add_XOR(K, C[i]);
	K = S(K);
	K = P(K);
	K = L(K);
	return K;
}

vector<byte> hash3411::E(vector<byte> k, vector<byte> m) {
	vector<byte> res;
	res = add_XOR(k, m);
	for (int i = 0; i < 12; i++) {
		res = S(res);
		res = P(res);
		res = L(res);
		k = KeySchedule(k, i);
		res = add_XOR(res, k);
	}
	return res;
}

//Функция сжатия
vector<byte> hash3411::g(vector<byte> N, vector<byte> h, vector<byte> m) {
	vector<byte> K = add_XOR(h, N);
	K = S(K);
	K = P(K);
	K = L(K);
	vector<byte> t = E(K, m);
	t = add_XOR(t, h);
	return add_XOR(t, m);
}

//Функция вычисления хэша для строки
vector<byte> hash3411::calculate_Hash(string msg) {
	vector<byte> msg_byte;
	for (size_t i = 0; i < msg.size(); i++) {
		msg_byte.push_back((int)msg[i]);
	}
	return calculate_Hash(msg_byte);
}

//Функция вычисления хэша для последовательности бит
vector<byte> hash3411::calculate_Hash(vector<byte> msg) {
	int len = msg.size() * 8;
	vector<byte> h, n, iv, sigma;
	vector<byte> N_0;
	N_0.resize(64, 0x00);
	//Заполнение начальных значений
	n.resize(64, 0x00);
	sigma.resize(64, 0x00);
	iv.resize(64, 0x01);
	h.resize(64, 0x01);
	vector<byte> N_512;
	export_bits(cpp_int(512), back_inserter(N_512), 8);
	while (N_512.size() < 64) {
		N_512.insert(N_512.begin(), 0x00);
	}
	int inc = 0;
	//Вычисления для 64 байтных подпоследовательностей
	while (len >= 512) {
		inc++;
		vector<byte> temp_msg;
		temp_msg.insert(temp_msg.end(), msg.end() - inc * 64, msg.end() - 64 * (inc - 1));
		h = g(n, h, temp_msg);
		n = add_mod512(n, N_512);
		sigma = add_mod512(sigma, temp_msg);
		len -= 512;
	}
	//Оставшееся сообщение
	vector<byte> padded_msg;
	padded_msg.insert(padded_msg.end(), msg.begin(), msg.end() - 64 * (inc));
	vector<byte> ln;
	export_bits(cpp_int(padded_msg.size()*8), back_inserter(ln), 8);
	ln = add_mod512(n, ln);
	padded_msg.insert(padded_msg.begin(), 0x01);
	while (padded_msg.size() < 64) {
		padded_msg.insert(padded_msg.begin(), 0x00);
	}
	h = g(n, h, padded_msg);
	h = g(N_0, h, ln);
	sigma = add_mod512(sigma, padded_msg);
	h = g(N_0, h, sigma);
	vector<byte> res;
	//MSB256
	res.insert(res.end(), h.begin(), h.begin() + 32);
	return res;
}