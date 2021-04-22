// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Вангелия Борисова Танчева
// ФН: 82192
// Специалност: КН
// Курс: 1
// Административна група: 3
// Ден, в който се явявате на контролното: 17.04.2021
// Начален час на контролното: < 10:30 >
// Кой компилатор използвате: < Visual Studio >
//

// (Можете да изтриете този коментар след като го прочетете)
// Редът по-долу е специфичен за Visual C++.
// Ако използвате друг компилатор, можете да го изтриете.
// Тъй като strlen, strcmp и т.н. са дефинирани като deprecated,
// имате две възможности:
//
// * да използвате безопасните версии на тези функции
//   (strlen_s, strcmp_s и т.н.). В този случай можете да
//   изтриете дадената по-долу #define директива.
//
// * да дефинирате _CRT_SECURE_NO_WARNINGS преди да
//   включите съответните header файлове от стандартната
//   библиотека.
//
#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>

int main()
{
	class MyString :
	{
	private:
		
		char* str
		size_t str_size;

	public:
		///Constuctor
		
		MyString();

		///Constructor with argument
		
		MyString(char* value);

		MyString(const char* value);

		/// Copy-assigment constructor
		
		MyString& operator = (const MyString & source);

		char& at(size_t pos);

		const char& at size_t pos const;

		char& operator[](size_t pos);

		const char& operator[](size_t pos) const;

		char front();

		const char& back() const;

		bool empty() const;

		void clear();

		void push_back(char c);

		void pop_back();

		MyString& operator += (char c);

		MyString& operator += (const MyString& source);

		MyString operator (char c) const;

		MyString operator+ (const MyString & source) const;

		const char* c_str() const;

		bool operator == (const MyString & rhs) const;

		bool operator <(const MyString & rhs) const;

		/// Move Constructor
		/*
		 MyString(MyString&& source)
		 {
		   str = source.str;
		   source.str = nullstr;
		 } */

		~MyString()
		{
			delete[] str;
		}
		int std::string id;
		int Date date;

		Registration(const str::string& id, const Date& date)

			Class Registration
		{
		private:

			size_t registration

		public:

			///Constructor with argument

			garage(size_t garage_size);

			void insert(registration & v);

			void erase const char* (registration)

				const registration& at(size_t pos) const;

			const registration& operator[](size_t pos) const;

			bool empty() const;

			size_t size() const;

			void clear();

			const registration* find(const char* registration) const;

			void print()


				MyString& MyString:: operator = (const MyString & source);
			{
				if (this == &source)
				{
					return *this;
				}

				delete[] str;

				str = new char[source.size() + 1];
				
				for( int i = '\0')

			}

		
		}

	}

	return 0;
}
