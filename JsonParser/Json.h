#pragma once
#include <fstream>
#include <unordered_map>
#include <algorithm>
#include "Json.h"
#include "Reader.h"
#include <BaseTsd.h>
enum JSONVALUETYPE {
	JSONVALUETYPE_NULL,   ///< @brief 空类型
	JSONVALUETYPE_BOOL,   ///< @brief 逻辑类型
	JSONVALUETYPE_NUMBER, ///< @brief 数字类型
	JSONVALUETYPE_STRING, ///< @brief 字符串类型
	JSONVALUETYPE_LIST,   ///< @brief 表类型
	JSONVALUETYPE_DICT,   ///< @brief 字典类型
};
class JsonValue;
class JsonList;
class JsonString;
class JsonDict;
class Json{
public:
	Json();
	Json(std::string &str);							//文本构造
	Json(std::ifstream &file);						//流构造
	~Json();
	JsonValue* parseValue(Reader &context);			//解析一个值			//你定义一个成员变量 得有成员函数去获取或者改变
	JsonValue* parseNumber(Reader &context);		//解析一个数
	JsonList* parseList(Reader &context);			//解析一个数组
	JsonDict* parseDict(Reader &context);			//解析一个字典
	JsonString* parseString(Reader &context);		//解析一个字符
	void writeToStr(std::string &str);				//将json写入到字符串
	void writeToStream(std::ofstream &file);
	JsonValue* getRoot();							//返回root结点
	void setRoot(JsonValue* root);					//设置root结点
private:
	std::ifstream file;		//视频文件句柄
	JsonValue* m_Root;		//json控制器根节点
	
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
	virtual void writeToStr(std::string &str);			//导出Json文件构建输出str
	//JsonValue* getValue(std::string str);
	virtual JsonDict* toDict();							//指向dict
	virtual JsonString* toString();						//指向string
	virtual JsonList* toList();							//指向List
private:
	union {
		double m_ValueNumber;
		bool m_ValueBool;
	};
	JSONVALUETYPE m_type;								//Json类型
};

class JsonList : public JsonValue {
public:
	JsonList();
	~JsonList();
	void append(JsonValue* value);						//载入
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
	bool contain(std::string str);		//包含
	void remove(std::string str);		//移除
	void clear();
	JsonValue* getValue(std::string tKey);
	JsonDict* toDict();
private:
	std::vector<std::string> m_ObjList;
	std::unordered_map<std::string, JsonValue*> m_Cache;			//key：name value:对应类型的值
};