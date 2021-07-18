#include <iostream>
#include "Cell.h"
#include "StringHelper.h"
#include "IntegerType.h"
#include "DoubleType.h"
#include "FormulaType.h"
#include "StringType.h"

using std::cout;
using std::invalid_argument;
using sh = StringHelper;

Cell::Cell(const string& content, const Table& ref)
{
	if (sh::isStringInteger(content))
	{
		m_content = new IntegerType(content);
	}
	else if (sh::isStringDouble(content))
	{
		m_content = new DoubleType(content);
	}
	else if (sh::isStringValidString(content))
	{
		string cpy(content);
		sh::trim(cpy);
		sh::removeQuotations(cpy);
		if (cpy[0] == '=')
		{
			if (sh::isStringValidFormula(cpy))
			{
				m_content = new FormulaType(cpy, ref);
			}
			else
			{
				string err = "Error: incorrect value " + content;
				throw invalid_argument(err);
			}
		}
		else
		{
			m_content = new StringType(cpy);
		}
	}
	else if (content.empty())
	{
		m_content = nullptr;
	}
	else
	{
		string err = "Error: incorrect value " + content;
		throw invalid_argument(err);
	}
}

void Cell::copyFrom(const Cell& other)
{
	if (other.m_content != nullptr)
		m_content = other.m_content->clone();
	else
		m_content = nullptr;
}

void Cell::moveFrom(Cell& other) {
	m_content = other.m_content;
	other.m_content = nullptr;
}

Cell::Cell(const Cell& other)
{
	copyFrom(other);
}

Cell& Cell::operator=(const Cell& other)
{
	if (this != &other)
	{
		delete m_content;
		copyFrom(other);
	}

	return *this;
}

Cell::Cell(Cell&& other) noexcept
{
	moveFrom(other);
}

Cell& Cell::operator=(Cell&& other) noexcept
{
	if (this != &other)
	{
		delete m_content;
		moveFrom(other);
	}

	return *this;
}

void Cell::print() const
{
	if (m_content == nullptr)
		cout << "";
	else
		m_content->print();
}

double Cell::getContentAsDouble() const
{
	if (m_content == nullptr)
	{
		return 0;
	}

	return m_content->toDouble();
}

CellType* Cell::getContent() const
{
	return m_content;
}

Cell::~Cell()
{
	delete m_content;
}