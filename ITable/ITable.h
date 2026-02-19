#pragma once
#include <iostream>
template<typename Tkey, typename Tval>
class ITable {

public:
	virtual void insert(const Tkey& key, const Tval& val) = 0;
	virtual Tval find(const Tkey& key ) const = 0;
	virtual void erase(const Tkey& key) = 0;
	virtual std::ostream& print(std::ostream& out) const noexcept = 0;
	virtual bool is_empty() const noexcept = 0;
	virtual bool consist(const Tkey& key) const noexcept = 0;
	virtual int size(const Tkey& key) const noexcept = 0;
	virtual void replace(const Tkey& ket, const Tval& val) = 0;
	~ITable(){}
};