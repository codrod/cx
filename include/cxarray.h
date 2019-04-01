/*
	Unofficial C - Array II - Header
	Cody M. Rodgers
*/

#if !CXARRAY_VER

	#define CXARRAY_VER 2000000L

	#include <cxui.h>

	#define CXARRAY_FLAG_DYN 1
	
	#define cxarray(type, ptr, size) {type, NULL, FALSE, {ptr, 0, size}}
	#define cxarray_dyn(type, size) {type, NULL, TRUE, {NULL, 0, size}}
	#define cxarray_auto(type, ptr, len, size) {type, NULL, FALSE, {type, ptr, len, size}}
	#define cxarray_const(type, ptr, len) {type, NULL, FALSE, {type, ptr, len, len}}
	
	typedef struct cxarray
	{
		cxui_t *type;
		struct cxarray *segs;
		uint32_t flags;
		
		cxaddress_t ptr;
		cxsize_t len;
		cxsize_t size;
	}
	cxarray_t;
	
	/*
	ucsize_t cxarray_verify(cxarray_t arr);
	ucsize_t cxarray_len(cxarray_t arr);
	
	cxarray_t cxarray_nsub(cxarray_t array, ucsize_t index, ucsize_t n);
	cxarray_t cxarray_sub(cxarray_t array, ucsize_t index);
	
	ucsize_t cxarray_cpyx(ucaddress_t (*realloc)(ucaddress_t, ucsize_t), cxarray_t *dest, ucsize_t index, cxarray_t src, ucsize_t n);
	ucsize_t cxarray_ncpy(cxarray_t *dest, ucsize_t index, cxarray_t src, ucsize_t n);
	ucsize_t cxarray_cpy(cxarray_t *dest, cxarray_t src);
	
	ucsize_t cxarray_move(cxarray_t *array, ucsize_t dest, ucsize_t src, ucsize_t n);
	
	ucsize_t cxarray_ninsert(cxarray_t *dest, ucsize_t index, cxarray_t src, ucsize_t n);
	ucsize_t cxarray_insert(cxarray_t *dest, ucsize_t index, cxarray_t src);
	
	ucsize_t cxarray_nreplace(cxarray_t *dest, ucsize_t index, ucsize_t n, cxarray_t src, ucsize_t n);
	ucsize_t cxarray_replace(cxarray_t *dest, ucsize_t index, ucsize_t n, cxarray_t src);
	
	ucsize_t cxarray_ncmp(cxarray_t array, cxarray_t array, ucsize_t n);
	ucsize_t cxarray_cmp(cxarray_t array, cxarray_t array, ucsize_t n);
	
	
	//int array[5]; cxarray(uctype_int, (int[5]){0}, 5);
	
	//int *array = malloc();
	
	//int *array = {1, 2, 3, 4, 5}; cxarray_auto(uctype_int, (int[5]){1, 2, 3, 4, 5}, 5, 5);
	//int array[10] = {1, 2, 3, 4}; cxarray_auto(uctype_int (int[10]){1, 2, 3, 4, 5}, 5, 10);
	
	//int array[10] = {1, 2, 3, 4, INT_MIN};
	//cxarray_t array = cxarray_auto(uctype_int, (int[10]){1, 2, 3, 4, 5, INT_MIN}, -1, 10);
	//array.terms = cxarray_terms_int;
	
	/*
		cxarray_len
		cxarray_verify
		
		cxarray_cpy
		cxarray_move
		
		cxarray_set
		cxarray_insert
		cxarray_replace
		
		cxarray_cmp
		
		cxarray_qsort
		cxarray_bsearch
		
		cxarray_union
		cxarray_inter
		cxarray_diff
	*/

#endif
