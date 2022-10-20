#include "core/CallbackMap.hpp"

namespace fenton
{

namespace core
{

void CallbackMap::set(const Input& input,Callback callback)
{
    m_callbacks.insert(input,callback);
}

void CallbackMap::execute(const Input& input)
{
    if(m_callbacks.size() > 0) {
        if(m_callbacks.contains(input))
        {
            m_callbacks.get(input)();
        }
    }
}

} // namespace core

} // namespace fenton
