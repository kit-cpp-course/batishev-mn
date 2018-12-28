#pragma once
#include <string> 

//Класс настроек
class settings {
	friend class cmdarguments;
	//Статический экземпляра класса
	static settings m_instance;
	//Исходный файл
	std::string m_input = "input.txt";
	//Результирующий файл
	std::string m_output = "output.txt";
	//Приватный конструктор
	settings() {}
public:
	//Метод для получения пути исходного файла
	const std::string & input() const {
		return m_input;
	}
	//Метод для получения пути результирующего файла
	const std::string & output() const {
		return m_output;
	}
	//Статический метод для получения экземпляра класса
	static settings & instance() {
		return m_instance;
	}
};