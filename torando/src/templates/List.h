/*
 * List.h
 *
 *  Created on: Apr 17, 2013
 *      Author: bruno
 */

#ifndef LIST_H_
#define LIST_H_

#include <stdlib.h>

template<typename T>
class ListNode;
template<typename T>
class ListIterator;

template<typename T, int size = 12>
class List {
	public:
		List();
		virtual ~List();

		bool add(const ListNode<T> & node);
		bool add(const List<T> & list);

		bool remove(const T & value);

		ListIterator<T> * getIterator();

	private:
		int size;
		List(const List<T> &);
		List<T> & operator=(const List<T>&);
};

template<typename T>
class ListNode {
	private:
		friend class List<T> ;

		ListNode(const T & value, const ListNode<T> & next = NULL);
		~ListNode();

		T & value;
		ListNode<T> * next;
};

template<typename T>
class ListIterator {
	public:
		void moveBegin();

		bool hasNext();
		const T & getNext();

	private:
		friend class List<T> ;

		ListIterator();
		~ListIterator();
};

template<typename T, int size>
List<T, size>::List() {

}
template<typename T, int size>
List<T, size>::~List() {

}

template<typename T, int size>
bool List<T, size>::add(const ListNode<T> & node) {
	return false;
}
template<typename T, int size>
bool List<T, size>::add(const List<T> & list) {
	return false;
}

template<typename T, int size>
bool List<T, size>::remove(const T & value) {
	return false;
}

template<typename T, int size>
ListIterator<T> * List<T, size>::getIterator() {
	return NULL;
}
/*=============================================================*/
template<typename T>
ListNode<T>::ListNode(const T & value, const ListNode<T> & next) :
		value(value), next(next) {

}
template<typename T>
ListNode<T>::~ListNode() {
}

/*================================================================*/
template<typename T>
void ListIterator<T>::moveBegin() {

}
template<typename T>
bool ListIterator<T>::hasNext() {
	return false;
}
template<typename T>
const T & ListIterator<T>::getNext() {
	return NULL;
}

template<typename T>
ListIterator<T>::ListIterator() {

}
template<typename T>
ListIterator<T>::~ListIterator() {

}

#endif /* LIST_H_ */
