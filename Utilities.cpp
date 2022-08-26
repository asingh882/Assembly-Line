// Name: Amritpal Singh
// Seneca Student ID: 150143196
// Seneca email: asingh882@myseneca.ca
// Date of completion: 31 July, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iostream>
#include "Utilities.h"

using namespace std;

namespace sdds{

	char Utilities::m_delimiter{};


	void Utilities::setFieldWidth(size_t newWidth)
	{
		m_widthField = newWidth;
	}

	size_t Utilities::getFieldWidth()const
	{
		return m_widthField;
	}

	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
	{
		string temp{};
		size_t c;
		c = str.find(m_delimiter, next_pos);
		if (c == next_pos)
		{
			more = false;
			throw " ";
		}
		else if (c > next_pos && c < str.size())
		{
			temp = str.substr(next_pos, c - next_pos);
			next_pos = ++c;
			more = true;
		}
		else
		{
			temp = str.substr(next_pos, str.size());
			more = false;
		}
		if (m_widthField < temp.size())
			m_widthField = temp.size();
		return temp;
	}

	void Utilities::setDelimiter(char newDelimiter)
	{
		m_delimiter = newDelimiter;
	}

	char Utilities::getDelimiter()
	{
		return m_delimiter;
	}

}