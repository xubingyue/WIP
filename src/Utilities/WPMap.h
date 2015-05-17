#ifndef __WPMAP_H__
#define __WPMAP_H__

#define USE_STD_UNORDERED_MAP 1

#include <vector>

#if USE_STD_UNORDERED_MAP
#include <unordered_map>
#else
#include <map>
#endif

template <class K, class V>
class  Map
{
public:
    // ------------------------------------------
    // Iterators
    // ------------------------------------------
#if USE_STD_UNORDERED_MAP
    typedef std::unordered_map<K, V> RefMap;
#else
    typedef std::map<K, V> RefMap;
#endif
    
    typedef typename RefMap::iterator iterator;
    typedef typename RefMap::const_iterator const_iterator;
	typedef typename RefMap::size_type size_type;
    typedef typename RefMap::mapped_type mapped_type;
	typedef typename RefMap::key_type key_type;

    iterator begin() { return _data.begin(); }
    const_iterator begin() const { return _data.begin(); }
    
    iterator end() { return _data.end(); }
    const_iterator end() const { return _data.end(); }
    
    const_iterator cbegin() const { return _data.cbegin(); }
    const_iterator cend() const { return _data.cend(); }
    
    /** Default constructor */
    Map<K, V>()
    : _data()
    {
    }
    
    /** Contructor with capacity */
    explicit Map<K, V>(size_type capacity)
    : _data()
    {
        _data.reserve(capacity);
    }
    
    /** Copy constructor */
    Map<K, V>(const Map<K, V>& other)
    {
        _data = other._data;
    }
    
    /** Move constructor */
    Map<K, V>(Map<K, V>&& other)
    {
        _data = std::move(other._data);
    }
    
    /** Destructor
     *  It will release all objects in map.
     */
    ~Map<K, V>()
    {
        clear();
    }
    
    /** Sets capacity of the map */
    void reserve(size_type capacity)
    {
#if USE_STD_UNORDERED_MAP
        _data.reserve(capacity);
#endif
    }
    
    /** Returns the number of buckets in the Map container. */
    size_type bucketCount() const
    {
#if USE_STD_UNORDERED_MAP
        return _data.bucket_count();
#else
        return 0;
#endif
    }
    
    /** Returns the number of elements in bucket n. */
    size_type bucketSize(size_type n) const
    {
#if USE_STD_UNORDERED_MAP
        return _data.bucket_size(n);
#else
        return 0;
#endif
    }
    
    /** Returns the bucket number where the element with key k is located. */
    size_type bucket(const K& k) const
    {
#if USE_STD_UNORDERED_MAP
        return _data.bucket(k);
#else
        return 0;
#endif
    }
    
    /** The number of elements in the map. */
   size_type size() const
    {
        return _data.size();
    }
    
    /** Returns a bool value indicating whether the map container is empty, i.e. whether its size is 0.
     *  @note This function does not modify the content of the container in any way.
     *        To clear the content of an array object, member function unordered_map::clear exists.
     */
    bool is_empty() const
    {
        return _data.empty();
    }
    
	mapped_type& operator[](const key_type& _Keyval)
	{
		return _data[_Keyval];
	}

    /** Returns all keys in the map */
    std::vector<K> keys() const
    {
        std::vector<K> keys;

        if (!_data.empty())
        {
            keys.reserve(_data.size());
            
            for (auto iter = _data.cbegin(); iter != _data.cend(); ++iter)
            {
                keys.push_back(iter->first);
            }
        }
        return keys;
    }
    
    /** Returns all keys that matches the object */
    std::vector<K> keys(V object) const
    {
        std::vector<K> keys;
        
        if (!_data.empty())
        {
            keys.reserve(_data.size() / 10);
            
            for (auto iter = _data.cbegin(); iter != _data.cend(); ++iter)
            {
                if (iter->second == object)
                {
                    keys.push_back(iter->first);
                }
            }
        }
        
        keys.shrink_to_fit();
        
        return keys;
    }
    
    /** @brief Returns a reference to the mapped value of the element with key k in the map.
     *  @note If key does not match the key of any element in the container, the function return nullptr.
     *  @param key Key value of the element whose mapped value is accessed.
     *       Member type K is the keys for the elements in the container. defined in Map<K, V> as an alias of its first template parameter (Key).
     */
    const V at(const K& key) const
    {
        auto iter = _data.find(key);
        if (iter != _data.end())
            return iter->second;
        return nullptr;
    }
    
    V at(const K& key)
    {
        auto iter = _data.find(key);
        if (iter != _data.end())
            return iter->second;
        return 0;
    }
    
    /** @brief Searches the container for an element with 'key' as key and returns an iterator to it if found,
     *         otherwise it returns an iterator to Map<K, V>::end (the element past the end of the container).
     *  @param key Key to be searched for.
     *         Member type 'K' is the type of the keys for the elements in the container,
     *         defined in Map<K, V> as an alias of its first template parameter (Key).
     *
     */
    const_iterator find(const K& key) const
    {
        return _data.find(key);
    }
    
    iterator find(const K& key)
    {
        return _data.find(key);
    }
    
    /** @brief Inserts new elements in the map.
     *  @note If the container has already contained the key, this function will erase the old pair(key, object)  and insert the new pair.
     *  @param key The key to be inserted.
     *  @param object The object to be inserted.
     */
    void insert(const K& key, V object)
    {
        erase(key);
        _data.insert(std::make_pair(key, object));
    }
    
    /** @brief Removes an element with an iterator from the Map<K, V> container.
     *  @param position Iterator pointing to a single element to be removed from the Map<K, V>.
     *         Member type const_iterator is a forward iterator type.
     */
    iterator erase(const_iterator position)
    {
        position->second->release();
        return _data.erase(position);
    }
    
    /** @brief Removes an element with an iterator from the Map<K, V> container.
     *  @param k Key of the element to be erased.
     *         Member type 'K' is the type of the keys for the elements in the container,
     *         defined in Map<K, V> as an alias of its first template parameter (Key).
     */
    size_t erase(const K& k)
    {
		/*
		//from cocos2dx
        auto iter = _data.find(k);
        if (iter != _data.end())
        {
            iter->second->release();
            _data.erase(iter);
            return 1;
        }
        
        return 0;
		*/
		return _data.erase(k);
    }
    
    /** @brief Removes some elements with a vector which contains keys in the map.
     *  @param keys Keys of elements to be erased.
     */
    void erase(const std::vector<K>& keys)
    {
        for(const auto &key : keys) {
            this->erase(key);
        }
    }
    
    /** All the elements in the Map<K,V> container are dropped:
     *  their reference count will be decreased, and they are removed from the container,
     *  leaving it with a size of 0.
     */
    void clear()
    {
        _data.clear();
    }
    
    /** @brief Gets a random object in the map
     *  @return Returns the random object if the map isn't empty, otherwise it returns nullptr.
     */
    V getRandomObject() const
    {
        if (!_data.empty())
        {
            size_type randIdx = rand() % _data.size();
            const_iterator randIter = _data.begin();
            std::advance(randIter , randIdx);
            return randIter->second;
        }
        return nullptr;
    }
    
    /** Copy assignment operator */
    Map<K, V>& operator= ( const Map<K, V>& other )
    {
        if (this != &other) {
            clear();
            _data = other._data;
        }
        return *this;
    }
    
    /** Move assignment operator */
    Map<K, V>& operator= ( Map<K, V>&& other )
    {
        if (this != &other) {
            clear();
            _data = std::move(other._data);
        }
        return *this;
    }
    
private:

   RefMap _data;
};

#endif /* __WPMAP_H__ */
