/*			List.hpp
	Ben Zech		10/8/2020
	All work below was written by Benjamin Zech. Do not steal
*/

/*  Private Data for Node
      	T data;
       	Node *prev;
       	Node *next;
*/
/*
    Protected data for const_iterator
	Node *current;              // pointer to node in List
	T & retrieve() const;       // retrieve the element refers to
	const_iterator(Node *p);    // protected constructor
*/

 //nested const_iterator class functions


template < typename T >
List< T >::const_iterator::const_iterator() : current{nullptr}
// default zero parameter constructor
{
	// current was set to nullptr in line above
}

template < typename T >
const T & List< T >::const_iterator::operator*() const
// operator*() to return element
{
	return retrieve();
}


template < typename T >
typename List< T >::const_iterator & List< T >::const_iterator::operator++()
// prefix increment operator (++x)
{
	current = current->next;
	return *this;
}

template < typename T >
typename List< T >::const_iterator List< T >::const_iterator::operator++(int)
// postfix increment operator (x++)
{
	const_iterator old = *this;
	++( *this );
	return old;
}

template < typename T >
typename List< T >::const_iterator & List< T >::const_iterator::operator--()
// prefix decrement operator (--x)
{
	current = current->prev;
	return *this;
}

template < typename T >
typename List< T >::const_iterator List< T >::const_iterator::operator--(int)
// postfix decrement operator (x--)
{
	const_iterator old = *this;
	--( *this );
	return old;
}

template < typename T >
bool List< T >::const_iterator::operator==(const const_iterator &rhs) const
// two iterators are equal if they refer to the same element
{
	return current == rhs.current;
}

template < typename T >
bool List< T >::const_iterator::operator!=(const const_iterator &rhs) const
// two iterators are not equal if they refer to different elements
{
	return !( *this == rhs );
}

template < typename T >
T & List< T >::const_iterator::retrieve() const
// return a reference to the corresponding element in the list.
{
	return current->data;
}

template < typename T >
List< T >::const_iterator::const_iterator(Node *p) : current{ p }
// one-parameter constructor. Set pointer current to the given node pointer p.
{
	// current set to p in line above
}


/* Protected data of nested iterator class

                iterator(Node *p);
*/

template < typename T >
List< T >::iterator::iterator()
// default constructor
{
	// left blank?
}

template < typename T >
T & List< T >::iterator::operator*()
// returns a reference to the corresponding element in the list by calling retrieve() member function
{
	return const_iterator::retrieve();
}

template < typename T >
const T & List< T >::iterator::operator*() const
// returns a reference to the corresponding element in the list by calling retrieve() member function
{
	return const_iterator::operator*();
}

template < typename T >
typename List< T >::iterator & List< T >::iterator::operator++()
// prefix increment operator (++x)
{
	this->current = this->current->next;
	return *this;
}

template < typename T >
typename List< T >::iterator List< T >::iterator::operator++(int)
// postfix increment operator (x++)
{
	iterator old = *this;
	++( *this );
	return old;
}

template < typename T >
typename List< T >::iterator & List< T >::iterator::operator--()
// prefix decrement operator (--x)
{
	this->current = this->current->prev;
	return *this;
}

template < typename T >
typename List< T >::iterator List< T >::iterator::operator--(int)
// postfix decrement operator (x--)
{
	iterator old = *this;
	--( *this );
	return old;
}

template < typename T >
List< T >::iterator::iterator(Node *p) : const_iterator{ p }
// one-parameter constructor
{
	// const iterator assigned p in above statement
}


/*	Private Data for List

          int theSize;           // number of elements
          Node *head;            // head node
          Node *tail;            // tail node
      
          void init();           // initialization
*/

template < typename T >
List< T >::List()
// default zero parameter constructor
{
	init();
}

template < typename T >
List< T >::List(const List &rhs)
// copy constructor
{
	init();
	for ( auto & x : rhs )
		push_back( x );
}

template < typename T >
List< T >::List(List && rhs) : theSize{rhs.theSize}, head{rhs.head}, tail{rhs.tail}
// move constructor
{
	rhs.theSize = 0;
	rhs.head = nullptr;
	rhs.tail = nullptr;
}

template < typename T >
List< T >::List(int num, const T& val)
// num elements with value of val
{
	init();

	for (int i = 0; i < num; i++)
		push_front(val);
}

template < typename T >
List< T >::List(const_iterator start, const_iterator end)
// constructs with elements [start, end) i.e., includes start, but not end
{
	init();

	while(start != end)
	{
		push_back(start.retrieve());
		start++;
	}
}

template < typename T >
List< T >::List(std::initializer_list<T> iList)
// constructs with a copy of each of the elements in the initalizer_list
{
	init();
	for ( auto & x : iList )
		push_back( x );
}

template < typename T >
List< T >::~List()
// destructor
{
	clear();
	delete head;
	delete tail;
}

template < typename T >
const List<T>& List< T >::operator=(const List &rhs)
// copy assignment operator
{
	List copy = rhs;
	std::swap( *this, copy );
	return *this;
}

template < typename T >
List<T> & List< T >::operator=(List && rhs)
// move assignment operator
{
	std::swap(theSize, rhs.theSize);
	std::swap(head, rhs.head);
	std::swap(tail, rhs.tail);

	return *this;
}

template < typename T >
List<T>& List< T >::operator=(std::initializer_list<T> iList)
// sets list to the elements of the initializer_list
{
	List copy = iList;
	std::swap( *this, copy );
	return *this;
}

template < typename T >
int List< T >::size() const
// number of elements
{
	return theSize;
}

template < typename T >
bool List< T >::empty() const
// check if list is empty
{
	if ( size() == 0 )
		return true;
	else
		return false;
}

template < typename T >
void List< T >::clear()
// delete all elements
{
	while ( !empty() )
		pop_front();
}

template < typename T >
void List< T >::reverse()
// reverse the order of the elements
{
	if( size() > 1 )  // size 0 or 1 wont change
	{

		iterator itrFront = begin();
		iterator itrBack = end();

		int tempsize = size();		// int that remembers size

		for (int i = 0; i < tempsize; i++)
		{
			itrFront = begin();
			itrBack = insert(itrBack, *itrFront);
			pop_front();
		}
	}
}

template < typename T >
T& List< T >::front()
// reference to the first element
{
	return *begin();
}

template < typename T >
const T& List< T >::front() const
// reference to the first element (const)
{
	return *begin();
}

template < typename T >
T& List< T >::back()
// reference to the last element
{
	return *--end();
}

template < typename T >
const T& List< T >::back() const
// reference to the last element (const)
{
	return *--end();
}

template < typename T >
void List< T >::push_front(const T & val)
// insert to the beginning
{
	insert( begin(), val );
}

template < typename T >
void List< T >::push_front(T && val)
// move version of insert
{
	insert( begin(), std::move(val) );
}

template < typename T >
void List< T >::push_back(const T & val)
// insert to the end
{
	insert( end(), val );
}

template < typename T >
void List< T >::push_back(T && val)
// move version of insert
{
	insert( end(), std::move(val) );
}

template < typename T >
void List< T >::pop_front()
// delete first element
{
	erase(begin());
}

template < typename T >
void List< T >::pop_back()
// delete last element
{
	erase(--end());
}

template < typename T >
void List< T >::remove(const T &val)
// remove all elements with value = val
{
	if ( size() != 0)	// only remove if elements exist
	{
		iterator itr = begin();
	
		while (itr != end())
		{
			if (*itr == val)
				itr = erase(itr);
			else
				itr++;
		}
	}
}

template < typename T >
template <typename PREDICATE>
void List< T >::remove_if(PREDICATE pred)
// remove all elements for which Predicate pred
//  returns true. pred can take in a function object
{
	if ( size() != 0 )	// only remove if elements exist
	{
		iterator itr = begin();

		while (itr != end())
		{
			if ( pred(*itr) )
				itr = erase(itr);
			else
				itr++;
		}
	}
}

template < typename T >
void List< T >::print(std::ostream& os, char ofc) const
// print out all elements. ofc is deliminitor
{
	if ( empty() )
	 	os << "The list is empty";
	else
	{
		const_iterator itr = begin();
		
		os << *itr;
		
		while ( itr != --end() )
		{
			os << ofc;
			itr++;
			os << *itr;
		}
	}
}

template < typename T >
typename List< T >::iterator List< T >::begin()
// iterator to first element
{
	return iterator( head->next );
}

template < typename T >
typename List< T >::const_iterator List< T >::begin() const
// const iterator to first element
{
	return const_iterator( head->next );
}

template < typename T >
typename List< T >::iterator List< T >::end()
// end marker iterator (tail)
{
	return iterator( tail );
}

template < typename T >
typename List< T >::const_iterator List< T >::end() const
// const end marker iterator (tail)
{
	return const_iterator( tail );
}

template < typename T >
typename List< T >::iterator List< T >::insert(iterator itr, const T& val)
// insert val ahead of itr
{
	Node *p = itr.current;
	++theSize;
	return iterator( p->prev = p->prev->next = new Node{ val, p->prev, p } );
}

template < typename T >
typename List< T >::iterator List< T >::insert(iterator itr, T && val)
// move version of insert
{
	Node *p = itr.current;
	++theSize;
	return iterator( p->prev = p->prev->next = new Node{ std::move(val), p->prev, p } );
} 

template < typename T >
typename List< T >::iterator List< T >::erase(iterator itr)
// erase one element
{
	Node *p = itr.current;
	iterator retVal( p->next );
	p->prev->next = p->next;
	p->next->prev = p->prev;
	delete p;
	--theSize;
	return retVal;
}

template < typename T >
typename List< T >::iterator List< T >::erase(iterator start, iterator end)
// erase [start, end)
{
	for( iterator itr = start; itr != end; )
		itr = erase( itr );

	return end;
}     

template < typename T >
void List< T >::init()
// initialization (private function) initialize the member variables of list.
{
	theSize = 0;
	head = new Node;
	tail = new Node;
	head->next = tail;
	tail->prev = head;
}

// NON CLASS OVERLOADS

template <typename T>
bool operator==(const List<T> & lhs, const List<T> &rhs)
// overloading comparison operators
{

	if (lhs.size() != rhs.size())
		return false;
	else
	{
		typename List<T>::const_iterator itrL = lhs.begin();
		typename List<T>::const_iterator itrR = rhs.begin();

		while (itrL != lhs.end())
		{
			if (*itrL++ != *itrR++)
				return false;
		}
	
		return true;
	}

}

template <typename T>
bool operator!=(const List<T> & lhs, const List<T> &rhs)
// opposite of operator==()
{
	if (lhs == rhs)
		return false;
	else
		return true;
}

template <typename T>
std::ostream & operator<<(std::ostream &os, const List<T> &l)
// overloading output operator
{
	l.print(os);
	return os;
}

