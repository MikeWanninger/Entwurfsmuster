#ifndef QUEUE_H
#define QUEUE_H

template<class T>
class Queue{
public:
	Queue():head(0),tail(0)	{}
	~Queue(){
		while(!empty()){
			pop();
		}
	}
    //Fügt am Ende der Liste den Node ein
	void push(T* value){
		Node* node = new Node();
		node->value = value;
		if(tail == 0){
			head = node;
			tail = node;
		}else{
			tail->next = node;
			tail = node;
		}
	}
    
    //Gibt das erste Objekt der Liste zurück und löscht dieses
	T* pop(){
		if(head != 0){
			Node* node = head;
			T* value = node->value;
			if(node->next == 0){
				head = 0;
				tail = 0;
			}else{
				head = node->next;
			}
			return value;
		}else{
			return 0;
		}
		
	}
    
    //Gibt das erste Objekt der Liste zurück
	T* top(){
		if(head != 0){
			return head->value;
		}else{
			return 0;
		}
	}
	
	//Gibt das erste Objekt der Liste zurück
	T* top() const{
		if(head != 0){
			return head->value;
		}else{
			return 0;
		}
	}
	
	bool empty(){
		return head == 0 && tail == 0;
	}
private:
struct Node{
		Node* next;
		T* value;
	};
	Node* head;
	Node* tail;
};

#endif // QUEUE_H
