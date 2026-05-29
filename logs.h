#ifndef OK_LOGS
#define OK_LOGS

#include <iostream>
#ifdef DEBUG
#define OK_DEBUG
#endif // DEBUG

namespace Logs::Warnings {


}

namespace Logs::Asserts {

// MACRO DEFINITONS

#if defined (OK_DEBUG)
#define assert_paranoid(COND, MSG)                       \
  do {                                                   \
    if (COND) {                                          \
      Logs::Asserts::_assert_paranoid(__LINE__, MSG);    \
    }                                                    \
  } while (0)
#else
#define assert_paranoid(COND, MSG) (void*)(0)
#endif // end assert_paranoid


#if defined (OK_DEBUG)
#define assert(COND, MSG) if(COND){_assert()}
#else 
#define assert(CONST, MSG) (void*)(0)
#endif // end assert








// FUNCTIONS DEFINITIONS

/***
 *
 * assert_paranoid() stops the execution of the program after displaying the 
 * error message that causes the crash. 
 * Paranoid is designed to be the most strict kind of assert, allways checking
 * the condition, even in release mode.
 *
 *
 *
 *
 *
 *
 *
 */
inline void constexpr _assert_paranoid(int line, const char* msg) {
  std::cout << line << "PARANOID : "<< msg << std::endl;
}


/***
 *  assert() stops the program and display a message
 *
 *
 *
 *
 */
inline void constexpr _assert(int line, const char *msg){
  std::cout << line << "ASSERT : " << msg << std::endl;
}



} // end Logs::Asserts

#endif // end of OK_LOGS guard 







// IMPLEMENTATION






