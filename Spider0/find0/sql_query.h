#pragma once
#include <pqxx/pqxx>
#include <iostream>

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