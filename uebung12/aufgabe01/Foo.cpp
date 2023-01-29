#include <cstdint>

// Defining template class for selecting a type based on a boolean parameter
template <bool Param, typename TrueResult, typename FalseResult>
class ConditionalType;

// Specialization for when the boolean parameter is true
template <typename TrueResult, typename FalseResult>
struct ConditionalType<true, TrueResult, FalseResult>
{
    // Typedef for the type that should be returned when the boolean parameter is true
    // result is then the type of the second template parameter
    typedef TrueResult result;
};

// Specialization for when the boolean parameter is false
template <typename TrueResult, typename FalseResult>
struct ConditionalType<false, TrueResult, FalseResult>
{
    // Typedef for the type that should be returned when the boolean parameter is false
    // result is then the type of the third template parameter
    typedef FalseResult result;
};

int main()
{
    // result is int, as the boolean parameter is true
    typename ConditionalType<true, int, void*>::result number(3);
    // result is void*, as the boolean parameter is false
    typename ConditionalType<false, int, void*>::result pointer(&number);

    // first checks sizeof(void *) > sizeof(uint32_t); result is first parameter of template class (in this case true)
    // result depends on the platform
    // ConditionalType then selects uint64_t or uint32_t based on the result of the first check
    // integral_ptr_t is then typedefed to the selected type
    // overall integral_ptr_t has a different type depending on the platform
    typedef typename ConditionalType<(sizeof(void *) > sizeof(uint32_t)), uint64_t, uint32_t>::result integral_ptr_t;

    // Pointer can then be converted to the correct type for the platform
    integral_ptr_t converted_pointer = reinterpret_cast<integral_ptr_t>(pointer);

    return 0;
}
