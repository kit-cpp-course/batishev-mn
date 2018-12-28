#include <iostream>
#include "signature_factory.h"
#include "UI.h"


int main(size_t count, char * args[]) {
	UI user(count, args);
	user.get_eds();
	system("pause");
	return 0;
}