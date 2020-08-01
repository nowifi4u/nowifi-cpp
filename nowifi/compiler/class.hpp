#pragma once


#define THIS (*this)
#define super_type __super



#define CLASS_MAKE_STATIC(classname, ...) \
classname() = delete; \
~classname() = delete; \
classname ( classname __VA_ARGS__ & ) = delete; \
classname & operator=( const classname __VA_ARGS__ & ) = delete; \
classname ( classname __VA_ARGS__ && ) = delete; \
classname & operator=( classname __VA_ARGS__ && ) = delete