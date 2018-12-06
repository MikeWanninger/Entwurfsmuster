#ifndef SET_H
#define SET_H
#include "Tree.h"

template <class Key, class Order = DefaultOrder>
class Set
{
public:
    //SetNode ist der Node aus Tree.h
	typedef SetNode<Key> Node;
	
	//Fügt einen eintrag zum Set hinzu
	void insert(Key key){
		m_tree.insert(key, true);
	}
	
	//ISt das Set leer?
	bool empty(){
		return m_tree.empty();
	}
	
	
    class Iterator{
    public:
        Iterator(typename Tree<Key, Node, Order>::Iterator iter) : _iter(iter){

        }
        
        friend bool operator!=(const Iterator& iter1, const Iterator& iter2){
			return iter1._iter != iter2._iter;
        }
        
        Node& operator*(){
			return (*_iter);
        }
		
		Node* operator->() {
			
            return &(*_iter);
        }
        
        Iterator operator++(){
			++_iter;
			return *this;
        }
		
		Node* get(){
			return _iter.get();
		}
        
    private:
		typename Tree<Key, Node, Order>::Iterator _iter;
    };
    

	
	Iterator begin(){
        return Iterator(m_tree.begin());
    }
	
	Iterator end(){
        return Iterator(m_tree.end());
    }
	
	//Entfernt einen Node aus dem Set
	void remove(Node* node){
		m_tree.remove(node);
	}
	
private:
	Tree<Key, Node, Order> m_tree;
};

#endif // SET_H
