#pragma

template <typename Type>
class MinPeriorityQueue
{
	int noOfElement, capacity;
	Type *heapArr;
public:
	//this will mantain the size of heapArr
	void doubleSize()
	{
		Type *temp = heapArr;
		capacity = capacity* 2;
		heapArr = new Type[capacity];
		for (int i = 0; i < noOfElement+1; ++i)
			heapArr[i] = temp[i];
		delete []temp;
		temp = nullptr;
		return;
	}
	void HalfSize()
	{
		Type *temp = heapArr;
		capacity /= 2;
		heapArr = new Type[capacity];
		for (int i = 0; i < noOfElement+1; ++i)
			heapArr[i] = temp[i];
		delete[]temp;
		temp = nullptr;
	}
public:
	MinPeriorityQueue();
	MinPeriorityQueue(const MinPeriorityQueue<Type> & obj);
	MinPeriorityQueue<Type> operator=(const MinPeriorityQueue<Type> RHS);
	void insert(const Type & item);
	Type top()const;
	bool isEmpty()const;
	void Delete();
	int size();
	~MinPeriorityQueue();
	void PrintArray()
	{
		//fun just for debugging
		for (int i = 1; i < noOfElement; i++)
		{
			cout << heapArr[i] << " ";
		}
	}
};

template <typename Type>
MinPeriorityQueue<Type>::MinPeriorityQueue() :capacity(2), noOfElement(0), heapArr(new Type[2])
{}

template <typename Type>
MinPeriorityQueue<Type>::MinPeriorityQueue(const MinPeriorityQueue<Type> & obj) : capacity(obj.capacity), noOfElement(obj.noOfElement)
{
	for (int i = 0; i < noOfElement; i++)
		heapArr[i] = obj.heapArr[i];
}

template <typename Type>
MinPeriorityQueue<Type> MinPeriorityQueue<Type>::operator=(const MinPeriorityQueue<Type> RHS)
{	
	noOfElement = RHS.noOfElement;
	capacity = RHS.capacity;
	if (heapArr != nullptr)
		delete heapArr[];
	heapArr = new heapArr[capacity];
	for (int i = 0; i < noOfElement; i++)
		heapArr[i] = RHS.heapArr[i];

	return (*this);
}

template <typename Type>
void MinPeriorityQueue<Type>::insert(const Type & item)
{
	if (noOfElement+1 == capacity)
		doubleSize();
	noOfElement++;
	int i = noOfElement;
	while (true)
	{
//		if (i == 1)break;
		if (i==1 || item > heapArr[i/2]) 
			break;
		heapArr[i] = heapArr[i / 2];
		i /= 2;
	}
	heapArr[i] = item;
}

template <typename Type>
void MinPeriorityQueue<Type>::Delete()
{
	int i = 0, j = 0;
	if (noOfElement == 0)return ;
//	const Type & item = heapArr[1];//top
	Type k = heapArr[noOfElement--];
	for (i = 1, j = 2; j <= noOfElement;)
	{
		if (j <= noOfElement)
		{
			if (heapArr[i] > heapArr[i + 1]) j++;// < in case of max
			if (k <= heapArr[j])break;//we found place
			heapArr[i] = heapArr[j];
			i = j;
			j *= 2;
		}
	}
	heapArr[i] = k;
}

template <typename Type>
int MinPeriorityQueue<Type>::size()
{
	return noOfElement;
}

//ONE HAS TO CHECK FOR EMPTY QUEUE BEFORE USING TOP :D
template <typename Type>
Type MinPeriorityQueue<Type>::top()const
{
	return heapArr[1];
}

template <typename Type>
bool MinPeriorityQueue<Type>::isEmpty()const
{
	if (noOfElement == 0)
		return true;
	return false;
}

template <typename Type>
MinPeriorityQueue<Type>::~MinPeriorityQueue()
{
	delete []heapArr;
	heapArr = nullptr;
}





