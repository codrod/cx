#if !CXEX_VERSION

	#define CXEX_VERSION 2000000L

	#include <setjmp.h>
	#include <cxdef.h>
	#include <cxerror.h>

	#define cxtry if(!cxex_setjmp(*CXEX_TRY())) {
	#define cxcatch(...) CXEX_END_TRY(); } else if(CXEX_CATCH(0, ##__VA_ARGS__, (cxexception_t){}))
	#define cxthrow_ret(ex, ret) cxex_longjmp(*CXEX_THROW(ex, ret), 1)
	#define cxthrow(ex) cxthrow_ret(ex, 0)

	#define cxex_setjmp(jump) sigsetjmp(jump, 1)
	#define cxex_longjmp siglongjmp

	typedef sigjmp_buf cxex_jmp_buf;

	typedef struct cxex_try_block
	{
		cxex_jmp_buf jump;
	}
	cxex_try_block_t;

	typedef struct cxexception
	{
		char *type;
		char *what;
		int ret;
	}
	cxexception_t;

	cxex_jmp_buf* CXEX_THROW(cxexception_t ex, int ret);
	cxex_jmp_buf* CXEX_TRY();
	void CXEX_END_TRY();
	int CXEX_CATCH(int var, ...);

	int cxex_istype(cxexception_t except, cxexception_t other);

	extern cxdef_thread_local cxexception_t cxexcept;
	extern cxexception_t CXException;

#endif
