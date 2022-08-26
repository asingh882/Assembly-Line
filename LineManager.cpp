// Name: Amritpal Singh
// Seneca Student ID: 150143196
// Seneca email: asingh882@myseneca.ca
// Date of completion: 31 July, 2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <deque>
#include <algorithm>
#include <fstream>
#include <string>
#include "LineManager.h"
#include "Workstation.h"
#include "Utilities.h"

using namespace std;

namespace sdds {
	static size_t count = 0;

	LineManager::LineManager(const std::string& filename, const std::vector<Workstation*>& stations)
	{
		ifstream file(filename);
		Utilities util;
		bool yesNo;
		string temp;
		size_t position = 0;
		string temp2;
		if (!file)
		{
			throw "ERROR: Cannot open file";
		}
		while(!file.eof())
		{
			position = 0;
			getline(file, temp);

			temp2 = util.extractToken(temp, position, yesNo);
			auto station1 = find_if(stations.begin(), stations.end(), [temp2](Workstation* s) {
				return s->getItemName() == temp2;
			});
			if (yesNo)
				temp2 = util.extractToken(temp, position, yesNo);
			else
				temp2 = "nullptr";
			if (station1 != stations.end())
			{
				auto station2 = find_if(stations.begin(), stations.end(), [temp2](Workstation* s) {
					return 	s->getItemName() == temp2;
				});
				if (station2 != stations.end())
					(*station1)->setNextStation(*station2);
				else
					(*station1)->setNextStation(nullptr);
				activeLine.push_back(*station1);
			}
			

		}
		for (auto i = activeLine.begin(); i != activeLine.end(); i++)
		{
			int value = count_if(activeLine.begin(), activeLine.end(), [i](Workstation* s) {
				return 	s->getNextStation() == *i;
			});
			if (value == 0)
			{
				m_firstStation = *i;
				break;
			}
		}
		m_cntCustomerOrder = pending.size();
	}

	void LineManager::linkStations()
	{
		vector<Workstation*> temp;
		temp.push_back(m_firstStation);
		temp.push_back(m_firstStation->getNextStation());
		for_each(activeLine.begin(), activeLine.end() - 2, [&](Workstation* s) {
				temp.push_back(temp.back()->getNextStation());
		});
		activeLine = temp;
	}
	
	bool LineManager::run(std::ostream& os)
	{
		count++;
		os << "Line Manager Iteration: " << count << endl;
		if (pending.size() > 0)
		{
			(*m_firstStation) += move(pending.front());
			pending.pop_front();
		}
		
		for_each(activeLine.begin(), activeLine.end(), [&](Workstation* s) {
				s->fill(os);
			});
		
		for (auto i = activeLine.begin(); i != activeLine.end(); i++)
		{
				(*i)->attemptToMoveOrder();
		}

		if ((completed.size() + incomplete.size()) == m_cntCustomerOrder)
			return true;
		return false;
	}

	void LineManager::display(std::ostream& os)const
	{
		for (auto i = activeLine.begin(); i != activeLine.end(); i++)
			(*i)->display(os);
	}

}
