#include <fstream>
#include <Vector>
#include <boost\locale.hpp>
#include <string>
#include <iostream>
//#include <asn1err.h>
#include "Client.h"
//#pragma execution_character_set("UTF-8")
using namespace pqxx;

int main()
{
	//SetConsoleCP(CP_UTF8);
	//SetConsoleOutputCP(CP_UTF8);
	//setvbuf(stdout, nullptr, _IOFBF, 1000);
	setlocale(LC_ALL, "RUS");

	std::ifstream read("config.ini");
	int n; //количество ступеней скачивания страниц сайта вглубь
	read >> n;
	std::string adr;
	read >> adr;
	std::cout << "Inserted depth, some added\n"<<n<<std::endl<<adr<<std::endl;
	int port;
	read >> port;
	std::vector<adr_web> a;
		a.resize(n);
		
	for (int i = 0; i < n; i++)
	{
		
		a[i].ind = i;
		std::cout <<port<< " depth " << i << std::endl;
	}
	try
	{
pqxx::connection c{ "host=127.0.0.1 port=5432 "
			"dbname=Ds1 user=Ds1 password=anna" };
		// Пример: загружаем главную страницу ya.ru

		auto content = Client_get(adr, "/index.php/Main_Page");
		std::cout << "HTTPS response:\n" << content << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Error_0: " << e.what() << std::endl;
	}
	return 0;
}
