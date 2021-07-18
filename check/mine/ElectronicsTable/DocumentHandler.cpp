#include <iostream>
#include <string>
#include <stdexcept>
#include "termcolor.hpp" // Open-source console coloring tool
#include "DocumentHandler.h"
#include "StringHelper.h"
#include "CommandParser.h"
#include "IntegerType.h"
#include "DoubleType.h"
#include "FormulaType.h"
#include "StringType.h"

using std::cin;
using std::cout;
using std::endl;
using std::exception;
using std::getline;
using std::invalid_argument;
using std::out_of_range;
using std::string;
using std::to_string;
using termcolor::green;
using termcolor::red;
using termcolor::reset;
using termcolor::yellow;
using termcolor::blue;
using sh = StringHelper;

DocumentHandler::DocumentHandler()
{
}

void DocumentHandler::menu() const
{
	cout << "\t\t\tMENU" << endl;
	cout << "open <path>		- opens the given file at <path>" << endl;
	cout << "close			- closes the current file" << endl;
	cout << "new			- creates new empty document. Can only be saved via saveas" << endl;
	cout << "save			- saves the current opened document in the current linked file" << endl;
	cout << "saveas <path>		- saves the current document in the file at <path>" << endl;
	cout << "edit <address> <value>	- edits the desired cell at <address> with desired <value>" << endl;
	cout << "print			- prints the contents of the table on the console" << endl;
	cout << "exit			- exits the program" << endl;
}

DocumentHandler& DocumentHandler::getInstance()
{
	static DocumentHandler inst;
	return inst;
}

void DocumentHandler::populateTableFromFile()
{
	initializeEmptyTableFromFile();

	if (!m_file.good())
		m_file.clear();

	m_file.seekg(0, std::ios_base::beg);

	fillTableFromFile();
}

bool DocumentHandler::openFile(const string& path)
{
	string cpy(path);
	if (!m_isClosed)
	{
		if (!closeFile())
			return false;
	}

	if (sh::isStringValidString(cpy))
		sh::removeQuotations(cpy);

	m_file.open(cpy, std::ios_base::in);

	if (!m_file.is_open())
	{
		throw invalid_argument("Couldn't open file for reading.");
	}

	clearState(false, false, true, false);
	populateTableFromFile();

	m_file.close();
	m_filePath = cpy;
	m_isClosed = false;
	clearState(false, true);
	return true;
}

bool DocumentHandler::closeFile()
{
	if (m_isClosed)
		throw invalid_argument("Cannot close - no document loaded");

	if (!m_isSaved)
	{
		while (true)
		{
			char choice;
			cout << "There are unsaved changes. SAVE/DON'T SAVE/CANCEL(s/d/c): ";
			cin >> choice;
			if (choice == 's')
			{
				saveToFile();
				cout << green << "File saved." << reset << endl;
				break;
			}
			else if (choice == 'd')
			{
				cout << yellow << "File not saved." << reset << endl;
				break;
			}
			else if (choice == 'c')
			{
				cin.ignore();
				return false;
			}
			else
			{
				cout << red << "Invalid choice" << reset << endl;
			}
		}
		cin.ignore();
	}

	m_isClosed = true;
	clearState(false, false, true, true);
	return true;
}

void DocumentHandler::saveToFile()
{
	if (m_isClosed)
	{
		throw invalid_argument("Cannot save - no document loaded");
	}

	m_file.open(m_filePath);

	for (size_t i = 0; i < m_table.getRows(); i++)
	{
		for (size_t j = 0; j < m_table[i].size(); j++)
		{
			if (m_table[i][j].getContent() != nullptr)
				m_file << m_table[i][j].getContent()->toFileFormat();

			if (j != m_table[i].size() - 1)
			{
				m_file << ",";
			}
		}
		m_file << endl;
	}

	m_file.close();
	m_isClosed = false;
	setState(true);
}

void DocumentHandler::saveFileAs(const string& path)
{
	if (m_isClosed && !m_isNew)
	{
		throw invalid_argument("Cannot saveas - there is no loaded document or the document is not new");
	}

	m_filePath = path;
	m_isClosed = false;
	saveToFile();
	clearState(false, true);
}

bool DocumentHandler::createNewDocument()
{
	if (!m_isClosed)
	{
		if (!closeFile())
			return false;
	}

	setState(false, true);
	clearState(false, false, true, true);

	return true;
}

void DocumentHandler::editFile(size_t row, size_t col, const string& content)
{
	if (!m_isNew && m_isClosed)
	{
		throw invalid_argument("Cannot edit - no document loaded");
	}

	alterCell(row, col, content);
	clearState(true);
}

void DocumentHandler::alterCell(size_t row, size_t col, const string& content)
{
	string cpy(content);
	sh::trim(cpy);

	Cell c(content, m_table);

	m_table.setCellAt(row, col, c);
}

void DocumentHandler::initializeEmptyTableFromFile()
{
	size_t rowsOfFile = 0;
	size_t maxColOfFile = 0;
	string content;

	while (getline(m_file, content))
	{
		if (sh::getQuotesCount(content) % 2 != 0)
		{
			string err = "Error: row " + to_string(rowsOfFile) + " has odd number of quotations";
			clearState(false, false, true, true);
			m_isClosed = true;
			throw invalid_argument(err);
		}

		vector<string> parts = sh::splitBy(content, ",");

		for (size_t i = 0; i < parts.size(); i++)
		{
			if (sh::isStringInteger(parts[i]))
			{
				continue;
			}
			else if (sh::isStringDouble(parts[i]))
			{
				continue;
			}
			else if (sh::isStringValidString(parts[i]))
			{
				string cpy(parts[i]);
				sh::removeQuotations(cpy);
				sh::trim(cpy);
				if (cpy[0] == '=')
				{
					if (!sh::isStringValidFormula(cpy))
					{
						string err = "Error: row " + to_string(rowsOfFile) + ", col " + to_string(i) + ", " + parts[i] + " is invalid formula";
						clearState(false, false, true, true);
						m_isClosed = true;
						throw invalid_argument(err);
					}
				}
				else
				{
					continue;
				}
			}
			else if (parts[i].empty())
			{
				continue;
			}
			else
			{
				string err = "Error: row " + to_string(rowsOfFile) + ", col " + to_string(i) + ", " + parts[i] + " is unknown data type";
				clearState(false, false, true, true);
				m_isClosed = true;
				throw invalid_argument(err);
			}
		}

		if (maxColOfFile < parts.size())
		{
			maxColOfFile = parts.size();
		}
		rowsOfFile++;
	}

	m_table.expandRows(rowsOfFile);
	m_table.expandCols(maxColOfFile);
}

void DocumentHandler::fillTableFromFile()
{
	size_t currRow = 0;
	string content;

	while (getline(m_file, content))
	{
		vector<string> parts = sh::splitBy(content, ",");
		for (size_t i = 0; i < parts.size(); i++)
		{
			alterCell(currRow, i, parts[i]);
		}
		currRow++;
	}
}

void DocumentHandler::exe()
{
	menu();
	CommandParser cp;

	while (true)
	{
		string cmd, fileIndicator;
		if (m_isNew)
			fileIndicator = "new document";
		else if (!m_filePath.empty())
			fileIndicator = m_filePath;
		else
			fileIndicator = "no selected file";
		cout << yellow << "(" + fileIndicator + ")" + ">" << reset;

		getline(cin, cmd);

		cp.clearCmd();
		try
		{
			cp.setData(cmd);
		}
		catch (const invalid_argument& e)
		{
			cout << red << e.what() << reset << endl;
			continue;
		}

		switch (cp.getCommandType())
		{
		case CommandType::OPEN:
			try
			{
				if (!openFile(cp.atToken(1)))
					break;
			}
			catch (const invalid_argument& e)
			{
				cout << red << e.what() << reset << endl;
				break;
			}
			catch (const out_of_range& e)
			{
				cout << red << e.what() << reset << endl;
				break;
			}

			cout << green << "Successfully opened " << cp.atToken(1) << reset << endl;
			break;
		case CommandType::CLOSE:
			try
			{
				if (!closeFile())
					break;
			}
			catch (const exception& e)
			{
				cout << red << e.what() << reset << endl;
				break;
			}

			cout << green << "Successfully closed file." << reset << endl;
			break;
		case CommandType::NEW:
			try
			{
				if (!createNewDocument())
					break;
			}
			catch (const exception& e)
			{
				cout << red << e.what() << reset << endl;
				break;
			}

			cout << green << "Succesfully created new document" << reset << endl;
			break;
		case CommandType::SAVE:
			try
			{
				saveToFile();
			}
			catch (const exception& e)
			{
				cout << red << e.what() << reset << endl;
				break;
			}

			cout << green << "Successfully saved file into " << m_filePath << reset << endl;
			break;
		case CommandType::SAVEAS:
			try
			{
				saveFileAs(cp.atToken(1));
			}
			catch (const exception& e)
			{
				cout << red << e.what() << reset << endl;
				break;
			}

			cout << green << "Successfully saved table to " << m_filePath << reset << endl;
			break;
		case CommandType::EDIT:
			try
			{
				if (!sh::isStringValidCellAddress(cp.atToken(1)))
				{
					cout << red << "Invalid formula address" << reset << endl;
					break;
				}

				Pair pair = sh::extractCellAddressDetails(cp.atToken(1));
				editFile(pair.key, pair.value, cp.atToken(2));
			}
			catch (const invalid_argument& e)
			{
				cout << red << e.what() << reset << endl;
				break;
			}
			catch (const exception& e)
			{
				cout << red << e.what() << reset << endl;
				break;
			}

			cout << green << "Successfully set cell " << cp.atToken(1) << ", with content " << cp.atToken(2) << reset << endl;
			break;
		case CommandType::PRINT:
			try
			{
				m_table.print();
			}
			catch (const std::exception& e)
			{
				cout << red << e.what() << reset << endl;
				break;
			}

			break;
		case CommandType::EXIT:
			try
			{
				if (!m_isClosed)
				{
					if (!closeFile())
						break;
				}
			}
			catch (const exception& e)
			{
				cout << red << e.what() << reset << endl;
				break;
			}

			cout << termcolor::magenta << "Exiting the program..." << reset << endl;
			return;
		case CommandType::NOCOMMAND:
			cout << red << "Invalid command." << reset << endl;
			break;
		default:
			break;
		}
	}
}

void DocumentHandler::clearState(bool turn_off_saved, bool turn_off_new, bool clear_table, bool clear_filePath)
{
	if (clear_filePath)
		m_filePath.clear();

	if (clear_table)
		m_table.clearTable();

	if (turn_off_new)
		m_isNew = false;

	if (turn_off_saved)
		m_isSaved = false;
}

void DocumentHandler::setState(bool turn_on_saved, bool turn_on_new)
{
	if (turn_on_new)
		m_isNew = true;

	if (turn_on_saved)
		m_isSaved = true;
}
