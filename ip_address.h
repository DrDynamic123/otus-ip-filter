#ifndef IP_ADDRESS
#define IP_ADDRESS

#include <string>
#include <array>
#include <algorithm>

class IpAddress
{
public:
    IpAddress() : m_ip{0,0,0,0}
    {}
    explicit IpAddress(const std::string &str)
    {
        char d = '.';
        std::string::size_type start = 0;
        std::string::size_type stop = str.find_first_of(d);
        for (std::size_t i = 0; i < m_ip.size(); ++i)
        {
            m_ip.at(i) = std::stoi(str.substr(start, stop - start));

            start = stop + 1;
            stop = str.find_first_of(d, start);
        }
    }

    const std::array<int, 4> & get() const
    {
        return m_ip;
    }

    std::string toString() const
    {
        std::string str;
        for(auto part : m_ip)
        {
            if (!str.empty())
            {
                str.append(".");
            }
            str.append(std::to_string(part));
        }
        return str;
    }

    bool contain(int value) const
    {
        return m_ip.cend() != std::find(m_ip.cbegin(), m_ip.cend(), value);
    }

    bool operator>(const IpAddress &other) const
    {
        return m_ip > other.m_ip;
    }

private:
    std::array<int, 4> m_ip;
};

#endif // IP_ADDRESS
