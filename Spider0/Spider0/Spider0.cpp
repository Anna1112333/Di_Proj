#include <fstream>
#include <Vector>
#include <boost\locale.hpp>
#include <string>
#include <iostream>
#include <asn1err.h>
#include "Client.h"
using namespace pqxx;
int main()
{	
	std::ifstream read(".ini");
	int n; //количество ступеней скачивания страниц сайта вглубь
	read >> n;
	std::string adr;
	read >> adr;
	std::cout << "Inserted depth, some addred\n"<<n<<std::endl<<adr<<std::endl;
	
	std::vector<adr_web> a;
		a.resize(n);
		pqxx::connection c{ "host=127.0.0.0 port=5432 dbname=Ds1 user=Ds1 password=anna" };
	for (int i = 0; i < n; i++)
	{
		
		a[i].ind = i;
		std::cout << "depth " << i << std::endl;
	}
	try
	{
		// Пример: загружаем главную страницу ya.ru
		auto content = Client_get(adr, "/");
		std::cout << "HTTPS response:\n" << content << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << "Ошибка: " << e.what() << std::endl;
	}
	return 0;
}
