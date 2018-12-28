#pragma once
#include "settings.h"

//����� ��� ��������� ���������� ��������� ������
class cmdarguments {
	//����������
	size_t count;
	//���������
	char ** arguments;
	//������ ������ ��������� 
	const std::string find(const std::string name) const;
	//�������� �������� �� ����� � ������� ������� ����������
	bool isName(size_t index) const;
	//�������� ������������
	bool isSuitable(size_t index, const std::string name) const;
public:
	//�����������
	cmdarguments(size_t count, char ** arguments) : count(count), arguments(arguments) {}
	//������ ���������
	void apply(settings & instance) const;
};