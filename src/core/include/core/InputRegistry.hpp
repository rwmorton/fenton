#pragma once

#include <list>
#include <iostream>

#include "core/Input.hpp"

namespace fenton
{

namespace core
{

//
// inputs are automatically sorted on addition/removal
// this enables easier comparision
//
class InputRegistry
{
    private:
        std::list<Keyboard> m_activeKeyPresses;
        std::list<Mouse> m_activeMouseButtons;
    public:
        // prevent copies
        InputRegistry(const InputRegistry&) = delete;
        InputRegistry& operator=(const InputRegistry&) = delete;

        InputRegistry() {}

        // keyboard input
        void add(Keyboard key);
        void remove(Keyboard key);

        // mouse input
        void add(Mouse button);
        void remove(Mouse button);

        // get state
        const std::list<Keyboard>& keys() const;
        const std::list<Mouse>& buttons() const;

        // class for storing an input combination
        // keys and buttons are automatically sorted...
        class InputCombo
        {
            friend class InputRegistry;
            private:
                std::list<Keyboard> m_keys;
                std::list<Mouse> m_buttons;
            public:
                InputCombo(const std::list<Keyboard>& keys,const std::list<Mouse>& buttons);
                const bool operator==(const InputCombo& rhs) const;
        };

        // test for an active combination of input(s)
        const bool active(const InputCombo& inputCombo) const;

        friend std::ostream &operator<<(std::ostream& out,const InputRegistry& inputRegistry);
};

using Input = InputRegistry::InputCombo;

namespace Key
{

static const Input Escape = Input({Keyboard::ESCAPE},{});
static const Input Up = Input({Keyboard::UP},{});
static const Input Down = Input({Keyboard::DOWN},{});
static const Input Left = Input({Keyboard::LEFT},{});
static const Input Right = Input({Keyboard::RIGHT},{});

static const Input W = Input({Keyboard::W},{});
static const Input S = Input({Keyboard::S},{});
static const Input A = Input({Keyboard::A},{});
static const Input D = Input({Keyboard::D},{});

static const Input T = Input({Keyboard::T},{});
static const Input E = Input({Keyboard::E},{});
static const Input P = Input({Keyboard::P},{});

static const Input ABC = Input({Keyboard::A,Keyboard::B,Keyboard::C},{});

} // namespace Key

namespace MouseButton
{

static const Input Left = Input({},{Mouse::BUTTON_LEFT});
static const Input Right = Input({},{Mouse::BUTTON_RIGHT});
static const Input Middle = Input({},{Mouse::BUTTON_MIDDLE});

} // namespace MouseButton

static const Input KeyA_MouseButtonLeft = Input({Keyboard::A},{Mouse::BUTTON_LEFT});
static const Input KeyA_MouseButtonRight = Input({Keyboard::A},{Mouse::BUTTON_RIGHT});

} // namespace core

} // namespace fenton
