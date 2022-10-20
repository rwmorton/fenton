#include "core/EventRegistry.hpp"

#include <algorithm>

namespace fenton
{

namespace core
{

EventRegistry::EventRegistry()
{
    std::fill_n(m_keys,NUM_KEYS,false);
    m_mouseDown = false;
    m_cursorInside = false;
    clear();
}

void EventRegistry::clear()
{
    std::fill_n(m_keyPressed,NUM_KEYS,false);
    std::fill_n(m_keyReleased,NUM_KEYS,false);
    m_mousePressed = m_mouseReleased = false;
}

bool EventRegistry::getCursorInside() const
{
    return m_cursorInside;
}

void EventRegistry::setCursorInside(bool cursorInside)
{
    m_cursorInside = cursorInside;
}

void EventRegistry::getCursor(unsigned int& x,unsigned int& y)
{
    x = m_cursorX;
    y = m_cursorY;
}

void EventRegistry::getMouseBegin(unsigned int& x,unsigned int &y)
{
    x = m_mouseBeginX;
    y = m_mouseBeginY;
}

void EventRegistry::getMouseEnd(unsigned int& x,unsigned int& y)
{
    x = m_mouseEndX;
    y = m_mouseEndY;
}

void EventRegistry::onKeyDown(Keyboard key)
{
    if(!m_keys[key])
    {
        m_keys[key] = true;
        m_keyPressed[key] = true;
        m_keyReleased[key] = false;
    }
}

void EventRegistry::onKeyUp(Keyboard key)
{
    if(m_keys[key])
    {
        m_keys[key] = false;
        m_keyReleased[key] = true;
        m_keyPressed[key] = false;
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

bool EventRegistry::isKeyReleased(Keyboard key) const
{
    return m_keyReleased[key];
}

void EventRegistry::onMouseDown(unsigned int h,unsigned int v)
{
    if(!m_mouseDown)
    {
        m_mouseDown = true;
        m_mousePressed = true;
        m_mouseReleased = false;

        m_mouseBeginX = h;
        m_mouseBeginY = v;
    }
}

void EventRegistry::onMouseUp()
{
    if(m_mouseDown)
    {
        m_mouseDown = false;
        m_mousePressed = false;
        m_mouseReleased = true;

        m_mouseEndX = m_cursorX;
        m_mouseEndY = m_cursorY;
    }
}

bool EventRegistry::isMouseDown(unsigned int& h,unsigned int& v) const
{
    if(m_mouseDown)
    {
        h = m_cursorX;
        v = m_cursorY;

        return true;
    }
    return false;
}

bool EventRegistry::isMousePressed(unsigned int& h,unsigned int &v) const
{
    if(m_mousePressed)
    {
        h = m_cursorX;
        v = m_cursorY;
        return true;
    }
    return false;
}

bool EventRegistry::isMouseReleased() const
{
    return m_mouseReleased;
}

std::ostream& operator<<(std::ostream& out,const EventRegistry& eventRegistry)
{
    for(int i=0; i<NUM_KEYS; i++)
    {
        out << eventRegistry.m_keys[i] << eventRegistry.m_keyPressed[i] << eventRegistry.m_keyReleased[i] << " ";
    }
    return out;
}

void EventRegistry::updateCursor(unsigned int x,unsigned int y)
{
    m_cursorX = x;
    m_cursorY = y;
}

} // namespace core

} // namespace fenton
