#pragma once

#include <functional>
#include <list>

#include "core/Map.hpp"
#include "core/InputRegistry.hpp"

namespace fenton
{

namespace core
{

using Callback = std::function<void()>;

class CallbackMap
{
    private:
        Map<Input,Callback> m_callbacks;
    public:
        void set(const Input& input,Callback callback);
        void execute(const Input& input);
};

} // namespace core

} // namespace fenton
