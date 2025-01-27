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

	//std::ifstream read("config.ini");
	//int n=3; //количество ступеней скачивания страниц сайта вглубь
	//read >> n;
	//std::string adr ="wiki.openssl.org";
	//read >> adr;
	//adr = "wiki.openssl.org";
	//std::cout << "Inserted depth, some added\n"<<n<<std::endl<<adr<<std::endl;
	//int port;
	//read >> port;
	std::string name[10]{};
	std::string value[10]{};
	read_ini(name, value);
	for (int i = 0; i < 10; i++)
		std::cout << name[i] << " = " << value[i] << std::endl;
	int n = 3;
	std::vector<adr_web> a;
		a.resize(3);
		
	for (int i = 0; i < 3; i++)
	{
		
		a[i].ind = i;
		std::cout <<443<< " depth " << i << std::endl;
	}
	try
	{
pqxx::connection c{ "host=127.0.0.1 port=5432 "
			"dbname=Ds1 user=Ds1 password=anna" };
		// Пример: загружаем главную страницу ya.ru

		auto content = Client_get(value[1], " ");
		std::cout << "HTTPS response:\n" << content << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Error_0: " << e.what() << std::endl;
	}
	return 0;
}
