#pragma once
#include <boost/multiprecision/cpp_int.hpp>
#include "Ecurve.h"
using namespace boost;
using namespace multiprecision;

//Класс для точек эллиптической кривой
class ECpoint
{
public:
	cpp_int x, y;
	Ecurve curve;
	ECpoint();
	ECpoint(cpp_int, cpp_int, const Ecurve &);
	ECpoint(const ECpoint &);

	ECpoint doubl() const;
	ECpoint multiply(cpp_int) const;

	ECpoint operator + (const ECpoint &) const;
};

