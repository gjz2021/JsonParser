#include "Json.h"
#include <iostream>
#include <algorithm>
Json::Json():m_Root(nullptr)
{
}
Json::Json(std::string & str) : m_Root(nullptr)
{
	Reader tReader(str);
	m_Root = parseValue(tReader);
}
Json::Json(std::ifstream &file) : m_Root(nullptr) {
	Reader tReader(file);
	m_Root = parseValue(tReader);
}

Json::~Json()
{
	if (m_Root) {
		delete m_Root;
	}
	
}

JsonValue * Json::parseValue(Reader &context)
{
	JsonValue* tRet = nullptr;
	context.ignoreSpace();
	char tChar = context.peekChar();
	switch (tChar)
	{
	case '{':
		tRet = parseDict(context);
		break;
	case '[':
		tRet = parseList(context);
		break;
	case '"':
		tRet = parseString(context);
		break;
	case 't':
		context.match("true");
		tRet = new JsonValue(true);
	case 'f':
		context.match("false");
		tRet = new JsonValue(false);
	case 'n':
		context.match("null");
		tRet = new JsonValue();
	default:
		if (tChar == '-' || iswdigit(tChar)) {
			tRet = parseNumber(context);
		}
		else {
			std::cout << "format is errot" << std::endl;
		}
		break;
	}

	return tRet;
}

JsonValue * Json::parseNumber(Reader &context)
{
	std::string tStr;
	char tChar = context.peekChar();
	while (iswdigit(tChar) || tChar == '-' || tChar == '.' || tChar == 'e' || tChar == 'E') {
		tStr += tChar;
		context.readChar();
		if(context.IsEOF()){
			break;
		}
		else {
			tChar = context.peekChar();
		}
	}
	return new JsonValue(atof(tStr.c_str()));
}

JsonList * Json::parseList(Reader &context)
{
	JsonList* tRet = new JsonList();
	context.match('[');
	while (1) {
		if (context.tryMatch(']')) {
			break;
		}
		JsonValue* Value = parseValue(context);
		tRet->append(Value);
		if (context.tryMatch(',')) {
			continue;
		}
	}
	
	return tRet;
}

JsonDict * Json::parseDict(Reader &context)
{
	JsonDict *tRet = new JsonDict();
	context.match('{');
	while (1) {
		if (context.tryMatch('}')) {
			break;
		}
		JsonString *tKey = nullptr;
		tKey = parseString(context);
		context.match('/:');
		JsonValue *tValue = nullptr;
		tValue = parseValue(context);
		tRet->setValue(tKey->getStr(), tValue);
		delete tKey;
		if (context.tryMatch(',')) {
			continue;
		}
	}
	return tRet;
}

JsonString * Json::parseString(Reader& context)
{
	std::string tRet;
	context.match('"');
	char tChar;
	while ((tChar = context.readChar()) != '"') 
	{
		if (iscntrl(tChar)) {
			std::cout <<  "tChar is a control charactor";
		}
		if (tChar == '\\') {
			tChar = context.readChar();
			switch (tChar)
			{
			case '"':
				tRet += "\"";
				break;
			case '\\':
				tRet += "\\";
				break;
			case '/':
				tRet += "/";
				break;
			case 'b':
				tRet += "\b";
				break;
			case 'f':
				tRet += "\f";
				break;
			case 'n':
				tRet += "\n";
				break;
			case 'r':
				tRet += "\r";
				break;
			case 't':
				tRet += "\t";
				break;
			default:
				std::cout <<  "";
				break;
			}
		}
		else {
			tRet += tChar;
		}
	}

	return new JsonString(tRet.c_str());
}

void Json::writeToStr(std::string & str)
{
	if (m_Root) {
		m_Root->writeToStr(str);
	}
}

void Json::writeToStream(std::ofstream &file)
{
	std::string tStr;
	if (!m_Root) {
		std::cout << "m_Root is nullptr" << std::endl;
		return;
	}
	m_Root->writeToStr(tStr);
	file << tStr << std::endl;
}

JsonValue * Json::getRoot()
{
	return m_Root;
}

void Json::setRoot(JsonValue * root)
{
	m_Root = root;
}


JsonValue::JsonValue() :m_type(JSONVALUETYPE_NULL), m_ValueNumber(0)
{
}

JsonValue::JsonValue(JSONVALUETYPE type) : m_type(type)
{
}

JsonValue::JsonValue(bool flag) : m_type(JSONVALUETYPE_BOOL)
{
	m_ValueBool = flag;
}
JsonValue::JsonValue(double num) : m_type(JSONVALUETYPE_NUMBER)
{
	m_ValueNumber = num;
}
JsonValue::~JsonValue()
{
}
void JsonValue::writeToStr(std::string & str)
{
	switch (m_type)
	{
	case JSONVALUETYPE_NULL:
		str += "NULL";
		break;
	case JSONVALUETYPE_BOOL:
		if (m_ValueBool) {
			str += "true";
		}
		else {
			str += "false";
		}
		break;
	case JSONVALUETYPE_NUMBER:
		char tStr[20];
		memset(tStr, 0, sizeof(tStr));
		_itoa_s(m_ValueNumber,tStr, 10);
		str += tStr;
		break;
	default:
		std::cout << "jsonvalue::writeTostr is error" << std::endl;
		break;
	}
}

JsonDict * JsonValue::toDict()
{
	return nullptr;
}

JsonString * JsonValue::toString()
{
	return nullptr;
}

JsonList * JsonValue::toList()
{
	return nullptr;
}

/*JsonValue * JsonValue::getValue(std::string str)
{
	return nullptr;
}*/

JsonString::JsonString(std::string value):JsonValue(m_type),m_Str(value)
{

}

JsonString::~JsonString()
{

}

std::string JsonString::getStr()
{
	return m_Str;
}

void JsonString::setString(std::string value)
{
	m_Str = value;
}

void JsonString::writeToStr(std::string & str)
{
	str += "\"";
	str += m_Str;
	str += "\"";
}

JsonString * JsonString::toString()
{
	return this;
}


JsonDict::JsonDict():JsonValue(JSONVALUETYPE_DICT)
{
}

JsonDict::~JsonDict()
{
	clear();
}

void JsonDict::setValue(std::string Name, JsonValue * pNew)
{
	if (contain(Name)) {
		remove(Name);
	}
	m_ObjList.push_back(Name);
	m_Cache[Name] = pNew;
}

void JsonDict::writeToStr(std::string & outStr)
{	
	outStr += "{";
	for (int i = 0; i < m_ObjList.size(); i++) {
		JsonValue *tRet = m_Cache[m_ObjList[i]];
		outStr += "\"";
		outStr += m_ObjList[i];
		outStr += "\":";
		tRet->writeToStr(outStr);
		if (i != m_ObjList.size() - 1) {
			outStr += ',';
		}
	}
	outStr += '}';
}

bool JsonDict::contain(std::string str)
{
	return m_Cache[str] ? true : false;
}

void JsonDict::remove(std::string str)
{
	auto it = find(m_ObjList.begin(),m_ObjList.end(),str);
	if (it != m_ObjList.end()) {
		m_ObjList.erase(it);
	}
	auto it_Oc = m_Cache.find(str);
	delete it_Oc->second;
	m_Cache.erase(it_Oc);
}

void JsonDict::clear()
{
	auto it = m_Cache.begin();
	while (it != m_Cache.end()) {
		delete (it->second);
		it++;
	}
	m_Cache.clear();
	m_ObjList.clear();
}


JsonValue * JsonDict::getValue(std::string tKey)
{
	auto it = m_Cache.find(tKey);
	if (it != m_Cache.end()) {
		return it->second;
	}
	return nullptr;
}

JsonDict * JsonDict::toDict()
{
	return this;
}

JsonList::JsonList():JsonValue(JSONVALUETYPE_LIST)
{
	
}

JsonList::~JsonList()
{
	clear();
}

void JsonList::append(JsonValue * value)
{
	m_ObjList.push_back(value);
}

void JsonList::writeToStr(std::string & str)
{
	str += '[';
	for (int i = 0; i < m_ObjList.size(); i++) {
		auto *it = m_ObjList[i];
		it->writeToStr(str);
		if (i != m_ObjList.size() - 1) {
			str += ',';
		}
	}
	str += ']';
}

int JsonList::getListSize()
{
	return m_ObjList.size();
}

JsonValue * JsonList::getValue(int index)
{
	if (index >= getListSize()) {
		return nullptr;
	}
	return m_ObjList[index];
}

JsonList * JsonList::toList()
{
	return this;
}

void JsonList::clear()
{
	std::vector<JsonValue*> ::iterator it = m_ObjList.begin();
	while (it != m_ObjList.end()) {
		delete (*it);
		++it;
	}
	m_ObjList.clear();
}
