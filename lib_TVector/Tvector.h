#pragma once
#include <initializer_list>
#include <stdexcept>

template <typename T>
class Tvector {
private:
    T* _data;
    int _size;
    int _capacity;
    static const int STEP_OF_CAPACITY = 16;

public:
    Tvector();
    Tvector(size_t capacity);
    Tvector(const Tvector& other);
    Tvector(T* data, size_t size);
    Tvector(std::initializer_list<T> data);
    Tvector(const T* data, size_t size);
    ~Tvector();

    Tvector& operator=(const Tvector& other);

    inline T& operator[](int indx) noexcept;
    inline const T& operator[](int indx) const noexcept;

    inline T& front();
    inline const T& front() const; 
    inline T& back();
    inline const T& back() const;

    inline T* data() noexcept;
    inline const T* data() const noexcept; 
    inline int size() const noexcept;
    inline int capacity() const noexcept;

    bool empty() const;
    void resize(size_t size);
    void reserve(size_t new_capacity);
    void push_front(T val);
    void push_back(T val);
    void insert(int pos, T val);
    void insert(T* pos, T val);
    T pop_front();
    T pop_back();
    T erase(int pos);
    T erase(T* pos);
    size_t find(const T& val) const; 
    void clear();

private:
    void repacking(size_t new_capacity); 
};

template <typename T>
const int Tvector<T>::STEP_OF_CAPACITY;

template <typename T>
Tvector<T>::Tvector() : _data(nullptr), _size(0), _capacity(0) {}

template <typename T>
Tvector<T>::Tvector(size_t size) {
    _capacity = (size + STEP_OF_CAPACITY - 1) / STEP_OF_CAPACITY * STEP_OF_CAPACITY;
    _size = size;
    _data = new T[_capacity];
    for (size_t i = 0; i < _size; i++) {
        _data[i] = T();
    }
}
template <typename T>
Tvector<T>::Tvector(const T* data, size_t size) {
    _size = static_cast<int>(size);
    _capacity = (_size + STEP_OF_CAPACITY - 1) / STEP_OF_CAPACITY * STEP_OF_CAPACITY;
    _data = new T[_capacity];
    for (size_t i = 0; i < size; i++) {
        _data[i] = data[i];
    }
}

template <typename T>
Tvector<T>::Tvector(const Tvector& other) {
    _size = other._size;
    _capacity = other._capacity;
    _data = new T[_capacity];
    for (size_t i = 0; i < _size; i++) {
        _data[i] = other._data[i];
    }
}

template <typename T>
Tvector<T>::Tvector(T* data, size_t size) {
    _size = size;
    _capacity = (size + STEP_OF_CAPACITY - 1) / STEP_OF_CAPACITY * STEP_OF_CAPACITY;
    _data = new T[_capacity];
    for (size_t i = 0; i < _size; i++) {
        _data[i] = data[i];
    }
}

template <typename T>
Tvector<T>::Tvector(std::initializer_list<T> data) {
    _size = data.size();
    _capacity = (_size + STEP_OF_CAPACITY - 1) / STEP_OF_CAPACITY * STEP_OF_CAPACITY;
    _data = new T[_capacity];
    size_t i = 0;
    for (const auto& item : data) {
        _data[i++] = item;
    }
}

template<typename T>
Tvector<T>::~Tvector() {
    if (_data != nullptr) {
        delete[] _data;
    }
}

template <typename T>
Tvector<T>& Tvector<T>::operator=(const Tvector& other) {
    if (this != &other) {
        delete[] _data;
        _size = other._size;
        _capacity = other._capacity;
        _data = new T[_capacity];
        for (size_t i = 0; i < _size; i++) {
            _data[i] = other._data[i];
        }
    }
    return *this;
}

template <typename T>
inline T& Tvector<T>::front() {
    if (_size < 1) throw std::logic_error("Vector is empty");
    return _data[0];
}

template <typename T>
inline const T& Tvector<T>::front() const {
    if (_size < 1) throw std::logic_error("Vector is empty");
    return _data[0];
}

template <typename T>
inline T& Tvector<T>::back() {
    if (_size < 1) throw std::logic_error("Vector is empty");
    return _data[_size - 1];
}

template <typename T>
inline const T& Tvector<T>::back() const {
    if (_size < 1) throw std::logic_error("Vector is empty");
    return _data[_size - 1];
}

template <typename T>
inline T* Tvector<T>::data() noexcept {
    return _data;
}

template <typename T>
inline const T* Tvector<T>::data() const noexcept {
    return _data;
}

template <typename T>
inline int Tvector<T>::size() const noexcept {
    return _size;
}

template <typename T>
inline int Tvector<T>::capacity() const noexcept {
    return _capacity;
}

template <typename T>
inline T& Tvector<T>::operator[](int indx) noexcept {
    return _data[indx];
}

template <typename T>
inline const T& Tvector<T>::operator[](int indx) const noexcept {
    return _data[indx];
}

template <typename T>
bool Tvector<T>::empty() const {
    return _size == 0;
}

template <typename T>
void Tvector<T>::resize(size_t new_size) {
    if (new_size > _capacity) {
        reserve(new_size);
    }
    if (new_size > _size) {
        for (size_t i = _size; i < new_size; i++) {
            _data[i] = T();
        }
    }
    _size = new_size;
}

template <typename T>
void Tvector<T>::reserve(size_t new_capacity) {
    if (new_capacity <= _capacity) return;

    _capacity = (new_capacity + STEP_OF_CAPACITY - 1) / STEP_OF_CAPACITY * STEP_OF_CAPACITY;
    T* new_data = new T[_capacity];

    for (size_t i = 0; i < _size; i++) {
        new_data[i] = _data[i];
    }

    delete[] _data;
    _data = new_data;
}

template <typename T>
void Tvector<T>::repacking(size_t new_capacity) {
    reserve(new_capacity);
}

template <typename T>
void Tvector<T>::push_back(T val) {
    if (_size == _capacity) {
        reserve(_capacity + STEP_OF_CAPACITY);
    }
    _data[_size++] = val;
}

template <typename T>
void Tvector<T>::push_front(T val) {
    insert(0, val);
}

template <typename T>
void Tvector<T>::insert(int pos, T val) {
    if (pos > _size) throw std::out_of_range("Index out of range");

    if (_size == _capacity) {
        reserve(_capacity + STEP_OF_CAPACITY);
    }

    for (size_t i = _size; i > pos; i--) {
        _data[i] = _data[i - 1];
    }

    _data[pos] = val;
    _size++;
}

template <typename T>
void Tvector<T>::insert(T* pos, T val) {
    if (pos < _data || pos > _data + _size) {
        throw std::out_of_range("Pointer out of range");
    }

    size_t index = pos - _data;
    insert(index, val);
}

template <typename T>
T Tvector<T>::pop_back() {
    if (_size == 0) throw std::logic_error("Vector is empty");
    return _data[--_size];
}

template <typename T>
T Tvector<T>::pop_front() {
    if (_size == 0) throw std::logic_error("Vector is empty");
    return erase(0);
}

template <typename T>
T Tvector<T>::erase(int pos) {
    if (pos >= _size) throw std::out_of_range("Index out of range");

    T removed = _data[pos];
    for (size_t i = pos; i < _size - 1; i++) {
        _data[i] = _data[i + 1];
    }
    _size--;
    return removed;
}

template <typename T>
T Tvector<T>::erase(T* pos) {
    if (pos < _data || pos >= _data + _size) {
        throw std::out_of_range("Pointer out of range");
    }

    size_t index = pos - _data;
    return erase(index);
}

template <typename T>
size_t Tvector<T>::find(const T& val) const {
    for (size_t i = 0; i < _size; i++) {
        if (_data[i] == val) {
            return i;
        }
    }
    return _size; 
}

template <typename T>
void Tvector<T>::clear() {
    _size = 0;
}