//#include <boost/asio/ssl/host_name_verification.hpp>
//#include <boost/asio/ssl.hpp>
#include "Client.h"
namespace asio = boost::asio;
using tcp = asio::ip::tcp;
std::string Client_get(const std::string& server, const std::string& path)
{
    // Контекст SSL. В данном примере включено лишь базовое доверие к корневым сертификатам.
    // Можно донастроить контекст (например, указать путь к сертификатам, отключить/включить разные версии TLS и т.д.)
    asio::ssl::context ctx(asio::ssl::context::sslv23_client);
    asio::io_context io_context; 

    ctx.set_default_verify_paths();
    ctx.set_verify_mode(asio::ssl::verify_none);
    // Создаём SSL-сокет (tcp::socket + ssl-слой)
    asio::ssl::stream<tcp::socket> ssl_socket(io_context, ctx);
    
    
    // Получаем endpoint (адрес, порт)
    tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve(server, "https"); // HTTPS-порт 443
    asio::connect(ssl_socket.lowest_layer(), endpoints);
    try {
        if (!SSL_set_tlsext_host_name(ssl_socket.native_handle(), server.c_str()))
        {
            boost::system::error_code ec{ static_cast<int>(::ERR_get_error()), boost::asio::error::get_ssl_category() };
            throw boost::system::system_error{ ec };
        }
    }
    catch (std::exception& ec)
    {
        std::cout << "Error_0_0: " << ec.what() << std::endl;
    }

   // tcp::resolver::query query("host.name", "https"); //+++
    // Устанавливаем соединение по TCP  
   
    // Инициируем SSL Handshake (TLS/SSL рукопожатие)
    ssl_socket.handshake(asio::ssl::stream_base::client);

    // Формируем простой HTTP GET-запрос:
    // Если нужен HTTP/1.1, важен заголовок "Host:"
    std::string request = 
        "GET " + path + " HTTP/1.1\r\n"
       "Host: " + server + "\r\n"
       // "Accept: */*" + "\r\n"
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


