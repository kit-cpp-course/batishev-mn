#pragma once
#include "signature_factory.h"
#include "cmdarguments.h"
#include "fstream"

//Класс пользовательского интерфейса
class UI {
	//Количество
	size_t count;
	//Аргументы
	char** args;
public:
	//Конструктор
	UI(size_t c, char ** arg) : count(c), args(arg) {}
	//Получение и подпись документа
	void get_eds() {
		//Создаем настройки
		settings props = settings::instance();
		cmdarguments arguments(count, args);
		//Применяем параметры
		arguments.apply(props);
		//Создаем фабрику
		signature_factory fact;
		//Открываем файл с подписываемым текстом
		ifstream file(props.input());
		//Открываем результирующим файлом
		ofstream res(props.output());
		try {
			//Подписываем документ
			const signature& sig = fact.sign(file);
			//Выводим подпись
			res << sig.tohex();
		}
		catch (...) {
			throw ("Error!");
		}
		//Проверяем подпись
		//И выносим вердикт о ее корректности
		if (fact.verify()) {
			cout << "EDS is correct!" << endl;
		}
		else {
			throw ("Bad EDS!");
		}
	}
};