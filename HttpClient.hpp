#pragma once
#include<string_view>
#include<boost/beast.hpp>
#include<boost/asio.hpp>

namespace __My_detail__
{
	using namespace boost::asio;
	using namespace boost::beast;
	boost::asio::io_context io;

	struct HttpClient
	{
	private:
		tcp_stream stream;
		flat_buffer buff;
		std::string_view host_name;
		bool is_avail_to_get_response = false;
	public:
		void connect(std::string_view host, std::string_view port)
		{
			host_name = host;
			ip::tcp::resolver resolv(io);
			const auto&& resolved = resolv.resolve(host.data(), port.data());
			stream.connect(resolved);
		}
		void request(http::verb ver, std::string_view target, int version)
		{
			http::request<http::string_body> req{ ver,target.data(),version };
			req.set(http::field::host,host_name.data());
			req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
			http::write(stream, req);
			is_avail_to_get_response = true;
			return;
		}
		[[nodiscard]] http::response<http::dynamic_body> response()
		{
			if (!is_avail_to_get_response) throw std::runtime_error("Tryed get resp without previous request\n");
			http::response<http::dynamic_body> res;
			http::read(stream, buff, res);
			return res;
		}
		~HttpClient()
		{
			stream.socket().shutdown(boost::asio::ip::tcp::socket::shutdown_both);
		}
		HttpClient			 (const HttpClient&) = delete;
		HttpClient& operator=(const HttpClient&) = delete;
		HttpClient			 (HttpClient&&)		 = default;
		HttpClient& operator=(HttpClient&&)		 = default;
		HttpClient():stream(io){}
	};
}

using __My_detail__::HttpClient;

