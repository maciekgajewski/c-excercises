#include <memory>
#include "comparers.h"

namespace homework12
{
std::unique_ptr<AComparer> CreateComparer(bool numeric, bool keyed, unsigned int column, char separator)
{
    std::unique_ptr<AComparer> comparer;
    if (numeric)
        comparer = std::make_unique<NumericComparer>();
    else comparer = std::make_unique<BasicComparer>();
    if (keyed)
    {
        auto column_comparer = std::make_unique<ColumnComparer>(column, separator, comparer);
        comparer = std::move(column_comparer);
    }
    return comparer;
}

}

