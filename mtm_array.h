//
// Created by Afik on 01/07/2018.
//

#ifndef EX5_MTM_ARRAY_H
#define EX5_MTM_ARRAY_H

#include <utility>
#include <stdexcept>
#include <iostream>     // std::cout
#include <exception>    // std::exception
#include <new>          // std::bad_array_new_length

template <class T, int SIZE>
class Array
{
    T* data;

public:
    // A c'tor function for the class Array.
    // Parameters: a specific type.
    // Initializes the Array's data array of one type T.
    // Will throw a bad_array_new_length error for invalid array length (e.g.
    // negative).
    explicit Array(T const& initial_value = T()):data(new T[SIZE]){
        for (int i = 0; i < SIZE; ++i) {
            data[i]=initial_value;
        }
    }
    // A copy c'tor for an Array class. Receives an Array (by reference), and
    // returns a copy of it (by value).
    Array(const Array<T,SIZE>& a): data(new T[SIZE]) {
        for (int i = 0; i < SIZE; ++i) {
            data[i] = a.data[i];
        }
    }
    // A d'tor function for the class Array.
    // Deletes the Array's T* array.
    ~Array<T,SIZE>(){
        delete[]data;
    }
    // An assignment c'tor for an Array class. Receives an Array (by reference),
    // deletes all current values of *this Array, and replaces it with the
    // values of the given array.
    Array<T,SIZE>& operator=(const Array& a){
        T* temp = allocate_and_copy(a);
        delete[]data;
        data = temp;
        return *this;
    }
    // Defining a [] operator for Array.
    // The operator enables the access to an entity in the array, by an index.
    // Can access the entity and change it (Read+Write).
    // In case of an access to an illegal index of the Array - throws:
    // std::out_of_range.
    T& operator[](int index){
        if (index>=SIZE || index<0){
            throw std::out_of_range("mtm_array::operator []: "
                                            "index out of range!");
        }
        return data[index];
    }
    // Defining a const [] operator for Array.
    // The operator enables the access to an entity in the array, by an index.
    // Can access the entity but can't change it (Read only).
    // In case of an access to an illegal index of the Array - throws:
    // std::out_of_range.
    const T& operator[](int index) const{
        if (index>=SIZE || index<0){
            throw std::out_of_range("mtm_array::operator []: "
                                            "index out of range!");
        }
        return data[index];
    }
    // The function receives an Array, allocates a new T* array, copies the
    // received data array of to the new allocated one, and returns a pointer
    // to its beginning.
    T* allocate_and_copy (const Array& arr){
        T* array = new T[SIZE];
        for (int i = 0; i < SIZE; ++i) {
            array[i] = arr.data[i];
        }
        return array;
    }


    class const_iterator {
        const Array<T,SIZE>* array;
        int index;
        friend class Array<T,SIZE>;


    public:
        // A c'tor function for the class const_iterator.
        // Parameters: a array and an index.
        // Initializes the Array and the index.
        const_iterator(const Array<T,SIZE>* array, int index):
                array(array), index(index){}
        // An * operator that returns a const array value of the current
        // iterator index.
        T const& operator*() const {
            if (index>=SIZE || index<0){
                throw std::out_of_range("mtm_array::operator []: "
                                                "index out of range!");
            }
            return array->data[index];
        }
        // An overload of a post-increment operator.
        // Advances the iterator, but the value of the expression is the
        // operand's original value prior to the increment operation.
        const_iterator& operator++(){
            ++index;
            return *this;
        }
        // An overload of a pre-increment operator.
        // Advances the iterator
        const_iterator operator++(int){
            const_iterator result = *this;
            ++*this;
            return result;
        }
        // An overload of an arrow operator.
        // Gets the member from the class that the left side points to (const).
        const T* operator->(){
            if (index>=SIZE || index<0){
                throw std::out_of_range("mtm_array::operator []: "
                                                "index out of range!");
            }            return &(array->data[index]);
        }
        // A comparison operation. compares between two iterators, and returns
        // true if equal.
        bool operator==(const const_iterator& const_iterator) const{
            if (array != const_iterator.array){
                return false;
            }
            return index == const_iterator.index;
        }
        // A comparison operation. compares between two iterators, and returns
        // true if not equal.
        bool operator!=(const const_iterator& const_iterator) const{
            return !(*this == const_iterator);
        }
        const_iterator(const const_iterator&) = default;
        const_iterator& operator=(const const_iterator&) = default;
    };

    class iterator {
        const Array<T,SIZE>* array;
        int index;
        friend class Array<T,SIZE>;
        friend class const_iterator;

    public:
        // A c'tor function for the class iterator.
        // Parameters: a array and an index.
        // Initializes the Array and the index.
        iterator(Array<T,SIZE>* array, int index):
                array(array), index(index){}
        // An * operator that returns a array value of the current
        // iterator index.
        T& operator*() const{
            if (index>=SIZE || index<0){
                throw std::out_of_range("mtm_array::operator []: "
                                                "index out of range!");
            }
            return array->data[index];
        }
        // An overload of a post-increment operator.
        // Advances the iterator, but the value of the expression is the
        // operand's original value prior to the increment operation.
        iterator& operator++(){
            ++index;
            return *this;
        }
        // An overload of a pre-increment operator.
        // Advances the iterator.
        iterator operator++(int){
            iterator result = *this;
            ++*this;
            return result;
        }
        // An overload of an arrow operator.
        // Gets the member from the class that the left side points to.
        T* operator->(){
            if (index>=SIZE || index<0){
                throw std::out_of_range("mtm_array::operator []: "
                                                "index out of range!");
            }
            return &(array->data[index]);
        }
        // A comparison operation. compares between two iterators, and returns
        // true if equal.
        bool operator==(const iterator& iterator) const{
            if (array != iterator.array){
                return false;
            }
            return index == iterator.index;
        }
        // A comparison operation. compares between two iterators, and returns
        // true if not equal
        bool operator!=(const iterator& iterator) const{
            return !(*this == iterator);
        }
        // A comparison operation. compares between two iterators, and returns
        // true if not equal
        bool operator!=(const const_iterator& iterator) const{

            return !(this == &iterator);

        }
        iterator(const iterator&) = default;
        iterator& operator=(const iterator&) = default;

    };
    // Returns an iterator pointing to the first element in the sequence.
    iterator begin(){
        return iterator(this, 0);
    }
    // Returns an iterator pointing to the first element in the sequence.
    const_iterator begin() const{
        return const_iterator(this, 0);
    }
    // Returns an iterator pointing to the last element in the sequence:
    iterator end(){
        return iterator(this, SIZE);
    }
    // Returns an iterator pointing to the last element in the sequence:
    const_iterator end() const{
        return const_iterator(this, SIZE);
    }
};

#endif //EX5_MTM_ARRAY_H