#ifndef __WP_STACK_H__
#define __WP_STACK_H__

#include <stack>


template<class _Ty,class _Container = deque<_Ty>>
class Stack
{
public:
	typedef Stack<_Ty,_Container> _Myt;
//	typedef _Container container_type;
	typedef typename std::stack<_Ty,_Container>::value_type value_type;
	typedef typename std::stack<_Ty,_Container>::size_type size_type;
	typedef typename std::stack<_Ty,_Container>::reference reference;
	typedef typename std::stack<_Ty,_Container>::const_reference const_reference;
	
	Stack():_data()
	{

	}

	Stack(const _Myt& _Right)
		: _data(_Right)
	{	// construct by copying _Right
	}

	explicit Stack(const _Container& _Cont)
		: c(_Cont)
	{	// construct by copying specified container
	}

	_Myt& operator=(const _Myt& _Right)
	{	// assign by copying _Right
		c = _Right._data;
		return (*this);
	}

	//////////////////////////////////////////////////////////////////////////
	template<class _Allocator>
	explicit Stack(const _Allocator& _Al)
		: _data(_Al)
	{	// construct with allocator
	}

	template<class _Allocator>
	Stack(const _Myt& _Right, const _Allocator& _Al)
		: _data(_Right,_Al)
	{	// construct by copying specified container
	}

	template<class _Allocator>
	Stack(const _Container& _Cont, const _Allocator& _Al)
		: _data(_Cont, _Al)
	{	// construct by copying specified container
	}

	Stack(_Myt&& _Right)
		: _data(std::move(_Right._data))
	{	// construct by moving _Right
	}

	explicit Stack(_Container&& _Cont)
		: _data(std::move(_Cont))
	{	// construct by moving specified container
	}

	template<class _Allocator>
	Stack(_Myt&& _Right, const _Allocator& _Al)
		: _data(std::move(_Right._data), _Al)
	{	// construct by moving specified container
	}

	template<class _Allocator>
	Stack(_Container&& _Cont, const _Allocator& _Al)
		: _data(_STD move(_Cont), _Al)
	{	// construct by moving specified container
	}

	_Myt& operator=(_Myt&& _Right)
	{	// assign by moving _Right
		_data = std::move(_Right._data);
		return (*this);
	}

	void push(value_type&& _Val)
	{	// insert element at beginning
		_data.push(std::move(_Val));
	}

	bool empty() const
	{	// test if stack is empty
		return (_data.empty());
	}

	size_type size() const
	{	// test length of stack
		return (_data.size());
	}

	reference top()
	{	// return last element of mutable stack
		return _data.top();
	}

	const_reference top() const
	{	// return last element of nonmutable stack
		return _data.top();
	}

	void push(const value_type& _Val)
	{	// insert element at end
		_data.push(_Val);
	}

	void pop()
	{	// erase last element
		_data.pop();
	}

	const _Container& _Get_container() const
	{	// get reference to container
		return (_data);
	}

	void swap(_Myt& _Right)
	{	// exchange contents with _Right
		_data.swap(_Right);
	}


private:
	std::stack<_Ty,_Container> _data;
};


















#endif