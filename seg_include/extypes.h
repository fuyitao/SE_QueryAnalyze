#ifndef _EX_TYPES_H
#define _EX_TYPES_H

/* all types used should be explicit sized */

typedef void* ref;

typedef void* ptr;

#ifdef __POSIX__
typedef unsigned int boolean;
#endif

#define BYTES_OF_UINT8			1
#define BYTES_OF_UINT16			2
#define BYTES_OF_UINT32			4
#define BYTES_OF_UINT64			8

#define BYTES_OF_INT8			1
#define BYTES_OF_INT16			2
#define BYTES_OF_INT32			4
#define BYTES_OF_INT64			8

#define BYTES_OF_REF			4

#ifndef NULL
#define NULL					0
#endif

#define EX_ERROR				(-1)

#ifndef __cplusplus
#define true 1
#define false 0
typedef uint8   bool;
#define inline __inline
#endif

/* array type declarations */
typedef struct _RefArray {
    uint32 len;
    ref value[1];
} RefArray;

#ifndef IN
#define IN
#endif
#ifndef OUT
#define OUT
#endif
#ifndef INOUT
#define INOUT
#endif
#ifndef OPTIONAL
#define OPTIONAL
#endif

#endif /* #ifndef _EX_TYPES_H */
