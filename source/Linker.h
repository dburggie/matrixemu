#ifndef _LINKER_H
#define _LINKER_H

#include <cstdlib>

namespace matrixemu
{
	template <class T> class Linker
	{
		private:
			T * obj;
			Linker * hp;
			Linker * np;
			Linker * pp;
		public:
			Linker();
			Linker(T * obj);
			Linker(T * obj, Linker * head);
			~Linker();

			Linker * next();
			Linker * prev();

			T * get();
			T * set(T * obj); //returns old pointer

			Linker * append(Linker * chain); //returns head
			Linker * remove(); //returns this
	};
}



using namespace matrixemu;

template <class T> Linker<T>::Linker()
{
	hp = this;
	np = this;
	pp = this;
	obj = NULL;
}

template <class T> Linker<T>::Linker(T * obj)
{
	hp = this;
	np = this;
	pp = this;
	this->obj = obj;
}

template <class T> Linker<T>::Linker(T * obj, Linker * node)
{
	append(node);
	this->obj = obj;
}

template <class T> Linker<T>::~Linker()
{
	//special case: deleting head node
	//resolution: delete all other nodes
	if (hp == this)
	{
		while (np != this)
		{
			delete np;
		}
	}

	//general case: delete contained object and remove self from list
	if (obj) delete obj;
	remove();
}

template <class T> Linker<T> * Linker<T>::append(Linker * node)
{
	//get head pointer
	Linker * head = node->hp;
	hp = head;

	//connect this to next and previous
	np = head;
	pp = head->pp;

	//connect next and previous to this
	pp->np = this;
	np->pp = this;

	return head;
}

template <class T> Linker<T> * Linker<T>::remove()
{
	//special case: removing the head pointer
	//resolution: delete all other nodes
	if (hp == this)
	{
		while (np != this)
		{
			delete np;
		}
	}

	//general case:
	
	//connect previous to next
	pp->np = np;
	np->pp = pp;

	//connect this to itself
	hp = this;
	np = this;
	pp = this;

	return this;
}

template <class T> T * Linker<T>::get()
{
	return obj;
}

template <class T> T * Linker<T>::set(T * obj)
{
	T * tmp = this->obj;
	this->obj = obj;
	return tmp;
}

template <class T> Linker<T> * Linker<T>::next() { return np; }
template <class T> Linker<T> * Linker<T>::prev() { return pp; }

#endif
