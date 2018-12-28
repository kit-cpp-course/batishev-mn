#pragma once
#include "signature_factory.h"
#include "cmdarguments.h"
#include "fstream"

//����� ����������������� ����������
class UI {
	//����������
	size_t count;
	//���������
	char** args;
public:
	//�����������
	UI(size_t c, char ** arg) : count(c), args(arg) {}
	//��������� � ������� ���������
	void get_eds() {
		//������� ���������
		settings props = settings::instance();
		cmdarguments arguments(count, args);
		//��������� ���������
		arguments.apply(props);
		//������� �������
		signature_factory fact;
		//��������� ���� � ������������� �������
		ifstream file(props.input());
		//��������� �������������� ������
		ofstream res(props.output());
		try {
			//����������� ��������
			const signature& sig = fact.sign(file);
			//������� �������
			res << sig.tohex();
		}
		catch (...) {
			throw ("Error!");
		}
		//��������� �������
		//� ������� ������� � �� ������������
		if (fact.verify()) {
			cout << "EDS is correct!" << endl;
		}
		else {
			throw ("Bad EDS!");
		}
	}
};