#include <iostream>

#include <Manager.h>

using namespace std;

int main()
{
	Manager *m = new Manager();
	m->init();
	m->run();
	delete m;

	return 0;
}
