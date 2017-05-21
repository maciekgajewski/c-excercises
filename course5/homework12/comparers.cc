#include <memory>
#include "comparers.h"

namespace homework12
{
std::unique_ptr<AComparer> CreateComparer(bool numeric, bool keyed, unsigned int column, char separator)
{   
    std::unique_ptr<AComparer> comparer = nullptr;
    if (keyed)
    {
        if (numeric)
            return std::make_unique<ColumnComparer<NumericComparer>>(column, separator);
        else
            return std::make_unique<ColumnComparer<BasicComparer>>(column, separator);
    }
    else
    {
        if (numeric)
            return std::make_unique<NumericComparer>();
        else
            return std::make_unique<BasicComparer>();

    }
}

}

