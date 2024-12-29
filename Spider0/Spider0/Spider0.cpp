#include <fstream>
#include <Vector>
#include <boost\locale.hpp>
#include <string>
#include <iostream>
#include <asn1err.h>
#include "Client.h"

int main()
{  
	std::ifstream read(".ini");
	int n; //количество ступеней скачивания страниц сайта вглубь
	read >> n;
	std::string adr;
	read >> adr;
	std::cout << "Inserted depth, some addred\n"<<n<<std::endl<<adr<<std::endl;
	for (int i = 1; i < n; i++) {
		std::cout << "0+";
	}std::cout << std::endl;
	std::vector<adr_web> a;
	a.resize(n);
	for (int i = 0; i < n; i++)
	{
		
		a[i].ind = i;
		std::cout << "depth " << i << std::endl;
	}
	try
	{
		// Пример: загружаем главную страницу boost.org
		auto content = Client_get(adr, "/");
		std::cout << "HTTPS response:\n" << content << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << "Ошибка: " << e.what() << std::endl;
	}
	return 0;
}
