// 
// �� "��. ������� ��������"
// �������� �� ���������� � �����������
// ���� �������-����������� ������������ 2020/21
// ��������� 2
// 
// ���: ���� ������� �������
// ��: 45625
// �����������: �����������
// ����: II
// ��������������� �����: II
// ���, � ����� �� ������� �� �����������: 29.05.2021
// ������� ��� �� �����������: 9:00
// ��� ���������� ����������: Visual C++
//

#include "processor.h"

#define _CRT_SECURE_NO_WARNINGS 

#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

int main()
{

	string path;
	std::cout << "Please enter file path: ";
	std::getline(std::cin, path);
	processor p(path);

	while (true)
	{
		string cmd;
		std::getline(std::cin, cmd);
		command command(cmd);
		try
		{
		p.execute(command);
		}
		catch (const std::invalid_argument& e)
		{
			std::cerr << e.what();
		}
	}

	return 0;
}