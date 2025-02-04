#include "sql_query.h"
void read_web() {
	std::string web_text = "";
	std::string sighn = "";
	int i = 0;
	std::ifstream read("web0.txt");
	while (!read.eof()) {
		
		if (sighn[0] == '<' && sighn[sighn.length()-1]=='>') {
			read >> sighn;
		}
		else if (sighn[0] == '<')
			while (sighn[sighn.length() - 1] != '>') read >> sighn;
		while (sighn[0] != '<') {
			read >> sighn;
			web_text += sighn;
			std::cout << web_text << "nnnnnn   ";
		}
		i++;
	}
	std::ofstream infile("Text_web.txt", std::ios::app);
	if (infile.is_open()) {
		// Write data to the end of the file
		infile << "This data will be appended.-------------------" << std::endl;
		infile << web_text << std::endl;
		std::cout << "++++++++++++++++++++++++++++" << std::endl;
		// Close the file when done
		infile.close();
		std::cout << "Data appended to file successfully." << std::endl;
	}
	else 
		std::cerr << "Unable to open the file for writing." << std::endl;
}
void tables() {}
void SqlSelectQueryBuilder::add()
{
	std::string cr_tab = "CREATE TABLE IF NOT EXISTS public.web (adress text NULL); ";
	int a = 1;
	a++;
	std::cout<<"a equal " << a << std::endl;
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
	
	