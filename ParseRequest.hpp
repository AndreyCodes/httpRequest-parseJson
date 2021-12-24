#pragma once
#include<json/json.h>


class jsonBuilder
{
	static inline Json::CharReaderBuilder builder;
	static inline Json::CharReader* reader = builder.newCharReader();

public:
	static Json::Value to_json(const char* begin, const char* end)
	{
		Json::Value res;
		reader->parse(begin, end, &res, {});
		return res;
	}
	static Json::Value to_json(const std::string& str)
	{
		Json::Value res;
		reader->parse(str.c_str(), str.c_str() + str.length(), &res, {});
		return res;
	}
	static Json::Value to_json(const std::string_view str)
	{
		Json::Value res;
		reader->parse(str.data(), str.data() + str.length(), &res, {});
		return res;
	}
};