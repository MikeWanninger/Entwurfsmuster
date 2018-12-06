#ifndef MAP_H
#define MAP_H
#include "Tree.h"
 
template<class Key,class Value, class Order = DefaultOrder>
class Map
{
public:
    //MapNode ist der Node aus Tree
	typedef MapNode<Key,Value> Node;
    
	//Fügt den Key im Node als First ein und setzt den Wert als Second
	void insert(Key key, Value value){
		Node* node = m_tree.insert(key, false);
		node->second = value;
	}
	
	bool empty(){
		return m_tree.empty();
	}
	
	
	//Sucht den Key im Baum und gibt den Wert zurück
	Value* get(const Key key){
		Node* node = m_tree.get(key);
		if(node == 0){
			return 0;
		}else{
			return &(node->second); 
		}
	}
    
    //Gibt wie bei der get Methode statt der Value den Node zurück
    Node* getNode(Key key){
        Node* node = m_tree.get(key);
		if(node == 0){
			return 0;
		}else{
			return node; 
		}
    }

    //Entfernt ein Element aus dem Tree
	void remove(Node* node){
		m_tree.remove(node);
	}
       
    class Iterator{
    public:
        Iterator(typename Tree<Key, Node, Order>::Iterator iter) : _iter(iter){

        }
        
        friend bool operator!=(const Iterator& iter1, const Iterator& iter2){
			return iter1._iter != iter2._iter;
        }
        
        Node& operator*(){
			return *_iter;
        }
		
		Node* operator->() {
			Node* node = &(*_iter);
            return node;
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
	
    
    Iterator find(const Node& rA){
        return Iterator(m_tree.find(rA));
    }
    
private:
	Tree<Key, Node, Order> m_tree;
};

#endif // MAP_H
