#pragma once
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


void read_ini(std::string* name, std::string* value);
std::string Client_get(const std::string& server, const std::string& path);


struct adr_web {
    int ind = 0;
    std::vector<std::string> adress;
    
};

