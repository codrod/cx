/*
	C Extension - Universal Interface II - Header
	Cody M. Rodgers
*/

/*

*/

#if !CXUI_VERSION

	#define CXUI_VERSION 1000000L

	#include <stdlib.h>
	#include <stdarg.h>
	#include <errno.h>
	#include <string.h>
	#include <ctype.h>
	#include <limits.h>
	#include <float.h>
	#include <math.h>
	#include <time.h>

	#include <cxdef.h>
	#include <cxerror.h>

	#define CXUI_COM_ERR -2
	#define CXUI_COM_LES -1
	#define CXUI_COM_EQU 0
	#define CXUI_COM_GRE 1

	#define CXUI_NUM_RECALLS 4

	#define CXUI_DEFAULT_FLOAT_PRECISION 6
	#define CXUI_DEFAULT_FLOAT_BASE 10

	typedef struct cxui
	{
		char *name;
		cxsize_t size_of;

		/*
			fail-safe:
			This function may fail but it can not interupt the flow of execution
			by jumping, or terminating the thread/process but it may throw exceptions.
			If this function sets errno then errno will not be overwritten
			by the calling function.
		*/

		/*
			construct: fail-safe

			This function will consturct the 'obj'. The width of 'obj' in bytes is 'size_of'.
			Implementation specific arguments will be passed on using 'argv'. If
			the implementation does not have any arguments then it will ignore 'argv'.
		*/
		void (*construct)(cxsize_t size_of, cxaddress_t obj, va_list *argv);

		/*
			destruct: fail-safe

			This function will destruct the 'obj'.
		*/
		void (*destruct)(cxaddress_t obj);

		/*
			compare: fail-safe

			This function will compare 'obj1' to 'obj2' the width of both
			objects, in bytes, is 'size_of'. If 'obj1' < 'obj2' then this function will
			return CXUI_COMPARE_LESSER. If 'obj1' > 'obj2' then this function will return
			CXUI_COMPARE_GREATER. If 'ojb' = 'obj2' then this function will return CXUI_COMPARE_EQUAL.

			The relational operators '<' and '>' need not be defined for every type; If those
			operators are not defined for the type then if 'obj1' = 'obj2' this function will
			return CXUI_COMPARE_EQUAL else this function will return CXUI_COMPARE_NOT_EQUAL
			which is an alias for CXUI_COMPARE_GREATER.

			If this function fails it will return CXUI_COMPARE_ERROR.
		*/
		int (*compare)(cxsize_t size_of, const cxaddress_t obj1, const cxaddress_t obj2, va_list *argv);

		/*
			copy: fail-safe

			This function will copy 'src' into 'des'. The width of both objects, in bytes,
			is 'size_of'. This function will return zero unless an error occurs.

			If an invocation like this "cop(sizeof(type), A, B)"
			is succesfull then its reverse invocation "cop(sizeof(type), B, A)"
			must be succesfull aswell.

			Example: If the object this function was copying happened to be a container then this
			function can dynamically manage the size of that container. More importantly this
			function can fail to expand the container but it can not fail to shrink the container
			(or simply occupy less space in the container). So if cop(sizeof(type), A, B) expands B, to
			to contain A, then cop(sizeof(type), B, A) will not cause an expansion and so should
			always be succesfull assuming no other errors are possible.
		*/
		int (*copy)(cxsize_t size_of, cxaddress_t des, const cxaddress_t src);


		/*
			string to object: fail-safe

			This function will convert the string represented by 'str' into an object of
			the same datatype as 'obj' and then copy that object into 'obj'. The width of
			'obj', in bytes, is 'size_of'. Implementation-specific arguments will passed on
			using 'argv'. If the implementation does not have arguments then it will ignore
			'argv'. This function will not edit the string represented by 'str'.

			If the function is succesfull then it will return the number of characters
			interpreted. Or if the function fails then it will return 0. If this function
			fails it still may change the value of 'obj'.
		*/
		cxsize_t (*string_to)(cxsize_t size_of, cxaddress_t str, cxaddress_t obj, va_list *argv);

		cxsize_t (*to_string)(cxsize_t size_of, const cxaddress_t obj, cxaddress_t str, va_list *argv);
	}
	cxui_t;

	int cxui_binary_compare(cxsize_t size_of, const cxaddress_t obj1, const cxaddress_t obj2, va_list *argv);
	int cxui_ints_compare(cxsize_t size_of, const cxaddress_t obj1, const cxaddress_t obj2, va_list *argv);
	int cxui_floats_equal(cxsize_t size_of, const cxaddress_t obj1, const cxaddress_t obj2, int ndigs, int base);
	int cxui_floats_compare(cxsize_t size_of, const cxaddress_t obj1, const cxaddress_t obj2, va_list *argv);
	int cxui_char_compare(cxsize_t size_of, const cxaddress_t obj1, const cxaddress_t obj2, va_list *argv);
	int cxui_time_t_compare(cxsize_t size_of, const cxaddress_t obj1, const cxaddress_t obj2, va_list *argv);
	int cxui_struct_tm_compare(cxsize_t size_of, const cxaddress_t obj1, const cxaddress_t obj2, va_list *argv);
	int cxui_clock_t_compare(cxsize_t size_of, const cxaddress_t obj1, const cxaddress_t obj2, va_list *argv);

	int cxui_binary_copy(cxsize_t size_of, cxaddress_t des, const cxaddress_t src);

	/*
	cxsize_t cxui_simple_strto(cxsize_t size_of, cxaddress_t str, cxaddress_t obj, va_list *argv);
	cxsize_t cxui_simple_tostr(cxsize_t size_of, const cxaddress_t obj, cxaddress_t str, va_list *argv);

	cxsize_t cxui_unsigned_ints_strto(cxsize_t size_of, cxaddress_t str, cxaddress_t obj, va_list *argv);
	cxsize_t cxui_unsigned_ints_tostr(cxsize_t size_of, const cxaddress_t obj, cxaddress_t str, va_list *argv);

	cxsize_t cxui_ints_strto(cxsize_t size_of, cxaddress_t str, cxaddress_t obj, va_list *argv);
	cxsize_t cxui_ints_tostr(cxsize_t size_of, const cxaddress_t obj, cxaddress_t str, va_list *argv);

	cxsize_t cxui_floats_strto(cxsize_t size_of, cxaddress_t str, cxaddress_t obj, va_list *argv);
	cxsize_t cxui_floats_tostr(cxsize_t size_of, const cxaddress_t obj, cxaddress_t str, va_list *argv);

	cxsize_t cxui_char_strto(cxsize_t size_of, cxaddress_t str, cxaddress_t obj, va_list *argv);
	cxsize_t cxui_char_tostr(cxsize_t size_of, const cxaddress_t obj, cxaddress_t str, va_list *argv);

	cxsize_t cxui_wchar_t_strto(cxsize_t size_of, cxaddress_t str, cxaddress_t obj, va_list *argv);
	cxsize_t cxui_wchar_t_tostr(cxsize_t size_of, const cxaddress_t obj, cxaddress_t str, va_list *argv);

	cxsize_t cxui_str_strto(cxsize_t size_of, cxaddress_t str, cxaddress_t obj, va_list *argv);
	cxsize_t cxui_str_tostr(cxsize_t size_of, const cxaddress_t obj, cxaddress_t str, va_list *argv);

	cxsize_t cxui_time_t_strto(cxsize_t size_of, cxaddress_t str, cxaddress_t obj, va_list *argv);
	cxsize_t cxui_time_t_tostr(cxsize_t size_of, const cxaddress_t obj, cxaddress_t str, va_list *argv);

	cxsize_t cxui_struct_tm_strto(cxsize_t size_of, cxaddress_t str, cxaddress_t obj, va_list *argv);
	cxsize_t cxui_struct_tm_tostr(cxsize_t size_of, const cxaddress_t obj, cxaddress_t str, va_list *argv);

	cxsize_t cxui_clock_t_strto(cxsize_t size_of, cxaddress_t str, cxaddress_t obj, va_list *argv);
	cxsize_t cxui_clock_t_tostr(cxsize_t size_of, const cxaddress_t obj, cxaddress_t str, va_list *argv);

	/*

	char

	cxsize_t cxui_simple_strto_char(cxsize_t size_of, cxaddress_t str, cxaddress_t obj, va_list *argv);
	cxsize_t cxui_simple_tostr_char(cxsize_t size_of, const cxaddress_t obj, cxaddress_t str, va_list *argv);

	cxsize_t cxui_unsigned_ints_strto_char(cxsize_t size_of, cxaddress_t str, cxaddress_t obj, va_list *argv);
	cxsize_t cxui_unsigned_ints_tostr_char(cxsize_t size_of, const cxaddress_t obj, cxaddress_t str, va_list *argv);

	cxsize_t cxui_ints_strto_char(cxsize_t size_of, cxaddress_t str, cxaddress_t obj, va_list *argv);
	cxsize_t cxui_ints_tostr_char(cxsize_t size_of, const cxaddress_t obj, cxaddress_t str, va_list *argv);

	cxsize_t cxui_floats_strto_char(cxsize_t size_of, cxaddress_t str, cxaddress_t obj, va_list *argv);
	cxsize_t cxui_floats_tostr_char(cxsize_t size_of, const cxaddress_t obj, cxaddress_t str, va_list *argv);

	cxsize_t cxui_char_strto_char(cxsize_t size_of, cxaddress_t str, cxaddress_t obj, va_list *argv);
	cxsize_t cxui_char_tostr_char(cxsize_t size_of, const cxaddress_t obj, cxaddress_t str, va_list *argv);

	cxsize_t cxui_wchar_t_strto_char(cxsize_t size_of, cxaddress_t str, cxaddress_t obj, va_list *argv);
	cxsize_t cxui_wchar_t_tostr_char(cxsize_t size_of, const cxaddress_t obj, cxaddress_t str, va_list *argv);

	cxsize_t cxui_str_strto_char(cxsize_t size_of, cxaddress_t str, cxaddress_t obj, va_list *argv);
	cxsize_t cxui_str_tostr_char(cxsize_t size_of, const cxaddress_t obj, cxaddress_t str, va_list *argv);

	cxsize_t cxui_time_t_strto_char(cxsize_t size_of, cxaddress_t str, cxaddress_t obj, va_list *argv);
	cxsize_t cxui_time_t_tostr_char(cxsize_t size_of, const cxaddress_t obj, cxaddress_t str, va_list *argv);

	cxsize_t cxui_struct_tm_strto_char(cxsize_t size_of, cxaddress_t str, cxaddress_t obj, va_list *argv);
	cxsize_t cxui_struct_tm_tostr_char(cxsize_t size_of, const cxaddress_t obj, cxaddress_t str, va_list *argv);

	cxsize_t cxui_clock_t_strto_char(cxsize_t size_of, cxaddress_t str, cxaddress_t obj, va_list *argv);
	cxsize_t cxui_clock_t_tostr(cxsize_t size_of, const cxaddress_t obj, cxaddress_t str, va_list *argv);
	*/

	extern cxui_t cxui_binary;
	extern cxui_t cxui_unsigned_ints;
	extern cxui_t cxui_ints;
	extern cxui_t cxui_floats;
	extern cxui_t cxui_char;
	//extern cxui_t cxui_str;
	extern cxui_t cxui_time_t;
	extern cxui_t cxui_struct_tm;
	extern cxui_t cxui_clock_t;

#endif
