#pragma once
//#include "Reader.h"
#include <fstream>
#include <string>
class Reader {
public:
	Reader();
	Reader(std::string str);
	Reader(std::ifstream &file);
	void ignoreSpace();					//过滤空格
	char readChar();					//读取字符 且偏移
	char peekChar();					//读取当前字符
	void match(char ch);				//匹配字符
	void match(std::string str);        //匹配字符串
	bool tryMatch(char ch);				//匹配尾字符
	bool IsEOF();
private:
	int m_pos;		//数据下标
	int m_len;		//文本长度
	std::string m_str;
	//char* m_data = nullptr;
};