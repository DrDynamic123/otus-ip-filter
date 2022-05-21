#ifndef IP_FILTER
#define IP_FILTER

#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
#include "ip_address.h"


std::vector<IpAddress> filter(const std::vector<IpAddress> &ip_pool, int param1)
{
    std::vector<IpAddress> filteredIp;
    std::copy_if(ip_pool.cbegin(), ip_pool.cend(), std::back_inserter(filteredIp),
        [&param1](const IpAddress& ip){ return ip.get().at(0) == param1; });
    return filteredIp;
}

std::vector<IpAddress> filter(const std::vector<IpAddress> &ip_pool, int param1, int param2)
{
    std::vector<IpAddress> filteredIp;
    std::copy_if(ip_pool.cbegin(), ip_pool.cend(), std::back_inserter(filteredIp),
        [&param1, &param2](const IpAddress& ip){ return ip.get().at(0) == param1 && ip.get().at(1) == param2; });
    return filteredIp;
}

std::vector<IpAddress> filter_any(const std::vector<IpAddress> &ip_pool, int param1)
{
    std::vector<IpAddress> filteredIp;
    std::copy_if(ip_pool.cbegin(), ip_pool.cend(), std::back_inserter(filteredIp),
        [&param1](const IpAddress& ip)
        {
            return ip.contain(param1);
        });
    return filteredIp;
}

#endif // IP_FILTER
