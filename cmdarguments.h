#pragma once
#include "settings.h"

//Класс для обработки аргументов командной строки
class cmdarguments {
	//Количество
	size_t count;
	//Аргументы
	char ** arguments;
	//Метода поиска параметра 
	const std::string find(const std::string name) const;
	//Проверка является ли слово с данного индекса параметром
	bool isName(size_t index) const;
	//Проверка корректности
	bool isSuitable(size_t index, const std::string name) const;
public:
	//Конструктор
	cmdarguments(size_t count, char ** arguments) : count(count), arguments(arguments) {}
	//Задаем настройки
	void apply(settings & instance) const;
};