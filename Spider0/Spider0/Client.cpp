#include "Client.h"
#include <boost/asio/query.hpp>


namespace asio = boost::asio;
using tcp = boost::asio::ip::tcp;
namespace beast = boost::beast;     // from <boost/beast.hpp>
namespace http = beast::http;       // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp> +++
namespace ssl = boost::asio::ssl;       // from <boost/asio/ssl.hpp> +++


std::string Client_get( std::string& server, const std::string& path)
{
    std::cout << "server is " << server << "path is " << path << std::endl;
    // Контекст SSL. В данном примере включено лишь базовое доверие к корневым сертификатам.
    // Можно донастроить контекст (например, указать путь к сертификатам, отключить/включить разные версии TLS и т.д.)
    ssl::context ctx(ssl::context::sslv23_client);
    asio::io_context io_context; 
    // Клиенту и серверу нужно позвонить
    SSL_CTX* an=SSL_CTX_new(TLS_method()); // Подать заявку на среду сеанса SSL  параметр const SSL_METHOD *method +++
    std::cout<<"        ------*******-------      " << an;
    

    ctx.set_default_verify_paths();
    ctx.set_verify_mode(ssl::verify_none);
    // Создаём SSL-сокет (tcp::socket + ssl-слой)
    asio::ssl::stream<tcp::socket> ssl_socket(io_context, ctx);
    
    
    // Получаем endpoint (адрес, порт)
    tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve(server, "https"); // HTTPS-порт 443
    auto ep=asio::connect(ssl_socket.lowest_layer(), endpoints);
   
    std::cout << "server is " << server<<std::endl;

    try {
        
       

        if (!SSL_set_tlsext_host_name(ssl_socket.native_handle(), server.c_str()))
        {
            boost::system::error_code ec{ static_cast<int>(ERR_get_error()), asio::error::get_ssl_category() };
            throw boost::system::system_error{ ec };
        }
    }
    catch (std::exception& ec)
    {
        std::cout << "Error_0_0: " << ec.what() << std::endl;
    }
    
    // Устанавливаем соединение по TCP  
   
    // Инициируем SSL Handshake (TLS/SSL рукопожатие)
    ssl_socket.handshake(ssl::stream_base::client);

    // Формируем простой HTTP GET-запрос:
    // Если нужен HTTP/1.1, важен заголовок "Host:"
    std::string request = 
        "GET " + path + " HTTP/1.1\r\n"
       "Host: " + server + "\r\n"
        "Accept: text/html" + "\r\n"
        //"Accept-Language: ru" + "\r\n"        
        "Connection: close\r\n"+ "\r\n";

    // Отправляем запрос
   asio::write(ssl_socket, asio::buffer(request));

    // Считываем ответ в буфер
    std::string response;
    boost::system::error_code ec;
    for (;;)
    {
        char buf[1024];
        std::size_t bytes_transferred = ssl_socket.read_some(asio::buffer(buf), ec);
        if (bytes_transferred > 0)
        {
            response.append(buf, bytes_transferred);
        }
        if (ec == asio::error::eof)
        {
            ssl_socket.shutdown();//+++
            // Достигнут конец потока
            break;
        }
        else if (ec)
        {
            // Произошла ошибка
            throw boost::system::system_error(ec);
        }
    }
    std::ofstream infile("web0.txt", std::ios::app);
    if (infile.is_open()) {
        // Write data to the end of the file
        infile << "This data will be appended.-------------------" << std::endl;
        infile << response << std::endl;
        infile << "This data appended.*********************" << std::endl;
        std::cout << "++++++++++++++++++++++++++++" << std::endl;
        // Close the file when done
        infile.close();
        std::cout << "Data appended to file successfully." << std::endl;
    }
    else {
        std::cerr << "Unable to open the file for writing." << std::endl;
    }
   
    return response;
}

void read_ini(std::string* name, std::string* value) {
    std::string sighn = "*";
    int i = 0;
    std::ifstream read("config.ini");
    while (!read.eof()) {
        read >> name[i];     
        read >> sighn;
        if (sighn == "=") {           
            read >> value[i];          
        }
        else { std::cout << "error " << i << "value"; }
        i++;     
    }  
}
