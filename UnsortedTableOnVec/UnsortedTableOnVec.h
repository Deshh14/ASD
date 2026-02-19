#pragma once
#include "..\ITable\ITable.h"
#include "Tvector.h"
#include <iostream>
#include <utility>

template<typename Tkey, typename Tval>
class UnsortedTableOnVec : public ITable<Tkey, Tval> {
	Tvector<std::pair<Tkey, Tval>> _rows;
public:
	~UnsortedTableOnVec(){}
	UnsortedTableOnVec() {}
	Tval find(const Tkey& key) const override;
	void erase(const Tkey& key) override;
	std::ostream& print(std::ostream& out) const noexcept override;
	bool is_empty() const noexcept override;
	bool consist(const Tkey& key) const noexcept override;
	int size(const Tkey& key) const noexcept override;
	void replace(const Tkey& key, const Tval& val) override;
	void insert(Tvector<Tval>& arr, const Tval& val);
};

template<typename Tkey, typename Tval>
Tval UnsortedTableOnVec<Tkey, Tval>::find(const Tkey& key) const {

}


template<typename Tkey, typename Tval>
void UnsortedTableOnVec<Tkey, Tval>::erase(const Tkey& key) {

}



template<typename Tkey, typename Tval>
bool UnsortedTableOnVec<Tkey, Tval>::is_empty() const noexcept {

}

template<typename Tkey, typename Tval>
bool UnsortedTableOnVec<Tkey, Tval>::consist(const Tkey& key) const noexcept {

}

template<typename Tkey, typename Tval>
int UnsortedTableOnVec<Tkey, Tval>::size(const Tkey& key) const noexcept {

}

template<typename Tkey, typename Tval>
void UnsortedTableOnVec<Tkey, Tval>::replace(const Tkey& ket, const Tval& val) {

}

template<typename Tkey, typename Tval>
void insert(Tvector<Tval>& arr, const Tval& val);