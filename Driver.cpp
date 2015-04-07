#include <iostream>
#include <fstream>
#include <random>
#include "Myqueues.h"
#include "RunWayData.h"
#include "Plane.h"
#include "QueueSLL.h"
#include "myHelperFunctions.h"
using namespace std;


/*
I Have defined all my helping function in myHelperFunctions.h
*/

int main()
{
	//we can take input from user for file name but i have used default here  just for ease in testing
	ofstream OutputFile("plane_data.txt");
	if (!OutputFile.is_open())
	{
		cout << "file not opened\n";
		return -1;
	}
	//random number generator using c++11 standards
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(0, 100);

	MinPeriorityQueue <Plane> HoldingPatterns[4];
	//i could have used Periority Queue for takeoff as well 
	//but i did't becoz simple queue does work in constant time (nodes)
	//and we dont need any special periority as well as in case of landing 
	QueueSLL <Plane> takeOffQueue[3];

	int simulationTime = 200;
	cout << "How Many Time Unit You Want to Simulate: ";
	cin >> simulationTime;

	int landingRandomInput = 0, takeoffRandomInput=0;
	int oddID = 1,evenID=0;
	int minSizeQueue = 0;
	int noOfPlaneCrashed = 0, noOfPlaneServed = 0, noOfPlaneLanded = 0, noOfPlaneFlown=0;
	double totalTakeOffWaitTime = 0, totalLandingWaitTime=0;
	int aveFlyRemLan = 0, noFuelLandings=0;
	for (int time = 1; time  <= simulationTime; time++)
	{
		OutputFile << "AT TIME: " << time << endl;
		landingRandomInput = dist(mt) % 4;//RANDOM NUMBER FROM 0-3
		//0=> NO LANDING & 1=> 1 PLAN HAS CAME TO LANS & 2=>2 PANE HAS HAME TO LANS & 3=>3 PLANE CAME TO LAND
		//NOW WE HAVE TO FIND QUEUE PATTERN WITH MIN SIZE
		OutputFile << "At landing queue: " << landingRandomInput<<" => { ";
		for (int  k = 0; k < landingRandomInput; k++)//INSERT NO OF PLANES ACCORDING TO RANDOM INPUT
		{
			noOfPlaneLanded++;
			int randomFuel = 1+dist(mt)%15 + time;//SO MAX FUEL IS 15 , AND A PLANE SHOULD HAVE AT LEAST ONE UNIT_TIME FUEL
			Plane newPlane(oddID,time,randomFuel);
			OutputFile << " (id=" << oddID << ") ";
			oddID += 2;
			minSizeQueue = WhichHasLeastSize(HoldingPatterns,4);//FUNCTION TELL US QUQUE INDEX WITH MIN PLANES
			HoldingPatterns[minSizeQueue].insert(newPlane);
		}OutputFile << " }\n";
		//LANDING WORK IS DONE HERE

		takeoffRandomInput = dist(mt)%4;//RANDOM NUMBER FROM 0-3
		OutputFile << "At TakeOff queue: " << takeoffRandomInput <<" => { ";
		//0=> NO TAKEOFF & 1=> 1 PLAN HAS CAME TO TAKEOFF & 2=>2 PANE HAS HAME TO TAKEOFF & 3=>3 PLANE CAME TO TAKEOFF
		//NOW WE HAVE TO FIND QUEUE PATTERN WITH MIN SIZE
		for (int j = 0; j < takeoffRandomInput; j++)//INSERT NO OF PLANCE ACCORDING TO RANDOM INPUT
		{
			noOfPlaneFlown++;
			//THOUGH THERE IS NO PROBLEM OF CRASHING AT TAKEOFF DUE TO NO FUEL...and i can ASSUME PALANE ARE FULL FUEL BEFORE TAKEOFF but i choosed random
			Plane newPlane(evenID, time, time + (1 + (dist(mt) % 15)));//(1 + (dist(mt) % 15)) =1-15 range 
			OutputFile << " (id=" << evenID << ") ";
			evenID += 2;
			minSizeQueue = WhichHasLeastSizeREV(takeOffQueue, 3);//RETURN QUQUE INDEX WITH MIN PLANES(iterate rever direction)
			takeOffQueue[minSizeQueue].Enqueue(newPlane);
		}OutputFile << " }\n";
		//TAKEOFF INPUT AND INSERTION IS DONE HERE

		SaveAirportState(OutputFile, HoldingPatterns, takeOffQueue);
		
		//NOW ITS THE TIME TO DECIDE THAT WHO IS GONNA LAND AND WHO WILL TAKE OFF :d SO THERE WE ARE
		//LANDGING PLANES HAVE HIGH PERIORITY SO FIRST CHECK THE LANDING QUEUES
		/*
		IS THERE ANY EMERGENCY LANDINGIN ANY QUEUE 
			IS SO THEN RESERVE RUNWAY 3 FOR THAT
		CHECK IS THERE ANY OTHER EMERGENCY LANDING
			IS SO RESERVE RUNWAY 2 FOR IT AND AGAIN CHECK FOR NEXT CASE
		NOTE: AT ONE TIME WE CAN SAVE AT MAX 3 PALNCE FROM CRASHING
		*/

		RunWayData RunwayArr[3];
		//CHECK FOR EMERGENCY LANDING 
		for (int i = 0; i < 3; ++i)
		{
			int emergencyPlaneQueueIndex = IsEmergencyLanding(HoldingPatterns,time);
			if (emergencyPlaneQueueIndex != -1)
			{
				if (!HoldingPatterns[emergencyPlaneQueueIndex].isEmpty())
				{
					RunwayArr[2 - i].setAssignData(HoldingPatterns[emergencyPlaneQueueIndex].top(), true);
					HoldingPatterns[emergencyPlaneQueueIndex].Delete();
				}
				else break;
			}
			else break;
		}
		//NOW IF ALL RUNWAYS ARE RESERVED BYE EMERGENCY LANDIGN THEN LETS EXECUTE ELSE CHECK FOR OTHER PLANES 
		/*
			FIRST OF ALL CHECK THAT EITHER R3 HAS RESERVED 
			IF NO THEN USE IT FOR TAKE OFF
		*/
		if (!RunwayArr[2].isReserved())
		{
			if (!takeOffQueue[2].isEmpty()) //NEGATIVE FUEL => PLANE IS LATE 
			{
				RunwayArr[2].setAssignData(takeOffQueue[2].top(), false);
				takeOffQueue[2].Dequeue();
			}
		}
		//AT THHIS POINT IS IF RUNWAY 3 IS STILL FREE => THERE IS NO PLANE TO TAKE OFF LAND AT THIS TIME UNIT
		if (!RunwayArr[1].isReserved())//IF RUNWAY 2 IS STILL IDLE
		{
			int HP3Size = HoldingPatterns[2].size(), HP4Size = HoldingPatterns[3].size();
			if ((takeOffQueue[1].size() > (HP3Size + HP4Size)) && !takeOffQueue[1].isEmpty())
			{
				RunwayArr[1].setAssignData(takeOffQueue[1].top(), false);
				takeOffQueue[1].Dequeue();
			}
			else
			{
				//LAND A PLANE FROM EITHER PATTERN 3,4 (WHICH HAS MORE SIZE i.e MORE PLANE)

				if (HP3Size + HP4Size>0)//IF BOTH ARE EMPTY NOTHING TO LAND
				{
					if (HP3Size > HP4Size)
					{
						RunwayArr[1].setAssignData(HoldingPatterns[2].top(), true);
						HoldingPatterns[2].Delete();
					}
					else
					{
						RunwayArr[1].setAssignData(HoldingPatterns[3].top(), true);
						HoldingPatterns[3].Delete();
					}
				}
			}
		}

		if (!RunwayArr[0].isReserved())//IF RUNWAY 2 IS STILL IDLE
		{
			int HP1Size = HoldingPatterns[0].size(), HP2Size = HoldingPatterns[1].size();
			if ((takeOffQueue[0].size() > (HP1Size + HP2Size)) && !takeOffQueue[0].isEmpty())
			{
				RunwayArr[0].setAssignData(takeOffQueue[0].top(), false);
				takeOffQueue[0].Dequeue();
			}
			else if (HP1Size + HP2Size >0)//IF BOTH ARE EMPTY NOTHING TO LAND
			{
				if (HP1Size > HP2Size)
				{
					RunwayArr[0].setAssignData(HoldingPatterns[0].top(), true);
					HoldingPatterns[0].Delete();
				}
				else
				{
					RunwayArr[0].setAssignData(HoldingPatterns[1].top(), true);
					HoldingPatterns[1].Delete();
				}
			}
		}
		OutputFile << "Services: [ ";
		//EXECUATION STARTS HERE
		for each (auto runway in RunwayArr)
		{
			if (runway.isReserved())
			{
				if (runway.IsLanding())
				{
					if ((runway.getAssignedPlane().getSecondTime()) < time)//plane crashed
					{
						cout << "Plane Crashed\n";
						++noOfPlaneCrashed;
					}else{
						//landed normally
						aveFlyRemLan += runway.getAssignedPlane().getSecondTime() - time;
						totalLandingWaitTime += time - runway.getAssignedPlane().getFirstTime();
					}

					if (time == runway.getAssignedPlane().getSecondTime())//last unit time landing
					{
						cout << "Last second landing: " << runway.getAssignedPlane().getSecondTime() << " " << time << endl;
						noFuelLandings++;
					}
				}
				else{ 
					//PLANE IS TAKING OFF
					totalTakeOffWaitTime += time - runway.getAssignedPlane().getFirstTime();
				}
			}
			runway.ExecuteProcess(OutputFile);
		}
		OutputFile << " ]\n";

		//you can print it in each time unit in case you want to test
//		OutputFile << "Plane Crashed: " << noOfPlaneCrashed << endl;
//		OutputFile << "Plane Served (crashes excluded): " << noOfPlaneLanded + noOfPlaneFlown << endl;
//		OutputFile << "Average Landing Waiting Time:" << (totalLandingWaitTime / noOfPlaneLanded) << endl;
//		OutputFile << "Average TakeOff Waiting Time:" << (totalTakeOffWaitTime / noOfPlaneFlown) << endl;
//		OutputFile << "Average Flying Time Remaining on Landing: " << (aveFlyRemLan / noOfPlaneLanded) << endl;
//		OutputFile << "Plane Landed With no Fuel Reserve: " << noFuelLandings << endl;





		//you can print the state of air port after operations
		//but i have commented because then data is cluttered in file

		//SaveAirportState(OutputFile, HoldingPatterns,takeOffQueue);

		OutputFile << endl<<endl;
	}
	OutputFile << "\n\n\n\n";
	OutputFile <<  "Plane Crashed: " << noOfPlaneCrashed<<endl;
	OutputFile <<  "Plane Served (crashes excluded): " << noOfPlaneLanded+noOfPlaneFlown << endl;
	OutputFile << "Average Landing Waiting Time:" << (totalLandingWaitTime / noOfPlaneLanded)<<endl;
	OutputFile << "Average TakeOff Waiting Time:" << (totalTakeOffWaitTime / noOfPlaneFlown)<<endl;
	OutputFile << "Average Flying Time Remaining on Landing: " << (aveFlyRemLan / noOfPlaneLanded)<<endl;
	OutputFile << "Plane Landed With no Fuel Reserve: " << noFuelLandings << endl;
	OutputFile << "\n\n\n\n";
	OutputFile.close(); //CLOSING THE FILE

	/*
	OutputFile << "Total Landing Waiting Time: " << totalLandingWaitTime << endl;
	OutputFile << "Total Taken off Time: " << totalTakeOffWaitTime << endl;

	*/
	return 0;
}

