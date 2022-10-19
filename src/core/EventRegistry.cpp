#include "core/EventRegistry.hpp"

#include <algorithm>

namespace fenton
{

namespace core
{

EventRegistry::EventRegistry()
{
    clear();
}

void EventRegistry::clear()
{
    std::fill_n(m_keys,NUM_KEYS,false);
    std::fill_n(m_keyPressed,NUM_KEYS,false);
    std::fill_n(m_keyReleased,NUM_KEYS,false);
    m_mouseDown = m_mousePressed = m_mouseReleased = false;
    m_mouseX = m_mouseY = 0;
}

void EventRegistry::onKeyDown(Keyboard key)
{
    if(!m_keys[key])
    {
        m_keys[key] = true;
        m_keyPressed[key] = true;
    }
}

void EventRegistry::onKeyUp(Keyboard key)
{
    if(m_keys[key])
    {
        m_keys[key] = false;
        m_keyReleased[key] = true;
    }
}

bool EventRegistry::isKeyDown(Keyboard key) const
{
    return m_keys[key];
}

bool EventRegistry::isKeyUp(Keyboard key) const
{
    return !m_keys[key];
}

bool EventRegistry::isKeyPressed(Keyboard key) const
{
    return m_keyPressed[key];
}

bool EventRegistry::isKeyRelased(Keyboard key) const
{
    return m_keyReleased[key];
}

void EventRegistry::onMouseDown(unsigned int h,unsigned int v)
{
    if(!m_mouseDown)
    {
        m_mouseDown = true;
        m_mousePressed = true;
    }
    m_mouseX = h;
    m_mouseY = v;
}

void EventRegistry::onMouseUp()
{
    if(m_mouseDown)
    {
        m_mouseDown = false;
        m_mouseReleased = true;
    }
}

bool EventRegistry::isMouseDown(unsigned int& h,unsigned int& v)
{
    if(m_mouseDown)
    {
        h = m_mouseX;
        v = m_mouseY;
        return true;
    }
    return false;
}

bool EventRegistry::isMousePressed(unsigned int& h,unsigned int &v)
{
    if(m_mousePressed)
    {
        h = m_mouseX;
        v = m_mouseY;
        return true;
    }
    return false;
}

bool EventRegistry::isMouseReleased() const
{
    return m_mouseReleased;
}

} // namespace core

} // namespace fenton
