#pragma 

template <typename Type>
class SinglyLinkedList
{
	struct Node
	{
		Node::Node(Type _value) :value(_value),Next(nullptr){}
		Type value;
		Node *Next;
	};
	Node *Start;
	Node* FindPreviousNode(const Type & key)
	{
		Node *temp = Start;
		Node *pre = Start;
		while (temp != nullptr && temp->value<key)
		{
			pre = temp;
			temp = temp->Next;
		}
		return pre;
	}
	Node* FindPreviousOfMatchedNode(const Type & item)
	{
		Node *handle = Start;
		Node *pre=nullptr;
		while (handle!=nullptr)
		{
			if (handle->value == item)
				return pre;
			pre = handle;
			handle = handle->Next;
		}
		return nullptr;
	}
public:
	SinglyLinkedList(void);
	SinglyLinkedList(const SinglyLinkedList <Type> & obj);
	~SinglyLinkedList();

	SinglyLinkedList<Type>& operator=(const SinglyLinkedList<Type> & obj);

	void InsertAtStart(const Type&item);
	void InsertAtEnd(const Type&item);
	void Clear();
	bool DeleteAtStart();
	bool DeleteAtEnd();
	void Insert(const Type & item);
	Type Peak(bool & IsValid)const;
	void Print();
	bool Delete(const Type & item);
	bool Search(const Type & item);
	bool IsEmpty();
};

template <typename Type>
SinglyLinkedList<Type>::SinglyLinkedList(): Start(nullptr){}

template <typename Type>
SinglyLinkedList<Type>::SinglyLinkedList(const SinglyLinkedList <Type> & obj)
{
	if (obj.Start == nullptr)
	{
		this->Start = nullptr;
		return;
	}
	Start = new Node(obj.Start->value);
	Node *handle2 = obj.Start->Next;
	Node *handle1 = Start;
	while (handle2 != nullptr)//until obj have data node
	{
		handle1->Next = new Node(handle2->value);
	//	handle1->Next->Previous = handle1;
		handle2 = handle2->Next;
		handle1 = handle1->Next;
	}
	return;
}

template <typename Type>
SinglyLinkedList<Type>::~SinglyLinkedList()
{
//	cout << "~SinglyLinkedList()\n";
	Node *handle = Start;
	while (handle)
	{
		Node *temp = handle->Next;
		delete handle;
		handle = temp;
	}
	Start = nullptr;
}

template <typename Type>
SinglyLinkedList<Type>& SinglyLinkedList<Type> ::operator=(const SinglyLinkedList<Type> & obj)
{
	if (this != &obj)//obj already same check
	{
		if (obj.Start == nullptr){
			this->Start = nullptr;
			return (*this);
		}
		this->Clear();
		Start = new Node(obj.Start->value);
		Node *handle2 = obj.Start->Next;
		Node *handle1 = Start;

		while (handle2 != nullptr)//until obj have data node
		{
			handle1->Next = new Node(handle2->value);
//			handle1->Next->Previous = handle1;
			handle2 = handle2->Next;
			handle1 = handle1->Next;
		}
	}
	return (*this);
}

template <typename Type>
void SinglyLinkedList<Type>::InsertAtStart(const Type&item)
{
	Node *newNode = new Node(item);
	newNode->Next = Start;
	Start = newNode;
}

template <typename Type>
void SinglyLinkedList<Type>::InsertAtEnd(const Type&item)
{
	//note we can have a endNode Pointer in List class but i am doing this 
	//without that option
	//have to ask teacher about this option
	//but for now its in this way
	if (Start == nullptr)
	{
		Start = new Node(item);
		return;
	}
	Node *handle = Start;
	while (handle->Next != nullptr)
		handle = handle->Next;

	//handle cantain the last data node
	Node *newNode = new Node(item);
	//newNode->Next is automatically nullptr here
	handle->Next = newNode;
}

template <typename Type>
void SinglyLinkedList<Type>::Clear()
{
	Node *handle = Start;
	while (handle != nullptr)
	{
		Node *temp = handle->Next;
		delete handle;
		handle = temp;
	}
	//	handle = nullptr;
	Start = nullptr;
	return;
}

template <typename Type>
bool SinglyLinkedList<Type>::IsEmpty()
{
	if (Start)
		return false;
	return true;
}

template <typename Type>
bool SinglyLinkedList<Type>::Search(const Type & item)
{
	if (Start == nullptr)
		return false;
	if (item == Start->value)
		return true;
	Node *handle = SinglyLinkedList::FindPreviousOfMatchedNode(item);
	if (handle!=nullptr)
		return true;
	//else handle==nullptr=> no match found
	return false;
}

template <typename Type>
bool SinglyLinkedList<Type>::Delete(const Type & item)
{
	//done
	//check for empty list here 
	if (Start == nullptr)
		return false;
	else if (item==Start->value)
	{
		Node *Next = Start->Next;
		delete Start;
		Start = Next;
	}
	Node *handle = FindPreviousOfMatchedNode(item);
	if (handle == nullptr)//no match flund so no deletion occured
		return false;
	else{
		Node *Next = handle -> Next;
		Node *Next_Next = Next->Next;
		delete Next;
		handle->Next = Next_Next;
	}
	return true;
}

template <typename Type>
void SinglyLinkedList<Type>::Print()
{
	cout << "Element Are: \n";
	Node * handle = Start;
	while (handle)
	{
		cout << handle->value << "\n";
		handle = handle->Next;
	}
}

template <typename Type>
void SinglyLinkedList<Type>::Insert(const Type & item)
{
	if (Start != nullptr && Start->value > item)//agr element start pa insert hona ho to.
	{
		Node *newNode = new Node(item);
		newNode->Next = Start;
		Start = newNode;
		return;
	}
	Node *handle = SinglyLinkedList::FindPreviousNode(item);
	if (handle)
	{
		Node *newNode = new Node(item);
		Node* Next = handle->Next;
		handle->Next = newNode;
		newNode->Next = Next;
	}
	else//list empty i.e Find fun return nullptr
	{
		Start = new Node(item);
		Start->Next = nullptr;
	}
}

template <typename Type>
bool SinglyLinkedList<Type>::DeleteAtStart()
{
	//return bool tels that eiterh element hase deleter or list is empty
	if (Start)
	{
		Node *temp = Start->Next;
		delete Start;
		Start = temp;
		return true;
	}
	return false;
}

template <typename Type>
bool SinglyLinkedList<Type>::DeleteAtEnd()
{	
	if (Start == nullptr)
		return false;
	Node *handle = Start;
	Node *pre = nullptr;
	while (handle->Next != nullptr)
	{
		pre = handle;
		handle = handle->Next;
	}
	//pre cantain the previous of last data node
	if (pre == nullptr)//only one data node is left in list *check
	{
		delete Start;
		Start = nullptr;
		return true;
	}
	Node *t = pre->Next;
	delete t;
	pre->Next = nullptr;
	return true;
}

template <typename Type>
Type SinglyLinkedList<Type>::Peak(bool & IsValid)const
{

	//note its responsibility of user of this liberary to call the IsEmpty() to check eiterh list is empty or not
	Type ans;
	if (Start != nullptr)
	{
		IsValid = true;
		ans=Start->value;
	}else IsValid = false;
	return ans;
}

