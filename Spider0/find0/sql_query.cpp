#include "sql_query.h"



void SqlSelectQueryBuilder::add()
{
	a++;
	std::cout << a << std::endl;
}


SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddColumn(std::string a) {
	if (query_point[0] == true)
		query[0] = query[0] +", "+ a + " ";
	else 
		query[0] = query[0] +  a + " ";
	query_point[0] = true;
	return *this;
	}
SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddFrom(std::string b) {
	if (query_point[1] == true)
		query[1] = query[1] +" join " + b + " ";
	else		
		query[1] =query[1] + b + " ";
	query_point[1] = true;
	return *this;
	}
SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddWhere(std::string c, std::string c1) {
	if (query_point[2] == true)
		query[2] = query[2] +" and " + c + " is " + c1;		
	else
		query[2] = query[2] + c + " is "+c1;
	query_point[2] = true;
	return *this;
}
	std::string SqlSelectQueryBuilder::BuildQuery()  {
		for (int i = 0; i < 4; i++)
			this->query0 += this->query[i];
		//std::cout << query0;
		return query0;		
	}
	
	