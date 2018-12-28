#pragma once
#include <string> 

//����� ��������
class settings {
	friend class cmdarguments;
	//����������� ���������� ������
	static settings m_instance;
	//�������� ����
	std::string m_input = "input.txt";
	//�������������� ����
	std::string m_output = "output.txt";
	//��������� �����������
	settings() {}
public:
	//����� ��� ��������� ���� ��������� �����
	const std::string & input() const {
		return m_input;
	}
	//����� ��� ��������� ���� ��������������� �����
	const std::string & output() const {
		return m_output;
	}
	//����������� ����� ��� ��������� ���������� ������
	static settings & instance() {
		return m_instance;
	}
};