#pragma once
#include <boost/multiprecision/cpp_int.hpp>
#include "Ecurve.h"

using namespace boost;
using namespace multiprecision;

//����� ��� ����� ������������� ������
class ECpoint
{
private:
	//���������� �����
	cpp_int x, y;
	//������ ������� ����������� �����
	Ecurve curve;
public:
	ECpoint();
	ECpoint(cpp_int, cpp_int, const Ecurve &);
	ECpoint(const ECpoint &);

	//����� ��� �������� �����
	ECpoint doubl() const;
	//����� ��������� ����� �� �����
	ECpoint multiply(cpp_int) const;

	//��������������� ��������� �������� ��� ���� �����
	ECpoint operator + (const ECpoint &) const;

	friend class Esign;
};

