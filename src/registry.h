#ifndef EXTERN_STRAT
#define EXTERN_STRAT extern
#endif // EXTERN_STRAT

// Definition of the strategy to implement
struct strategy
{
  const char* name;
  void (* play)(struct board *);
};

#define MAX_STRATEGIES 10

// Simple macro for registering a strategy
// Not POSIX, real users use dlfcn.h
#define REGISTER_STRATEGY(__name, __strat)	\
  static const struct strategy strat = { __name, __strat };	\
  __attribute__((constructor))  \
    static void initialize_strategy() { \
      strategies[strategies_count ++ ] = &strat;\
    }

// Array of all the registered strategies. If the strategies are
// registered via the previous macro, then there are exactly
// strategies_count strategies inside the strategies array. 
EXTERN_STRAT const struct strategy *strategies[MAX_STRATEGIES];
// Global variable guaranteed to be initialized to zero
EXTERN_STRAT int strategies_count;
