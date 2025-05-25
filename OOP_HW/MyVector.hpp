#pragma once
#include <iostream>
#include "OutputMessages.h"

template<typename T>
class MyVector
{

private:
	T* data;
	int capacity;
	int current;

	void moveFrom(MyVector&& other);
	void copyFrom(const MyVector& other);
	void free();

public:
	MyVector();
	~MyVector();

	MyVector(const MyVector& other);
	MyVector(MyVector&& other) noexcept;

	MyVector& operator=(const MyVector& other);
	MyVector& operator=(MyVector&& other) noexcept;

	void push(T other);
	void insert(T other, unsigned index);

	T& get(unsigned index) const;
	void pop();
	void delete_at(unsigned index);
	int size() const;
	int get_capacity() const;
	void clear();

	T& operator[](unsigned index);
	T& operator[](unsigned index) const;
};

template<class T>
void MyVector<T>::moveFrom(MyVector&& other)
{
	data = other.data;
	capacity = other.capacity;
	current = other.current;

	other.data = nullptr;
	other.capacity = 0;
	other.current = 0;
}

template<class T>
void MyVector<T>::free()
{
	if constexpr (std::is_pointer_v<T>)
	{
		for (size_t i = 0; i < current; i++)
		{
			delete data[i]; 
			data[i] = nullptr; 
		}
	}

	delete[] data; 
	data = nullptr;

	current = 0;
	capacity = 0;
}

template<class T>
void MyVector<T>::clear()
{
	free();
	data = new T[1];
	capacity = 1;
	current = 0;
}

template<class T>
MyVector<T>::MyVector()
{
	data = new T[1];
	capacity = 1;
	current = 0;
}

template<class T>
MyVector<T>::~MyVector()
{
	free();
}

template<class T>
MyVector<T>::MyVector(const MyVector& other)
{
	copyFrom(other);
}

template<class T>
MyVector<T>::MyVector(MyVector&& other) noexcept
{
	moveFrom(std::move(other));
}

template<class T>
void MyVector<T>::copyFrom(const MyVector& other)
{

	data = new T[other.capacity];
	for (int i = 0; i < other.current; i++)
	{
		data[i] = other.data[i];
	}
	capacity = other.capacity;
	current = other.current;
}

template<class T>
void MyVector<T>::delete_at(unsigned index)
{
	if (index >= current)
	{
		throw std::out_of_range(ErrorMessages::INDEX_OUT_OF_RANGE);
	}

	for (unsigned i = index; i < current - 1; ++i)
	{
		data[i] = std::move(data[i + 1]);
	}

	--current;

	if (current < capacity / 4)
	{
		capacity /= 2;
		T* newData = new T[capacity];

		for (unsigned i = 0; i < current; ++i)
		{
			newData[i] = std::move(data[i]);
		}

		delete[] data;
		data = newData;
	}
}

template<class T>
void MyVector<T>::push(T other)
{
	if (current == capacity)
	{
		T* temp = new T[2 * capacity];

		for (int i = 0; i < capacity; i++)
		{
			temp[i] = data[i];
		}

		delete[] data;
		capacity *= 2;
		data = temp;
	}

	data[current] = other;
	current++;
}

template<class T>
void MyVector<T>::insert(T other, unsigned index)
{
	if (index > current)
		throw std::out_of_range(ErrorMessages::INDEX_OUT_OF_RANGE);

	if (current == capacity)
	{
		capacity *= 2;
		T* newData = new T[capacity];
		for (int i = 0; i < current; i++)
			newData[i] = data[i];
		delete[] data;
		data = newData;
	}

	for (int i = current; i > index; --i)
		data[i] = data[i - 1];

	data[index] = other;
	++current;
}

template<class T>
T& MyVector<T>::get(unsigned index) const
{
	if (index >= current)
		throw std::out_of_range(ErrorMessages::INDEX_OUT_OF_RANGE);
	return data[index];
}

template<class T>
void MyVector<T>::pop()
{
	if (current > 0)
	{
		current--;
	}
}

template<class T>
int MyVector<T>::size() const
{
	return current;
}

template<class T>
int MyVector<T>::get_capacity() const
{
	return capacity;
}

template<class T>
T& MyVector<T>::operator[](unsigned index)
{
	if (index >= current)
	{
		throw std::out_of_range(ErrorMessages::INDEX_OUT_OF_RANGE);
	}
	return data[index];
}

template<class T>
T& MyVector<T>::operator[](unsigned index) const
{
	if (index >= current)
	{
		throw std::out_of_range("Index out of range!");
	}
	return data[index];
}

template<class T>
MyVector<T>& MyVector<T>::operator=(const MyVector& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

template<class T>
MyVector<T>& MyVector<T>::operator=(MyVector&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}
