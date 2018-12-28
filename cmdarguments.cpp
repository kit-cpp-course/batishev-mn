#include "cmdarguments.h"
#include <exception>

using namespace std;

//�������� �� ������ ����� � ��������� �������
bool cmdarguments::isName(size_t index) const {
	return *arguments[index] == '/';
}

//�������� �� ������������
bool cmdarguments::isSuitable(size_t index, const std::string name) const {
	return isName(index) && (strcmp(arguments[index], name.data()) == 0) && !isName(index + 1);
}

//����� ���������
const string cmdarguments::find(const string name) const {
	for (size_t i = 0; i < count; i++) {
		if (isSuitable(i, name)) {
			return arguments[i + 1];
		}
	}
	throw logic_error("Unable to locate parameter value!");
}

//����� ��� ������� ���������
void cmdarguments::apply(settings & instance) const {
	instance.m_input = find("/input");
	instance.m_output = find("/output");
}