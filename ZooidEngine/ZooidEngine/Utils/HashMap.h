#ifndef  __ZE_HASHMAP__
#define __ZE_HASHMAP__

#include "Array.h"
#include "String.h"

#define HASH_MAP_LINEAR_PROBING 1

// #TODO Quadratic probing need more advance resizing, since it wont guarantee find the empty spot if size > size / 2, esp if size is not prime
#define HASH_MAP_QUADRATIC_PROBING 2 

#define HASH_MAP_PROBING HASH_MAP_LINEAR_PROBING

namespace ZE {

	template<class K, class V>
	struct HashKeyValue
	{
		ZE::Int8 m_occupied = 0;
		K m_key;
		uint32_t m_hashKey;
		V m_value;
	};

	template<class K>
	class HashFunc
	{
	public:
		ZE::UInt32 operator()(const K& Object)
		{
			return reinterpret_cast<ZE::UInt32> Object;
		}
	};

	template<>
	class HashFunc<String>
	{
	public:
		ZE::UInt32 operator()(String& object)
		{
			return StringFunc::Hash(object.c_str(), StringFunc::Length(object.c_str()));
		}
	};

	template<>
	class HashFunc<ZE::Int32>
	{
	public:
		ZE::UInt32 operator()(const ZE::Int32& object)
		{
			return object;
		}
	};

	template<>
	class HashFunc<ZE::UInt32>
	{
	public:
		ZE::UInt32 operator()(const ZE::UInt32& object)
		{
			return object;
		}
	};

	template<>
	class HashFunc<const char *>
	{
		ZE::UInt32 operator()(const char* object)
		{
			return StringFunc::Hash(object, StringFunc::Length(object));
		}
	};

	template<class K, class V, class Func = HashFunc<K>>
	class HashMap : public Array<HashKeyValue<K,V>, true>
	{

	public:
		bool put_internal(const K& key, const V& value)
		{
			Func func;
			ZE::UInt32 hashValue = func(key);
			int initial_index = hashValue % m_capacity;
			int index = initial_index;

			// TODO Check if the index currently occupied
			// TODO Probing until find empty spot
			// Question? How to check if the spot is empty
#if HASH_MAP_PROBING == HASH_MAP_QUADRATIC_PROBING
			int q_offset = 1;
#endif
			while (get(index).m_occupied == 1)
			{
				// Try to reposition the current index for better performance
				HashKeyValue<K, V>& hashKeyValue = get(index);
				hashKeyValue.m_occupied = 0;
				m_length--;
				put_internal(hashKeyValue.m_key, hashKeyValue.m_value);

				if (get(index).m_occupied != 1) { break; }

#if HASH_MAP_PROBING == HASH_MAP_LINEAR_PROBING
				index = (index + 1) % m_capacity;
#elif HASH_MAP_PROBING == HASH_MAP_QUADRATIC_PROBING
				index = (initial_index + (q_offset * q_offset)) % m_capacity;
				q_offset++;
#endif
			}

			HashKeyValue<K, V>& hashKeyValue = get(index);
			hashKeyValue.m_occupied = 1;
			m_length++;
			hashKeyValue.m_hashKey = hashValue;
			hashKeyValue.m_key = key;
			hashKeyValue.m_value = value;

			return true;
		}

		bool put(const K& key, const V& value)
		{
			int index = 0;
			if (hasKey_internal(key, index))
			{
				HashKeyValue<K, V>& hashKeyValue = get(index);
				hashKeyValue.m_value = value;
				return true;
			}

			if (m_capacity == 0)
			{
				reset(1);
			}
			else if (m_capacity <= m_length + 1)
			{
				resize(m_capacity * 2);
			}

			return put_internal(key, value);
		}

		V& operator[](const K& key)
		{
			int index = 0;
			if (hasKey_internal(key, index))
			{
				return get(index).m_value;
			}

			// if nothing, then put
			V temp;
			put(key, temp);
			hasKey_internal(key, index);

			return get(index).m_value;
		}

		bool hasKey_internal(const K& key, int& index)
		{
			int currentCapacity = m_capacity;
			Func func;
			ZE::UInt32 hashValue = func(key);
			while (currentCapacity > 0)
			{
				int initial_index = hashValue % currentCapacity;
				index = initial_index;

				int offset = 1;
				
				while ((get(index).m_occupied == 0 || get(index).m_hashKey != hashValue) && offset < currentCapacity)
				{
#if HASH_MAP_PROBING == HASH_MAP_LINEAR_PROBING
					index = (index + 1) % currentCapacity;
#elif HASH_MAP_PROBING == HASH_MAP_QUADRATIC_PROBING
					index = (initial_index + (offset * offset)) % currentCapacity;
#endif
					offset++;
				}

				if (get(index).m_occupied == -1)
				{
					// is deleted
					index = -1;
					return false;
				}

				if (get(index).m_hashKey == hashValue)
				{
					return true;
				}

				if (offset >= currentCapacity) // already search whole capacity
				{
					return false;
				}

				currentCapacity /= 2;
			}

			index = -1;

			return false;
		}

		bool hasKey(const K& key)
		{
			int index = 0;
			return hasKey_internal(key, index);
		}

		void erase(const K& key)
		{
			int index = 0;
			if (hasKey_internal(key, index))
			{
				get(index).m_occupied = -1;
			}
		}

		Array<K, true> getKeys()
		{
			Array<K, true> keys;
			for (int i = 0; i < m_capacity; i++)
			{
				if (get(i).m_occupied == 1)
				{
					keys.push_back(get(i).m_key);
				}
			}

			return keys;
		}
	};

	template<class V>
	class HashMap<String, V, HashFunc<String>> : public Array<HashKeyValue<String, V>, true>
	{

	public:

		V& operator[](const char* key)
		{
			int index = 0;
			if (hasKey_internal(key, index))
			{
				return get(index).m_value;
			}

			// if nothing put
			V temp;
			put(key, temp);
			hasKey_internal(key, index);

			return get(index).m_value;
		}

		bool put_internal(const char* key, const V& value)
		{
			ZE::UInt32 hashValue = StringFunc::Hash(key, StringFunc::Length(key));
			int initial_index = hashValue % m_capacity;
			int index = initial_index;

			// TODO Check if the index currently occupied
			// TODO Probing until find empty spot
			// Question? How to check if the spot is empty
#if HASH_MAP_PROBING == HASH_MAP_QUADRATIC_PROBING
			int q_offset = 1;
#endif
			while (get(index).m_occupied == 1)
			{
				// Try to reposition the current index for better performance
				HashKeyValue<String, V>& hashKeyValue = get(index);
				hashKeyValue.m_occupied = 0;
				m_length--;
				put_internal(hashKeyValue.m_key.c_str(), hashKeyValue.m_value);
				
				if(!get(index).m_occupied) { break; }

#if HASH_MAP_PROBING == HASH_MAP_LINEAR_PROBING
				index = (index + 1) % m_capacity;
#elif HASH_MAP_PROBING == HASH_MAP_QUADRATIC_PROBING
				index = (initial_index + (q_offset * q_offset)) % m_capacity;
				q_offset++;
#endif
			}

			HashKeyValue<String, V>& hashKeyValue = get(index);
			hashKeyValue.m_occupied = 1;
			m_length++;
			hashKeyValue.m_hashKey = hashValue;
			hashKeyValue.m_key = key;
			hashKeyValue.m_value = value;

			return true;
		}

		bool put(const char* key, const V& value)
		{
			int index = 0;
			if (hasKey_internal(key, index))
			{
				HashKeyValue<String, V>& hashKeyValue = get(index);
				hashKeyValue.m_value = value;
				return true;
			}

			if (m_capacity == 0)
			{
				reset(1);
			}
			else if (m_capacity <= m_length + 1)
			{
				resize(m_capacity * 2);
			}

			return put_internal(key, value);
		}

		bool hasKey_internal(const char* key, int& index)
		{
			int currentCapacity = m_capacity;
			ZE::UInt32 hashValue = StringFunc::Hash(key, StringFunc::Length(key));
			while (currentCapacity > 0)
			{
				int initial_index = hashValue % currentCapacity;
				index = initial_index;

				int offset = 1;

				while ((get(index).m_occupied == 0 || get(index).m_hashKey != hashValue) && offset < currentCapacity)
				{
#if HASH_MAP_PROBING == HASH_MAP_LINEAR_PROBING
					index = (index + 1) % currentCapacity;
#elif HASH_MAP_PROBING == HASH_MAP_QUADRATIC_PROBING
					index = (initial_index + (offset * offset)) % currentCapacity;
#endif
					offset++;
				}

				if (get(index).m_occupied == -1)
				{
					// is deleted
					index = -1;
					return false;
				}

				if (get(index).m_hashKey == hashValue)
				{
					return true;
				}

				if (offset >= currentCapacity) // already search whole capacity
				{
					index = -1;
					return false;
				}

				currentCapacity /= 2;
			}

			index = -1;

			return false;
		}

		bool hasKey(const char* key)
		{
			int index = 0;
			return hasKey_internal(key, index);
		}

		void erase(const char* key)
		{
			int index = 0;
			if (hasKey_internal(key, index))
			{
				get(index).m_occupied = -1;
			}
		}

		Array<String, true> getKeys()
		{
			Array<String, true> keys;
			for (int i = 0; i < m_capacity; i++)
			{
				if (get(i).m_occupied == 1)
				{
					keys.push_back(get(i).m_key);
				}
			}

			return keys;
		}
	};


}
#endif // ! __ZE_HASHMAP__
