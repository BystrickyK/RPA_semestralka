/*
 * DEBUGGER code
 * 
 * On "publish", when buffer is free, debugger stores arbitrary variables 
 * content into, and mark this buffer as filled
 * 
 * 
 * Buffer content is read asynchronously, (from non real time part), 
 * and then buffer marked free again.
 *  
 * 
 * */
#ifdef TARGET_DEBUG_AND_RETAIN_DISABLE

void __init_debug    (void){}
void __cleanup_debug (void){}
void __retrieve_debug(void){}
void __publish_debug (void){}

#else

#include "iec_types_all.h"
#include "POUS.h"
/*for memcpy*/
#include <string.h>
#include <stdio.h>

#ifndef TARGET_ONLINE_DEBUG_DISABLE
#define BUFFER_SIZE 165

/* Atomically accessed variable for buffer state */
#define BUFFER_FREE 0
#define BUFFER_BUSY 1
static long buffer_state = BUFFER_FREE;

/* The buffer itself */
char debug_buffer[BUFFER_SIZE];

/* Buffer's cursor*/
static char* buffer_cursor = debug_buffer;
#endif

static unsigned int retain_offset = 0;
/***
 * Declare programs 
 **/
extern SUPERSTATE_MACHINE RES0__SSM;
extern SERVICE RES0__SVC;
extern EMERIGENCY RES0__EM;
extern AUTOPRODUCTION RES0__AP;
extern MANUALPRODUCTION RES0__MP;
extern FAILURE RES0__FAIL;
extern WATCHDOGTIMER RES0__WDTIMER;

/***
 * Declare global variables from resources and conf 
 **/
extern __IEC_DWORD_t CONFIG0__CONTROLLER_OUTPUT;
extern __IEC_UINT_t CONFIG0__WDT;
extern __IEC_INT_t CONFIG0__CURRENT_SUPERSTATE;
extern __IEC_INT_t CONFIG0__CURRENT_STATE;
extern __IEC_DWORD_t CONFIG0__SENSOR_OUTPUT;
extern __IEC_DWORD_t CONFIG0__SSM_TRANSITIONS;
extern __IEC_BOOL_t CONFIG0__OUT_AP;
extern __IEC_BOOL_t CONFIG0__OUT_AM;
extern __IEC_BOOL_t CONFIG0__OUT_B;
extern __IEC_BOOL_t CONFIG0__OUT_C;
extern __IEC_BOOL_t CONFIG0__OUT_DP;
extern __IEC_BOOL_t CONFIG0__OUT_DM;
extern __IEC_BOOL_t CONFIG0__OUT_PREASURE_OFF;
extern       SUPERSTATE_MACHINE   RES0__SSM;
extern       SERVICE   RES0__SVC;
extern       EMERIGENCY   RES0__EM;
extern       AUTOPRODUCTION   RES0__AP;
extern       MANUALPRODUCTION   RES0__MP;
extern       FAILURE   RES0__FAIL;
extern       WATCHDOGTIMER   RES0__WDTIMER;

typedef const struct {
    void *ptr;
    __IEC_types_enum type;
} dbgvardsc_t;

static dbgvardsc_t dbgvardsc[] = {
{&(CONFIG0__CONTROLLER_OUTPUT), DWORD_ENUM},
{&(CONFIG0__WDT), UINT_ENUM},
{&(CONFIG0__CURRENT_SUPERSTATE), INT_ENUM},
{&(CONFIG0__CURRENT_STATE), INT_ENUM},
{&(CONFIG0__SENSOR_OUTPUT), DWORD_ENUM},
{&(CONFIG0__SSM_TRANSITIONS), DWORD_ENUM},
{&(CONFIG0__OUT_AP), BOOL_ENUM},
{&(CONFIG0__OUT_AM), BOOL_ENUM},
{&(CONFIG0__OUT_B), BOOL_ENUM},
{&(CONFIG0__OUT_C), BOOL_ENUM},
{&(CONFIG0__OUT_DP), BOOL_ENUM},
{&(CONFIG0__OUT_DM), BOOL_ENUM},
{&(CONFIG0__OUT_PREASURE_OFF), BOOL_ENUM},
{&(RES0__SSM.SSM_TRANSITIONS), DWORD_P_ENUM},
{&(RES0__SSM.CURRENT_SUPERSTATE), INT_P_ENUM},
{&(RES0__SSM.WDT), UINT_P_ENUM},
{&(RES0__SSM.COL), INT_ENUM},
{&(RES0__SSM.TMP1), WORD_ENUM},
{&(RES0__SSM.TMP2), WORD_ENUM},
{&(RES0__SSM.TMP3), INT_ENUM},
{&(RES0__SSM.SENSOR_OUTPUT), DWORD_P_ENUM},
{&(RES0__SSM.EM), BOOL_ENUM},
{&(RES0__SSM.SAP), BOOL_ENUM},
{&(RES0__SSM.APF), BOOL_ENUM},
{&(RES0__SSM.SMP), BOOL_ENUM},
{&(RES0__SSM.MPF), BOOL_ENUM},
{&(RES0__SSM.SSVC), BOOL_ENUM},
{&(RES0__SSM.SVCF), BOOL_ENUM},
{&(RES0__SSM.EMF), BOOL_ENUM},
{&(RES0__SSM.WDOX), BOOL_ENUM},
{&(RES0__SSM.RESX), BOOL_ENUM},
{&(RES0__SSM.BAD), BOOL_ENUM},
{&(RES0__SVC.CURRENT_SUPERSTATE), INT_P_ENUM},
{&(RES0__SVC.SENSOR_OUTPUT), DWORD_P_ENUM},
{&(RES0__SVC.SSM_TRANSITIONS), DWORD_P_ENUM},
{&(RES0__SVC.IN_AP), BOOL_ENUM},
{&(RES0__SVC.IN_AM), BOOL_ENUM},
{&(RES0__SVC.IN_B), BOOL_ENUM},
{&(RES0__SVC.IN_C), BOOL_ENUM},
{&(RES0__SVC.IN_DP), BOOL_ENUM},
{&(RES0__SVC.IN_DM), BOOL_ENUM},
{&(RES0__SVC.IN_PREASURE_OFF), BOOL_ENUM},
{&(RES0__SVC.OUT_AP), BOOL_P_ENUM},
{&(RES0__SVC.OUT_AM), BOOL_P_ENUM},
{&(RES0__SVC.OUT_B), BOOL_P_ENUM},
{&(RES0__SVC.OUT_C), BOOL_P_ENUM},
{&(RES0__SVC.OUT_DP), BOOL_P_ENUM},
{&(RES0__SVC.OUT_DM), BOOL_P_ENUM},
{&(RES0__SVC.OUT_PREASURE_OFF), BOOL_P_ENUM},
{&(RES0__EM.CONTROLLER_OUTPUT), DWORD_P_ENUM},
{&(RES0__EM.CURRENT_SUPERSTATE), INT_P_ENUM},
{&(RES0__EM.SENSOR_OUTPUT), DWORD_P_ENUM},
{&(RES0__EM.SSM_TRANSITIONS), DWORD_P_ENUM},
{&(RES0__EM.CURRENT_STATE), INT_P_ENUM},
{&(RES0__EM.OUT_AP), BOOL_P_ENUM},
{&(RES0__EM.OUT_AM), BOOL_P_ENUM},
{&(RES0__EM.OUT_B), BOOL_P_ENUM},
{&(RES0__EM.OUT_C), BOOL_P_ENUM},
{&(RES0__EM.OUT_DP), BOOL_P_ENUM},
{&(RES0__EM.OUT_DM), BOOL_P_ENUM},
{&(RES0__EM.OUT_PREASURE_OFF), BOOL_ENUM},
{&(RES0__AP.CONTROLLER_OUTPUT), DWORD_P_ENUM},
{&(RES0__AP.CURRENT_SUPERSTATE), INT_P_ENUM},
{&(RES0__AP.SENSOR_OUTPUT), DWORD_P_ENUM},
{&(RES0__AP.WDT), UINT_P_ENUM},
{&(RES0__AP.SSM_TRANSITIONS), DWORD_P_ENUM},
{&(RES0__AP.CURRENT_STATE), INT_P_ENUM},
{&(RES0__AP.COLUMN), INT_ENUM},
{&(RES0__AP.OUT_AP), BOOL_P_ENUM},
{&(RES0__AP.OUT_AM), BOOL_P_ENUM},
{&(RES0__AP.OUT_B), BOOL_P_ENUM},
{&(RES0__AP.OUT_C), BOOL_P_ENUM},
{&(RES0__AP.OUT_DP), BOOL_P_ENUM},
{&(RES0__AP.OUT_DM), BOOL_P_ENUM},
{&(RES0__AP.IN_PROX), BOOL_ENUM},
{&(RES0__AP.IN_A0), BOOL_ENUM},
{&(RES0__AP.IN_A1), BOOL_ENUM},
{&(RES0__AP.IN_B), BOOL_ENUM},
{&(RES0__AP.IN_C0), BOOL_ENUM},
{&(RES0__AP.IN_C1), BOOL_ENUM},
{&(RES0__AP.IN_D0), BOOL_ENUM},
{&(RES0__AP.IN_D1), BOOL_ENUM},
{&(RES0__MP.CONTROLLER_OUTPUT), DWORD_P_ENUM},
{&(RES0__MP.CURRENT_SUPERSTATE), INT_P_ENUM},
{&(RES0__MP.SENSOR_OUTPUT), DWORD_P_ENUM},
{&(RES0__MP.WDT), UINT_P_ENUM},
{&(RES0__MP.SSM_TRANSITIONS), DWORD_P_ENUM},
{&(RES0__MP.CURRENT_STATE), INT_P_ENUM},
{&(RES0__MP.COLUMN), INT_ENUM},
{&(RES0__FAIL.CURRENT_SUPERSTATE), INT_P_ENUM},
{&(RES0__FAIL.SSM_TRANSITIONS), DWORD_P_ENUM},
{&(RES0__WDTIMER.WDT), UINT_P_ENUM}
};

typedef void(*__for_each_variable_do_fp)(dbgvardsc_t*);
void __for_each_variable_do(__for_each_variable_do_fp fp)
{
    unsigned int i;
    for(i = 0; i < sizeof(dbgvardsc)/sizeof(dbgvardsc_t); i++){
        dbgvardsc_t *dsc = &dbgvardsc[i];
        if(dsc->type != UNKNOWN_ENUM) 
            (*fp)(dsc);
    }
}

#define __Unpack_case_t(TYPENAME) \
        case TYPENAME##_ENUM :\
            *flags = ((__IEC_##TYPENAME##_t *)varp)->flags;\
            forced_value_p = *real_value_p = &((__IEC_##TYPENAME##_t *)varp)->value;\
            break;

#define __Unpack_case_p(TYPENAME)\
        case TYPENAME##_O_ENUM :\
            *flags = __IEC_OUTPUT_FLAG;\
        case TYPENAME##_P_ENUM :\
            *flags |= ((__IEC_##TYPENAME##_p *)varp)->flags;\
            *real_value_p = ((__IEC_##TYPENAME##_p *)varp)->value;\
            forced_value_p = &((__IEC_##TYPENAME##_p *)varp)->fvalue;\
            break;

void* UnpackVar(dbgvardsc_t *dsc, void **real_value_p, char *flags)
{
    void *varp = dsc->ptr;
    void *forced_value_p = NULL;
    *flags = 0;
    /* find data to copy*/
    switch(dsc->type){
        __ANY(__Unpack_case_t)
        __ANY(__Unpack_case_p)
    default:
        break;
    }
    if (*flags & __IEC_FORCE_FLAG)
        return forced_value_p;
    return *real_value_p;
}

void Remind(unsigned int offset, unsigned int count, void * p);

void RemindIterator(dbgvardsc_t *dsc)
{
    void *real_value_p = NULL;
    char flags = 0;
    UnpackVar(dsc, &real_value_p, &flags);

    if(flags & __IEC_RETAIN_FLAG){
        USINT size = __get_type_enum_size(dsc->type);
        /* compute next cursor positon*/
        unsigned int next_retain_offset = retain_offset + size;
        /* if buffer not full */
        Remind(retain_offset, size, real_value_p);
        /* increment cursor according size*/
        retain_offset = next_retain_offset;
    }
}

extern int CheckRetainBuffer(void);
extern void InitRetain(void);

void __init_debug(void)
{
    /* init local static vars */
#ifndef TARGET_ONLINE_DEBUG_DISABLE	
    buffer_cursor = debug_buffer;
    buffer_state = BUFFER_FREE;
#endif

    retain_offset = 0;
    InitRetain();
    /* Iterate over all variables to fill debug buffer */
    if(CheckRetainBuffer()){
    	__for_each_variable_do(RemindIterator);
    }else{
    	char mstr[] = "RETAIN memory invalid - defaults used";
        LogMessage(LOG_WARNING, mstr, sizeof(mstr));
    }
    retain_offset = 0;
}

extern void InitiateDebugTransfer(void);
extern void CleanupRetain(void);

extern unsigned long __tick;

void __cleanup_debug(void)
{
#ifndef TARGET_ONLINE_DEBUG_DISABLE	
    buffer_cursor = debug_buffer;
    InitiateDebugTransfer();
#endif    

    CleanupRetain();
}

void __retrieve_debug(void)
{
}


void Retain(unsigned int offset, unsigned int count, void * p);

static inline void BufferIterator(dbgvardsc_t *dsc, int do_debug)
{
    void *real_value_p = NULL;
    void *visible_value_p = NULL;
    char flags = 0;

    visible_value_p = UnpackVar(dsc, &real_value_p, &flags);

    if(flags & ( __IEC_DEBUG_FLAG | __IEC_RETAIN_FLAG)){
        USINT size = __get_type_enum_size(dsc->type);

#ifndef TARGET_ONLINE_DEBUG_DISABLE	
        if(flags & __IEC_DEBUG_FLAG){
            /* copy visible variable to buffer */;
            if(do_debug){
                /* compute next cursor positon.
                   No need to check overflow, as BUFFER_SIZE
                   is computed large enough */
		if((dsc->type == STRING_ENUM)   ||
		   (dsc->type == STRING_P_ENUM) ||
		   (dsc->type == STRING_O_ENUM)){
                    /* optimization for strings */
                    size = ((STRING*)visible_value_p)->len + 1;
                }
                char* next_cursor = buffer_cursor + size;
                /* copy data to the buffer */
                memcpy(buffer_cursor, visible_value_p, size);
                /* increment cursor according size*/
                buffer_cursor = next_cursor;
            }
            /* re-force real value of outputs (M and Q)*/
            if((flags & __IEC_FORCE_FLAG) && (flags & __IEC_OUTPUT_FLAG)){
                memcpy(real_value_p, visible_value_p, size);
            }
        }
#endif	

        if(flags & __IEC_RETAIN_FLAG){
            /* compute next cursor positon*/
            unsigned int next_retain_offset = retain_offset + size;
            /* if buffer not full */
            Retain(retain_offset, size, real_value_p);
            /* increment cursor according size*/
            retain_offset = next_retain_offset;
        }
    }
}

void DebugIterator(dbgvardsc_t *dsc){
    BufferIterator(dsc, 1);
}

void RetainIterator(dbgvardsc_t *dsc){
    BufferIterator(dsc, 0);
}


unsigned int retain_size = 0;

/* GetRetainSizeIterator */
void GetRetainSizeIterator(dbgvardsc_t *dsc)
{
    void *real_value_p = NULL;
    char flags = 0;
    UnpackVar(dsc, &real_value_p, &flags);

    if(flags & __IEC_RETAIN_FLAG){
        USINT size = __get_type_enum_size(dsc->type);
        /* Calc retain buffer size */
        retain_size += size;
    }
}

/* Return size of all retain variables */
unsigned int GetRetainSize(void)
{
    __for_each_variable_do(GetRetainSizeIterator);
    return retain_size;
}


extern void PLC_GetTime(IEC_TIME*);
extern int TryEnterDebugSection(void);
extern long AtomicCompareExchange(long*, long, long);
extern long long AtomicCompareExchange64(long long* , long long , long long);
extern void LeaveDebugSection(void);
extern void ValidateRetainBuffer(void);
extern void InValidateRetainBuffer(void);

void __publish_debug(void)
{
    retain_offset = 0;
    InValidateRetainBuffer();
    
#ifndef TARGET_ONLINE_DEBUG_DISABLE 
    /* Check there is no running debugger re-configuration */
    if(TryEnterDebugSection()){
        /* Lock buffer */
        long latest_state = AtomicCompareExchange(
            &buffer_state,
            BUFFER_FREE,
            BUFFER_BUSY);
            
        /* If buffer was free */
        if(latest_state == BUFFER_FREE)
        {
            /* Reset buffer cursor */
            buffer_cursor = debug_buffer;
            /* Iterate over all variables to fill debug buffer */
            __for_each_variable_do(DebugIterator);
            
            /* Leave debug section,
             * Trigger asynchronous transmission 
             * (returns immediately) */
            InitiateDebugTransfer(); /* size */
        }else{
            /* when not debugging, do only retain */
            __for_each_variable_do(RetainIterator);
        }
        LeaveDebugSection();
    }else
#endif
    {
        /* when not debugging, do only retain */
        __for_each_variable_do(RetainIterator);
    }
    ValidateRetainBuffer();
}

#ifndef TARGET_ONLINE_DEBUG_DISABLE
#define __RegisterDebugVariable_case_t(TYPENAME) \
        case TYPENAME##_ENUM :\
            ((__IEC_##TYPENAME##_t *)varp)->flags |= flags;\
            if(force)\
             ((__IEC_##TYPENAME##_t *)varp)->value = *((TYPENAME *)force);\
            break;
#define __RegisterDebugVariable_case_p(TYPENAME)\
        case TYPENAME##_P_ENUM :\
            ((__IEC_##TYPENAME##_p *)varp)->flags |= flags;\
            if(force)\
             ((__IEC_##TYPENAME##_p *)varp)->fvalue = *((TYPENAME *)force);\
            break;\
        case TYPENAME##_O_ENUM :\
            ((__IEC_##TYPENAME##_p *)varp)->flags |= flags;\
            if(force){\
             ((__IEC_##TYPENAME##_p *)varp)->fvalue = *((TYPENAME *)force);\
             *(((__IEC_##TYPENAME##_p *)varp)->value) = *((TYPENAME *)force);\
            }\
            break;
void RegisterDebugVariable(unsigned int idx, void* force)
{
    if(idx  < sizeof(dbgvardsc)/sizeof(dbgvardsc_t)){
        unsigned char flags = force ?
            __IEC_DEBUG_FLAG | __IEC_FORCE_FLAG :
            __IEC_DEBUG_FLAG;
        dbgvardsc_t *dsc = &dbgvardsc[idx];
        void *varp = dsc->ptr;
        switch(dsc->type){
            __ANY(__RegisterDebugVariable_case_t)
            __ANY(__RegisterDebugVariable_case_p)
        default:
            break;
        }
    }
}

#define __ResetDebugVariablesIterator_case_t(TYPENAME) \
        case TYPENAME##_ENUM :\
            ((__IEC_##TYPENAME##_t *)varp)->flags &= ~(__IEC_DEBUG_FLAG|__IEC_FORCE_FLAG);\
            break;

#define __ResetDebugVariablesIterator_case_p(TYPENAME)\
        case TYPENAME##_P_ENUM :\
        case TYPENAME##_O_ENUM :\
            ((__IEC_##TYPENAME##_p *)varp)->flags &= ~(__IEC_DEBUG_FLAG|__IEC_FORCE_FLAG);\
            break;

void ResetDebugVariablesIterator(dbgvardsc_t *dsc)
{
    /* force debug flag to 0*/
    void *varp = dsc->ptr;
    switch(dsc->type){
        __ANY(__ResetDebugVariablesIterator_case_t)
        __ANY(__ResetDebugVariablesIterator_case_p)
    default:
        break;
    }
}

void ResetDebugVariables(void)
{
    __for_each_variable_do(ResetDebugVariablesIterator);
}

void FreeDebugData(void)
{
    /* atomically mark buffer as free */
    AtomicCompareExchange(
        &buffer_state,
        BUFFER_BUSY,
        BUFFER_FREE);
}
int WaitDebugData(unsigned long *tick);
/* Wait until debug data ready and return pointer to it */
int GetDebugData(unsigned long *tick, unsigned long *size, void **buffer){
    int wait_error = WaitDebugData(tick);
    if(!wait_error){
        *size = buffer_cursor - debug_buffer;
        *buffer = debug_buffer;
    }
    return wait_error;
}
#endif
#endif

