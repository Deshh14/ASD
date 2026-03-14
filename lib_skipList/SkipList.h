#pragma once
#include <iostream>
#include "list.h"
#include <utility>

template<typename Tkey, typename Tval>
struct Node
{
	std::pair<Tkey, Tval> data;
	size_t levels;
	Node** next;
	Node(Tkey& key, Tval& val) : data(key,val), levels(0) {}
};

template<typename Tkey, typename Tval>
class SkipList {
private:
	List<Node*> heads;
	size_t lvl, max_lvl;
	size_t generate_level() {
		size_t lvl = 1;
		while (rand() % 100 < 50) {
			lvl++;
		}
		return lvl;
	}
public:
	SkipList();
	~SkipList(){}
	void insert(const Tkey& key,const Tval& val);
	void find(const Tkey& key, const Tval& val);
	bool is_empty() const;

};

template<typename Tkey,typename Tval>
SkipList<Tkey,Tval>::SkipList() : heads(nullptr), lvl(0), max_lvl(0) {}

template<typename Tkey, typename Tval>
bool SkipList<Tkey, Tval>::is_empty() const {
	if (heads.size == 0) { return true; }
	return false;
}


//template<typename Tkey, typename Tval>
//void SkipList<Tkey, Tval>::find(const Tkey& key, const Tval& val) {
//	Node* new_node = new Node(key, val);
//	List<Node**> path;
//	for (auto it = path.begin(); it != path.end(); ++it) {
//		new_node.next[i] = *it;
//		*it = new_node;
//	}
//}

template<typename Tkey, typename Tval>
void SkipList<Tkey, Tval>::insert(const Tkey& key,const Tval& val) {
	Node* new_node = new Node(key, val);
	if (is_empty()) {
		for (int i = 0; i < new_node.levels; ++i) {
			heads.push_front(new_node);
		}
	}
	else {
		Node* prev;
		for (int i = 0; i < min(new_node.levels, prev.levels); ++i) {
			prev.next[i] = new_node;
		}
	}
}