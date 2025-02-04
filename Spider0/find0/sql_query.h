#pragma once
//#include <pqxx/pqxx>    //Этот проект находит ссылки и слова в web0.ini
//#include <iostream>
//#include <fstream>

//#pragma once
#include <boost/asio/ssl/host_name_verification.hpp>//+++
#include <boost/asio/ssl.hpp>//+++
#include <boost/locale.hpp>
#include <boost/asio.hpp>   //+++
#include <boost/asio/ssl.hpp>//+++ ok
#include <boost/asio/ssl/stream.hpp> //+ok +++ 
#include <boost/beast/websocket/ssl.hpp> //+ok   +++
#include <openssl/ssl.h> //+++
#include <boost/beast/core.hpp> //ok
#include <boost/beast/http.hpp>
#include <boost/asio/connect.hpp> //ok
#include <boost/asio/ip/tcp.hpp> //ok
#include <cstdlib> //ok
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <pqxx/pqxx>
#include <windows.h>

void read_web();
 void tables();

class SqlSelectQueryBuilder {
	public:
		std::string query0 = "";
		int a=0;
		void add();
		bool query_point[3] = { false, false, false };
	std::string query[4] = { "select ", "from ",  "where ", ";" };
	
	SqlSelectQueryBuilder& AddColumn(std::string);
	SqlSelectQueryBuilder& AddFrom(std::string);
	SqlSelectQueryBuilder& AddWhere(std::string, std::string);
	std::string BuildQuery();
};