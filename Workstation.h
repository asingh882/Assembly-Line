// Name: Amritpal Singh
// Seneca Student ID: 150143196
// Seneca email: asingh882@myseneca.ca
// Date of completion: 31 July, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#pragma once
#include <deque>
#include <iostream>
#include "CustomerOrder.h"
#include "Station.h"

namespace sdds {

	extern std::deque<CustomerOrder> pending;
	extern std::deque<CustomerOrder> completed;
	extern std::deque<CustomerOrder> incomplete;

	class Workstation : public Station
	{
		std::deque<CustomerOrder> m_orders{};
		Workstation* m_pNextStation{};
	public:
		Workstation(const std::string& record);

		Workstation(Workstation& station) = delete;
		Workstation(Workstation&& station) = delete;

		Workstation& operator=(Workstation& station) = delete;
		Workstation& operator=(Workstation&& station) = delete;

		void fill(std::ostream& os);
		bool attemptToMoveOrder();


		void setNextStation(Workstation* station = nullptr);
		Workstation* getNextStation()const;

		void display(std::ostream& os)const;

		Workstation& operator+=(CustomerOrder&& newOrder);

	};

}

