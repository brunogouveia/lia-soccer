/*
 * Array.h
 *
 *  Created on: 02/03/2013
 *      Author: yuriclaure
 */

#ifndef ARRAY_H_
#define ARRAY_H_

template<typename E>
class ArrayIterator {
	private:
		E * data;
		int length;
		int currentPosition;
	public:
		ArrayIterator(E * data, int length) :
				currentPosition(0) {
			this->data = data;
			this->length = length;
		}
		virtual ~ArrayIterator() {
		}
		virtual bool hasNext() const {
			return currentPosition < length;
		}
		virtual const E& next() {
			return data[currentPosition++];
		}
};

template<typename E, int initialSize = 10>
class Array {
	private:
		E * data;
		int length;
		int alocatedPositions;
	public:
		Array() :
				length(0), alocatedPositions(initialSize) {
			data = new E[initialSize];
		}

		virtual ~Array() {
			delete[] data;
		}

		void add(const E& value);
		bool remove(const E& value);
		void clear() {
			length = 0;
		}
		bool isEmpty() const {
			return length == 0;
		}
		int size() const {
			return length;
		}
		bool contains(const E& value) const;

		ArrayIterator<E>* iterator() const {
			return new ArrayIterator<E>(data, length);
		}

		void expand();

		E operator[](int i) const {
			return data[i];
		}
		E& operator[](int i) {
			return data[i];
		}

		void setLength(int len) {
			while (len >= alocatedPositions)
				expand();
			length = len;
			return;
		}
};

template<typename E, int initialSize>
void Array<E, initialSize>::add(const E& value) {
	if (length == alocatedPositions)
		expand();
	(*this)[length++] = value;
}

template<typename E, int initialSize>
bool Array<E, initialSize>::remove(const E& value) {
	int i = 0;
	while ((*this)[i++] != value && i < length)
		;
	if ((*this)[i] == value) {
		while (i < length - 1) {
			(*this)[i] = (*this)[i + 1];
			i++;
		}
		length--;
		return true;
	} else {
		return false;
	}
}

template<typename E, int initialSize>
bool Array<E, initialSize>::contains(const E& value) const {
	for (ArrayIterator<E> * i = iterator(); i->hasNext();)
		if (i->next() == value)
			return true;
	return false;
}

template<typename E, int initialSize>
void Array<E, initialSize>::expand() {
	E * newData = new E[alocatedPositions + initialSize];
	for (int i = 0; i < length; i++)
		newData[i] = (*this)[i];
	delete[] data;
	data = newData;
	alocatedPositions = alocatedPositions + initialSize;
}

#endif /* ARRAY_H_ */
