// Name: Amritpal Singh
// Seneca Student ID: 150143196
// Seneca email: asingh882@myseneca.ca
// Date of completion: 31 July, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#pragma once
#include <iostream>
#include "Station.h"
#include "Utilities.h"

namespace sdds {

	struct Item
	{
		std::string m_itemName;
		size_t m_serialNumber{ 0 };
		bool m_isFilled{ false };

		Item(const std::string& src) : m_itemName(src) {};
	};

	class CustomerOrder
	{
		std::string m_name{};
		std::string m_product{};
		size_t m_cntItem{};
		Item** m_lstitem{};

		static size_t m_widthField;
	public:
		CustomerOrder() {};
		CustomerOrder(const std::string& s);
		CustomerOrder(CustomerOrder& c);
		CustomerOrder(CustomerOrder&& c)noexcept;

		CustomerOrder& operator=(CustomerOrder& c) = delete;
		CustomerOrder& operator=(CustomerOrder&& c)noexcept;

		bool isFilled()const;
		bool isItemFilled(const std::string& itemName)const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os)const;
		~CustomerOrder();

	};

}

