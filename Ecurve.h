#pragma once

#include <boost/multiprecision/cpp_int.hpp>
#include <string>

using namespace boost;
using namespace multiprecision;

//Класс эллиптических кривых
class Ecurve
{
public:
	//h - cofactor
	cpp_int a, b, p, m, h = 1;
	Ecurve() : a(), b(), p(), m() {}
	Ecurve(cpp_int na, cpp_int nb, cpp_int np, cpp_int nm) : a(na), b(nb), p(np), m(nm) {}
	Ecurve(const Ecurve &nw) : a(nw.a), b(nw.b), p(nw.p), m(nw.m) {}
};

