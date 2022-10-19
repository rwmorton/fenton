#include "core/InputRegistry.hpp"

namespace fenton
{

namespace core
{

// keyboard input

void InputRegistry::add(Keyboard key)
{
    m_activeKeyPresses.push_back(key);
    m_activeKeyPresses.sort();
}

void InputRegistry::remove(Keyboard key)
{
    m_activeKeyPresses.remove(key);
    m_activeKeyPresses.sort();
}

// mouse input

void InputRegistry::add(Mouse button)
{
    m_activeMouseButtons.push_back(button);
    m_activeMouseButtons.sort();
}

void InputRegistry::remove(Mouse button)
{
    m_activeMouseButtons.remove(button);
    m_activeMouseButtons.sort();
}

const std::list<Keyboard>& InputRegistry::keys() const
{
    return m_activeKeyPresses;
}

const std::list<Mouse>& InputRegistry::buttons() const
{
    return m_activeMouseButtons;
}

InputRegistry::InputCombo::InputCombo(const std::list<Keyboard>& keys,const std::list<Mouse>& buttons) : m_keys(keys),m_buttons(buttons)
{
    m_keys.sort();
    m_buttons.sort();
}

const bool InputRegistry::InputCombo::operator==(const InputCombo& rhs) const
{
    std::list<Keyboard>::const_iterator kIter = m_keys.begin();
    std::list<Keyboard>::const_iterator rhskIter = rhs.m_keys.begin();
    while(kIter != m_keys.end()) {
        if(*kIter != *rhskIter) {
            return false;
        }
        std::advance(kIter,1);
        std::advance(rhskIter,1);
    }

    std::list<Mouse>::const_iterator bIter = m_buttons.begin();
    std::list<Mouse>::const_iterator rhsbIter = rhs.m_buttons.begin();
    while(bIter != m_buttons.end()) {
        if(*bIter != *rhsbIter) {
            return false;
        }
        std::advance(bIter,1);
        std::advance(rhsbIter,1);
    }

    return true;
}

const bool InputRegistry::active(const InputRegistry::InputCombo& inputCombo) const
{
    if(inputCombo.m_keys.size() != m_activeKeyPresses.size() || inputCombo.m_buttons.size() != m_activeMouseButtons.size()) {
        return false;
    }
    
    auto inputComboKeysIter = inputCombo.m_keys.begin();
    auto activeKeysIter = m_activeKeyPresses.begin();
    while(inputComboKeysIter != inputCombo.m_keys.end()) {
        if(*inputComboKeysIter != *activeKeysIter) {
            return false;
        }
        std::advance(inputComboKeysIter,1);
        std::advance(activeKeysIter,1);
    }
    
    auto inputComboButtonsIter = inputCombo.m_buttons.begin();
    auto activeButtonsIter = m_activeMouseButtons.begin();
    while(inputComboButtonsIter != inputCombo.m_buttons.end()) {
        if(*inputComboButtonsIter != *activeButtonsIter) {
            return false;
        }
        std::advance(inputComboButtonsIter,1);
        std::advance(activeButtonsIter,1);
    }

    return true;
}

std::ostream &operator<<(std::ostream& out,const InputRegistry& inputRegistry)
{
    out << "keys: ";
    for(auto k : inputRegistry.m_activeKeyPresses) out << k << " ";
    out << std::endl;
    out << "buttons: ";
    for(auto b : inputRegistry.m_activeMouseButtons) out << b << " ";
    out << std::endl;
    return out;
}

} // namespace core

} // namespace fenton
