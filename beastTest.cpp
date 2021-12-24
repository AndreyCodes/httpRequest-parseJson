#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include<json/json.h>
#include"HttpClient.hpp"
#include"ParseRequest.hpp"

#include<conio.h>

const double KELVIN = 273.15;


int main(int argc, char** argv)
{
    HttpClient cl;
    std::string adr = "api.openweathermap.org";
    std::string port = "80";
    std::string targ = "/data/2.5/weather?q=London,uk&appid=04ca6582139bb1ffbb6ce2726e3367fa";
    cl.connect(adr, port);

    while (true)
    {
        char k = _getch();
        switch (k)
        {
        case 'l':
            cl.request(boost::beast::http::verb::get,targ , 11);
            auto&& res = cl.response();
            auto&& rawJson = boost::beast::buffers_to_string(res.body().data());
            auto&& my_json = jsonBuilder::to_json(rawJson);
            std::cout <<"Current temperature in London is: " << my_json["main"]["temp"].asDouble() - KELVIN << '\n';
            break;
        case 'z':
            return EXIT_SUCCESS;

        }
    }

    return EXIT_SUCCESS;
}