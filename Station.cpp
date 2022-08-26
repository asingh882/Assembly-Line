// Name: Amritpal Singh
// Seneca Student ID: 150143196
// Seneca email: asingh882@myseneca.ca
// Date of completion: 31 July, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include<iostream>
#include<iomanip>
#include<string>
#include "Station.h"
#include"Utilities.h"

using namespace std;

namespace sdds {


	int Station::m_widthField{};
	int Station::m_idGenerator{};


	Station::Station(const std::string& record)
	{
		m_idGenerator++;
		s_id = m_idGenerator;
		Utilities util;
		bool yesNo;
		string temp;
		size_t position = 0;
		s_name = util.extractToken(record, position, yesNo);
		if(m_widthField < (int)util.getFieldWidth())
			m_widthField = util.getFieldWidth();
		if (yesNo == true)
		{
			temp = util.extractToken(record, position, yesNo);
			s_serialNumber = (size_t)stoi(temp);
		}
		if (yesNo == true)
		{
			temp = util.extractToken(record, position, yesNo);
			s_qty = (size_t)stoi(temp);
		}
		if (yesNo == true)
		{
			if (m_widthField < (int)util.getFieldWidth())
				m_widthField = util.getFieldWidth();
			s_description = util.extractToken(record, position, yesNo);
		}
	}

	const std::string& Station::getItemName()const
	{
		return s_name;
	}
	
	size_t Station::getNextSerialNumber()
	{
		return s_serialNumber++;
	}

	size_t Station::getQuantity()const
	{
		return s_qty;
	}
	
	void Station::updateQuantity()
	{
		if (s_qty > 0)
			s_qty--;
	}
	
	void Station::display(std::ostream& os, bool full)const
	{
		if (full == true)
		{
			os << "[" << setw(3) << setfill('0') << right << s_id << "] Item: ";
			
			os.setf(ios::left);
			os.width(m_widthField);
			os.fill(' ');
			os << left << s_name;
			os.unsetf(ios::left);


			os << " [" << setw(6) << setfill('0') << s_serialNumber << "] ";

			os.setf(ios::left);
			os << "Quantity: " << setw(m_widthField) << setfill(' ') << s_qty;
			os.unsetf(ios::left);

			os << " Description: " << s_description;

			os << endl;
		}
		else
		{
			os << "[" << setw(3) << setfill('0') << s_id << "]";
			
			os.setf(ios::left);
			os << " Item: " << setw(m_widthField) << setfill(' ') << s_name;
			os.unsetf(ios::left);
			os << " [" << setw(6) << setfill('0') << s_serialNumber << "]"; 
			
			os << endl;

		}
	}
}