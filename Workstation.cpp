// Name: Amritpal Singh
// Seneca Student ID: 150143196
// Seneca email: asingh882@myseneca.ca
// Date of completion: 31 July, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#include "Workstation.h"
#include <iostream>
#include <string>

using namespace std;

namespace sdds {

	std::deque<CustomerOrder> pending{};
	std::deque<CustomerOrder> completed{};
	std::deque<CustomerOrder> incomplete{};

	Workstation::Workstation(const std::string& record) : Station(record){}

	void Workstation::fill(std::ostream& os)
	{
		if (m_orders.size() > 0)
		{
			m_orders.front().fillItem(*this, os);
		}
	}

	
	bool Workstation::attemptToMoveOrder()
	{
		bool yesNo = false;
		
		if (m_orders.empty())
		{
			yesNo = false;
		}
		else if (m_orders.front().isItemFilled(getItemName()))
		{
			if (m_pNextStation == nullptr)
			{
				completed.push_back(move(m_orders.front()));
			}
			else
				*m_pNextStation += move(m_orders.front());
			m_orders.pop_front();
			yesNo = true;
		}
		else 
		{
			if (getQuantity() == 0)
			{
				if (m_pNextStation == nullptr)
					incomplete.push_back(move(m_orders.front()));

				else
					*m_pNextStation += move(m_orders.front());
				m_orders.pop_front();
				yesNo = true;
			}
		}
		deque<CustomerOrder> temp = move(completed);
		int size = temp.size();
		for (int i = 0; i < size; i++)
		{
			if (temp.front().isFilled())
				completed.push_back(move(temp.front()));
			else
				incomplete.push_back(move(temp.front()));
			temp.pop_front();
		}
		return yesNo;
	}

	void Workstation::setNextStation(Workstation* station)
	{
		m_pNextStation = station;
	}

	Workstation* Workstation::getNextStation()const
	{
		return m_pNextStation;
	}

	void Workstation::display(std::ostream& os)const
	{
		if (m_pNextStation == nullptr)
			os << Station::getItemName() << " --> End of Line";
		else
			os << Station::getItemName() << " --> " << m_pNextStation->getItemName();
		os << endl;
	}


	Workstation& Workstation::operator+=(CustomerOrder&& newOrder)
	{
		m_orders.push_back(move(newOrder));
		return *this;
	}




}