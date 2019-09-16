#pragma once

#ifdef __cplusplus

# define NASNR_COMPILER_IS_Clang 0
# define NASNR_COMPILER_IS_GNU 0
# define NASNR_COMPILER_IS_MSVC 0


#if defined(__clang__)
# undef NASNR_COMPILER_IS_Clang
# define NASNR_COMPILER_IS_Clang 1

#elif defined(__GNUC__) || defined(__GNUG__)
# undef NASNR_COMPILER_IS_GNU
# define NASNR_COMPILER_IS_GNU 1

#elif defined(_MSC_VER)
# undef NASNR_COMPILER_IS_MSVC
# define NASNR_COMPILER_IS_MSVC 1


#endif

#  if NASNR_COMPILER_IS_GNU

#    if !((__GNUC__ * 100 + __GNUC_MINOR__) >= 404)
#      error Unsupported compiler version
#    endif

# if defined(__GNUC__)
#  define NASNR_COMPILER_VERSION_MAJOR (__GNUC__)
# else
#  define NASNR_COMPILER_VERSION_MAJOR (__GNUG__)
# endif
# if defined(__GNUC_MINOR__)
#  define NASNR_COMPILER_VERSION_MINOR (__GNUC_MINOR__)
# endif
# if defined(__GNUC_PATCHLEVEL__)
#  define NASNR_COMPILER_VERSION_PATCH (__GNUC_PATCHLEVEL__)
# endif

#    if (__GNUC__ * 100 + __GNUC_MINOR__) >= 404 && (__cplusplus >= 201103L || (defined(__GXX_EXPERIMENTAL_CXX0X__) && __GXX_EXPERIMENTAL_CXX0X__))
#      define NASNR_COMPILER_CXX_VARIADIC_TEMPLATES 1
#    else
#      define NASNR_COMPILER_CXX_VARIADIC_TEMPLATES 0
#    endif

#    if (__GNUC__ * 100 + __GNUC_MINOR__) >= 406 && (__cplusplus >= 201103L || (defined(__GXX_EXPERIMENTAL_CXX0X__) && __GXX_EXPERIMENTAL_CXX0X__))
#      define NASNR_COMPILER_CXX_CONSTEXPR 1
#    else
#      define NASNR_COMPILER_CXX_CONSTEXPR 0
#    endif

#    if (__GNUC__ * 100 + __GNUC_MINOR__) >= 407 && __cplusplus >= 201103L
#      define NASNR_COMPILER_CXX_FINAL 1
#    else
#      define NASNR_COMPILER_CXX_FINAL 0
#    endif

#    if (__GNUC__ * 100 + __GNUC_MINOR__) >= 406 && (__cplusplus >= 201103L || (defined(__GXX_EXPERIMENTAL_CXX0X__) && __GXX_EXPERIMENTAL_CXX0X__))
#      define NASNR_COMPILER_CXX_NOEXCEPT 1
#    else
#      define NASNR_COMPILER_CXX_NOEXCEPT 0
#    endif

#    if (__GNUC__ * 100 + __GNUC_MINOR__) >= 407 && __cplusplus >= 201103L
#      define NASNR_COMPILER_CXX_OVERRIDE 1
#    else
#      define NASNR_COMPILER_CXX_OVERRIDE 0
#    endif

#    if (__GNUC__ * 100 + __GNUC_MINOR__) >= 404 && (__cplusplus >= 201103L || (defined(__GXX_EXPERIMENTAL_CXX0X__) && __GXX_EXPERIMENTAL_CXX0X__))
#      define NASNR_COMPILER_CXX_EXTERN_TEMPLATES 1
#    else
#      define NASNR_COMPILER_CXX_EXTERN_TEMPLATES 0
#    endif

#    if (__GNUC__ * 100 + __GNUC_MINOR__) >= 404 && (__cplusplus >= 201103L || (defined(__GXX_EXPERIMENTAL_CXX0X__) && __GXX_EXPERIMENTAL_CXX0X__))
#      define NASNR_COMPILER_CXX_DELETED_FUNCTIONS 1
#    else
#      define NASNR_COMPILER_CXX_DELETED_FUNCTIONS 0
#    endif

#    if (__GNUC__ * 100 + __GNUC_MINOR__) >= 408 && __cplusplus >= 201103L
#      define NASNR_COMPILER_CXX_ALIGNAS 1
#    else
#      define NASNR_COMPILER_CXX_ALIGNAS 0
#    endif

#    if (__GNUC__ * 100 + __GNUC_MINOR__) >= 406 && (__cplusplus >= 201103L || (defined(__GXX_EXPERIMENTAL_CXX0X__) && __GXX_EXPERIMENTAL_CXX0X__))
#      define NASNR_COMPILER_CXX_NULLPTR 1
#    else
#      define NASNR_COMPILER_CXX_NULLPTR 0
#    endif

#    if (__GNUC__ * 100 + __GNUC_MINOR__) >= 408 && __cplusplus >= 201103L
#      define NASNR_COMPILER_CXX_ALIGNOF 1
#    else
#      define NASNR_COMPILER_CXX_ALIGNOF 0
#    endif

#    if (__GNUC__ * 100 + __GNUC_MINOR__) >= 404 && (__cplusplus >= 201103L || (defined(__GXX_EXPERIMENTAL_CXX0X__) && __GXX_EXPERIMENTAL_CXX0X__))
#      define NASNR_COMPILER_CXX_STATIC_ASSERT 1
#    else
#      define NASNR_COMPILER_CXX_STATIC_ASSERT 0
#    endif

#    if (__GNUC__ * 100 + __GNUC_MINOR__) >= 409 && __cplusplus > 201103L
#      define NASNR_COMPILER_CXX_ATTRIBUTE_DEPRECATED 1
#    else
#      define NASNR_COMPILER_CXX_ATTRIBUTE_DEPRECATED 0
#    endif

#    if (__GNUC__ * 100 + __GNUC_MINOR__) >= 409 && __cplusplus > 201103L
#define NASNR_COMPILER_CXX_ATTRIBUTE_NODISCARD 1
#else
#define NASNR_COMPILER_CXX_ATTRIBUTE_NODISCARD 0
#endif

#    if (__GNUC__ * 100 + __GNUC_MINOR__) >= 409 && __cplusplus > 201103L
#define NASNR_COMPILER_CXX_ATTRIBUTE_INLINE 1
#else
#define NASNR_COMPILER_CXX_ATTRIBUTE_INLINE 0
#endif

#    if (__GNUC__ * 100 + __GNUC_MINOR__) >= 409 && __cplusplus > 201103L
#define NASNR_COMPILER_CXX_BRACE_OR_EQUAL_INITIALIZER 1
#else
#define NASNR_COMPILER_CXX_BRACE_OR_EQUAL_INITIALIZER 0
#endif

#define NASNR_COMPILER_CXX_TYPE_DEDUCE 1
#define NASNR_COMPILER_CXX_USING_ALIAS 1
#define NASNR_COMPILER_CXX_STATIC_CAST_VOID 1
#define NASNR_COMPILER_CXX_VECTOR_DATA 1
#define NASNR_COMPILER_CXX_INTTYPES 1
#define NASNR_COMPILER_CXX_VA_COPY 1

#  elif NASNR_COMPILER_IS_MSVC

#    if !(_MSC_VER >= 1500)
#      error Unsupported compiler version
#    endif

  /* _MSC_VER = VVRR */
# define NASNR_COMPILER_VERSION_MAJOR (_MSC_VER / 100)
# define NASNR_COMPILER_VERSION_MINOR (_MSC_VER % 100)
# if defined(_MSC_FULL_VER)
#  if _MSC_VER >= 1400
    /* _MSC_FULL_VER = VVRRPPPPP */
#   define NASNR_COMPILER_VERSION_PATCH (_MSC_FULL_VER % 100000)
#  else
    /* _MSC_FULL_VER = VVRRPPPP */
#   define NASNR_COMPILER_VERSION_PATCH (_MSC_FULL_VER % 10000)
#  endif
# endif
# if defined(_MSC_BUILD)
#  define NASNR_COMPILER_VERSION_TWEAK (_MSC_BUILD)
# endif

#    if _MSC_VER >= 1800
#      define NASNR_COMPILER_CXX_VARIADIC_TEMPLATES 1
#    else
#      define NASNR_COMPILER_CXX_VARIADIC_TEMPLATES 0
#    endif

#    if _MSC_VER >= 1900
#      define NASNR_COMPILER_CXX_CONSTEXPR 1
#    else
#      define NASNR_COMPILER_CXX_CONSTEXPR 0
#    endif

#    if _MSC_VER >= 1700
#      define NASNR_COMPILER_CXX_FINAL 1
#    else
#      define NASNR_COMPILER_CXX_FINAL 0
#    endif

#    if _MSC_VER >= 1900
#      define NASNR_COMPILER_CXX_NOEXCEPT 1
#    else
#      define NASNR_COMPILER_CXX_NOEXCEPT 0
#    endif

#    if _MSC_VER >= 1600
#      define NASNR_COMPILER_CXX_OVERRIDE 1
#    else
#      define NASNR_COMPILER_CXX_OVERRIDE 0
#    endif

#    if _MSC_VER >= 1600
#      define NASNR_COMPILER_CXX_EXTERN_TEMPLATES 1
#    else
#      define NASNR_COMPILER_CXX_EXTERN_TEMPLATES 0
#    endif

#    if _MSC_VER >= 1900
#      define NASNR_COMPILER_CXX_DELETED_FUNCTIONS 1
#    else
#      define NASNR_COMPILER_CXX_DELETED_FUNCTIONS 0
#    endif

#if _MSC_VER >= 1900
#define NASNR_COMPILER_CXX_DEFAULT_FUNCTIONS 1
#else
#define NASNR_COMPILER_CXX_DEFAULT_FUNCTIONS 0
#endif

#if _MSC_VER >= 1900
#define NASNR_COMPILER_CXX_STATIC_CAST_VOID 1
#else
#define NASNR_COMPILER_CXX_STATIC_CAST_VOID 0
#endif

#    if _MSC_VER >= 1900
#      define NASNR_COMPILER_CXX_ALIGNAS 1
#    else
#      define NASNR_COMPILER_CXX_ALIGNAS 0
#    endif

#    if _MSC_VER >= 1600
#      define NASNR_COMPILER_CXX_NULLPTR 1
#    else
#      define NASNR_COMPILER_CXX_NULLPTR 0
#    endif

#    if _MSC_VER >= 1900
#      define NASNR_COMPILER_CXX_ALIGNOF 1
#    else
#      define NASNR_COMPILER_CXX_ALIGNOF 0
#    endif

#    if _MSC_VER >= 1600
#      define NASNR_COMPILER_CXX_STATIC_ASSERT 1
#    else
#      define NASNR_COMPILER_CXX_STATIC_ASSERT 0
#    endif

#    if _MSC_VER >= 1900
#      define NASNR_COMPILER_CXX_ATTRIBUTE_DEPRECATED 1
#    else
#      define NASNR_COMPILER_CXX_ATTRIBUTE_DEPRECATED 0
#    endif

#if _MSC_VER >= 1900
#define NASNR_COMPILER_CXX_ATTRIBUTE_NODISCARD 1
#else
#define NASNR_COMPILER_CXX_ATTRIBUTE_NODISCARD 0
#endif

#if _MSC_VER >= 1900
#define NASNR_COMPILER_CXX_INLINE 1
#else
#define NASNR_COMPILER_CXX_INLINE 0
#endif

#if _MSC_VER >= 1900
#define NASNR_COMPILER_CXX_BRACE_OR_EQUAL_INITIALIZER 1
#else
#define NASNR_COMPILER_CXX_BRACE_OR_EQUAL_INITIALIZER 0
#endif

#if _MSC_VER >= 1900
#define NASNR_COMPILER_CXX_TYPE_DEDUCE 1
#else
#define NASNR_COMPILER_CXX_TYPE_DEDUCE 0
#endif

#if _MSC_VER >= 1900
#define NASNR_COMPILER_CXX_USING_ALIAS 1
#define NASNR_COMPILER_CXX_STDSIZE 1
#define NASNR_COMPILER_CXX_VECTOR_DATA 1
#define NASNR_COMPILER_CXX_INTTYPES 1
#define NASNR_COMPILER_CXX_VA_COPY 1
#else
#define NASNR_COMPILER_CXX_USING_ALIAS 0
#define NASNR_COMPILER_CXX_STDSIZE 0
#define NASNR_COMPILER_CXX_VECTOR_DATA 0
#define NASNR_COMPILER_CXX_INTTYPES 0
#define NASNR_COMPILER_CXX_VA_COPY 0
#endif

#  elif NASNR_COMPILER_IS_Clang

#    if !(((__clang_major__ * 100) + __clang_minor__) >= 301)
#      error Unsupported compiler version
#    endif

# define NASNR_COMPILER_VERSION_MAJOR (__clang_major__)
# define NASNR_COMPILER_VERSION_MINOR (__clang_minor__)
# define NASNR_COMPILER_VERSION_PATCH (__clang_patchlevel__)
# if defined(_MSC_VER)
   /* _MSC_VER = VVRR */
#  define NASNR_SIMULATE_VERSION_MAJOR (_MSC_VER / 100)
#  define NASNR_SIMULATE_VERSION_MINOR (_MSC_VER % 100)
# endif

#    if ((__clang_major__ * 100) + __clang_minor__) >= 301 && __has_feature(cxx_variadic_templates)
#      define NASNR_COMPILER_CXX_VARIADIC_TEMPLATES 1
#    else
#      define NASNR_COMPILER_CXX_VARIADIC_TEMPLATES 0
#    endif

#    if ((__clang_major__ * 100) + __clang_minor__) >= 301 && __has_feature(cxx_constexpr)
#      define NASNR_COMPILER_CXX_CONSTEXPR 1
#    else
#      define NASNR_COMPILER_CXX_CONSTEXPR 0
#    endif

#    if ((__clang_major__ * 100) + __clang_minor__) >= 301 && __has_feature(cxx_override_control)
#      define NASNR_COMPILER_CXX_FINAL 1
#    else
#      define NASNR_COMPILER_CXX_FINAL 0
#    endif

#    if ((__clang_major__ * 100) + __clang_minor__) >= 301 && __has_feature(cxx_noexcept)
#      define NASNR_COMPILER_CXX_NOEXCEPT 1
#    else
#      define NASNR_COMPILER_CXX_NOEXCEPT 0
#    endif

#    if ((__clang_major__ * 100) + __clang_minor__) >= 301 && __has_feature(cxx_override_control)
#      define NASNR_COMPILER_CXX_OVERRIDE 1
#    else
#      define NASNR_COMPILER_CXX_OVERRIDE 0
#    endif

#    if ((__clang_major__ * 100) + __clang_minor__) >= 301 && __cplusplus >= 201103L
#      define NASNR_COMPILER_CXX_EXTERN_TEMPLATES 1
#    else
#      define NASNR_COMPILER_CXX_EXTERN_TEMPLATES 0
#    endif

#    if ((__clang_major__ * 100) + __clang_minor__) >= 301 && __has_feature(cxx_deleted_functions)
#      define NASNR_COMPILER_CXX_DELETED_FUNCTIONS 1
#    else
#      define NASNR_COMPILER_CXX_DELETED_FUNCTIONS 0
#    endif

#    if ((__clang_major__ * 100) + __clang_minor__) >= 301 && __has_feature(cxx_alignas)
#      define NASNR_COMPILER_CXX_ALIGNAS 1
#    else
#      define NASNR_COMPILER_CXX_ALIGNAS 0
#    endif

#    if ((__clang_major__ * 100) + __clang_minor__) >= 301 && __has_feature(cxx_nullptr)
#      define NASNR_COMPILER_CXX_NULLPTR 1
#    else
#      define NASNR_COMPILER_CXX_NULLPTR 0
#    endif

#    if ((__clang_major__ * 100) + __clang_minor__) >= 301 && __has_feature(cxx_alignas)
#      define NASNR_COMPILER_CXX_ALIGNOF 1
#    else
#      define NASNR_COMPILER_CXX_ALIGNOF 0
#    endif

#    if ((__clang_major__ * 100) + __clang_minor__) >= 301 && __has_feature(cxx_static_assert)
#      define NASNR_COMPILER_CXX_STATIC_ASSERT 1
#    else
#      define NASNR_COMPILER_CXX_STATIC_ASSERT 0
#    endif

#    if ((__clang_major__ * 100) + __clang_minor__) >= 304 && __cplusplus > 201103L
#      define NASNR_COMPILER_CXX_ATTRIBUTE_DEPRECATED 1
#    else
#      define NASNR_COMPILER_CXX_ATTRIBUTE_DEPRECATED 0
#    endif

#    if ((__clang_major__ * 100) + __clang_minor__) >= 304 && __cplusplus > 201103L
#define NASNR_COMPILER_CXX_ATTRIBUTE_NODISCARD 1
#else
#define NASNR_COMPILER_CXX_ATTRIBUTE_NODISCARD 0
#endif

#    if ((__clang_major__ * 100) + __clang_minor__) >= 304 && __cplusplus > 201103L
#define NASNR_COMPILER_CXX_ATTRIBUTE_INLINE 1
#else
#define NASNR_COMPILER_CXX_ATTRIBUTE_INLINE 0
#endif

#    if ((__clang_major__ * 100) + __clang_minor__) >= 304 && __cplusplus > 201103L
#define NASNR_COMPILER_CXX_BRACE_OR_EQUAL_INITIALIZER 1
#else
#define NASNR_COMPILER_CXX_BRACE_OR_EQUAL_INITIALIZER 0
#endif

#define NASNR_COMPILER_CXX_TYPE_DEDUCE 1
#define NASNR_COMPILER_CXX_USING_ALIAS 1
#define   NASNR_COMPILER_CXX_STATIC_CAST_VOID 1
#define NASNR_COMPILER_CXX_STDSIZE 1
#define NASNR_COMPILER_CXX_VECTOR_DATA 1
#define NASNR_COMPILER_CXX_INTTYPES 1
#define NASNR_COMPILER_CXX_VA_COPY 1

#  else
#    error Unsupported compiler
#  endif

#  if defined(NASNR_COMPILER_CXX_CONSTEXPR) && NASNR_COMPILER_CXX_CONSTEXPR
#    define NASNR_CONSTEXPR constexpr
#  else
#    define NASNR_CONSTEXPR
#  endif


#  if defined(NASNR_COMPILER_CXX_FINAL) && NASNR_COMPILER_CXX_FINAL
#    define NASNR_FINAL final
#  else
#    define NASNR_FINAL
#  endif


#  if defined(NASNR_COMPILER_CXX_NOEXCEPT) && NASNR_COMPILER_CXX_NOEXCEPT
#    define NASNR_NOEXCEPT noexcept
#    define NASNR_NOEXCEPT_EXPR(X) noexcept(X)
#  else
#    define NASNR_NOEXCEPT
#    define NASNR_NOEXCEPT_EXPR(X)
#  endif


#  if defined(NASNR_COMPILER_CXX_OVERRIDE) && NASNR_COMPILER_CXX_OVERRIDE
#    define NASNR_OVERRIDE override
#  else
#    define NASNR_OVERRIDE
#  endif


#  if defined(NASNR_COMPILER_CXX_EXTERN_TEMPLATES) && NASNR_COMPILER_CXX_EXTERN_TEMPLATES
#    define NASNR_EXTERN_TEMPLATE extern
#  else
#    define NASNR_EXTERN_TEMPLATE
#  endif


#  if defined(NASNR_COMPILER_CXX_DELETED_FUNCTIONS) && NASNR_COMPILER_CXX_DELETED_FUNCTIONS
#    define NASNR_DELETED_FUNCTION = delete
#  else
#    define NASNR_DELETED_FUNCTION
#  endif

#if defined(NASNR_COMPILER_CXX_DEFAULT_FUNCTIONS) && NASNR_COMPILER_CXX_DEFAULT_FUNCTIONS
#define NASNR_DEFAULT_FUNCTION = default
#else
#define NASNR_DEFAULT_FUNCTION
#endif

#if defined(NASNR_COMPILER_CXX_ATTRIBUTE_NODISCARD) && NASNR_COMPILER_CXX_ATTRIBUTE_NODISCARD
#define NASNR_NODISCARD [[nodiscard]]
#else
#define NASNR_NODISCARD
#endif

#if defined(NASNR_COMPILER_CXX_TYPE_DEDUCE) && \
    NASNR_COMPILER_CXX_TYPE_DEDUCE
#define NASNR_AUTO(X) auto
#else
#define NASNR_AUTO(X) X
#endif

#if defined(NASNR_COMPILER_CXX_INLINE) && NASNR_COMPILER_CXX_INLINE
#define NASNR_INLINE inline
#else
#define NASNR_INLINE __declspec(selectany) extern
#endif

#if defined(NASNR_COMPILER_CXX_USING_ALIAS) && NASNR_COMPILER_CXX_USING_ALIAS
#else
#endif

#if defined(NASNR_COMPILER_CXX_BRACE_OR_EQUAL_INITIALIZER) && NASNR_COMPILER_CXX_BRACE_OR_EQUAL_INITIALIZER
#define NASNR_EQUAL_INIT(X) = X
#define NASNR_LIST_INIT(X, ...) {__VA_ARGS__}
#else
#define NASNR_EQUAL_INIT(X)
#define NASNR_LIST_INIT(X, ...) X(__VA_ARGS__)
#endif

#  if defined(NASNR_COMPILER_CXX_ALIGNAS) && NASNR_COMPILER_CXX_ALIGNAS
#    define NASNR_ALIGNAS(X) alignas(X)
#  elif NASNR_COMPILER_IS_GNU || NASNR_COMPILER_IS_Clang || NASNR_COMPILER_IS_AppleClang
#    define NASNR_ALIGNAS(X) __attribute__ ((__aligned__(X)))
#  elif NASNR_COMPILER_IS_MSVC
#    define NASNR_ALIGNAS(X) __declspec(align(X))
#  else
#    define NASNR_ALIGNAS(X)
#  endif


#  if defined(NASNR_COMPILER_CXX_NULLPTR) && NASNR_COMPILER_CXX_NULLPTR
#    define NASNR_NULLPTR nullptr
#  elif NASNR_COMPILER_IS_GNU
#    define NASNR_NULLPTR __null
#  else
#define nullptr 0
#    define NASNR_NULLPTR 0
#  endif


#  if defined(NASNR_COMPILER_CXX_ALIGNOF) && NASNR_COMPILER_CXX_ALIGNOF
#    define NASNR_ALIGNOF(X) alignof(X)
#  elif NASNR_COMPILER_IS_GNU || NASNR_COMPILER_IS_Clang || NASNR_COMPILER_IS_AppleClang
#    define NASNR_ALIGNOF(X) __alignof__(X)
#  elif NASNR_COMPILER_IS_MSVC
#    define NASNR_ALIGNOF(X) __alignof(X)
#  endif

#  if defined(NASNR_COMPILER_CXX_STATIC_ASSERT) && NASNR_COMPILER_CXX_STATIC_ASSERT
#    define NASNR_STATIC_ASSERT(X) static_assert(X, #X)
#    define NASNR_STATIC_ASSERT_MSG(X, MSG) static_assert(X, MSG)
#  else
#    define NASNR_STATIC_ASSERT_JOIN(X, Y) NASNR_STATIC_ASSERT_JOIN_IMPL(X, Y)
#    define NASNR_STATIC_ASSERT_JOIN_IMPL(X, Y) X##Y
template<bool> struct NASNRStaticAssert;
template<> struct NASNRStaticAssert<true>{};
#    define NASNR_STATIC_ASSERT(X) enum { NASNR_STATIC_ASSERT_JOIN(NASNRStaticAssertEnum, __LINE__) = sizeof(NASNRStaticAssert<X>) }
#    define NASNR_STATIC_ASSERT_MSG(X, MSG) enum { NASNR_STATIC_ASSERT_JOIN(NASNRStaticAssertEnum, __LINE__) = sizeof(NASNRStaticAssert<X>) }
#  endif


#  ifndef NASNR_DEPRECATED
#    if defined(NASNR_COMPILER_CXX_ATTRIBUTE_DEPRECATED) && NASNR_COMPILER_CXX_ATTRIBUTE_DEPRECATED
#      define NASNR_DEPRECATED [[deprecated]]
#      define NASNR_DEPRECATED_MSG(MSG) [[deprecated(MSG)]]
#    elif NASNR_COMPILER_IS_GNU || NASNR_COMPILER_IS_Clang
#      define NASNR_DEPRECATED __attribute__((__deprecated__))
#      define NASNR_DEPRECATED_MSG(MSG) __attribute__((__deprecated__(MSG)))
#    elif NASNR_COMPILER_IS_MSVC
#      define NASNR_DEPRECATED __declspec(deprecated)
#      define NASNR_DEPRECATED_MSG(MSG) __declspec(deprecated(MSG))
#    else
#      define NASNR_DEPRECATED
#      define NASNR_DEPRECATED_MSG(MSG)
#    endif
#  endif

#endif

#ifndef __cplusplus
# define NASNR_COMPILER_IS_Clang 0
# define NASNR_COMPILER_IS_GNU 0
# define NASNR_COMPILER_IS_MSVC 0

#if defined(__clang__)
# undef NASNR_COMPILER_IS_Clang
# define NASNR_COMPILER_IS_Clang 1

#elif defined(__GNUC__)
# undef NASNR_COMPILER_IS_GNU
# define NASNR_COMPILER_IS_GNU 1

#elif defined(_MSC_VER)
# undef NASNR_COMPILER_IS_MSVC
# define NASNR_COMPILER_IS_MSVC 1

#endif

#  if NASNR_COMPILER_IS_GNU

#    if !((__GNUC__ * 100 + __GNUC_MINOR__) >= 304)
#      error Unsupported compiler version
#    endif

# define NASNR_COMPILER_VERSION_MAJOR (__GNUC__)
# if defined(__GNUC_MINOR__)
#  define NASNR_COMPILER_VERSION_MINOR (__GNUC_MINOR__)
# endif
# if defined(__GNUC_PATCHLEVEL__)
#  define NASNR_COMPILER_VERSION_PATCH (__GNUC_PATCHLEVEL__)
# endif

#    if (__GNUC__ * 100 + __GNUC_MINOR__) >= 304 && defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#      define NASNR_COMPILER_C_RESTRICT 1
#    else
#      define NASNR_COMPILER_C_RESTRICT 0
#    endif

#  elif NASNR_COMPILER_IS_MSVC

#    if !(_MSC_VER >= 1500)
#      error Unsupported compiler version
#    endif

  /* _MSC_VER = VVRR */
# define NASNR_COMPILER_VERSION_MAJOR (_MSC_VER / 100)
# define NASNR_COMPILER_VERSION_MINOR (_MSC_VER % 100)
# if defined(_MSC_FULL_VER)
#  if _MSC_VER >= 1400
    /* _MSC_FULL_VER = VVRRPPPPP */
#   define NASNR_COMPILER_VERSION_PATCH (_MSC_FULL_VER % 100000)
#  else
    /* _MSC_FULL_VER = VVRRPPPP */
#   define NASNR_COMPILER_VERSION_PATCH (_MSC_FULL_VER % 10000)
#  endif
# endif
# if defined(_MSC_BUILD)
#  define NASNR_COMPILER_VERSION_TWEAK (_MSC_BUILD)
# endif

#    define NASNR_COMPILER_C_RESTRICT 0

#  elif NASNR_COMPILER_IS_Clang

#    if !(((__clang_major__ * 100) + __clang_minor__) >= 304)
#      error Unsupported compiler version
#    endif

# define NASNR_COMPILER_VERSION_MAJOR (__clang_major__)
# define NASNR_COMPILER_VERSION_MINOR (__clang_minor__)
# define NASNR_COMPILER_VERSION_PATCH (__clang_patchlevel__)
# if defined(_MSC_VER)
   /* _MSC_VER = VVRR */
#  define NASNR_SIMULATE_VERSION_MAJOR (_MSC_VER / 100)
#  define NASNR_SIMULATE_VERSION_MINOR (_MSC_VER % 100)
# endif

#    if ((__clang_major__ * 100) + __clang_minor__) >= 304 && defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
#      define NASNR_COMPILER_C_RESTRICT 1
#    else
#      define NASNR_COMPILER_C_RESTRICT 0
#    endif

#  else
#    error Unsupported compiler
#  endif

#  if defined(NASNR_COMPILER_C_RESTRICT) && NASNR_COMPILER_C_RESTRICT
#    define NASNR_RESTRICT restrict
#  else
#    define NASNR_RESTRICT
#  endif

#endif

