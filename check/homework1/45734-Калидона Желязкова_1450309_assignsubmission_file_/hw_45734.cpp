#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <cstring>

using namespace std;
class MyString {
	char* str;
public:
	MyString();
	MyString(char* arg);
	MyString(const MyString& arg);
	MyString(MyString& arg);
	MyString(const char* arg);

};
MyString::MyString()
	:str{ nullptr } {
	str = new char[1];
	str[0] = '\0';
}
MyString::MyString(char* arg) {
	if (arg == nullptr) {
		str = new char[1];
		str[0] = '\0';
	}
	else {
		str = new char[strlen(arg) + 1];
		strcpy(str, arg);
		cout << "The string is: " << str << endl;
	}
}
MyString::MyString(const MyString& arg) {
	str = new char[strlen(arg.str) + 1];
	strcpy(str, arg.str);
}
MyString::MyString(MyString& arg) {
	str = arg.str;
	arg.str = nullptr;
}
MyString::MyString(const char* arg) {
	const size_t len = strlen(arg);
	char* temp = new char[len + 1];
	strncpy(temp, arg, len);
	temp[len] = '\0';
	delete[] arg;
	arg = temp;
}


int main() {
	
	return 0;
}