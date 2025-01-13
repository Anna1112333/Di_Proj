

#include "Client.h"
// Функция для загрузки страницы по HTTPS
std::string Client_get(const std::string& server, const std::string& path)
{
    namespace asio = boost::asio;
    // Контекст SSL. В данном примере включено лишь базовое доверие к корневым сертификатам.
    // Можно донастроить контекст (например, указать путь к сертификатам, отключить/включить разные версии TLS и т.д.)
    asio::ssl::context ctx(asio::ssl::context::sslv23_client);
   

    // Обёртка над io_service (или io_context в более новых версиях Boost)
    asio::io_context io_context;
    
    //socket.connect(server);
    // Создаём SSL-сокет (tcp::socket + ssl-слой)
    asio::ssl::stream<tcp::socket> ssl_socket(io_context, ctx);
  

    // Получаем endpoint (адрес, порт)
    tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve(server, "443"); // HTTPS-порт 443

    // Устанавливаем соединение по TCP
   // asio::async_connect(ssl_socket.lowest_layer(), endpoints); //+++async_
    asio::connect(ssl_socket.lowest_layer(), endpoints); //+++async_
    // Инициируем SSL Handshake (TLS/SSL рукопожатие)
    ssl_socket.handshake(asio::ssl::stream_base::client);

    // Формируем простой HTTP GET-запрос:
    // Если нужен HTTP/1.1, важен заголовок "Host:"
    std::string request = 
        "GET " + path + " HTTP/1.1\r\n"
       "Host: " + server + "\r\n"
        "Accept: */*"
        "Connection: close\r\n"
        "\r\n";

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
   //  request = "Connection: close\r\n" "\r\n";///+++
    // Отправляем запрос
   // asio::write(ssl_socket, asio::buffer(request));///+++

    return response;
}






// Performs an HTTP GET and prints the response
/*int client00(int argc, char** argv)
{
    try
    {
        // Check command line arguments.
        if (argc != 4 && argc != 5)
        {
            std::cerr <<
                "Usage: http-client-sync <host> <port> <target> [<HTTP version: 1.0 or 1.1(default)>]\n" <<
                "Example:\n" <<
                "    http-client-sync www.example.com 80 /\n" <<
                "    http-client-sync www.example.com 80 / 1.0\n";
            return EXIT_FAILURE;
        }
        auto const host = argv[1];
        auto const port = argv[2];
        auto const target = argv[3];
        int version = argc == 5 && !std::strcmp("1.0", argv[4]) ? 10 : 11;

        // The io_context is required for all I/O
        asio::io_context ioc;

        // These objects perform our I/O
        tcp::resolver resolver(ioc);
        beast::tcp_stream stream(ioc);

        // Look up the domain name
        auto const results = resolver.resolve(host, port);

        // Make the connection on the IP address we get from a lookup
        stream.connect(results);

        // Set up an HTTP GET request message
        http::request<http::string_body> req{ http::verb::get, target, version };
        req.set(http::field::host, host);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

        // Send the HTTP request to the remote host
        http::write(stream, req);

        // This buffer is used for reading and must be persisted
        beast::flat_buffer buffer;

        // Declare a container to hold the response
        http::response<http::dynamic_body> res;

        // Receive the HTTP response
        http::read(stream, buffer, res);

        // Write the message to standard out
        std::cout << res << std::endl;

        // Gracefully close the socket
        beast::error_code ec;
        stream.socket().shutdown(tcp::socket::shutdown_both, ec);

        // not_connected happens sometimes
        // so don't bother reporting it.
        //
        if (ec && ec != beast::errc::not_connected)
            throw beast::system_error{ ec };

        // If we get here then the connection is closed gracefully
    }
    catch (std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}*/