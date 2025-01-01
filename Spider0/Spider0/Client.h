#pragma once
#include <boost/asio.hpp>   //+++
#include <boost/asio/ssl.hpp>//+++
#include <fstream>
#include <openssl/ssl.h> //+++
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

namespace asio = boost::asio;
using tcp = asio::ip::tcp;


namespace beast = boost::beast;     // from <boost/beast.hpp>
namespace http = beast::http;       // from <boost/beast/http.hpp>
//namespace net = boost::asio;        // from <boost/asio.hpp>
//using tcp = net::ip::tcp;           // from <boost/asio/ip/tcp.hpp>

struct adr_web {
    int ind = 0;
    std::vector<std::string> adress;
    
};
std::string Client_get(const std::string& server, const std::string& path = "/");