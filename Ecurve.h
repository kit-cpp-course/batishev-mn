#pragma once

#include <boost/multiprecision/cpp_int.hpp>

using namespace boost;
using namespace multiprecision;

//Класс эллиптических кривых
class Ecurve
{
private:
	//h - кофактор
	//а, b - параметры эллиптической кривой
	//р - простое число, модуль кривой
	//m - порядок группы точек
	cpp_int a, b, p, m, h = 1;
public:
	Ecurve() : a(), b(), p(), m() {}
	Ecurve(cpp_int na, cpp_int nb, cpp_int np, cpp_int nm) : a(na), b(nb), p(np), m(nm) {}
	Ecurve(const Ecurve &nw) : a(nw.a), b(nw.b), p(nw.p), m(nw.m) {}

	friend class ECpoint;
	friend class Esign;
};

