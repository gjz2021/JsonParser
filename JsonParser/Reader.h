#pragma once
//#include "Reader.h"
#include <fstream>
#include <string>
class Reader {
public:
	Reader();
	Reader(std::string str);
	Reader(std::ifstream &file);
	void ignoreSpace();					//���˿ո�
	char readChar();					//��ȡ�ַ� ��ƫ��
	char peekChar();					//��ȡ��ǰ�ַ�
	void match(char ch);				//ƥ���ַ�
	void match(std::string str);        //ƥ���ַ���
	bool tryMatch(char ch);				//ƥ��β�ַ�
	bool IsEOF();
private:
	int m_pos;		//�����±�
	int m_len;		//�ı�����
	std::string m_str;
	//char* m_data = nullptr;
};