#include "Reader.h"
#include <fstream>
#include <iostream>
Reader::Reader()
{
}
Reader::Reader(std::string str) 
	: m_str(str),m_pos(0)
{
	m_len = str.size();
}
Reader::Reader(std::ifstream &file) 
	: m_pos(0), m_len(0){
	if (!file) {
		std::cout <<  "file is not existed";
	}
	char str[128];
	while (!file.eof()) 
	{
		file.getline(str, 128);
		m_str += str;
	}
	m_len = m_str.size();
}

void Reader::ignoreSpace()
{
	while (m_pos < m_len) {
		char tChar = peekChar();
		if (isspace(tChar)) {
			readChar();
		}
		else {
			break;
		}
	}
}

char Reader::readChar()
{
	if (m_pos >= m_len) {
		std::cout <<  "Data has been read";
		//exit(0);
		return ' ';
	}
	char tRet= m_str[m_pos];
	m_pos++;
	return tRet;
}

char Reader::peekChar()
{
	if (m_pos >= m_len) {
		std::cout <<  "Data has been read";
	}
	char tRet = m_str[m_pos];
	return tRet;
}

void Reader::match(char ch)
{
	ignoreSpace();
	char tchar = readChar();
	if (ch != tchar) {
		std::cout << ch << " " << tchar << std::endl;
		std::cout <<  "ch is not charactor";
	}
}

void Reader::match(std::string str)
{
	for (int i = 0; i < str.size(); i++) {
		if (m_str[m_pos] != str[i]) {
			std::cout << "true is not true" << std::endl;
		}
		m_pos++;
	}
}

bool Reader::tryMatch(char ch)
{
	int tPos = m_pos;
	ignoreSpace();
	if (m_pos >= m_len) {
		m_pos = tPos;
		return false;
	}
	char tchar = readChar();
	if (ch != tchar) {
		m_pos = tPos;
		return false;
	}
	else {
		return true;
	}
}

bool Reader::IsEOF()
{
	return m_pos >= m_len;
}

