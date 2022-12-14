#ifndef MARRAY_H
#define MARRAY_H

#include <iostream>
#include <stdexcept>                        
#include <string>                           
#include <utility>                          

namespace Movesemantics 
{
    template <typename T>
    class Array
    {
    public:
        Array();                                  
        explicit Array(size_t size);              
        // Rule of five
        ~Array();                                 
        Array(const Array& array);                // Copy constructor
        Array(Array&& array) noexcept;        // Move constructor
        Array& operator=(const Array& rhs);       // Copy assignment operator
        Array& operator=(Array&& rhs) noexcept; // Move assignment operator

        void swap(Array& other) noexcept;         // Swap member function
        T& operator[](size_t index);              // Subscript operator
        const T& operator[](size_t index) const;  // Subscript operator-const arrays
        size_t getSize() const { return m_size; } // Accessor for m_size
        void push_back(T element);                // Copy or move element to the back of the array

    private:
        T* m_elements;    // Array of type T
        size_t m_size;    // Number of array elements
    };

    template <typename T>
    Array<T>::Array() : Array{ 0 }
    {}


    template <typename T>
    Array<T>::Array(size_t size) : m_elements{ new T[size] {} }, m_size{ size }
    {}


    template <typename T>
    Array<T>::Array(const Array& array) : Array{ array.m_size }
    {
        std::cout << "Array of " << m_size << " elements copied" << std::endl;
        for (size_t i{}; i < m_size; ++i)
            m_elements[i] = array.m_elements[i];
    }


    template <typename T>
    Array<T>::Array(Array&& moved) noexcept
        : m_size{ moved.m_size }, m_elements{ moved.m_elements }
    {
        std::cout << "Array of " << m_size << " elements moved" << std::endl;
        moved.m_elements = nullptr; // Otherwise destructor of moved would delete[] m_elements!
    }


    template <typename T>
    Array<T>::~Array() { delete[] m_elements; }

    template <typename T>
    const T& Array<T>::operator[](size_t index) const
    {
        if (index >= m_size)
            throw std::out_of_range{ "Index too large: " + std::to_string(index) };
        return m_elements[index];
    }

    // Uses the 'const-and-back-again' idiom
    template <typename T>
    T& Array<T>::operator[](size_t index)
    {
        return const_cast<T&>(std::as_const(*this)[index]);
    }

    // Template for exception-safe copy assignment operators
    // (expressed in terms of copy constructor and swap member)
    template <typename T>
    Array<T>& Array<T>::operator=(const Array& rhs)
    {
        Array<T> copy{ rhs }; // Copy...       
        swap(copy);
        return *this;
    }

    // Move assignment operator template
    template <typename T>
    Array<T>& Array<T>::operator=(Array&& rhs) noexcept
    {
        std::cout << "Array of " << rhs.m_size << " elements moved (assignment)" << std::endl;

        if (&rhs != this)            // prevent trouble with self-assignments
        {
            delete[] m_elements;       // delete[] all existing elements

            m_elements = rhs.m_elements; // copy the elements pointer and the size
            m_size = rhs.m_size;

            rhs.m_elements = nullptr;  // make sure rhs does not delete[] m_elements
        }
        return *this;                // return lhs
    }

    // Swap member function template
    template <typename T>
    void Array<T>::swap(Array& other) noexcept
    {
        std::swap(m_elements, other.m_elements); // Swap two pointers
        std::swap(m_size, other.m_size);         // Swap the sizes
    }

    // Swap non-member function template (optional)
    template <typename T>
    void swap(Array<T>& one, Array<T>& other) noexcept
    {
        one.swap(other);     // Forward to public member function
    }

    // push_back() overload for lvalue references
    template <typename T>
    void Array<T>::push_back(T element)   // Pass by value (copy of lvalue, or moved rvalue!)
    {
        Array<T> newArray{ m_size + 1 };      // Allocate a larger Array<>
        for (size_t i{}; i < m_size; ++i)   // Move all existing elements...
            newArray[i] = std::move(m_elements[i]);

        newArray[m_size] = std::move(element); // Move the new one (could itself be a copy already)...

        swap(newArray);                     // ... and swap!
}
}
#endif