#pragma once

#include "core/Input.hpp"

#include <iostream>

namespace fenton
{

namespace core
{

// forward declarations
class App;

class EventRegistry
{
    private:
        bool m_keys[NUM_KEYS];
        bool m_keyPressed[NUM_KEYS];
        bool m_keyReleased[NUM_KEYS];

        bool m_mouseDown;
        bool m_mousePressed;
        bool m_mouseReleased;

        unsigned int m_cursorX;
        unsigned int m_cursorY;
        bool m_cursorInside;

        unsigned int m_mouseBeginX,m_mouseEndX;
        unsigned int m_mouseBeginY,m_mouseEndY;
    public:
        EventRegistry(const EventRegistry&) = delete;
        EventRegistry& operator=(const EventRegistry&) = delete;

        EventRegistry();

        void clear();

        bool getCursorInside() const;
        void setCursorInside(bool cursorInside);
        void getCursor(unsigned int& x,unsigned int& y);

        void getMouseBegin(unsigned int& x,unsigned int &y);
        void getMouseEnd(unsigned int& x,unsigned int& y);
        
        // keyboard
        void onKeyDown(Keyboard key);
        void onKeyUp(Keyboard key);
        bool isKeyDown(Keyboard key) const;
        bool isKeyUp(Keyboard key) const;
        bool isKeyPressed(Keyboard key) const;
        bool isKeyReleased(Keyboard key) const;

        // mouse
        void onMouseDown(unsigned int h,unsigned int v);
        void onMouseUp();
        bool isMouseDown(unsigned int& h,unsigned int& v) const;
        bool isMousePressed(unsigned int& h,unsigned int &v) const;
        bool isMouseReleased() const;

        friend std::ostream& operator<<(std::ostream& out,const EventRegistry& eventRegistry);
    private:
        friend class App;
        void updateCursor(unsigned int x,unsigned int y);
};

} // namespace core

} // namespace fenton
