#include <iostream>
#include "Ecurve.h"
#include "ECpoint.h"
#include "Esign.h"

typedef uint8_t byte;

using namespace boost;
using namespace multiprecision;
using namespace random;
using namespace std;

int main()
{
	cpp_int a("7"),
		b("43308876546767276905765904595650931995942111794451039583252968842033849580414"),
		p("0x8000000000000000000000000000000000000000000000000000000000000431"),
		m("57896044618658097711785492504343953927082934583725450622380973592137631069619");
	cpp_int x("2"), y("4018974056539037503335449422937059775635739389905545080690979365213431566280");
	Ecurve curve(a, b, p, m);
	ECpoint G(x, y, curve);
	Esign e(curve, G);
	string res = e.GenerateSign("Test string");
	cout << res << endl;
	cout << e.tohex(res) << endl;
	cout << e.VerifySign(res, "Test string") << endl;
	return 0;
}