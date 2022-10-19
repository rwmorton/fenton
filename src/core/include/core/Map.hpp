#pragma once

#include <list>

namespace fenton
{

namespace core
{

//
// basic and limited custom map to allow direct equality comparision (==) on arbitrary keys
// not as efficient as std::map which uses a binary tree, but cannot use == comparision.
//
// if a custom type is used as the key then the == operator must be overloaded.
//
template<typename Key,typename Value>
class Map
{
    struct Pair
    {
        Key key;
        Value value;

        Pair(Key k,Value v) : key(k),value(v) {}
    };

    using List = std::list<Pair>;
    using ListIter = std::list<Pair>::const_iterator;

    private:
        List m_pairs;
    public:
        // prevent copies
        Map(const Map&) = delete;
        Map& operator=(const Map&) = delete;

        Map() {}

        const size_t size() const
        {
            return m_pairs.size();
        }

        const bool insert(const Key& key,const Value& value)
        {
            // first search for existing key
            ListIter iter = m_pairs.begin();
            while(iter != m_pairs.end())
            {
                if((*iter).key == key)
                {
                    return false;
                }
                ++iter;
            }

            // key doesn't exist, insert this pair
            m_pairs.push_back(Pair(key,value));

            return true;
        }

        const bool contains(const Key& key) const
        {
            ListIter iter = m_pairs.begin();
            while(iter != m_pairs.end())
            {
                if((*iter).key == key)
                {
                    return true;
                }
                ++iter;
            }

            return false;
        }

        Value get(const Key& key)
        {
            ListIter iter = m_pairs.begin();
            while(iter != m_pairs.end())
            {
                if((*iter).key == key)
                {
                    return (*iter).value;
                }
                ++iter;
            }
            
            return nullptr;
        }
};

} // namespace core

} // namespace fenton
