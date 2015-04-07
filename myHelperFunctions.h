#pragma


//more the value of this=> lesser will be the crashes, great time ave at takeoff, and lesser at landing
const int LOW_FUEL_LIMIT = 2;

int IsEmergencyLanding(MinPeriorityQueue <Plane> patterns[], int time)
{
	for (int i = 0; i < 4; i++)//THERE ARE TOTAL FOUR QUEUE TO CHECK FOR THAT PLANE
	{
		if (patterns[i].isEmpty() == false)
		{
			int diff = (patterns[i].top()).getSecondTime() - time;
			if (diff < LOW_FUEL_LIMIT)//means only last time unit has left of his life (:D)
				return i;
		}
	}
	return -1;//-1 => no emergency landing
}

int WhichHasLeastSizeREV(QueueSLL <Plane> *list, const int & _size)
{
	int minIndex = 2; //we prefer to take off at runway three (special devoted for take off)
	for (int i = _size - 1; i >= 0; --i)
	{
		int t = list[i].size();
		if (t < list[minIndex].size())
		{
			minIndex = i;
		}
	}
	return minIndex;
}

int WhichHasLeastSize(MinPeriorityQueue <Plane> *list, const int & _size)
{
	int minIndex = 0;
	for (int i = 0; i < _size; i++)//we know there are 4 patterns (constants)
	{
		int t = list[i].size();
		if (t < list[minIndex].size())
			minIndex = i;
	}
	return minIndex;
}

int WhichHasMaxSize(MinPeriorityQueue <Plane> list[], const int & _size)
{
	int max = 0;
	for (int i = 0; i < _size; i++)//we know there are 4 patterns (constants)
	{
		int t = list[i].size();
		if (t > list[max].size())
			max = i;
	}
	return max;
}

void SaveAirportState(ofstream & OutputFile, MinPeriorityQueue<Plane>HoldingPatterns[], QueueSLL<Plane> takeOffQueue[])
{
	OutputFile << "Sizes of H_Pattern(respectively) [";
	for (int j = 0; j < 4; j++)
		OutputFile << HoldingPatterns[j].size() << " ";
	OutputFile << "] & ";
	OutputFile << "Top elements of H_Pattern: {";
	for (int j = 0; j < 4; j++){
		if (!HoldingPatterns[j].isEmpty())
			(HoldingPatterns[j].top()).printToFile(OutputFile);
		else OutputFile << "  EMPTY   ";
	}
	OutputFile<<"}" << endl;
	OutputFile << "Sizes of Take off queues (respectively) [";
	for (int j = 0; j < 3; j++)
		OutputFile << takeOffQueue[j].size() << " ";
	OutputFile << "] & ";
	OutputFile << "Top elements of take off queue: {";
	for (int j = 0; j < 3; j++){
		if (!takeOffQueue[j].isEmpty())
			(takeOffQueue[j].top()).printToFile(OutputFile);
		else OutputFile << "  EMPTY   ";
	}
	OutputFile << "}" << endl;
}

