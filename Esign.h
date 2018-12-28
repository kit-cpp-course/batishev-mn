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
	//����� �������������� ����� � ������ ���
	std::string tobinarystr(cpp_int);
	//����� �������������� ������ ��� � �����
	cpp_int strtoint(std::string);
	//����� ��������� ��������� �����
	cpp_int GeneratePrivateKey();
	//����� �������� ��������� ����� �� ���������
	ECpoint GeneratePublicKey(cpp_int);
	//������������� ������
	Ecurve curve;
	//Q - ��������� ����
	//� - ����� ������
	ECpoint P, Q;
	//d - �������� ����
	cpp_int d;
public:

	Esign();
	Esign(const Ecurve &, const ECpoint &);

	//����������� ����������� ����� ������������� ������ ��� ��������� �������
	void generate(std::vector<byte>);
	//����� ��������� �������
	bool VerifySign(std::string, std::vector<byte>);
};

