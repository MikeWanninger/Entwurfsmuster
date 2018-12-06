#ifndef STACK_H
#define STACK_H
#include <iostream>

template<class T>
class Stack{

public:
    Stack& operator = (const Stack& other) {
		DEFAULT_CAPACITY = 10;
		size = other.size;
		maxSize = other.maxSize;
		
		elements = new T*[maxSize];
        for(int i=0; i<size;++i){
            elements[i] = other.elements[i];
        }	
		return *this;
	}
    Stack (const Stack& other) {
		DEFAULT_CAPACITY = 10;
		size = other.size;
		maxSize = other.maxSize;
		
		elements = new T*[maxSize];
        for(int i=0; i<size;++i){
            elements[i] = other.elements[i];
        }		
	}

    Stack():size(0),DEFAULT_CAPACITY(10),maxSize(DEFAULT_CAPACITY){
        elements = new T*[DEFAULT_CAPACITY];
    }

    ~Stack(){
        delete[] elements;
		elements = NULL;
    }
    
    //Überprüft ob der Stack voll ist. Wenn ja wird der Stack verdoppelt und
    //fügt das neue Element an der nächsten freien Position ein
    void push(T* elem){
        if(size == maxSize){
            ensureCapacity();
        }
        elements[size++] = elem;
    }
    
    //Löscht das neuste Element auf dem Stack und gibt dieses zurück.
    T* pop(){
        if(size > 0){
            T* e = elements[--size];
            elements[size] = 0;
            return e;
        }else
            return 0;
        
    }
    
    //Gibt das oberste Element auf dem Stack zurück
    T* top(){
		if(size == 0){
			return NULL;
		}else{
			return elements[size-1];
		}
    }
    
    bool empty(){
        return size == 0 ? true : false;
    }
    
    //Wird beim vergrößern des Stacks ausgerufen und kopiert die Elemente in das neue Array
    void ensureCapacity(){
        maxSize = maxSize*2;
        T** tmp = new T*[maxSize];
        for(int i=0; i<size;++i){
            tmp[i] = elements[i];
        }
        delete[] elements;
		elements = 0;
        elements = tmp;
    }
private:
    int size;
    int DEFAULT_CAPACITY;
	int maxSize;
    T** elements;
};

#endif // STACK_H
