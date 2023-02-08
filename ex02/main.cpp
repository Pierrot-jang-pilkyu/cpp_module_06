#include "A.hpp"
#include "B.hpp"
#include "C.hpp"
#include "Base.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>


Base * generate(void)
{
	int num = rand() % 3 + 1;

	switch (num)
	{
	case 1:
		return (new A);

	case 2:
		return (new B);

	case 3:
		return (new C);
	}

	return (NULL);
}

void identify(Base* p)
{
	if (dynamic_cast<A*>(p))
		std::cout << "Pointer is A\n";
	if (dynamic_cast<B*>(p))
		std::cout << "Pointer is B\n";
	if (dynamic_cast<C*>(p))
		std::cout << "Pointer is C\n";
}

void identify(Base& p)
{
	try
	{
		A &a = dynamic_cast<A&>(p);
		std::cout << "Reference is A\n";
		static_cast<void>(a);
		
	}
	catch(const std::exception& e) {}
	try
	{
		B &b = dynamic_cast<B&>(p);
		std::cout << "Reference is B\n";
		static_cast<void>(b);
		
	}
	catch(const std::exception& e) {}
	try
	{
		C &c = dynamic_cast<C&>(p);
		std::cout << "Reference is C\n";
		static_cast<void>(c);
		
	}
	catch(const std::exception& e) {}
}

int main(void)
{
	Base *arr[10];
	srand(time(NULL));

	for (int i = 0; i < 10; ++i)
		arr[i] = generate();

	for (int i = 0; i < 10; ++i)
		identify(arr[i]);

	for (int i = 0; i < 10; ++i)
		identify(*arr[i]);

	return (0);
}
