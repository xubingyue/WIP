#ifndef __WP_SET_H__
#define __WP_SET_H__


#include <set>

template<class _Kty,
class _Pr = less<_Kty>,
class _Alloc = allocator<_Kty> >
class Set
{
public:
	typedef Set<_Kty, _Pr, _Alloc> _Myt;
	typedef _Kty key_type;
	typedef _Pr key_compare;
	typedef typename std::set<_Kty, _Pr, _Alloc>::_Pairib _Pairib;
	typedef typename std::set<_Kty, _Pr, _Alloc>::value_compare value_compare;
	typedef typename std::set<_Kty, _Pr, _Alloc>::allocator_type allocator_type;
	typedef typename std::set<_Kty, _Pr, _Alloc>::size_type size_type;
	typedef typename std::set<_Kty, _Pr, _Alloc>::difference_type difference_type;
	typedef typename std::set<_Kty, _Pr, _Alloc>::pointer pointer;
	typedef typename std::set<_Kty, _Pr, _Alloc>::const_pointer const_pointer;
	typedef typename std::set<_Kty, _Pr, _Alloc>::reference reference;
	typedef typename std::set<_Kty, _Pr, _Alloc>::const_reference const_reference;
	typedef typename std::set<_Kty, _Pr, _Alloc>::iterator iterator;
	typedef typename std::set<_Kty, _Pr, _Alloc>::const_iterator const_iterator;
	typedef typename std::set<_Kty, _Pr, _Alloc>::reverse_iterator reverse_iterator;
	typedef typename std::set<_Kty, _Pr, _Alloc>::const_reverse_iterator const_reverse_iterator;
	typedef typename std::set<_Kty, _Pr, _Alloc>::value_type value_type;

	Set<_Kty, _Pr, _Alloc>(): _data()
	{	// construct empty set from defaults
	}

	explicit Set<_Kty, _Pr, _Alloc>(const allocator_type& _Al)
		: _data(_Al)
	{	// construct empty set from defaults, allocator
	}

	Set<_Kty, _Pr, _Alloc>(const _Myt& _Right):_data(_Right)
	{

	}

	Set<_Kty, _Pr, _Alloc>(const _Myt& _Right, const allocator_type& _Al)
		:_data(_Right, _Al)
	{	// construct set by copying _Right, allocator
	}

	explicit Set<_Kty, _Pr, _Alloc>(const key_compare& _Pred)
		:_data(_Pred)
	{	// construct empty set from comparator
	}

	Set<_Kty, _Pr, _Alloc>(const key_compare& _Pred, const allocator_type& _Al)
		: _Mybase(_Pred, _Al)
	{	// construct empty set from comparator and allocator
	}

	template<class _Iter>
	Set<_Kty, _Pr, _Alloc>(_Iter _First, _Iter _Last)
		: _data(_First,_Last)
	{	// construct set from [_First, _Last), defaults
	}

	template<class _Iter>
	Set<_Kty, _Pr, _Alloc>(_Iter _First, _Iter _Last,
		const key_compare& _Pred)
		: _data(_First,_Last,_Pred)
	{	// construct set from [_First, _Last), comparator
	}

	template<class _Iter>
	Set<_Kty, _Pr, _Alloc>(_Iter _First, _Iter _Last,
		const key_compare& _Pred, const allocator_type& _Al)
		: _data(_First,_Last,_Pred,_Al)
	{	// construct set from [_First, _Last), defaults, and allocator
	}

	_Myt& operator=(const _Myt& _Right)
	{	// assign by copying _Right
		_data::operator=(_Right);
		return (*this);
	}

	_Myt(_Myt&& _Right)
		: _data(std::move(_Right))
	{	// construct set by moving _Right
	}

	_Myt(_Myt&& _Right, const allocator_type& _Al)
		: _data(std::move(_Right), _Al)
	{	// construct set by moving _Right, allocator
	}

	_Myt& operator=(_Myt&& _Right)
	{	// assign by moving _Right
		_data::operator=(std::move(_Right));
		return (*this);
	}

	_Pairib insert(value_type&& _Val)
	{	// insert a key value
		return _data.insert(_Val);
	}

	iterator insert(const_iterator _Where, value_type&& _Val)
	{	// insert a key value, with hint
		return _data.insert(_Where,_Val);
	}

	void swap(_Myt& _Right)
	{	// exchange contents with non-movable _Right
		_data::swap(_Right);
	}

	_Pairib insert(const value_type& _Val)
	{	// insert a key value
		return (_data::insert(_Val));
	}

	iterator insert(const_iterator _Where, const value_type& _Val)
	{	// insert a key value, with hint
		return (_data::insert(_Where, _Val));
	}

	template<class _Iter>
	void insert(_Iter _First, _Iter _Last)
	{	// insert [_First, _Last)
		_data.insert(_First,_Last);
	}

private:
	std::set<_Kty, _Pr, _Alloc> _data;

};


template<class _Kty,
class _Pr,
class _Alloc> inline
	void swap(Set<_Kty, _Pr, _Alloc>& _Left,
	Set<_Kty, _Pr, _Alloc>& _Right)
{	// swap _Left and _Right sets
	_Left.swap(_Right);
}


#endif