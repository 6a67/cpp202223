#include <cstdint>

template <bool Param, typename TrueResult, typename FalseResult>
class foo;
  
template <typename TrueResult, typename FalseResult>
struct foo<true, TrueResult, FalseResult>
{
    typedef TrueResult result;
};
 
template <typename TrueResult, typename FalseResult>
struct foo<false, TrueResult, FalseResult>
{
    typedef FalseResult result;
};


int main()
{
   typename foo<true, int, void*>::result number(3);
   typename foo<false, int, void*>::result pointer(&number);

   typedef typename foo<(sizeof(void *) > sizeof(uint32_t)), uint64_t, uint32_t>::result integral_ptr_t;

   return integral_ptr_t converted_pointer = reinterpret_cast<integral_ptr_t>(pointer);
}
