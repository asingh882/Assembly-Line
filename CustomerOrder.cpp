// Name: Amritpal Singh
// Seneca Student ID: 150143196
// Seneca email: asingh882@myseneca.ca
// Date of completion: 31 July, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#include "CustomerOrder.h"
#include<iostream>
#include <iomanip>
#include "Station.h"
#include "Utilities.h"

using namespace std;

namespace sdds {

	size_t CustomerOrder::m_widthField{};

	CustomerOrder::CustomerOrder(const std::string& record)
	{
		Utilities util;
		Item** tempStorage{};
		bool yesNo;
		string temp;
		size_t position = 0;

		m_name = util.extractToken(record, position, yesNo);
		
		if (yesNo == true)
		{
			m_product = util.extractToken(record, position, yesNo);
		}
		
		while (yesNo)
		{
			Item* newItem = nullptr;
			if (m_cntItem == 0)
			{
				temp = util.extractToken(record, position, yesNo);
				delete[] m_lstitem;
				m_lstitem = new Item * [m_cntItem + 1];

				delete newItem;
				newItem = new Item(temp);

				m_lstitem[0] = newItem;
			}
			else
			{
				temp = util.extractToken(record, position, yesNo);
				
				delete newItem;
				newItem = nullptr;
				newItem = new Item(temp);
				
				delete[] tempStorage;
				tempStorage = new Item*[m_cntItem];
				
				for (size_t i = 0; i < m_cntItem; i++)
					tempStorage[i] = m_lstitem[i];
				
				delete[] m_lstitem;
				m_lstitem = new Item * [m_cntItem + 1];
				
				for (size_t i = 0; i < m_cntItem; i++)
					m_lstitem[i] = tempStorage[i];
				
				m_lstitem[m_cntItem] = newItem;

				
			}
			m_cntItem++;
		}
		if (m_widthField < util.getFieldWidth())
			m_widthField = util.getFieldWidth();

		delete[] tempStorage;
		tempStorage = nullptr;
	}
	
	CustomerOrder::CustomerOrder(CustomerOrder& c)
	{
		throw "COPY CONSTRUCTOR IS NOT SUPPORTED!\n";
	}

	CustomerOrder::CustomerOrder(CustomerOrder&& c)noexcept
	{

		*this = move(c);
	}
	
	CustomerOrder& CustomerOrder::operator=(CustomerOrder&& c)noexcept
	{
		if (this != &c)
		{

			swap(m_lstitem, c.m_lstitem);
			m_name = c.m_name;
			m_product = c.m_product;
			m_cntItem = c.m_cntItem;


			c.m_name.clear();
			c.m_product.clear();
			c.m_cntItem = 0;
			
			delete[] c.m_lstitem;
			c.m_lstitem = nullptr;
		}
		return *this;
	}

	
	bool CustomerOrder::isFilled()const
	{
		bool filled = true;
		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (!m_lstitem[i]->m_isFilled)
			{
				filled = false;
				break;
			}
		}
		return filled;

	}
	
	bool CustomerOrder::isItemFilled(const std::string& itemName)const
	{
		bool yesNo = false;
		size_t i = 0;
		for (i = 0; i < m_cntItem; i++)
		{
			if (m_lstitem[i]->m_itemName == itemName)
			{
				yesNo = m_lstitem[i]->m_isFilled;
				break;
			}
		}
		if (i == m_cntItem)
			yesNo = true;
		return yesNo;
	}
	
	void CustomerOrder::fillItem(Station& station, std::ostream& os)
	{
	
		if (!isItemFilled(station.getItemName()) && station.getQuantity() > 0)
		{
			for (size_t i = 0; i < m_cntItem; i++)
			{
				if (m_lstitem[i]->m_itemName == station.getItemName())
				{
					m_lstitem[i]->m_serialNumber = station.getNextSerialNumber();
					m_lstitem[i]->m_isFilled = true;
					os << setw(11) << right << "Filled " << left << m_name << ", " << m_product << " [" << m_lstitem[i]->m_itemName << "]\n";
					station.updateQuantity();
				}
			}
		}
		else if(station.getQuantity() == 0 && !isItemFilled(station.getItemName()))
		{
			for (size_t i = 0; i < m_cntItem; i++)
			{
				if (m_lstitem[i]->m_itemName == station.getItemName())
				{
					os << setw(19) << right << "Unable to fill " << left << m_name << ", " << m_product << " [" << m_lstitem[i]->m_itemName << "]\n";
				}
			}
		}

	}
	
	void CustomerOrder::display(std::ostream& os)const
	{
		os << m_name << " - " << m_product << endl;
		for (size_t i = 0; i < m_cntItem; i++)
		{
			os << "[" << setw(6) << setfill('0') << right <<m_lstitem[i]->m_serialNumber << setfill(' ') << "] " << setw(m_widthField) << left << m_lstitem[i]->m_itemName << " - ";
			if (!m_lstitem[i]->m_isFilled)
				os << "TO BE FILLED\n";
			else
				os << "FILLED\n";
		}
	}

	CustomerOrder::~CustomerOrder()
	{
		for (size_t i = 0; i < m_cntItem; i++)
			delete m_lstitem[i];
		delete[] m_lstitem;
		m_lstitem = nullptr;
	}

}