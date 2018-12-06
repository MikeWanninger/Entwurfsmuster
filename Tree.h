#ifndef TREE_H
#define TREE_H
#include <iostream>
#include "Stack.h"



template<class Key, class Node, class Order>
class Tree
{
public:
	Tree():mHead(NULL){};
	~Tree(){

		if(mHead != NULL){
			destroy(mHead);
		}
	}
	
	//löscht alle Nodes
	void destroy(Node* node){
		if(node == NULL){
			return;
		}else{
			destroy(node->left);
			destroy(node->right);
			delete node;
		}
	}
	
    //gibt den eingefügten Node zurück
    //wird der Key nicht im Kopf gespeichert so wird die Hilfsmethode aufgerufen
	Node* insert(Key key, bool duplicate){
		if(mHead == NULL){
			Node* node = new Node(key);
			mHead = node;
			return node;
		}else{
			return insert(key, mHead, duplicate);
		}
	}
    
    //sucht im Subtree den Platz zum einfügen, abhängig von der order
	Node* insert(Key key, Node* current, bool duplicate){
		if(!duplicate && current->first == key) {
			return current;
		} else if(order(key, current->first)) {
			if(current->left == NULL) {
				Node* node = new Node(key);
				current->left = node;
				return node;
			} else {
				return insert(key, current->left, duplicate);
			}
		} else {
			if(current->right == NULL) {
				Node* node = new Node(key);
				current->right = node;
				return node;
			} else {
				return insert(key, current->right, duplicate);
			}
		}
	}
	
    //gibt den Node im Tree zurück
	Node* get(Key key){
		if(mHead == 0){
			return 0;
		}else{
			return get(key, mHead);
		}
	}
    
    //gibt den Node im Subtree zurück
	Node* get(Key key, Node* current){
		if(current->first == key) {
			return current;
		} else if(order(key, current->first)) {
			if(current->left == NULL) {
				return NULL;
			} else {
				return get(key, current->left);
			}
		} else {
			if(current->right == NULL) {
				return 0;
			} else {
				return get(key, current->right);
			}
		}
	}
	
	bool empty(){
		return mHead == 0;
	}
    
   
    class Iterator{
    public:
    //zeigt nach der Initialisierung auf das kleinste/größte Element im Baum
        Iterator(Node *leaf) : _elem(leaf){
            while(leaf != 0){
                _elem = leaf;
                _stack.push(_elem);
                leaf = leaf->left;
            }
//            _stack.pop();
        }
        
        friend bool operator!=(const Iterator& iter1, const Iterator& iter2){
            return iter1._elem != iter2._elem;
        }
        
        //Gibt den Key des Iterators zurück
        Node& operator*(){
            return *_elem;
        }
		
		Node* operator->(){
            return _elem;
        }
		
		Node* get(){
			return _elem;
		}
        
        //ist der Stack leer wird ein leerer Iterator zurückgegeben
        //ansonsten wird aufsteigend durch den Baum gelaufen und der Iterator dazu zurückgegeben
        Iterator operator++(){
            if (_stack.empty()){
                _elem = NULL;
                return *this;
            }
			_stack.pop();
            
            if (NULL != _elem->right){
                Node *current = _elem->right;
                while (NULL != current){
                    _stack.push(current);
                    current = current->left;
                }
            }
			_elem = _stack.top();
            return *this;
        }
        
    private:
        Stack<Node> _stack;
        Node *_elem;
    };
    
   
    //gibt den Iterator mit dem ersten Node im Baum zurück
    Iterator begin(){
        return Iterator(mHead);
    }

    Iterator end(){
        return Iterator(NULL);
    }
    
    //sucht den übergebenen Node und gibt den Iterator mit dem Node zurück
    Iterator find(const Node& rA){
        typename Tree::Iterator iter1(mHead);
        typename Tree::Iterator iter2(NULL);
        for(; iter1!=iter2; ++iter1){
            if((*iter1).first == (rA).first){
                return iter1;
            }
        }
        return Iterator(NULL);
    }


    
private:
	Node* mHead;
	Order order;
    
public:
	bool remove(Node* node) {
		if(mHead == 0) {
			return false;
		}
		Node** ppCurrent = &mHead;
		while((*ppCurrent) != node) {
			if(order((*ppCurrent)->first, node->first)) {
				ppCurrent = &(*ppCurrent)->right;
			} else {
				ppCurrent = &(*ppCurrent)->left;
			}

			if(*ppCurrent == 0) {
				return false;
			}
		}
		return remove(ppCurrent);
	}
private:

    //sucht das zu löschenede Element und tauscht den Node mit dem größten Node im Subtree
    //gibt true/false zurück je nachdem ob das löschen funktioniert hat
	bool remove(Node** ppCurrent) {
		if((*ppCurrent)->left == 0 &&  (*ppCurrent)->right == 0) { // Blatt
			delete *ppCurrent;
			*ppCurrent = 0;
			return true;
		} else if((*ppCurrent)->left != 0 &&  (*ppCurrent)->right == 0) { //Linker Nachfolger
			Node* pChild = (*ppCurrent)->left;
			delete *ppCurrent;
			*ppCurrent = pChild;
			return true;
		} else if((*ppCurrent)->left == 0 &&  (*ppCurrent)->right != 0) { //Rechter Nachfolger
			Node* pChild = (*ppCurrent)->right;
			delete *ppCurrent;
			*ppCurrent = pChild;
			return true;
		} else if((*ppCurrent)->left != 0 &&  (*ppCurrent)->right != 0) { //Zwei Nachfolger
			Node** ppNextBigger = &(*ppCurrent)->right;
			while((*ppNextBigger)->left != 0) {
				ppNextBigger = &(*ppNextBigger)->left;
			}
			swap(ppCurrent,ppNextBigger);
			
			ppNextBigger = &(*ppCurrent)->right;
			while((*ppNextBigger)->left != 0) {
				ppNextBigger = &(*ppNextBigger)->left;
			}
			return remove(ppNextBigger);
		}
		return false;
	}
		
	//Tauscht 2 Knoten im Tree	
	void swap(Node** ppNode1, Node** ppNode2){
		Node* pNode1 = *ppNode1;
		Node* pNode2 = *ppNode2;
		
		Node* tmp = *ppNode1;
		*ppNode1 = *ppNode2;
		*ppNode2 = tmp;
		
		tmp = pNode1->left;
		pNode1->left = pNode2->left;
		pNode2->left = tmp;
		
		tmp = pNode1->right;
		pNode1->right = pNode2->right;
		pNode2->right = tmp;
	}
	
};



class DefaultOrder{
public:
	bool operator() (int i1,int i2) {
		return i1 < i2;
	}
};

//Node für die Map
template<class Key, class Value>
struct MapNode{
	MapNode(Key k):first(k),left(0),right(0){}
	Key first;
	Value second;
	MapNode<Key,Value>* left;
	MapNode<Key,Value>* right;
};

//Node für das Set
template<class Key>
struct SetNode{
	SetNode(Key k):first(k),second(first),left(0),right(0){}
	Key first;
	Key& second;
	SetNode<Key>* left;
	SetNode<Key>* right;
};
#endif // TREE_H
