#pragma once
#include <iostream>
#include <iomanip>
using namespace std;


class Plane
{
	int id;
	int deadLineTime;//unit time (or fuel)
	int entryTime;

public:
	Plane() :id(-2), deadLineTime(-1),entryTime(-1){} //-1=> no data is assigned yet
	Plane(int _id, int _entrytime, int _dealLineTime) :id(_id), deadLineTime(_dealLineTime), entryTime(_entrytime){}
	int getId(){ return this->id;}


	void setId(int _id){ this->id=_id; }
	void setFuel(int a){  deadLineTime=a; }

	// > , < BEHAVIOUR OF THIS FUNCTION DEPENDS ON OUR NEED
	bool operator>(const Plane & RHS)
	{
		if (this->deadLineTime > RHS.deadLineTime)
			return true;
		return false;
	}

	void Print()
	{
		cout << "ID: " << id;
		cout << " & Entry: " << entryTime<< endl;
		cout << " & Dead line : " << deadLineTime << endl;
	}


	int getSecondTime()
	{
		return deadLineTime;
	}
	int getFirstTime()
	{
		return entryTime;
	}

	void printToFile(ofstream & out)
	{
		out << " (id="  << id;
	//	out	<< "," << std::setw(3) << (deadLineTime) ;
		out<< ")";
	}

	friend bool operator>(const Plane & LHS, const Plane & RHS);
	void operator=(const Plane RHS)
	{
		this->id = RHS.id;
		this->deadLineTime = RHS.deadLineTime;
		this->entryTime  = RHS.entryTime;
	}
	bool operator<=(const Plane RHS)
	{
		if (this->id == RHS.id && this->deadLineTime == RHS.deadLineTime && this->entryTime == RHS.entryTime)
			return true;
		else if (this->deadLineTime < RHS.deadLineTime)
			return true;
		
		return false;
	}

	friend ostream& operator<<(ostream& os, const Plane& dt);
	~Plane()
	{	
		//NOTHING TO DELET 
	}
};


ostream& operator<<(ostream& os, const Plane& dt)
{
	cout << " (" << dt.id << "," << dt.deadLineTime << ") ";
	return os;
}

bool operator>(const Plane & LHS, const Plane & RHS)
{
	if (LHS.deadLineTime > RHS.deadLineTime)
		return true;
	return false;
}



