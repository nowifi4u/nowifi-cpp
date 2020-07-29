#pragma once


#define THIS (*this)
#define super_type __super

#define __MAKE_STATIC__impl ( classname ) \
classname ( ) = delete; \
~classname ( ) = delete; \
classname ( const  classname & ) = delete; \
classname & operator=( const classname & ) = delete; \
classname ( classname && ) = delete; \
classname & operator=( classname && ) = delete

#define MAKE_STATIC( classname ) \
classname ( ) = delete; \
~classname ( ) = delete; \
typedef classname SelfTy ; \
classname ( const  SelfTy & ) = delete; \
classname & operator=( const SelfTy & ) = delete; \
classname ( SelfTy && ) = delete; \
classname & operator=( SelfTy && ) = delete


#define MAKE_STATIC_TEMPLATE_1( classname , tmplt1 ) \
classname ( ) = delete; \
~classname ( ) = delete; \
typedef classname tmplt1 SelfTy ; \
classname ( const  SelfTy & ) = delete; \
classname & operator=( const SelfTy & ) = delete; \
classname ( SelfTy && ) = delete; \
classname & operator=( SelfTy && ) = delete


#define MAKE_STATIC_TEMPLATE_2( classname , tmplt1 , tmplt2 ) \
classname ( ) = delete; \
~classname ( ) = delete; \
typedef classname tmplt1 , tmplt2 SelfTy ; \
classname ( const  SelfTy & ) = delete; \
classname & operator=( const SelfTy & ) = delete; \
classname ( SelfTy && ) = delete; \
classname & operator=( SelfTy && ) = delete


#define MAKE_STATIC_TEMPLATE_3( classname , tmplt1 , tmplt2 , tmplt3 ) \
classname ( ) = delete; \
~classname ( ) = delete; \
typedef classname tmplt1 , tmplt2 , tmplt3 SelfTy ; \
classname ( const  SelfTy & ) = delete; \
classname & operator=( const SelfTy & ) = delete; \
classname ( SelfTy && ) = delete; \
classname & operator=( SelfTy && ) = delete


#define MAKE_STATIC_TEMPLATE_4( classname , tmplt1 , tmplt2 , tmplt3 , tmplt4 ) \
classname ( ) = delete; \
~classname ( ) = delete; \
typedef classname tmplt1 , tmplt2 , tmplt3 , tmplt4 SelfTy ; \
classname ( const  SelfTy & ) = delete; \
classname & operator=( const SelfTy & ) = delete; \
classname ( SelfTy && ) = delete; \
classname & operator=( SelfTy && ) = delete


#define MAKE_STATIC_TEMPLATE_5( classname , tmplt1 , tmplt2 , tmplt3 , tmplt4 , tmplt5 ) \
classname ( ) = delete; \
~classname ( ) = delete; \
typedef classname tmplt1 , tmplt2 , tmplt3 , tmplt4 , tmplt5 SelfTy ; \
classname ( const  SelfTy & ) = delete; \
classname & operator=( const SelfTy & ) = delete; \
classname ( SelfTy && ) = delete; \
classname & operator=( SelfTy && ) = delete


#define MAKE_STATIC_TEMPLATE_6( classname , tmplt1 , tmplt2 , tmplt3 , tmplt4 , tmplt5 , tmplt6 ) \
classname ( ) = delete; \
~classname ( ) = delete; \
typedef classname tmplt1 , tmplt2 , tmplt3 , tmplt4 , tmplt5 , tmplt6 SelfTy ; \
classname ( const  SelfTy & ) = delete; \
classname & operator=( const SelfTy & ) = delete; \
classname ( SelfTy && ) = delete; \
classname & operator=( SelfTy && ) = delete


#define MAKE_STATIC_TEMPLATE_7( classname , tmplt1 , tmplt2 , tmplt3 , tmplt4 , tmplt5 , tmplt6 , tmplt7 ) \
classname ( ) = delete; \
~classname ( ) = delete; \
typedef classname tmplt1 , tmplt2 , tmplt3 , tmplt4 , tmplt5 , tmplt6 , tmplt7 SelfTy ; \
classname ( const  SelfTy & ) = delete; \
classname & operator=( const SelfTy & ) = delete; \
classname ( SelfTy && ) = delete; \
classname & operator=( SelfTy && ) = delete


#define MAKE_STATIC_TEMPLATE_8( classname , tmplt1 , tmplt2 , tmplt3 , tmplt4 , tmplt5 , tmplt6 , tmplt7 , tmplt8 ) \
classname ( ) = delete; \
~classname ( ) = delete; \
typedef classname tmplt1 , tmplt2 , tmplt3 , tmplt4 , tmplt5 , tmplt6 , tmplt7 , tmplt8 SelfTy ; \
classname ( const  SelfTy & ) = delete; \
classname & operator=( const SelfTy & ) = delete; \
classname ( SelfTy && ) = delete; \
classname & operator=( SelfTy && ) = delete


#define MAKE_STATIC_TEMPLATE_9( classname , tmplt1 , tmplt2 , tmplt3 , tmplt4 , tmplt5 , tmplt6 , tmplt7 , tmplt8 , tmplt9 ) \
classname ( ) = delete; \
~classname ( ) = delete; \
typedef classname tmplt1 , tmplt2 , tmplt3 , tmplt4 , tmplt5 , tmplt6 , tmplt7 , tmplt8 , tmplt9 SelfTy ; \
classname ( const  SelfTy & ) = delete; \
classname & operator=( const SelfTy & ) = delete; \
classname ( SelfTy && ) = delete; \
classname & operator=( SelfTy && ) = delete


#define MAKE_STATIC_TEMPLATE_10( classname , tmplt1 , tmplt2 , tmplt3 , tmplt4 , tmplt5 , tmplt6 , tmplt7 , tmplt8 , tmplt9 , tmplt10 ) \
classname ( ) = delete; \
~classname ( ) = delete; \
typedef classname tmplt1 , tmplt2 , tmplt3 , tmplt4 , tmplt5 , tmplt6 , tmplt7 , tmplt8 , tmplt9 , tmplt10 SelfTy ; \
classname ( const  SelfTy & ) = delete; \
classname & operator=( const SelfTy & ) = delete; \
classname ( SelfTy && ) = delete; \
classname & operator=( SelfTy && ) = delete


