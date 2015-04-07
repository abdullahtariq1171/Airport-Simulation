#pragma
#include "SinglyLinkedList.h"

template <typename Type>
class QueueSLL
{
	SinglyLinkedList <Type> List;
public:
	int queue_size;
public:
	QueueSLL() :queue_size(0){}
	~QueueSLL(){}
	QueueSLL(const QueueSLL<Type> & obj) :List(obj.List), queue_size(0){}
	QueueSLL <Type> operator=(QueueSLL <Type> & RHS){ List = RHS.List; }

	void Enqueue(const Type &item){
		List.InsertAtEnd(item);
		queue_size++;
	}
	Type Dequeue()
	{
//		if (List.IsEmpty())
		
		bool IsValid = true;
		Type a=List.Peak(IsValid);
		if (IsValid == true)
		{
			List.DeleteAtStart();
			queue_size--; 
		}
		return a;
	}
	Type Peak(bool &IsValid){return List.Peak(IsValid);}
	bool isEmpty(){ return List.IsEmpty(); }
	void Clear(){ List.Clear(); }
	void Print(){ List.Print(); }
	bool Search(Type & item){ return List.Search(item);}
	Type  top()
	{
		bool flag=true;
		return List.Peak(flag);
	}
	int size(){ return queue_size; }


};

