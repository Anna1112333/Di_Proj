#include "Client.h"

//#pragma execution_character_set("UTF-8")
using namespace pqxx;

int main()
{
	//SetConsoleCP(CP_UTF8);
	//SetConsoleOutputCP(CP_UTF8);
	//setvbuf(stdout, nullptr, _IOFBF, 1000);
	setlocale(LC_ALL, "RUS");

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
std::cout << "value1 is " << value[1]<<" " << "value3 is " << value[3] << std::endl;

		auto content = Client_get(value[1], value[3]);  // Пример: загружаем главную страницу 
		std::cout << "HTTPS response:\n" << content << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "Error_0: " << e.what() << std::endl;
	}
	return 0;
}
