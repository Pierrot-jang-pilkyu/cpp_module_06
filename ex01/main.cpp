#include <iostream>


struct Data
{
	std::string data;
};

uintptr_t serialize(Data* ptr)
{
	return (reinterpret_cast<uintptr_t>(ptr));
}

Data* deserialize(uintptr_t raw)
{
	return (reinterpret_cast<Data *>(raw));
}

int main()
{
	struct Data d;
	struct Data *dPtr;

	d.data = "id";
	
	uintptr_t ptr = serialize(&d);
	dPtr = deserialize(ptr);

	std::cout << "before	: " << d.data << std::endl;
	std::cout << "after	: " << dPtr->data << std::endl;
}
