#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class CustomVector {
private:
    T* arr_ptr;               
    size_t current_size;      
    size_t max_capacity;      

    void resize(size_t new_capacity);

public:
    CustomVector();
    ~CustomVector();
    CustomVector(const CustomVector& other);
    CustomVector(CustomVector&& other) noexcept;

    void assign_copy(const CustomVector& other);
    void assign_move(CustomVector&& other);

    size_t size() const;
    size_t capacity() const;
    bool is_empty() const;
    T at(size_t index) const;
    void push(T item);
    void insert(size_t index, T item);
    void prepend(T item);
    T pop();
    void delete_at(size_t index);
    void remove(T item);
    int find(T item) const;
};

template <typename T>
void CustomVector<T>::resize(size_t new_capacity) {
    T* new_arr = new T[new_capacity];
    for (size_t i = 0; i < current_size; ++i) {
        *(new_arr + i) = move(*(arr_ptr + i)); 
    }
    delete[] arr_ptr;       
    arr_ptr = new_arr;      
    max_capacity = new_capacity;
}

template <typename T>
CustomVector<T>::CustomVector() : arr_ptr(new T[16]), current_size(0), max_capacity(16) {}

template <typename T>
CustomVector<T>::~CustomVector() {
    if (arr_ptr != nullptr) {
        delete[] arr_ptr;
        arr_ptr = nullptr;
    }
}

template <typename T>
CustomVector<T>::CustomVector(const CustomVector& other) {
    current_size = other.current_size;
    max_capacity = other.max_capacity;
    arr_ptr = new T[max_capacity];
    for (size_t i = 0; i < current_size; ++i) {
        *(arr_ptr + i) = *(other.arr_ptr + i);
    }
}

template <typename T>
    CustomVector<T>::CustomVector(CustomVector&& other) noexcept {
        arr_ptr = other.arr_ptr;
        current_size = other.current_size;
        max_capacity = other.max_capacity;

        other.arr_ptr = nullptr;
        other.current_size = 0;
        other.max_capacity = 0;
    }

template <typename T>
void CustomVector<T>::assign_copy(const CustomVector<T>& other) {
    if (this == &other) return; 

    delete[] arr_ptr; 

    current_size = other.current_size;
    max_capacity = other.max_capacity;
    arr_ptr = new T[max_capacity]; 

    for (size_t i = 0; i < current_size; ++i) {
        *(arr_ptr + i) = *(other.arr_ptr + i); 
    }
}

template <typename T>
void CustomVector<T>::assign_move(CustomVector<T>&& other) {
    if (this == &other) return; 

    delete[] arr_ptr; 

    arr_ptr = other.arr_ptr;
    current_size = other.current_size;
    max_capacity = other.max_capacity;

    other.arr_ptr = nullptr;
    other.current_size = 0;
    other.max_capacity = 0;
}

template <typename T>
size_t CustomVector<T>::size() const { 
    return current_size; 
}

template <typename T>
size_t CustomVector<T>::capacity() const { 
    return max_capacity; 
}

template <typename T>
bool CustomVector<T>::is_empty() const { 
    return current_size == 0; 
}

template <typename T>
T CustomVector<T>::at(size_t index) const {
    if (index >= current_size) {
        throw out_of_range("");
    }
    return *(arr_ptr + index); 
}

template <typename T>
void CustomVector<T>::push(T item) {
    if (current_size == max_capacity) {
        resize(max_capacity * 2); 
    }
    *(arr_ptr + current_size) = item; 
    current_size++;
}

template <typename T>
void CustomVector<T>::insert(size_t index, T item) {
    if (index > current_size) {
        throw out_of_range("");
    }
    if (current_size == max_capacity) {
        resize(max_capacity * 2);
    }
    for (size_t i = current_size; i > index; --i) {
        *(arr_ptr + i) = move(*(arr_ptr + (i - 1)));
    }
    *(arr_ptr + index) = item;
    current_size++;
}

template <typename T>
void CustomVector<T>::prepend(T item) {
    insert(0, item);
}

template <typename T>
T CustomVector<T>::pop() {
    if (is_empty()) {
        throw underflow_error("");
    }
    T last_item = *(arr_ptr + (current_size - 1)); 
    current_size--;

    if (current_size > 0 && current_size <= max_capacity / 4 && max_capacity / 2 >= 16) {
        resize(max_capacity / 2);
    }
    return last_item;
}

template <typename T>
void CustomVector<T>::delete_at(size_t index) {
    if (index >= current_size) {
        throw out_of_range("");
    }
    for (size_t i = index; i < current_size - 1; ++i) {
        *(arr_ptr + i) = move(*(arr_ptr + (i + 1)));
    }
    current_size--;

    if (current_size > 0 && current_size <= max_capacity / 4 && max_capacity / 2 >= 16) {
        resize(max_capacity / 2);
    }
}

template <typename T>
void CustomVector<T>::remove(T item) {
    for (size_t i = 0; i < current_size; ++i) {
        if (*(arr_ptr + i) == item) {
            delete_at(i);
            --i; 
        }
    }
}

template <typename T>
int CustomVector<T>::find(T item) const {
    for (size_t i = 0; i < current_size; ++i) {
        if (*(arr_ptr + i) == item) {
            return (int)i; 
        }
    }
    return -1;
}