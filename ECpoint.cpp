#include "ECpoint.h"

ECpoint::ECpoint() : x(), y(), curve() {}

ECpoint::ECpoint(cpp_int nx, cpp_int ny, const Ecurve &ncurve) : x(nx), y(ny), curve(ncurve) {}

ECpoint::ECpoint(const ECpoint &nw) : x(nw.x), y(nw.y), curve(nw.curve) {}


//—ложение двух точек
ECpoint ECpoint::operator +(const ECpoint &that) const {
	ECpoint res(*this);

	cpp_int dx = that.x - x;
	if (dx < 0) dx += curve.p;
	cpp_int dy = that.y - y;
	if (dy < 0) dy += curve.p;
	//powm(dx, p - 2, p) = x^(-1) mod p = x^(p-2) mod p
	//так как р - простое используем формулу Ёйлера (смотри статью на Wiki Modular Multiplicative inverse)
	cpp_int lambda = (dy*cpp_int(powm(dx, curve.p - 2, curve.p))) % curve.p;
	if (lambda < 0) lambda += curve.p;

	res.x = (lambda*lambda - x - that.x) % curve.p;
	if (res.x < 0) res.x += curve.p;
	res.y = (lambda*(x - res.x) - y) % curve.p;
	if (res.y < 0) res.y += curve.p;

	return res;
}

//—ложение точки с собой(удвоение точки)
ECpoint ECpoint::doubl() const{
	ECpoint res(*this);

	cpp_int dx = 3 * x*x + curve.a;
	if (dx < 0) dx += curve.p;
	cpp_int dy = 2 * y;
	if (dy < 0) dy += curve.p;

	cpp_int lambda = (dx*cpp_int(powm(dy, curve.p - 2, curve.p))) % curve.p;
	if (lambda < 0) lambda += curve.p;

	res.x = (lambda*lambda - 2*x) % curve.p;
	if (res.x < 0) res.x += curve.p;
	res.y = (lambda*(x - res.x) - y) % curve.p;
	if (res.y < 0) res.y += curve.p;

	return res;
}

//”множение точки на число
ECpoint ECpoint::multiply(cpp_int k) const {
	if (k <= 0) {
		throw("Wrong number!");
	}
	ECpoint res(*this), p(*this);
	k--;
	while (k > 0) {
		if ((k % 2) != 0) {
			if ((res.x == p.x) || (res.y == p.y))
				res = res.doubl();
			else
				res = res + p;
			k--;
		}
		k = k / 2;
		p = p.doubl();
	}
	return res;
}