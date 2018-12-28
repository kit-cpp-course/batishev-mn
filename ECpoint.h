#pragma once
#include <boost/multiprecision/cpp_int.hpp>
#include "Ecurve.h"

using namespace boost;
using namespace multiprecision;

//Класс для точек эллиптической кривой
class ECpoint
{
private:
	//Координаты точки
	cpp_int x, y;
	//Кривая которой принадлежит точка
	Ecurve curve;
public:
	ECpoint();
	ECpoint(cpp_int, cpp_int, const Ecurve &);
	ECpoint(const ECpoint &);

	//Метод для удвоения точки
	ECpoint doubl() const;
	//Метод умножения точки на число
	ECpoint multiply(cpp_int) const;

	//Переопределения оператора сложения для двух точек
	ECpoint operator + (const ECpoint &) const;

	friend class Esign;
};

