/*
 * This file is part of the Micro Python project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2013, 2014 Damien P. George
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#ifndef __MICROPY_INCLUDED_PY_MPCONFIG_H__
#define __MICROPY_INCLUDED_PY_MPCONFIG_H__

// This file contains default configuration settings for MicroPython.
// You can override any of the options below using mpconfigport.h file
// located in a directory of your port.

// mpconfigport.h is a file containing configuration settings for a
// particular port. mpconfigport.h is actually a default name for
// such config, and it can be overriden using MP_CONFIGFILE preprocessor
// define (you can do that by passing CFLAGS_EXTRA='-DMP_CONFIGFILE="<file.h>"'
// argument to make when using standard MicroPython makefiles).
// This is useful to have more than one config per port, for example,
// release vs debug configs, etc. Note that if you switch from one config
// to another, you must rebuild from scratch using "-B" switch to make.

#ifdef MP_CONFIGFILE
#include MP_CONFIGFILE
#else
#include <mpconfigport.h>
#endif

// Any options not explicitly set in mpconfigport.h will get default
// values below.

/*****************************************************************************/
/* Object representation                                                     */

// A Micro Python object is a machine word having the following form:
//  - xxxx...xxx1 : a small int, bits 1 and above are the value
//  - xxxx...xx10 : a qstr, bits 2 and above are the value
//  - xxxx...xx00 : a pointer to an mp_obj_base_t (unless a fake object)
#define MICROPY_OBJ_REPR_A (0)

// A Micro Python object is a machine word having the following form:
//  - xxxx...xx01 : a small int, bits 2 and above are the value
//  - xxxx...xx11 : a qstr, bits 2 and above are the value
//  - xxxx...xxx0 : a pointer to an mp_obj_base_t (unless a fake object)
#define MICROPY_OBJ_REPR_B (1)

#ifndef MICROPY_OBJ_REPR
#define MICROPY_OBJ_REPR (MICROPY_OBJ_REPR_A)
#endif

/*****************************************************************************/
/* Memory allocation policy                                                  */

// Number of words allocated (in BSS) to the GC stack (minimum is 1)
#ifndef MICROPY_ALLOC_GC_STACK_SIZE
#define MICROPY_ALLOC_GC_STACK_SIZE (64)
#endif

// Number of bytes to allocate initially when creating new chunks to store
// interned string data.  Smaller numbers lead to more chunks being needed
// and more wastage at the end of the chunk.  Larger numbers lead to wasted
// space at the end when no more strings need interning.
#ifndef MICROPY_ALLOC_QSTR_CHUNK_INIT
#define MICROPY_ALLOC_QSTR_CHUNK_INIT (128)
#endif

// Initial amount for lexer indentation level
#ifndef MICROPY_ALLOC_LEXER_INDENT_INIT
#define MICROPY_ALLOC_LEXER_INDENT_INIT (10)
#endif

// Increment for lexer indentation level
#ifndef MICROPY_ALLOC_LEXEL_INDENT_INC
#define MICROPY_ALLOC_LEXEL_INDENT_INC (8)
#endif

// Initial amount for parse rule stack
#ifndef MICROPY_ALLOC_PARSE_RULE_INIT
#define MICROPY_ALLOC_PARSE_RULE_INIT (64)
#endif

// Increment for parse rule stack
#ifndef MICROPY_ALLOC_PARSE_RULE_INC
#define MICROPY_ALLOC_PARSE_RULE_INC (16)
#endif

// Initial amount for parse result stack
#ifndef MICROPY_ALLOC_PARSE_RESULT_INIT
#define MICROPY_ALLOC_PARSE_RESULT_INIT (32)
#endif

// Increment for parse result stack
#ifndef MICROPY_ALLOC_PARSE_RESULT_INC
#define MICROPY_ALLOC_PARSE_RESULT_INC (16)
#endif

// Strings this length or less will be interned by the parser
#ifndef MICROPY_ALLOC_PARSE_INTERN_STRING_LEN
#define MICROPY_ALLOC_PARSE_INTERN_STRING_LEN (10)
#endif

// Initial amount for ids in a scope
#ifndef MICROPY_ALLOC_SCOPE_ID_INIT
#define MICROPY_ALLOC_SCOPE_ID_INIT (4)
#endif

// Increment for ids in a scope
#ifndef MICROPY_ALLOC_SCOPE_ID_INC
#define MICROPY_ALLOC_SCOPE_ID_INC (6)
#endif

// Maximum length of a path in the filesystem
// So we can allocate a buffer on the stack for path manipulation in import
#ifndef MICROPY_ALLOC_PATH_MAX
#define MICROPY_ALLOC_PATH_MAX (512)
#endif

// Initial size of module dict
#ifndef MICROPY_MODULE_DICT_SIZE
#define MICROPY_MODULE_DICT_SIZE (1)
#endif

// Whether realloc/free should be passed allocated memory region size
// You must enable this if MICROPY_MEM_STATS is enabled
#ifndef MICROPY_MALLOC_USES_ALLOCATED_SIZE
#define MICROPY_MALLOC_USES_ALLOCATED_SIZE (0)
#endif

// Number of bytes used to store qstr length
// Dictates hard limit on maximum Python identifier length, but 1 byte
// (limit of 255 bytes in an identifier) should be enough for everyone
#ifndef MICROPY_QSTR_BYTES_IN_LEN
#define MICROPY_QSTR_BYTES_IN_LEN (1)
#endif

// Avoid using C stack when making Python function calls. C stack still
// may be used if there's no free heap.
#ifndef MICROPY_STACKLESS
#define MICROPY_STACKLESS (0)
#endif

// Never use C stack when making Python function calls. This may break
// testsuite as will subtly change which exception is thrown in case
// of too deep recursion and other similar cases.
#ifndef MICROPY_STACKLESS_STRICT
#define MICROPY_STACKLESS_STRICT (0)
#endif

/*****************************************************************************/
/* Micro Python emitters                                                     */

// Whether to emit CPython byte codes (for debugging/testing)
// Enabling this overrides all other emitters
#ifndef MICROPY_EMIT_CPYTHON
#define MICROPY_EMIT_CPYTHON (0)
#endif

// Whether to emit x64 native code
#ifndef MICROPY_EMIT_X64
#define MICROPY_EMIT_X64 (0)
#endif

// Whether to emit x86 native code
#ifndef MICROPY_EMIT_X86
#define MICROPY_EMIT_X86 (0)
#endif

// Whether to emit thumb native code
#ifndef MICROPY_EMIT_THUMB
#define MICROPY_EMIT_THUMB (0)
#endif

// Whether to enable the thumb inline assembler
#ifndef MICROPY_EMIT_INLINE_THUMB
#define MICROPY_EMIT_INLINE_THUMB (0)
#endif

// Whether to enable float support in the Thumb2 inline assembler
#ifndef MICROPY_EMIT_INLINE_THUMB_FLOAT
#define MICROPY_EMIT_INLINE_THUMB_FLOAT (1)
#endif

// Whether to emit ARM native code
#ifndef MICROPY_EMIT_ARM
#define MICROPY_EMIT_ARM (0)
#endif

// Convenience definition for whether any native emitter is enabled
#define MICROPY_EMIT_NATIVE (MICROPY_EMIT_X64 || MICROPY_EMIT_X86 || MICROPY_EMIT_THUMB || MICROPY_EMIT_ARM)

/*****************************************************************************/
/* Compiler configuration                                                    */

// Whether to enable lookup of constants in modules; eg module.CONST
#ifndef MICROPY_COMP_MODULE_CONST
#define MICROPY_COMP_MODULE_CONST (0)
#endif

// Whether to enable constant optimisation; id = const(value)
#ifndef MICROPY_COMP_CONST
#define MICROPY_COMP_CONST (1)
#endif

// Whether to enable optimisation of: a, b = c, d
// Costs 124 bytes (Thumb2)
#ifndef MICROPY_COMP_DOUBLE_TUPLE_ASSIGN
#define MICROPY_COMP_DOUBLE_TUPLE_ASSIGN (1)
#endif

// Whether to enable optimisation of: a, b, c = d, e, f
// Cost 156 bytes (Thumb2)
#ifndef MICROPY_COMP_TRIPLE_TUPLE_ASSIGN
#define MICROPY_COMP_TRIPLE_TUPLE_ASSIGN (0)
#endif

/*****************************************************************************/
/* Internal debugging stuff                                                  */

// Whether to collect memory allocation stats
#ifndef MICROPY_MEM_STATS
#define MICROPY_MEM_STATS (0)
#endif

// Whether to build functions that print debugging info:
//   mp_lexer_show_token
//   mp_bytecode_print
//   mp_parse_node_print
#ifndef MICROPY_DEBUG_PRINTERS
#define MICROPY_DEBUG_PRINTERS (0)
#endif

/*****************************************************************************/
/* Optimisations                                                             */

// Whether to use computed gotos in the VM, or a switch
// Computed gotos are roughly 10% faster, and increase VM code size by a little
#ifndef MICROPY_OPT_COMPUTED_GOTO
#define MICROPY_OPT_COMPUTED_GOTO (0)
#endif

// Whether to cache result of map lookups in LOAD_NAME, LOAD_GLOBAL, LOAD_ATTR,
// STORE_ATTR bytecodes.  Uses 1 byte extra RAM for each of these opcodes and
// uses a bit of extra code ROM, but greatly improves lookup speed.
#ifndef MICROPY_OPT_CACHE_MAP_LOOKUP_IN_BYTECODE
#define MICROPY_OPT_CACHE_MAP_LOOKUP_IN_BYTECODE (0)
#endif

/*****************************************************************************/
/* Python internal features                                                  */

// Whether to include the garbage collector
#ifndef MICROPY_ENABLE_GC
#define MICROPY_ENABLE_GC (0)
#endif

// Whether to enable finalisers in the garbage collector (ie call __del__)
#ifndef MICROPY_ENABLE_FINALISER
#define MICROPY_ENABLE_FINALISER (0)
#endif

// Whether to check C stack usage. C stack used for calling Python functions,
// etc. Not checking means segfault on overflow.
#ifndef MICROPY_STACK_CHECK
#define MICROPY_STACK_CHECK (0)
#endif

// Whether to have an emergency exception buffer
#ifndef MICROPY_ENABLE_EMERGENCY_EXCEPTION_BUF
#define MICROPY_ENABLE_EMERGENCY_EXCEPTION_BUF (0)
#endif
#if MICROPY_ENABLE_EMERGENCY_EXCEPTION_BUF
#   ifndef MICROPY_EMERGENCY_EXCEPTION_BUF_SIZE
#   define MICROPY_EMERGENCY_EXCEPTION_BUF_SIZE (0)   // 0 - implies dynamic allocation
#   endif
#endif

// Whether to include REPL helper function
#ifndef MICROPY_HELPER_REPL
#define MICROPY_HELPER_REPL (0)
#endif

// Whether port requires event-driven REPL functions
#ifndef MICROPY_REPL_EVENT_DRIVEN
#define MICROPY_REPL_EVENT_DRIVEN (0)
#endif

// Whether to include lexer helper function for unix
#ifndef MICROPY_HELPER_LEXER_UNIX
#define MICROPY_HELPER_LEXER_UNIX (0)
#endif

// Long int implementation
#define MICROPY_LONGINT_IMPL_NONE (0)
#define MICROPY_LONGINT_IMPL_LONGLONG (1)
#define MICROPY_LONGINT_IMPL_MPZ (2)

#ifndef MICROPY_LONGINT_IMPL
#define MICROPY_LONGINT_IMPL (MICROPY_LONGINT_IMPL_NONE)
#endif

#if MICROPY_LONGINT_IMPL == MICROPY_LONGINT_IMPL_LONGLONG
typedef long long mp_longint_impl_t;
#endif

// Whether to include information in the byte code to determine source
// line number (increases RAM usage, but doesn't slow byte code execution)
#ifndef MICROPY_ENABLE_SOURCE_LINE
#define MICROPY_ENABLE_SOURCE_LINE (0)
#endif

// Whether to include doc strings (increases RAM usage)
#ifndef MICROPY_ENABLE_DOC_STRING
#define MICROPY_ENABLE_DOC_STRING (0)
#endif

// Exception messages are short static strings
#define MICROPY_ERROR_REPORTING_TERSE    (1)
// Exception messages provide basic error details
#define MICROPY_ERROR_REPORTING_NORMAL   (2)
// Exception messages provide full info, e.g. object names
#define MICROPY_ERROR_REPORTING_DETAILED (3)

#ifndef MICROPY_ERROR_REPORTING
#define MICROPY_ERROR_REPORTING (MICROPY_ERROR_REPORTING_NORMAL)
#endif

// Whether issue warnings during compiling/execution
#ifndef MICROPY_WARNINGS
#define MICROPY_WARNINGS (0)
#endif

// Float and complex implementation
#define MICROPY_FLOAT_IMPL_NONE (0)
#define MICROPY_FLOAT_IMPL_FLOAT (1)
#define MICROPY_FLOAT_IMPL_DOUBLE (2)

#ifndef MICROPY_FLOAT_IMPL
#define MICROPY_FLOAT_IMPL (MICROPY_FLOAT_IMPL_NONE)
#endif

#if MICROPY_FLOAT_IMPL == MICROPY_FLOAT_IMPL_FLOAT
#define MICROPY_PY_BUILTINS_FLOAT (1)
#define MICROPY_FLOAT_C_FUN(fun) fun##f
typedef float mp_float_t;
#elif MICROPY_FLOAT_IMPL == MICROPY_FLOAT_IMPL_DOUBLE
#define MICROPY_PY_BUILTINS_FLOAT (1)
#define MICROPY_FLOAT_C_FUN(fun) fun
typedef double mp_float_t;
#else
#define MICROPY_PY_BUILTINS_FLOAT (0)
#endif

#ifndef MICROPY_PY_BUILTINS_COMPLEX
#define MICROPY_PY_BUILTINS_COMPLEX (MICROPY_PY_BUILTINS_FLOAT)
#endif

// Enable features which improve CPython compatibility
// but may lead to more code size/memory usage.
// TODO: Originally intended as generic category to not
// add bunch of once-off options. May need refactoring later
#ifndef MICROPY_CPYTHON_COMPAT
#define MICROPY_CPYTHON_COMPAT (1)
#endif

// Whether POSIX-semantics non-blocking streams are supported
#ifndef MICROPY_STREAMS_NON_BLOCK
#define MICROPY_STREAMS_NON_BLOCK (0)
#endif

// Whether module weak links are supported
#ifndef MICROPY_MODULE_WEAK_LINKS
#define MICROPY_MODULE_WEAK_LINKS (0)
#endif

// Whether frozen modules are supported
#ifndef MICROPY_MODULE_FROZEN
#define MICROPY_MODULE_FROZEN (0)
#endif

// Whether you can override builtins in the builtins module
#ifndef MICROPY_CAN_OVERRIDE_BUILTINS
#define MICROPY_CAN_OVERRIDE_BUILTINS (0)
#endif

// Whether to check that the "self" argument of a builtin method has the
// correct type.  Such an explicit check is only needed if a builtin
// method escapes to Python land without a first argument, eg
// list.append([], 1).  Without this check such calls will have undefined
// behaviour (usually segfault) if the first argument is the wrong type.
#ifndef MICROPY_BUILTIN_METHOD_CHECK_SELF_ARG
#define MICROPY_BUILTIN_METHOD_CHECK_SELF_ARG (1)
#endif

/*****************************************************************************/
/* Fine control over Python builtins, classes, modules, etc                  */

// Whether to implement attributes on functions
#ifndef MICROPY_PY_FUNCTION_ATTRS
#define MICROPY_PY_FUNCTION_ATTRS (0)
#endif

// Whether to support descriptors (__get__ and __set__)
// This costs some code size and makes all load attrs and store attrs slow
#ifndef MICROPY_PY_DESCRIPTORS
#define MICROPY_PY_DESCRIPTORS (0)
#endif

// Whether str object is proper unicode
#ifndef MICROPY_PY_BUILTINS_STR_UNICODE
#define MICROPY_PY_BUILTINS_STR_UNICODE (0)
#endif

// Whether str.splitlines() method provided
#ifndef MICROPY_PY_BUILTINS_STR_SPLITLINES
#define MICROPY_PY_BUILTINS_STR_SPLITLINES (0)
#endif

// Whether to support bytearray object
#ifndef MICROPY_PY_BUILTINS_BYTEARRAY
#define MICROPY_PY_BUILTINS_BYTEARRAY (1)
#endif

// Whether to support memoryview object
#ifndef MICROPY_PY_BUILTINS_MEMORYVIEW
#define MICROPY_PY_BUILTINS_MEMORYVIEW (0)
#endif

// Whether to support set object
#ifndef MICROPY_PY_BUILTINS_SET
#define MICROPY_PY_BUILTINS_SET (1)
#endif

// Whether to support slice subscript operators and slice object
#ifndef MICROPY_PY_BUILTINS_SLICE
#define MICROPY_PY_BUILTINS_SLICE (1)
#endif

// Whether to support frozenset object
#ifndef MICROPY_PY_BUILTINS_FROZENSET
#define MICROPY_PY_BUILTINS_FROZENSET (0)
#endif

// Whether to support property object
#ifndef MICROPY_PY_BUILTINS_PROPERTY
#define MICROPY_PY_BUILTINS_PROPERTY (1)
#endif

// Whether to implement the start/stop/step attributes (readback) on
// the "range" builtin type. Rarely used, and costs ~60 bytes (x86).
#ifndef MICROPY_PY_BUILTINS_RANGE_ATTRS
#define MICROPY_PY_BUILTINS_RANGE_ATTRS (1)
#endif

// Whether to support timeout exceptions (like socket.timeout)
#ifndef MICROPY_PY_BUILTINS_TIMEOUTERROR
#define MICROPY_PY_BUILTINS_TIMEOUTERROR (0)
#endif

// Whether to support complete set of special methods
// for user classes, otherwise only the most used
#ifndef MICROPY_PY_ALL_SPECIAL_METHODS
#define MICROPY_PY_ALL_SPECIAL_METHODS (0)
#endif

// Whether to support compile function
#ifndef MICROPY_PY_BUILTINS_COMPILE
#define MICROPY_PY_BUILTINS_COMPILE (0)
#endif

// Whether to support enumerate function(type)
#ifndef MICROPY_PY_BUILTINS_ENUMERATE
#define MICROPY_PY_BUILTINS_ENUMERATE (1)
#endif

// Whether to support the Python 2 execfile function
#ifndef MICROPY_PY_BUILTINS_EXECFILE
#define MICROPY_PY_BUILTINS_EXECFILE (0)
#endif

// Whether to support reversed function(type)
#ifndef MICROPY_PY_BUILTINS_REVERSED
#define MICROPY_PY_BUILTINS_REVERSED (1)
#endif

// Whether to define "NotImplemented" special constant
#ifndef MICROPY_PY_BUILTINS_NOTIMPLEMENTED
#define MICROPY_PY_BUILTINS_NOTIMPLEMENTED (0)
#endif

// Whether to set __file__ for imported modules
#ifndef MICROPY_PY___FILE__
#define MICROPY_PY___FILE__ (1)
#endif

// Whether to provide mem-info related functions in micropython module
#ifndef MICROPY_PY_MICROPYTHON_MEM_INFO
#define MICROPY_PY_MICROPYTHON_MEM_INFO (0)
#endif

// Whether to provide "array" module. Note that large chunk of the
// underlying code is shared with "bytearray" builtin type, so to
// get real savings, it should be disabled too.
#ifndef MICROPY_PY_ARRAY
#define MICROPY_PY_ARRAY (1)
#endif

// Whether to support slice assignments for array (and bytearray).
// This is rarely used, but adds ~0.5K of code.
#ifndef MICROPY_PY_ARRAY_SLICE_ASSIGN
#define MICROPY_PY_ARRAY_SLICE_ASSIGN (0)
#endif

// Whether to support attrtuple type (MicroPython extension)
// It provides space-efficient tuples with attribute access
#ifndef MICROPY_PY_ATTRTUPLE
#define MICROPY_PY_ATTRTUPLE (1)
#endif

// Whether to provide "collections" module
#ifndef MICROPY_PY_COLLECTIONS
#define MICROPY_PY_COLLECTIONS (1)
#endif

// Whether to provide "collections.OrderedDict" type
#ifndef MICROPY_PY_COLLECTIONS_ORDEREDDICT
#define MICROPY_PY_COLLECTIONS_ORDEREDDICT (0)
#endif

// Whether to provide "math" module
#ifndef MICROPY_PY_MATH
#define MICROPY_PY_MATH (1)
#endif

// Whether to provide special math functions: math.{erf,erfc,gamma,lgamma}
#ifndef MICROPY_PY_MATH_SPECIAL_FUNCTIONS
#define MICROPY_PY_MATH_SPECIAL_FUNCTIONS (0)
#endif

// Whether to provide "cmath" module
#ifndef MICROPY_PY_CMATH
#define MICROPY_PY_CMATH (0)
#endif

// Whether to provide "gc" module
#ifndef MICROPY_PY_GC
#define MICROPY_PY_GC (1)
#endif

// Whether to return number of collected objects from gc.collect()
#ifndef MICROPY_PY_GC_COLLECT_RETVAL
#define MICROPY_PY_GC_COLLECT_RETVAL (0)
#endif

// Whether to provide "io" module
#ifndef MICROPY_PY_IO
#define MICROPY_PY_IO (1)
#endif

// Whether to provide "io.FileIO" class
#ifndef MICROPY_PY_IO_FILEIO
#define MICROPY_PY_IO_FILEIO (0)
#endif

// Whether to provide "io.BytesIO" class
#ifndef MICROPY_PY_IO_BYTESIO
#define MICROPY_PY_IO_BYTESIO (1)
#endif

// Whether to provide "struct" module
#ifndef MICROPY_PY_STRUCT
#define MICROPY_PY_STRUCT (1)
#endif

// Whether to provide "sys" module
#ifndef MICROPY_PY_SYS
#define MICROPY_PY_SYS (1)
#endif

// Whether to provide "sys.maxsize" constant
#ifndef MICROPY_PY_SYS_MAXSIZE
#define MICROPY_PY_SYS_MAXSIZE (0)
#endif

// Whether to provide "sys.exc_info" function
// Avoid enabling this, this function is Python2 heritage
#ifndef MICROPY_PY_SYS_EXC_INFO
#define MICROPY_PY_SYS_EXC_INFO (0)
#endif

// Whether to provide "sys.exit" function
#ifndef MICROPY_PY_SYS_EXIT
#define MICROPY_PY_SYS_EXIT (0)
#endif

// Whether to provide sys.{stdin,stdout,stderr} objects
#ifndef MICROPY_PY_SYS_STDFILES
#define MICROPY_PY_SYS_STDFILES (0)
#endif

// Whether to provide sys.{stdin,stdout,stderr}.buffer object
// This is implemented per-port
#ifndef MICROPY_PY_SYS_STDIO_BUFFER
#define MICROPY_PY_SYS_STDIO_BUFFER (0)
#endif

// Extended modules

#ifndef MICROPY_PY_UCTYPES
#define MICROPY_PY_UCTYPES (0)
#endif

#ifndef MICROPY_PY_UZLIB
#define MICROPY_PY_UZLIB (0)
#endif

#ifndef MICROPY_PY_UJSON
#define MICROPY_PY_UJSON (0)
#endif

#ifndef MICROPY_PY_URE
#define MICROPY_PY_URE (0)
#endif

#ifndef MICROPY_PY_UHEAPQ
#define MICROPY_PY_UHEAPQ (0)
#endif

#ifndef MICROPY_PY_UHASHLIB
#define MICROPY_PY_UHASHLIB (0)
#endif

#ifndef MICROPY_PY_UBINASCII
#define MICROPY_PY_UBINASCII (0)
#endif

#ifndef MICROPY_PY_MACHINE
#define MICROPY_PY_MACHINE (0)
#endif

/*****************************************************************************/
/* Hooks for a port to add builtins                                          */

// Additional builtin function definitions - see builtintables.c:builtin_object_table for format.
#ifndef MICROPY_PORT_BUILTINS
#define MICROPY_PORT_BUILTINS
#endif

// Additional builtin module definitions - see builtintables.c:builtin_module_table for format.
#ifndef MICROPY_PORT_BUILTIN_MODULES
#define MICROPY_PORT_BUILTIN_MODULES
#endif

// Any module weak links - see builtintables.c:mp_builtin_module_weak_links_table.
#ifndef MICROPY_PORT_BUILTIN_MODULE_WEAK_LINKS
#define MICROPY_PORT_BUILTIN_MODULE_WEAK_LINKS
#endif

// Additional constant definitions for the compiler - see compile.c:mp_constants_table.
#ifndef MICROPY_PORT_CONSTANTS
#define MICROPY_PORT_CONSTANTS
#endif

// Any root pointers for GC scanning - see mpstate.c
#ifndef MICROPY_PORT_ROOT_POINTERS
#define MICROPY_PORT_ROOT_POINTERS
#endif

/*****************************************************************************/
/* Miscellaneous settings                                                    */

// All uPy objects in ROM must be aligned on at least a 4 byte boundary
// so that the small-int/qstr/pointer distinction can be made.  For machines
// that don't do this (eg 16-bit CPU), define the following macro to something
// like __attribute__((aligned(4))).
#ifndef MICROPY_OBJ_BASE_ALIGNMENT
#define MICROPY_OBJ_BASE_ALIGNMENT
#endif

// On embedded platforms, these will typically enable/disable irqs.
#ifndef MICROPY_BEGIN_ATOMIC_SECTION
#define MICROPY_BEGIN_ATOMIC_SECTION() (0)
#endif
#ifndef MICROPY_END_ATOMIC_SECTION
#define MICROPY_END_ATOMIC_SECTION(state) (void)(state)
#endif

// Allow to override static modifier for global objects, e.g. to use with
// object code analysis tools which don't support static symbols.
#ifndef STATIC
#define STATIC static
#endif

#define BITS_PER_BYTE (8)
#define BITS_PER_WORD (BITS_PER_BYTE * BYTES_PER_WORD)
// mp_int_t value with most significant bit set
#define WORD_MSBIT_HIGH (((mp_uint_t)1) << (BYTES_PER_WORD * 8 - 1))

// Make sure both MP_ENDIANNESS_LITTLE and MP_ENDIANNESS_BIG are
// defined and that they are the opposite of each other.
#if defined(MP_ENDIANNESS_LITTLE)
#define MP_ENDIANNESS_BIG (!MP_ENDIANNESS_LITTLE)
#elif defined(MP_ENDIANNESS_BIG)
#define MP_ENDIANNESS_LITTLE (!MP_ENDIANNESS_BIG)
#else
  // Endiannes not defined by port so try to autodetect it.
  #if defined(__BYTE_ORDER__)
    #if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
      #define MP_ENDIANNESS_LITTLE (1)
    #else
      #define MP_ENDIANNESS_LITTLE (0)
    #endif
  #elif defined(__LITTLE_ENDIAN__) || defined(__LITTLE_ENDIAN) || defined (_LITTLE_ENDIAN)
    #define MP_ENDIANNESS_LITTLE (1)
  #elif defined(__BIG_ENDIAN__) || defined(__BIG_ENDIAN) || defined (_BIG_ENDIAN)
    #define MP_ENDIANNESS_LITTLE (0)
  #else
    #include <endian.h>
      #if defined(__BYTE_ORDER)
        #if __BYTE_ORDER == __LITTLE_ENDIAN
          #define MP_ENDIANNESS_LITTLE (1)
        #else
          #define MP_ENDIANNESS_LITTLE (0)
        #endif
      #else
        #error endianness not defined and cannot detect it
      #endif
  #endif
  #define MP_ENDIANNESS_BIG (!MP_ENDIANNESS_LITTLE)
#endif

// Make a pointer to RAM callable (eg set lower bit for Thumb code)
// (This scheme won't work if we want to mix Thumb and normal ARM code.)
#ifndef MICROPY_MAKE_POINTER_CALLABLE
#define MICROPY_MAKE_POINTER_CALLABLE(p) (p)
#endif

// If these MP_PLAT_*_EXEC macros are overridden then the memory allocated by them
// must be somehow reachable for marking by the GC, since the native code
// generators store pointers to GC managed memory in the code.
#ifndef MP_PLAT_ALLOC_EXEC
#define MP_PLAT_ALLOC_EXEC(min_size, ptr, size) do { *ptr = m_new(byte, min_size); *size = min_size; } while (0)
#endif

#ifndef MP_PLAT_FREE_EXEC
#define MP_PLAT_FREE_EXEC(ptr, size) m_del(byte, ptr, size)
#endif

// This macro is used to do all output (except when MICROPY_PY_IO is defined)
#ifndef MP_PLAT_PRINT_STRN
#define MP_PLAT_PRINT_STRN(str, len) printf("%.*s", (int)len, str)
#endif

#ifndef MP_SSIZE_MAX
#ifndef SYLIXOS
#define MP_SSIZE_MAX SSIZE_MAX
#else
#define MP_SSIZE_MAX INT_MAX
#endif
#endif

// printf format spec to use for mp_int_t and friends
#ifndef INT_FMT
#ifdef __LP64__
// Archs where mp_int_t == long, long != int
#define UINT_FMT "%lu"
#define INT_FMT "%ld"
#else
// Archs where mp_int_t == int
#define UINT_FMT "%u"
#define INT_FMT "%d"
#endif
#endif //INT_FMT

// Modifier for function which doesn't return
#ifndef NORETURN
#define NORETURN __attribute__((noreturn))
#endif

// Modifier for weak functions
#ifndef MP_WEAK
#define MP_WEAK __attribute__((weak))
#endif

// Condition is likely to be true, to help branch prediction
#ifndef MP_LIKELY
#define MP_LIKELY(x) __builtin_expect((x), 1)
#endif

// Condition is likely to be false, to help branch prediction
#ifndef MP_UNLIKELY
#define MP_UNLIKELY(x) __builtin_expect((x), 0)
#endif

#endif // __MICROPY_INCLUDED_PY_MPCONFIG_H__
