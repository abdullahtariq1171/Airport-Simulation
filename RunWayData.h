#pragma

#include <iostream>
using namespace std;

#include "Plane.h"

class RunWayData
{
	Plane assignedPlance;
	bool isLanding;//WHETHER PALNE GOING TO LAND OR TAKE OFF
	bool IsReserved;
public:
	RunWayData():isLanding(false),IsReserved(false){}
	RunWayData(const Plane&_plane, bool _islanding) :assignedPlance(_plane), isLanding(_islanding), IsReserved(true){}
	void setAssignData(Plane _p, bool status){ assignedPlance = _p, isLanding = status, IsReserved = true; }
	bool IsLanding(){ return isLanding; }
	bool isReserved(){ return IsReserved; }
	void ExecuteProcess(ofstream & out)
	{
		if (IsReserved)
		{
			if (isLanding)
				out << "LN:(";
			else out << "TO:(";
			out <<"ID=" <<assignedPlance.getId();
//			out<<"," << assignedPlance.getSecondTime();
			out << ") ";
			IsReserved = false;
		}
		else out << "  IDLE  ";
	}
	Plane getAssignedPlane(){ return assignedPlance; }
};

