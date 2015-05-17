#ifndef __WPLIST_H__
#define __WPLIST_H__

#include <list>

template<class _Ty>
class List
{
public:
	typedef List<_Ty> _Myt;

	typedef typename std::list<_Ty>::const_iterator const_iterator;
	typedef typename std::list<_Ty>::const_pointer  const_pointer;
	typedef typename std::list<_Ty>::const_reference const_reference;
	typedef typename std::list<_Ty>::reverse_iterator reverse_iterator;
	typedef typename std::list<_Ty>::const_reverse_iterator const_reverse_iterator;
	typedef typename std::list<_Ty>::reference reference;
	typedef typename std::list<_Ty>::iterator iterator;
	typedef typename std::list<_Ty>::pointer pointer;
	typedef typename std::list<_Ty>::size_type size_type;

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

	List<_Ty>()
	: _data()
	{

	}

	explicit List<_Ty>(size_type _Count)
		: _data(_Count)
	{	// construct list from _Count * _Ty()
	}

	List<_Ty>(size_type _Count, const _Ty& _Val)
		: _data(_Count,_Val)
	{	// construct list from _Count * _Val
	}

	List<_Ty>(const _Myt& _Right):_data(_Right)
	{

	}

	template<class _Iter>
	List<_Ty>(_Iter _First, _Iter _Last)
		: _data(_First,_Last)
	{

	}

	List<_Ty>(_Myt&& _Right)
		: _data(_Right)
	{	// construct list by moving _Right
	}
//////////////////////////////////////////////////////////////////////////
	List<_Ty>& operator=(const Vector<_Ty>& other)
	{
		if (this != &other) {
			clear();
			_data = other._data;
		}
		return *this;
	}

	/** Move assignment operator */
	List<_Ty>& operator=(List<_Ty>&& other)
	{
		if (this != &other) {
			clear();
			_data = std::move(other._data);
		}
		return *this;
	}
//////////////////////////////////////////////////////////////////////////
	~List<_Ty>()
	{
		clear();
	}

	void reserve(size_type n)
	{
		_data.reserve(n);
	}

	size_type size()
	{
		return _data.size();
	}

	size_type max_size() const
	{
		return _data.max_size();
	}

	bool is_empty() const
	{
		return _data.empty();
	}

	void pop_back()
	{
		_data.pop_back();
	}

	void pop_front()
	{
		_data.pop_front();
	}

	void push_back(_Ty object)
	{
		_data.push_back(object);
	}

	void push_back(const _Myt& other)
	{
		for(const auto &obj : other) {
			_data.push_back(obj);
		}
	}

	void push_front(const List<_Ty>& other)
	{
		for(const auto &obj : other) {
			_data.push_back(obj);
		}
	}

	void push_front(_Ty object)
	{
		_data.push_front(object);
	}

	void remove(const List<_Ty>& other)
	{
		_data.remove(other);
	}

	void resize(size_type _Newsize) 
	{
		_data.resize(_Newsize);
	}

	void resize(size_type _Newsize, const List<_Ty>& value)
	{
		_data.resize(_Newsize,value);
	}

	void reverse()
	{
		std::reverse( std::begin(_data), std::end(_data) );
	}

	void  sort()
	{
		_data.sort();
	}

	iterator insert(const_iterator _Where, const List<_Ty>& _Val)
	{
		return _data.insert(_Where,_Val);
	}

	iterator insert(const_iterator _Where, size_type _Count, const List<_Ty>& _Val)
	{
		return _data.insert(_Where,_Count,_Val);
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
	{	
		return _data.back();
	}

	void assign(size_type _Count, const List<_Ty>& _Val)
	{	
		_data.assign(_Count,_Val);
	}

	void clear()
	{
		_data.clear();

	}


	/*T at(size_type index) const
	{
		return _data.at;
	}*/

	bool equals(const List<_Ty> &other)
	{
		size_type s = this->size();
		if (s != other.size())
			return false;

		for (size_type i = 0; i < s; i++)
		{
			if (this->at(i) != other.at(i))
			{
				return false;
			}
		}
		return true;
	}

	const_iterator find(_Ty object) const
	{
		return std::find(_data.begin(), _data.end(), object);
	}

	iterator find(_Ty object)
	{
		return std::find(_data.begin(), _data.end(), object);
	}

	size_type getIndex(_Ty object) const
	{
		auto iter = std::find(_data.begin(), _data.end(), object);
		if (iter != _data.end())
			return iter - _data.begin();

		return -1;
	}


private:
	std::list<_Ty> _data;
};


#endif