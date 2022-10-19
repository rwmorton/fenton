#include "core/Clock.hpp"

#include <GLFW/glfw3.h>

namespace fenton
{

namespace core
{

void Clock::update()
{
    double now = glfwGetTime();
    m_elapsedTime = now - m_currentTime;
    m_currentTime = now;
}

void Clock::reset()
{
    m_currentTime = m_elapsedTime = 0.0;
}

double Clock::current() const
{
    return m_currentTime;
}

double Clock::elapsed() const
{
    return m_elapsedTime;
}

} // namespace core

} // namespace fenton
