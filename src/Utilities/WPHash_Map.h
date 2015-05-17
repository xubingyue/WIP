#ifndef __WPHASH_MAP_H__
#define __WPHASH_MAP_H__

#include <hash_map>
using namespace stdext;

template<class _Kty,class _Ty,
class _Tr = hash_compare<_Kty,less<_Kty>>,
class _Alloc = allocator<pair<const _Kty, _Ty> >>
class Hash_Map
{
public:
	typedef Hash_Map<_Kty,_Ty,_Tr,_Alloc> _Myt;
	typedef _Kty key_type;
	typedef _Ty mapped_type;
	typedef _Ty referent_type;
	typedef _Tr key_compare;
	typedef typename hash_map<_Kty,_Ty,_Tr,_Alloc>::allocator_type allocator_type;
	typedef typename hash_map<_Kty,_Ty,_Tr,_Alloc>::allocator_type allocator_type;
	typedef typename hash_map<_Kty,_Ty,_Tr,_Alloc>::const_iterator const_iterator;
	typedef typename hash_map<_Kty,_Ty,_Tr,_Alloc>::const_local_iterator const_local_iterator;
	typedef typename hash_map<_Kty,_Ty,_Tr,_Alloc>::const_pointer const_pointer; 
	typedef typename hash_map<_Kty,_Ty,_Tr,_Alloc>::const_reference const_reference;
	typedef typename hash_map<_Kty,_Ty,_Tr,_Alloc>::const_reverse_iterator const_reverse_iterator;
	typedef typename hash_map<_Kty,_Ty,_Tr,_Alloc>::difference_type difference_type;
	typedef typename hash_map<_Kty,_Ty,_Tr,_Alloc>::iterator iterator;

	//typedef typename hash_map<_Kty, _Ty, _Tr, _Alloc>::key_type key_type;
	typedef typename hash_map<_Kty,_Ty,_Tr,_Alloc>::local_iterator local_iterator;
	//typedef typename hash_map<_Kty, _Ty, _Tr, _Alloc>::mapped_type mapped_type;
	typedef typename hash_map<_Kty,_Ty,_Tr,_Alloc>::pointer pointer;
	typedef typename hash_map<_Kty,_Ty,_Tr,_Alloc>::reference reference;
	//typedef typename hash_map<_Kty, _Ty, _Tr, _Alloc>::referent_type referent_type;
	typedef typename hash_map<_Kty,_Ty,_Tr,_Alloc>::size_type size_type;
	typedef typename hash_map<_Kty,_Ty,_Tr,_Alloc>::reverse_iterator reverse_iterator;
	//typedef typename hash_map<_Kty,_Ty>::allocator_type allocator_type;
	typedef typename hash_map<_Kty,_Ty,_Tr,_Alloc>::value_type value_type;
	typedef typename hash_map<_Kty,_Ty,_Tr,_Alloc>::value_compare value_compare;
	Hash_Map():_data()
	{
	}

	explicit Hash_Map(const allocator_type& _Al):_data(_Al)
	{
	}

	Hash_Map(const _Myt& _Right):_data(_Right)
	{
	}

	Hash_Map(const _Myt& _Right, const allocator_type& _Al):_data(_Right,_Al)
	{
	}

	explicit Hash_Map(const key_compare& _Traits)
		: _data(_Traits)
	{	// construct empty map from comparator
	}

	Hash_Map(const key_compare& _Traits, const allocator_type& _Al)
		: _data(key_compare,_Al)
	{	// construct empty map from comparator and allocator
	}

	template<class _Iter>
	Hash_Map(_Iter _First, _Iter _Last)
		: _data(_First,_Last)
	{	// construct map from sequence, defaults
	}

	template<class _Iter>
	Hash_Map(_Iter _First, _Iter _Last,
		const key_compare& _Traits)
		: _data(_First,_Last,_Traits)
	{	// construct map from sequence, comparator
	}

	template<class _Iter>
	Hash_Map(_Iter _First, _Iter _Last,
		const key_compare& _Traits,
		const allocator_type& _Al)
		: _data(_First,_Last,_Traits,_Val)
	{	// construct map from sequence, comparator, and allocator
	}

	_Myt& operator=(const _Myt& _Right)
	{	// assign by copying _Right
		_data::operator=(_Right);
		return (*this);
	}

	Hash_Map(_Myt&& _Right)
		: _data(std::move(_Right))
	{	// construct map by moving _Right
	}

	Hash_Map(_Myt&& _Right, const allocator_type& _Al)
		:_data(std::move(_Right),_Al)
	{	// construct map by moving _Right, allocator
	}

	_Myt& operator=(_Myt&& _Right)
	{	// assign by moving _Right
		return _data.operator =_Right;
	}

	mapped_type& operator[](key_type&& _Keyval)
	{	// find element matching _Keyval or insert with default mapped
		return _data[_Keyval];
	}

	void swap(_Myt& _Right)
	{	// exchange contents with non-movable _Right
		_data.swap(_Right);
	}

	//mapped_type& operator[](const key_type& _Keyval)
	//{	// find element matching _Keyval or insert with default mapped
	//	iterator _Where = this->lower_bound(_Keyval);
	//	if (_Where == this->end())
	//		_Where = this->insert(
	//		pair<key_type, mapped_type>(
	//		_Keyval,
	//		mapped_type())).first;
	//	return (_Where->second);
	//}
	mapped_type& operator[](const key_type& _Keyval)
	{	// find element matching _Keyval or insert with default mapped
		return _data[_Keyval];
	}


	mapped_type& at(const key_type& _Keyval)
	{	
		return _data.at(_Keyval); 
	}

	const mapped_type& at(const key_type& _Keyval) const
	{	
		return _data.at(_Keyval);
	}

	//template<class _Kty,
	//class _Ty,
	//class _Tr,
	//class _Alloc> inline
	//	void swap(Hash_Map<_Kty, _Ty, _Tr, _Alloc>& _Left,
	//	Hash_Map<_Kty, _Ty, _Tr, _Alloc>& _Right)
	//{	// swap _Left and _Right hash_maps
	//	_Left.swap(_Right);
	//}

	//template<class _Kty,
	//class _Ty,
	//class _Tr,
	//class _Alloc> inline
	//	bool operator==(
	//	const hash_map<_Kty, _Ty, _Tr, _Alloc>& _Left,
	//	const hash_map<_Kty, _Ty, _Tr, _Alloc>& _Right)
	//{	// test for hash_map equality
	//	return (_STD _Hash_equal(_Left, _Right));
	//}

	iterator begin() { return _data.begin(); }
	const_iterator begin() const { return _data.begin(); }

	iterator end() { return _data.end(); }
	const_iterator end() const { return _data.end(); }

	const_iterator cbegin() const { return _data.cbegin(); }
	const_iterator cend() const { return _data.cend(); }

	const_reverse_iterator crbegin() const { return _data.crbegin(); }
	const_reverse_iterator crend() const { return _data.crend(); }

	size_type count()
	{
		return _data.count();
	}

	bool is_empty()
	{
		return _data.empty();
	}

	iterator erase(iterator _Where)
	{
		return _data.erase(_Where);
	}
	iterator erase(iterator _First,iterator _Last)
	{
		return _data.erase(_First,_Last);
	}
	size_type erase(const key_type& _Key)
	{
		return _data.erase(_Key);
	}

	iterator find(const key_type& _Key)
	{
		return _data.find(_Key);
	}

	const_iterator find(const key_type& _Key) const
	{
		return _data.find(_Key);
	}

	/*allocator get_allocator( ) const
	{
		return _data.get_allocator();
	}*/

	pair <iterator, bool> insert(const value_type& _Val)
	{
		return _data.insert(_Val);
	}

	iterator insert(const_iterator _Where,const value_type& _Val)
	{
		return _data.insert(_Where,_Val);
	}

	template<class InputIterator>
	void insert(InputIterator _First,InputIterator _Last)
	{
		_data.insert(_First,_Last);
	}

	template<class ValTy>
	pair <iterator, bool> insert(ValTy&& _Val)
	{
		return _data.insert(_Val);
	}

	template<class ValTy>
	iterator insert(const_iterator _Where,ValTy&& _Val)
	{
		return _data.insert(_Where,_Val);
	}

	key_compare key_comp() const
	{
		return _data.key_comp();
	}

	iterator lower_bound(const key_type& _Key)
	{
		return _data.lower_bound(_Key);
	}

	const_iterator lower_bound(const key_type& _Key) const
	{
		return _data.lower_bound(_Key);
	}

	size_type max_size( ) const
	{
		return _data.max_size();
	}

	size_type size( ) const
	{
		return _data.size();
	}

	iterator upper_bound(const key_type& _Key)
	{
		return _data.upper_bound(_Key);
	}
	const_iterator upper_bound(const key_type& _Key) const
	{
		return _data.upper_bound(_Key);
	}

	value_compare value_comp( ) const
	{
		return _data.value_comp();
	}

private:
	std::hash_map<_Kty,_Ty,_Tr,_Alloc> _data;
};

#endif;