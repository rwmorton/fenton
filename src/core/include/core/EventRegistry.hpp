#pragma once

#include "core/Input.hpp"

#include <iostream>

namespace fenton
{

namespace core
{

class EventRegistry
{
    private:
        bool m_keys[NUM_KEYS];
        bool m_keyPressed[NUM_KEYS];
        bool m_keyReleased[NUM_KEYS];

        bool m_mouseDown;
        bool m_mousePressed;
        bool m_mouseReleased;
        unsigned int m_mouseX;
        unsigned int m_mouseY;
    public:
        EventRegistry(const EventRegistry&) = delete;
        EventRegistry& operator=(const EventRegistry&) = delete;

        EventRegistry();

        void clear();
        
        // keyboard
        void onKeyDown(Keyboard key);
        void onKeyUp(Keyboard key);
        bool isKeyDown(Keyboard key) const;
        bool isKeyUp(Keyboard key) const;
        bool isKeyPressed(Keyboard key) const;
        bool isKeyRelased(Keyboard key) const;

        // mouse
        void onMouseDown(unsigned int h,unsigned int v);
        void onMouseUp();
        bool isMouseDown(unsigned int& h,unsigned int& v);
        bool isMousePressed(unsigned int& h,unsigned int &v);
        bool isMouseReleased() const;

        friend std::ostream& operator<<(std::ostream& out,const EventRegistry& eventRegistry)
        {
            for(int i=0; i<NUM_KEYS; i++)
            {
                std::cout << eventRegistry.m_keys[i] << eventRegistry.m_keyPressed[i] << eventRegistry.m_keyReleased[i] << " ";
            }
            return out;
        }
    protected:
        //
};

} // namespace core

} // namespace fenton
