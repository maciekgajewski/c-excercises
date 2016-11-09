#pragma once

namespace course{


template<typename T, typename TIterator>
int count_until(TIterator begin, TIterator end, const T& target, const T& terminal)
{
    int result = 0;

    for(auto it = begin; it!=end; ++it)
    {
        if(*it == terminal) { break; }

        if(*it == target) { result++; }
    }

    return result;
}

template<typename TIterator, typename TTerminalPredicate, typename TTargetPredicate>
int count_until_func(
        TIterator begin,
        TIterator end,
        TTargetPredicate isTarget,
        TTerminalPredicate isTerminal)
{
    int result = 0;

    for(auto it = begin; it!=end; ++it)
    {
        if(isTerminal(*it)) { break; }

        if(isTarget(*it)) { result++; }
    }

    return result;
}}
