// Name: Amritpal Singh
// Seneca Student ID: 150143196
// Seneca email: asingh882@myseneca.ca
// Date of completion: 31 July, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#pragma once
#include <vector>
#include <iostream>
#include "Workstation.h"

namespace sdds {
	class LineManager
	{
		std::vector<Workstation*> activeLine;
		size_t m_cntCustomerOrder{};
		Workstation* m_firstStation{};
	public:
		LineManager(const std::string& file, const std::vector<Workstation*>& stations);

		void linkStations();
		bool run(std::ostream& os);

		void display(std::ostream& os)const;
	};

}

