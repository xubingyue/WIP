#ifndef __DEQUE_H__
#define __DEQUE_H__

#include <deque>

template<class _Type,
		class _Allocator = allocator<_Type>>
class Deque
{
public:
	typedef _Allocator allocator_type;
	typedef Deque<_Type, _Allocator> _Mytype;

	typedef typename std::deque<_Type,_Allocator>::value_type value_type;
	typedef typename std::deque<_Type,_Allocator>::size_type size_type;
	typedef typename std::deque<_Type,_Allocator>::difference_type difference_type;
	typedef typename std::deque<_Type,_Allocator>::pointer pointer;
	typedef typename std::deque<_Type,_Allocator>::const_pointer const_pointer;
	typedef typename std::deque<_Type,_Allocator>::reference reference;
	typedef typename std::deque<_Type,_Allocator>::const_reference const_reference;

	typedef typename std::deque<_Type,_Allocator>::iterator iterator;
	typedef typename std::deque<_Type,_Allocator>::const_iterator const_iterator;

	typedef typename std::deque<_Type,_Allocator>::reverse_iterator reverse_iterator;
	typedef typename std::deque<_Type,_Allocator>::const_reverse_iterator const_reverse_iterator;

	iterator begin() { return _data.begin(); }
	const_iterator begin() const { return _data.begin(); }

	iterator end() { return _data.end(); }
	const_iterator end() const { return _data.end(); }

	const_iterator cbegin() const { return _data.cbegin(); }
	const_iterator cend() const { return _data.cend(); }

	reverse_iterator rbegin() { return _data.rbegin(); }
	const_reverse_iterator rbegin() const { return _data.rbegin(); }

	reverse_iterator rend() { return _data.rend(); }
	const_reverse_iterator rend() const { return _data.rend(); }

	const_reverse_iterator crbegin() const { return _data.crbegin(); }
	const_reverse_iterator crend() const { return _data.crend(); }

	Deque():_data()
	{

	}

	explicit Deque(const _Allocator& _Al)
		: _data(_Al)
	{	// construct empty deque with allocator

	}

	explicit Deque(size_type _Count)
		: _data(size_type _Count)
	{	// construct from _Count * value_type()

	}

	Deque(size_type _Count, const value_type& _Val)
		: _data(_Count,_Val)
	{	// construct from _Count * _Val
	}


	Deque(size_type _Count, const value_type& _Val, const _Allocator& _Al)
		: _data(_Count,_Val,_Al)
	{	// construct from _Count * _Val with allocator

	}

	Deque(const _Mytype& _Right):_data(_Right)
	{

	}

	Deque(const _Mytype& _Right, const _Allocator& _Al)
		: _data(_Right,_Al)
	{	// construct by copying _Right
	}
	
	template<class _Iter>
	Deque(_Iter _First, _Iter _Last)
		: _data(_First,_Last)
	{	// construct from [_First, _Last)
	}

	template<class _Iter>
	Deque(_Iter _First, _Iter _Last, const _Allocator& _Al)
		: _data(_First,_Last,_Al)
	{	// construct from [_First, _Last) with allocator
	}

	Deque(_Mytype&& _Right)
		: _data(_Right)
	{	// construct by moving _Right
	}

	Deque(_Mytype&& _Right, const _Allocator& _Al)
		: _data(_Right,_Al)
	{	// construct by moving _Right
	}

	_Mytype& operator=(_Mytype&& _Right)
	{

	}

	~Deque() 
	{	// destroy the deque
	}

	_Mytype& operator=(const _Mytype& _Right)
	{

	}

	void shrink_to_fit()
	{
		_data.shrink_to_fit();
	}

	void resize(size_type _Newsize)
	{
		_data.resize(_Newsize);
	}

	void resize(size_type _Newsize, const value_type& _Val)
	{
		_data.resize(_Newsize,_Val);
	}

	size_type size() const 
	{	// return length of sequence
		return _data.size();
	}

	size_type max_size() const 
	{	// return maximum possible length of sequence
		return _data.max_size();
	}

	bool isempty() const 
	{	// test if sequence is empty
		return _data.empty();
	}

	allocator_type get_allocator() const 
	{	// return allocator object for values
		return _data.get_allocator();
	}

	const_reference at(size_type _Pos) const
	{
		return _data.at(_Pos);
	}

	reference at(size_type _Pos)
	{
		return _data.at(_Pos);
	}

	const_reference operator[](size_type _Pos) const
	{
		return _data[_Pos];
	}

	reference operator[](size_type _Pos)
	{
		return _data[_Pos];
	}

	reference front()
	{
		return _data.front();
	}

	const_reference front() const
	{
		return _data.front();
	}

	reference back()
	{
		return _data.back();
	}

	const_reference back() const
	{	// return last element of nonmutable sequence
		return _data.back();
	}

	void push_front(const value_type& _Val)
	{	// insert element at beginning
		_data.push_front(_Val);
	}

	void pop_front()
	{	// erase element at beginning
		_data.push_front();
	}

	void push_back(const value_type& _Val)
	{	// insert element at end
		_data.push_back(_Val);
	}

	void pop_back()
	{	// erase element at end
		return _data.pop_back();
	}

	//template<class _Iter>
	//	assign(_Iter _First, _Iter _Last)
	//{	// assign [_First, _Last), input iterators
	//	_data.assign(_First,_Last);
	//}

	void assign(size_type _Count, const value_type& _Val)
	{	// assign _Count * _Val
		_data.assign(_Count,_Val);
	}
	//////////////////////////////////////////////////////////////////////////
	iterator insert(const_iterator _Where,
		const value_type& _Val)
	{	
		return _data.insert(_Where,_Val);
	}


	iterator insert(const_iterator _Where, size_type _Count,
		const value_type& _Val)
	{	// insert _Count * _Val at _Where
		return _data.insert(_Where,_Count,_Val);
	}

	//template<class _Iter>
	//	insert(const_iterator _Where, _Iter _First, _Iter _Last)
	//{	// insert [_First, _Last) at _Where, input iterators
	//	return _data.insert(_Where,_First,_Last);
	//}

	iterator erase(const_iterator _Where)
	{	// erase element at _Where
		return _data.erase(_Where);
	}

	iterator erase(const_iterator _First_arg,
		const_iterator _Last_arg)
	{	// erase [_First, _Last)
		return _data.erase(_First_arg,-_Last_arg);
	}

	void clear() 
	{	// erase all
		_data.clear();
	}

	void swap(_Mytype& _Right)
	{	
		_data.swap(_Right);
	}


private:
	std::deque<_Type,_Allocator> _data;
};


#endif