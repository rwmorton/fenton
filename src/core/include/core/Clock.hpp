#pragma once

namespace fenton
{

namespace core
{

class Clock
{
    private:
        double m_currentTime;
        double m_elapsedTime;
    public:
        // prevent copies
        Clock(const Clock&) = delete;
        Clock& operator=(const Clock&) = delete;

        Clock() : m_currentTime(0.0),m_elapsedTime(0.0) {}

        void update();
        void reset();
        double current() const;
        double elapsed() const;
};

} // namespace core

} // namespace fenton
