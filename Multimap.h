#ifndef MULTIMAP_H
#define MULTIMAP_H
#include "Set.h"
#include "Map.h"
#include <iostream>
#include "Queue.h"


template<class Key, class Value, class Order = DefaultOrder>
class Multimap
{
private:
	
public:
	typedef Set<Value, Order> _Set;
	typedef Map<Key,_Set, Order> _Map;
	
    //Fügt Value ins Set ein und fügt das Set mit dem Key in die Multimap
	void insert(Key key, Value value){
		_Set* set = m_tree.get(key);
		if(set == 0){
			m_tree.insert(key, _Set());
			set = m_tree.get(key);
		}
		set->insert(value);
	}
	
	//Struct, der den Key und Value entgegen nimmt und welches der Iterator zurückgibt
	struct IterObj{
		IterObj(Key& key, Value& value):first(key),second(value){}
			
		Key &first;
		Value &second;
	};
	
	class Iterator{
    public:
		//Constructor für den End() Iterator
        Iterator(){}
		
		//Constructor für einen vollständigen Iterator
		Iterator(_Map& map){
			for(typename _Map::Iterator i = map.begin(); i != map.end(); ++i){
				mapQueue.push(i.get());
			}
			fillSetQueue();
        }
		
		//Constructor für einen Iterator, der nur einen bestimmten Key benötigt
		Iterator(MapNode<Key,_Set>* entry){
			
			mapQueue.push(entry);
			fillSetQueue();
		}
        
		//Füllt die SetQueue mit den Einträgen, welche im ersten Element der MapQueue liegen
		void fillSetQueue(){
			if(mapQueue.top() != 0){
				_Set* set = &mapQueue.top()->second;
				for(typename _Set::Iterator i = set->begin(); i != set->end(); ++i){
					setQueue.push(i.get());
				}			
			}
		}
		
		//Vergleicht 2 Iteratoren
        friend bool operator!=(const Iterator& iter1, const Iterator& iter2){
			return iter1.setQueue.top() != iter2.setQueue.top();
        }
        
        
        //Gibt das Objekt zurück, auf das der Iterator derzeit zeigt
        IterObj& operator*(){
			SetNode<Value>* value = setQueue.top();
			MapNode<Key,_Set>* key = mapQueue.top();
			IterObj* obj = new IterObj(key->first,value->first);
			return *obj;
        }
		
        //Tut das gleiche wie der * Operator
		IterObj* operator->() {
			SetNode<Value>* value = setQueue.top();
			MapNode<Key,_Set>* key = mapQueue.top();
			IterObj* obj = new IterObj(key->first,value->first);
			return obj;
        }
        
        //Erhöht den Iterator zum nächst größeren/kleineren Node
        Iterator operator++(){
			setQueue.pop();
			if(setQueue.empty()){
				mapQueue.pop();
				if(!mapQueue.empty())
					fillSetQueue();
			}
			return *this;
        }
		
		//Gibt den aktuellen MapNode zurück, auf den der Iterator zeigt
		MapNode<Key,_Set>* getMapNode(){
			return mapQueue.top();
		}
		
		//Gibt den aktuellen SetNode zurück, auf den der Iterator zeigt
		SetNode<Value>* getSetNode(){
			return setQueue.top();
		}
        
    private:
		Queue<MapNode<Key,_Set> > mapQueue;
		Queue<SetNode<Value> > setQueue;
    };
    
    
	Iterator begin(){
        return Iterator(m_tree);
    }
	
	Iterator end(){
        return Iterator();
    }

	//Gibt den Iterator für den gesuchten Key zurück
	Iterator find(Key key){
		MapNode<Key,_Set>* entry = m_tree.getNode(key);
		if(entry != 0){
			return Iterator(entry);
		}else{
			return Iterator();
		}
	}
	
    //Sucht den key und löscht den zugehörigen Node
    void remove(const Key& key){
        remove(find(key),end());
    }
    
	
	//Bekommt 2 Iteratoren übergeben und löscht alle Einträge, die Zwischen diesen
	//Iteratoren liegen
    void remove(Iterator iter1, Iterator iter2){
		
			while(iter1 != iter2 && iter1 != end()){
				MapNode<Key,_Set>* map = iter1.getMapNode();
				SetNode<Value>* set = iter1.getSetNode();
				++iter1;
				map->second.remove(set);
				if(map->second.empty()){
					m_tree.remove(map);
				}
			}
			
			if(iter1 != end()){
				MapNode<Key,_Set>* map = iter1.getMapNode();
				SetNode<Value>* set = iter1.getSetNode();
				++iter1;
				map->second.remove(set);
				if(map->second.empty()){
					m_tree.remove(map);
				}
			}
		
    }
    
private:
	_Map m_tree;
};

#endif // MULTIMAP_H
