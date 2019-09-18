#include "List.h"

int main() {
	List<int>  l;
	for (int i = 0; i < 100; ++i)
		l.insertBack(i);
	List<int> l2 = l.split(33);
	List<int> l3 = l2.split(33);
	for (int x : l)
		std::cout << x << std::endl;
	for (int x : l2)
		std::cout << x << std::endl;
	for (int x : l3)
		std::cout << x << std::endl;
}
