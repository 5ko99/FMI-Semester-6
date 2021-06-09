// 
// �� "��. ������� ��������"
// �������� �� ���������� � �����������
// ���� �������-����������� ������������ 2020/21
// ��������� 2
// 
// ���: ��������� ��������
// ��: 45657
// �����������: �����������
// ����: 2
// ��������������� �����: 4
// ���, � ����� �� ������� �� �����������: 29.05.2021
// ������� ��� �� �����������: 09:00
// ��� ���������� ����������: Visual C++
//
#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

std::size_t countWords(std::string& text)
{
	std::size_t count = 0;

	for (std::size_t i = 0; i < text.length(); ++i)
	{
		if (text[i] != ' ')
		{
			++count;
			while (text[i] != ' ' && i < text.length())
			{
				++i;
			}
		}
	}

	return count;
}

class Command
{
private:
	std::string text;
	std::string* partition = nullptr;
	std::size_t partitionSize = 0;
public:
	Command(std::string& text)
	{
		this->text = text;
		partitionSize = countWords(text);
		try
		{
			partition = new std::string[partitionSize + 1];
		}
		catch (const std::bad_alloc& e)
		{
			std::cout << e.what();
		}
		
		
	}

	~Command()
	{
		delete[] partition;
		partitionSize = 0;
	}

	std::size_t size() const
	{
		return partitionSize;
	}

	Command& operator[](std::size_t index) const
	{
		if (index >= partitionSize)
		{
			throw std::out_of_range(" ");
		}

		std::cout << partition[index];
	}
};

int main()
{
	
	return 0;
}