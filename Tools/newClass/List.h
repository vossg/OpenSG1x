#ifndef LIST_H
#define LIST_H

#include <iostream>

///
template <class T> class List {
  
///
	struct ListElem {
	  
///
		ListElem *_next;
///
		ListElem *_prev;
///
		T *_data;

///
		ListElem(void) { _next = 0; _prev = 0; _data = 0; }
///
		ListElem(T *data) { _data = data; _next = _prev = 0; }
///
	  virtual ~ListElem(void) {;}

	};

protected:

///
	ListElem *_first;
///
	ListElem *_last;
///
	ListElem *_current;
	
///
	unsigned int _numberOfElem;

public:

///
	List(void);
///
	List(List &list);
///
	virtual ~List();
///
	virtual void deleteAllElem();
///
	virtual void excludeAllElem();
	
///
	unsigned int numOfElem (void) { return _numberOfElem; }

///
	T *first(void) { return (_first ? _first->_data : 0); }
///
	T *last(void)  { return (_last ? _last->_data : 0); }
///
	bool begin(void) { return ((_current = _first) ? true : false); }
///
	bool end(void) { return ((_current = _last) ? true : false); }
///
	bool next(); 
///
	bool operator++ () { return next(); }
///
	bool prev(); 
///
	bool operator-- () { return prev(); }

	virtual T *getNext(void)  
	{ 
	  if (_current && _current->_next)
		  return _current->_next->_data;
		else
		  return 0;
  }

///
	virtual T *getPrev(void) 
	{ 
		if (_current && _current->_prev) 
			return _current->_prev->_data;
		else
			return 0;
	}

///
	bool find(T *data);
///
	bool find(T &data) { return find(&data); }

///
	virtual T *current (void) { return _current ? _current->_data : 0; }
///
	virtual T *exclude ();
///
	virtual T *exclude (T *data);
///
	virtual void deleteElem ();
///
	virtual void deleteElem (T* data);

///
	void append (List* list);
///
	void append (List &list) { append(&list); }
///
	virtual void merge (List* list);
///
	virtual void merge (List &list) { merge(&list); }

///
	bool append (T *data);
///
	bool append (T &data) { return append(&data); }
///
	bool insert (T *data);
///
	bool insert (T &data) { return insert(&data); }
///
	bool merge  (T *data);
///
	bool merge  (T &data) { return merge(&data); }

///
	virtual void sort ();

///
	virtual void operator= (List &list);
///
	virtual void swap (List &list);

///
	virtual bool operator== (List &list);
///
	virtual bool operator< (List &list);
///
	virtual bool operator> (List &list);
};


//----------------------------------------------------------------------
template <class T> List<T>::List(void)
{ 
  _first = _last = _current = 0; 
  _numberOfElem = 0; 
}

//----------------------------------------------------------------------
template <class T> List<T>::List(List &list)
{
	_first = _last = _current = 0;
	_numberOfElem = 0;

	cout << "In template <class T> List<T>::List(List &list) !\n";
	
	for (ListElem *current = list._first; current; current = current->_next)
		append(new T(*(current->_data)));
}	

//----------------------------------------------------------------------
template <class T> List<T>::~List()
{
	if (_first)
		{	while (_first->_next)
				{ _current = _first;
					_first = _first->_next;
					// delete _current->_data;
					delete _current;
				}
			// delete _first->_data;
			delete _first;
			_current = _first = _last = 0;
			_numberOfElem = 0;
		}
}
		
//----------------------------------------------------------------------
template <class T> void List<T>::deleteAllElem()
{
	ListElem *current;

	if (_first)
		{	while (_first->_next)
				{ current = _first;
					_first = _first->_next;
					delete current->_data;
					delete current;
				}
			current = _first;
			_current = _first = _last = 0;
			_numberOfElem = 0;
			delete current->_data;
			delete current;
		}
}

//----------------------------------------------------------------------
//	Method name : excludeAllElem
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
template <class T> void List<T>::excludeAllElem(void)
{
	ListElem *current;

	if (_first)
		{	while (_first->_next)
				{ current = _first;
					_first = _first->_next;
					delete current;
				}
			delete _first;
			_current = _first = _last = 0;
			_numberOfElem = 0;
		}
}


//----------------------------------------------------------------------
template <class T> bool List<T>::next()
{
  if (_current)
    {	_current = _current->_next;
    	return true;
    }
	else
		return false;
}

//----------------------------------------------------------------------
template <class T> bool List<T>::prev()
{
  if (_current)
    { _current = _current->_prev;
    	return true;
    }
  else 
  	return false;
}

//----------------------------------------------------------------------
template <class T> bool List<T>::find(T *data)
{
	ListElem *current = _first;
	
	for (; current; current = current->_next)
		if (current->_data == data)
			{	_current = current;
				return true;
			}
	return false;
}

//----------------------------------------------------------------------
template<class T> T *List<T>::exclude ()
{
	ListElem *excludeElem = _current;
	T*	data = 0;

	if (_current)
		{	if (_current->_prev)
				_current->_prev->_next = _current->_next;
			else
				_first = _current->_next;
			if (_current->_next)
				{	_current->_next->_prev = _current->_prev;
					_current = _current->_next;
				}
			else
				_last = _current = _current->_prev;
			data = excludeElem->_data;
			excludeElem->_data = 0;
			delete excludeElem;
			_numberOfElem--;
		}
	return data;
}

//----------------------------------------------------------------------
template<class T> T *List<T>::exclude(T *data)
{
	return (find(data) ? exclude() : 0);
}


//----------------------------------------------------------------------
template <class T> void List<T>::append (List<T> * list)
{
	ListElem *current;
	
	if (list && list->_first)
		for (current = list->_first; current; current = current->_next)
			append(current->_data);
}

//----------------------------------------------------------------------
template <class T> void List<T>::merge (List<T> * list)
{
	// NOT TESTED !!!  - DEBUG
	append(list);
	sort();
}

//----------------------------------------------------------------------
template <class T> bool List<T>::append (T *data)
{
	ListElem *listElem = new ListElem(data);

	if (!listElem)
		{	cerr << "Can't alloc ListElem in List<T>::append ?!\n";
			return false;
		}
	else
		_numberOfElem++;

	if (_last)
		{	listElem->_prev = _last;
			_current = _last = _last->_next = listElem;
		}
	else
		{	_first = _last = _current = listElem;
			listElem->_prev = 0;
		}
	_last->_next = 0;

	return true;
}

//----------------------------------------------------------------------
template <class T> bool List<T>::insert(T *data)
{
	ListElem *listElem;

	if (_current)
		{ if (!(listElem = new ListElem(data)))
				{	cerr << "Can't alloc ListElem in List<T>::include() ?!\n";
					return false;
				}
			else
				_numberOfElem++;
				
			listElem->_prev = _current->_prev;
			if (listElem->_prev)
				listElem->_prev->_next = listElem;
			else
				_first = listElem;
			_current->_prev = listElem;
			listElem->_next = _current;
			_current = listElem;
			return true;
		}
	else
		return append(data);
}

//----------------------------------------------------------------------
template <class T> bool List<T>::merge(T *data)
{
	for (_current = _first; _current; _current = _current->_next)
		if (*_current->_data > *data)	
			return insert(data);
	return append(data);
}

//----------------------------------------------------------------------
template <class T> void List<T>::sort (void)
{
	// NOT TESTED !!! - DEBUG
	List<T> sortList;
	T *data;

	// while (data = exluce())
	for (data = exclude(); data; data = exclude())
		sortList.merge(data);
	_first = sortList._first;
	_last = sortList._last;
	sortList._first = sortList._last = sortList._current = 0;
}

//----------------------------------------------------------------------
template <class T> void List<T>::operator= (List<T> &list)
{
	ListElem *current = list._first;

	excludeAllElem();	
	for (current = list._first; current; current = current->_next)
		append(current->_data);
	_current = _first;
}

//----------------------------------------------------------------------
template <class T> void List<T>::swap (List<T> &list)
{
	ListElem *first, *last, *current;

	first = _first; 
	last = _last; 
	current = _current;
	
	_first = list._first; 
	_last = list._last; 
	_current = list._current;
	
	list._first = first; 
	list._last = last; 
	list._current = current;
}

//----------------------------------------------------------------------
template <class T> bool List<T>::operator== (List<T> &list)
{
  ListElem *current1, *current2;
  
  if (numOfElem() != list.numOfElem())
    return false;
  
  for (current1 = _first; current1; current1 = current1->_next)
    {	for (current2 = list._first; current2; current2 = current2->_next)
  			if (current1->_data == current2->_data)
			  	break;
			if (current2)
			  return false;
    }
  
	return true;
}

//----------------------------------------------------------------------
template <class T> bool List<T>::operator> (List<T> &list)
{
	return (numOfElem() > list.numOfElem() ? true : false);
}

//----------------------------------------------------------------------
template <class T> bool List<T>::operator< (List<T> &list)
{
	return (numOfElem() < list.numOfElem() ? true : false);
}

//----------------------------------------------------------------------
//	Method name : deleteElem
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
template <class T> void List<T>::deleteElem(void)
{
  delete exclude();
}


//----------------------------------------------------------------------
//	Method name : deleteElem
//
//	Author : Johannes Behr 
//	Description :
//	Input :
//	Output :
//
template <class T> void List<T>::deleteElem(T* data)
{
  delete exclude(data);
}


#endif // LIST_H
