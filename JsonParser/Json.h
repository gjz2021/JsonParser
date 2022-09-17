#pragma once
#include <fstream>
#include <unordered_map>
#include <algorithm>
#include "Json.h"
#include "Reader.h"
#include <BaseTsd.h>
enum JSONVALUETYPE {
	JSONVALUETYPE_NULL,   ///< @brief ������
	JSONVALUETYPE_BOOL,   ///< @brief �߼�����
	JSONVALUETYPE_NUMBER, ///< @brief ��������
	JSONVALUETYPE_STRING, ///< @brief �ַ�������
	JSONVALUETYPE_LIST,   ///< @brief ������
	JSONVALUETYPE_DICT,   ///< @brief �ֵ�����
};
class JsonValue;
class JsonList;
class JsonString;
class JsonDict;
class Json{
public:
	Json();
	Json(std::string &str);							//�ı�����
	Json(std::ifstream &file);						//������
	~Json();
	JsonValue* parseValue(Reader &context);			//����һ��ֵ			//�㶨��һ����Ա���� ���г�Ա����ȥ��ȡ���߸ı�
	JsonValue* parseNumber(Reader &context);		//����һ����
	JsonList* parseList(Reader &context);			//����һ������
	JsonDict* parseDict(Reader &context);			//����һ���ֵ�
	JsonString* parseString(Reader &context);		//����һ���ַ�
	void writeToStr(std::string &str);				//��jsonд�뵽�ַ���
	void writeToStream(std::ofstream &file);
	JsonValue* getRoot();							//����root���
	void setRoot(JsonValue* root);					//����root���
private:
	std::ifstream file;		//��Ƶ�ļ����
	JsonValue* m_Root;		//json���������ڵ�
	
};
class JsonValue {
	friend class JsonString;
	friend class JsonList;
	friend class JsonDict;
	friend class Json;
public:
	JsonValue();
	JsonValue(JSONVALUETYPE type);
	JsonValue(bool flag);
	JsonValue(double num);
	virtual ~JsonValue();
	virtual void writeToStr(std::string &str);			//����Json�ļ��������str
	//JsonValue* getValue(std::string str);
	virtual JsonDict* toDict();							//ָ��dict
	virtual JsonString* toString();						//ָ��string
	virtual JsonList* toList();							//ָ��List
private:
	union {
		double m_ValueNumber;
		bool m_ValueBool;
	};
	JSONVALUETYPE m_type;								//Json����
};

class JsonList : public JsonValue {
public:
	JsonList();
	~JsonList();
	void append(JsonValue* value);						//����
	void writeToStr(std::string &str);
	int getListSize();
	JsonValue* getValue(int index);
	JsonList* toList();
	void clear();
private:
	std::vector<JsonValue*> m_ObjList;
	
};

class JsonString : public JsonValue {
public:
	JsonString(std::string value);
	~JsonString();
	std::string getStr();
	void setString(std::string value);		
	void writeToStr(std::string &str);	
	JsonString* toString();
private:
	std::string m_Str;			
};

class JsonDict : public JsonValue {
public:	
	JsonDict();
	~JsonDict();
	void setValue(std::string Name, JsonValue* pNew);
	void writeToStr(std::string &str);
	bool contain(std::string str);		//����
	void remove(std::string str);		//�Ƴ�
	void clear();
	JsonValue* getValue(std::string tKey);
	JsonDict* toDict();
private:
	std::vector<std::string> m_ObjList;
	std::unordered_map<std::string, JsonValue*> m_Cache;			//key��name value:��Ӧ���͵�ֵ
};