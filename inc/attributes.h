#ifndef ATTRIBUTES_H
# define ATTRIBUTES_H

#define MALLOC_COLD				__attribute__((cold))
#define MALLOC_NONNULL(...)		__attribute__((nonnull))
#define MALLOC_DEPRECATED		__attribute__((deprecated))
#define MALLOC_ERROR(msg)		__attribute__((error(msg)))
#define MALLOC_UNUSED_RESULT	__attribute__((warn_unused_result))
#define MALLOC_RETURNS_NONNULL	__attribute__((returns_nonnull))
#define MALLOC_ALWAYS_INLINE	__attribute__((__always_inline__))

#endif