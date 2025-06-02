// Copyright [2018] <Jessllena>
#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>


namespace structures {

template<typename T>
class ArrayList {
 public:
    ArrayList();
    explicit ArrayList(std::size_t max_size);
    ~ArrayList();

    void clear();
    void push_back(const T& data);
    void push_front(const T& data);
    void insert(const T& data, std::size_t index);
    void insert_sorted(const T& data);
    T pop(std::size_t index);
    T pop_back();
    T pop_front();
    void remove(const T& data);
    bool full() const;
    bool empty() const;
    bool contains(const T& data) const;
    std::size_t find(const T& data) const;
    std::size_t size() const;
    std::size_t max_size() const;
    T& at(std::size_t index);
    T& operator[](std::size_t index);
    const T& at(std::size_t index) const;
    const T& operator[](std::size_t index) const;
    // descricao do 'operator []' na FAQ da disciplina

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;

    static const auto DEFAULT_MAX = 10u;
};

}   // namespace structures

#endif

template<typename T>
structures::ArrayList<T>::ArrayList() {
    max_size_ = DEFAULT_MAX;
    contents = new T[DEFAULT_MAX];
    size_ = 0;
}

template<typename T>
structures::ArrayList<T>::ArrayList(std::size_t max_size) {
    max_size_ = max_size;
    contents = new T[max_size_];
    size_ = 0;
}

template<typename T>
bool structures::ArrayList<T>::full() const {
    // return (top_ == static_cast<int>(max_size()-1));
    return size() == max_size();
}

template<typename T>
std::size_t structures::ArrayList<T>::size() const {
    return size_;
}

template<typename T>
std::size_t structures::ArrayList<T>::max_size() const {
    return max_size_;
}

template<typename T>
bool structures::ArrayList<T>::empty() const {
    return (size_ == 0);
}

template<typename T>
structures::ArrayList<T>::~ArrayList() {
    delete [] contents;
}

template<typename T>
void structures::ArrayList<T>::clear() {
    size_ = 0;
}

template<typename T>
void structures::ArrayList<T>::push_back(const T& data) {
    if (full())
        throw std::out_of_range("lista cheia");
    contents[size_] = data;
    size_++;
}

template<typename T>
void structures::ArrayList<T>::push_front(const T& data) {
    if (full())
        throw std::out_of_range("lista cheia");
    for (int i = size_; i > 0; i--) {
    contents[i] = contents[i-1];
    }
    contents[0] = data;
    size_++;
}

template<typename T>
void structures::ArrayList<T>::insert(const T& data, std::size_t index) {
    if (full() || index > size()) {
        throw std::out_of_range("lista cheia");
    }
     for (std::size_t i = size_; i > index; i--) {
        contents[i] = contents[i-1];
    }
    contents[index] = data;
    size_++;
}

template<typename T>
void structures::ArrayList<T>::insert_sorted(const T& data) {
    if (full())
        throw std::out_of_range("lista cheia");
    std::size_t i = 0;
    while (i < size_ && contents[i] < data) {
        i++;
    }
    insert(data, i);
}

template<typename T>
T structures::ArrayList<T>::pop(std::size_t index) {
    if (empty() || index >= size()) {
        throw std::out_of_range("lista vazia");
    }
    T aux = contents[index];
    for (std::size_t i = index + 1; i < size_; i++) {
        contents[i-1] = contents[i];
    }
    size_--;
    return aux;
}

template<typename T>
T structures::ArrayList<T>::pop_back() {
    if (empty())
        throw std::out_of_range("lista vazia");
    size_--;
    return contents[size_];
}


template<typename T>
T structures::ArrayList<T>::pop_front() {
    if (empty())
        throw std::out_of_range("lista vazia");
    T aux = contents[0];
    for (std::size_t i = 1; i < size_; i++) {
        contents[i-1] = contents[i];
    }
    size_--;
    return aux;
}

template<typename T>
void structures::ArrayList<T>::remove(const T& data) {
    if (empty())
        throw std::out_of_range("lista vazia");
    std::size_t i = 0;
    while (i < size_ && contents[i] != data) {
        i++;
    }
    if (i < size_) {
        pop(i);
    }
}


template<typename T>
T& structures::ArrayList<T>::operator[](std::size_t index) {
    return contents[index];
}


template<typename T>
T& structures::ArrayList<T>::at(std::size_t index) {
    if (empty() || index >= size_) {
        throw std::out_of_range("lista vazia ou posição invalida");
    }
    return contents[index];
}



template<typename T>
bool structures::ArrayList<T>::contains(const T& data) const {
    if (empty())
        return false;
    bool aux = false;
    for (std::size_t i = 0; i < size(); i++) {
        aux = contents[i] == data;
        if (aux) {
            break;
        }
    }
    return aux;
}

template<typename T>
std::size_t structures::ArrayList<T>::find(const T& data) const {
    if (empty())
        return false;
    std::size_t i = 0;
    bool aux = false;
    for (i = 0; i < size(); i++) {
        if (contents[i] == data) {
            aux = 1;
            break;
        }
    }
    if (aux) {
        return i;
    } else {
        return size_;
    }
}
