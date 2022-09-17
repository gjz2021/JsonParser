// JsonParser.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
#include "Reader.h"
#include "Json.h"
#include "define.h"
//void func1();
//void func2();
/*int main()
{
	/*std::ifstream file("test.json");
	Json json(file);
	std::string str;
	json.writeToStr(str);
	std::cout << str << std::endl;
	std::string str1;
	json.getRoot()->writeToStr(str1);
	std::cout << str1 << std::endl;
	std::string str2;
	json.getRoot()->toDict()->getValue("key4")->toList()->getValue(1)->writeToStr(str2);
	std::string str3;
	json.getRoot()->toDict()->getValue("key6")->toDict()->getValue("val1")->writeToStr(str3);
	std::cout << str3 << std::endl;
	Json json;
	JsonDict dict1;
	JsonString str1("jwj");
	JsonList list1;
	JsonValue val1(3.0);
	JsonValue val2(4.0);
	dict1.setValue("key1", &val1);
	dict1.setValue("key2", &val2);
	list1.append(&val1);
	list1.append(&val2);
	list1.append(&str1);
	dict1.setValue("key3",&list1);
	std::string str;
	json.setRoot(&dict1);
	json.writeToStr(str);
	std::cout << str <<  std::endl;
	std::ofstream file("a.json");
	json.writeToStream(file);
	system("pause");
	callBackOnEventMessage = func1;
	callBackOnBinaryMessage = func2;

}
*/

/*typedef char(*p)(int);
p pFun;
char *glFun(int a) { 
	std::cout << " 2";
	return nullptr; }
void main()
{
	pFun = (char(*)(int))glFun; 
	(*pFun)(2);
	
}*/

int main() {
	int a = 3;
	if (a < 4) {
		std::cout << "1" << std::endl;
	}
	else if (a == 3) {
		std::cout << "2" << std::endl;
	}
	else {

	}
}