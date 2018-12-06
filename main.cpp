#include <iostream>
#include "Multimap.h"

class ReversOrder {
public:
	bool operator()(int i1,int i2) {
		return i1 > i2;
	}
};

template<class T>
void printAll(T& crMap) {
	for(typename T::Iterator i = crMap.begin(); i !=
	        crMap.end(); ++i)
		std::cout << i->second << std::endl;
}

template<class T>
void printAll2(T& crMap) {
	for(typename T::Iterator i = crMap.begin(); i !=
	        crMap.end(); ++i)
		std::cout << i->first << std::endl;
}

template<class T>
void printSome( T& crMap,int j) {
	for(typename T::Iterator i = crMap.find(j); i !=
	        crMap.end(); ++i)
		std::cout << i->second << std::endl;
;
}

template<class T>
void changeSome(T& rMap,int j,char c) {
	typename T::Iterator i = rMap.find(j);
	i->second = c;
}

template<class T>
void deleteSome(T& rMap) {
	typename T::Iterator i1 = rMap.begin();
	++i1;
	typename T::Iterator i2 = rMap.find(30);
	rMap.remove(i1,i2);
	rMap.remove(3);
	rMap.remove(rMap.begin(),rMap.begin());
}

template<class T>
void test() {
	T m;
	m.insert(3,'d');
	m.insert(2,'e');
	m.insert(30,'g');
	m.insert(3,'f');
	printAll(m);
	printSome(m,3);
	changeSome(m,3,'?');
	printSome(m,3);
	std::cout << "deleteSome" << std::endl;
	printAll(m);
	deleteSome(m);
	std::cout << "----" << std::endl;
	printAll(m);
}

int main() {
	typedef Multimap<int,char> m;
	typedef Multimap<int,char,ReversOrder> revers_m;
	std::cout << "Normal" << std::endl;
	test<m>(); // druckt e,d,f,d d,f ?,f
	std::cout << "Reverse" << std::endl;
	test<revers_m>(); // druckt d,f,d,e d,f ?,f
}
