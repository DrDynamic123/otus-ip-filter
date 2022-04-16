#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using split_ip = std::vector<std::string>;

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
split_ip split(const std::string &str, char d)
{
    split_ip r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

void print(const std::vector<split_ip> &ip_pool)
{
    for(const auto &ip : ip_pool)
    {
        for(auto ip_part = ip.cbegin(); ip_part != ip.cend(); ++ip_part)
        {
            if (ip_part != ip.cbegin())
            {
                std::cout << ".";
            }
            std::cout << *ip_part;
        }
        std::cout << std::endl;
    }
}
/*
std::vector<split_ip> filter(const std::vector<split_ip> &ip_pool, const std::string& param1)
{
    auto first =
    auto last 
    return {};
}*/

std::vector<split_ip> filter(const std::vector<split_ip> &ip_pool, const std::string& param1)
{
    std::vector<split_ip> filteredIp;
    std::copy_if(ip_pool.cbegin(), ip_pool.cend(), std::back_inserter(filteredIp),
        [&param1](const split_ip& ip){ return ip.at(0) == param1; });
    return filteredIp;
}

std::vector<split_ip> filter(const std::vector<split_ip> &ip_pool, const std::string& param1, const std::string& param2)
{
    std::vector<split_ip> filteredIp;
    std::copy_if(ip_pool.cbegin(), ip_pool.cend(), std::back_inserter(filteredIp),
        [&param1, &param2](const split_ip& ip){ return ip.at(0) == param1 && ip.at(1) == param2; });
    return filteredIp;
}

std::vector<split_ip> filter_any(const std::vector<split_ip> &ip_pool, const std::string& param1)
{
    std::vector<split_ip> filteredIp;
    std::copy_if(ip_pool.cbegin(), ip_pool.cend(), std::back_inserter(filteredIp),
        [&param1](const split_ip& ip)
        {
            return std::any_of(ip.cbegin(), ip.cend(), [&](const std::string& part){ return part == param1;});
        });
    return filteredIp;
}

int main()
{
    try
    {
        std::vector<split_ip> ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            auto v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        // TODO reverse lexicographically sort
        std::sort(ip_pool.begin(), ip_pool.end(), 
            [](split_ip& ip1, split_ip& ip2)
            {
                auto first1 = ip1.begin();
                auto last1 = ip1.end();
                auto first2 = ip2.begin();
                auto last2 = ip2.end();

                for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 )
                {
                    if (std::stoi(*first1) > std::stoi(*first2)) return true;
                    if (std::stoi(*first1) < std::stoi(*first2)) return false;
                }
                return first1 != last1;
            });

        print(ip_pool);

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)
        print(filter(ip_pool, "1"));

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)
        print(filter(ip_pool, "46", "70"));

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)
        print(filter_any(ip_pool, "46"));

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
