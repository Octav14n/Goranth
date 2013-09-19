#ifndef MACROS_H
#define MACROS_H

#define DEF_SINGLETON( NAME )    \
public:                        \
   static NAME& instance()      \
   {                            \
      static NAME _instance;    \
      return _instance;         \
   }                            \
private:                       \
   NAME();               \
   NAME( const NAME& );

#endif // MACROS_H
