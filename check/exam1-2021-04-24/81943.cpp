// 
// СУ "Св. Климент Охридски"
// Факултет по математика и информатика
// Курс Обектно-ориентирано програмиране 2020/21
// Контролно 1
// 
// Име: Димитър Пламенов Иванов
// ФН: 81943
// Специалност: Компютърни науки
// Курс: 2 курс
// Административна група: 4-та група
// Ден, в който се явявате на контролното: 24 април 2021
// Начален час на контролното: 9:30
// Кой компилатор използвате: Visual Studio Community 2019
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
#include <cstddef>
#include <cstdlib>
#include <stdexcept>
#include <iostream>

//3 zad
int* create_set(const size_t size, int* arr)
{
	for (int i = 0; i < size; ++i)
	{
		arr[i] = std::rand(); // set a lower boundary?
	}

	return arr;
}

void spoof (const size_t size, int* arr) // shows the generated numbers
{
	std::cout << "the generated numbers are: ";

	for (int i = 0; i < size; ++i)
	{
		std::cout << arr[i] << ' ';
	}
	std::cout << std::endl;
}

void current (const size_t size, int* arr) // shows the current guessed numbers
{
	std::cout << "current guessed numbers: ";

	for (int i = 0; i < size; ++i)
	{
		std::cout << arr[i] << ' ';
	}

	std::cout << std::endl;
}

bool n_is_in_generated(const int number, const int* arr, const size_t size)
{
	for (int i = 0; i < size; ++i)
	{
		if (arr[i] == number)
			return true;
	}

	return false;
}

bool n_is_not_guessed(const int number, const int* arr, const size_t size)
{
	//bool flag = true;

	for (int i = 0; i < size; i++)
	{
		if (number == arr[i])
		{
			return false;
		}
	}

	return true;
}

void game_loop (const size_t size, int* generated_numbers, int* guessed_numbers)
{
	//bool guessed_generated_numbers[100];
	//set_false(size, guessed_generated_numbers);

	int n;
	size_t GN_size = 0;
	size_t number_of_turns = 0; //for cosmetic purposes

	while (/*!all_numbers_are_guessed(size, guessed_generated_numbers)*/
		   GN_size != size)
	{
		std::cin >> n;
		// the negative numbers (with their respecitve functions) are introduced to check the solution faster

		if (n == -1)
		{
			current(GN_size,guessed_numbers);
			++number_of_turns;
		}
		else if (n == -2)
		{
			spoof(size, generated_numbers);
			++number_of_turns;
		}
		else if (n_is_in_generated(n, generated_numbers, size) && n_is_not_guessed(n, guessed_numbers, GN_size))
		{
			std::cout << "Hooray! You guessed a number!";
			std::cout << std::endl;
			guessed_numbers[GN_size] = n;
			++GN_size;
			++number_of_turns;
		}
		else if (n_is_in_generated(n, generated_numbers, size) && !n_is_not_guessed(n, guessed_numbers, GN_size))
		{
			std::cout << "You have already found this number.";
			std::cout << std::endl;
			++number_of_turns;
		}
		else /*n is not present in the generated numbers*/
		{
			std::cout << "n is not present in the generated numbers. Try again.";
			std::cout << std::endl;
			++number_of_turns;
		}
	}

	std::cout << "Congratulations! You guessed all the numbers correctly! It took you "
		<< number_of_turns
		<< " turns."
		<< std::endl;
}

bool* set_false (const size_t size, bool* arr)
{
	for (int i = 0; i < size; ++i)
	{
		arr[i] = false;
	}

	return arr;
}

bool all_numbers_are_guessed (const size_t size, bool* arr)
{
	bool flag = true;

	for (int i = 0; i < size; ++i)
	{
		if (!arr[i])
		{
			flag = false;
		}
	}

	return flag;
}

//zad 1
class IntBuffer
{
	int* data;
	int size; // current amount of elements
	int capacity; // maximum amount of elements. can be expanded
};

int main()
{
	//zad 3
	
	std::size_t N;
	std::cin >> N;

	int generated[100]; // size boundaries?
	create_set(N, generated);

	int G[100];

	game_loop(N, generated, G);
	

	//zad 1


	return 0;
}