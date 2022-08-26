// Name: Amritpal Singh
// Seneca Student ID: 150143196
// Seneca email: asingh882@myseneca.ca
// Date of completion: 31 July, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#pragma once
#include <iostream>

namespace sdds {
	class Station
	{
		int s_id;
		std::string s_name;
		std::string s_description;
		size_t s_serialNumber;
		size_t s_qty;
		static int m_widthField;
		static int m_idGenerator;
	public:
		Station(const std::string& record);
		const std::string& getItemName()const;
		size_t getNextSerialNumber();
		size_t getQuantity()const;
		void updateQuantity();
		void display(std::ostream& os, bool full)const;
	};
}

