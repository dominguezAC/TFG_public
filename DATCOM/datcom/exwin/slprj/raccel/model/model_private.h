#include "__cf_model.h"
#ifndef RTW_HEADER_model_private_h_
#define RTW_HEADER_model_private_h_
#include "rtwtypes.h"
#include "builtin_typeid_types.h"
#include "multiword_types.h"
#include "model.h"
#if !defined(rt_VALIDATE_MEMORY)
#define rt_VALIDATE_MEMORY(S, ptr)   if(!(ptr)) {\
  ssSetErrorStatus(rtS, RT_MEMORY_ALLOCATION_ERROR);\
  }
#endif
#if !defined(rt_FREE)
#if !defined(_WIN32)
#define rt_FREE(ptr)   if((ptr) != (NULL)) {\
  free((ptr));\
  (ptr) = (NULL);\
  }
#else
#define rt_FREE(ptr)   if((ptr) != (NULL)) {\
  free((void *)(ptr));\
  (ptr) = (NULL);\
  }
#endif
#endif
extern real_T rt_urand_Upu32_Yd_f_pw_snf ( uint32_T * u ) ; extern real_T
rt_nrand_Upu32_Yd_f_pw_snf ( uint32_T * u ) ; extern void
rt_mrdivide_U1d1x3_U2d3x3_Yd1x3_snf ( const real_T u0 [ 3 ] , const real_T u1
[ 9 ] , real_T y [ 3 ] ) ; extern uint32_T plook_bincpa ( real_T u , const
real_T bp [ ] , uint32_T maxIndex , real_T * fraction , uint32_T * prevIndex
) ; extern real_T intrp2d_la_pw ( const uint32_T bpIndex [ ] , const real_T
frac [ ] , const real_T table [ ] , const uint32_T stride , const uint32_T
maxIndex [ ] ) ; extern int32_T plook_s32dd_bincp ( real_T u , const real_T
bp [ ] , uint32_T maxIndex , real_T * fraction , int32_T * prevIndex ) ;
extern real_T look1_plinlcpw ( real_T u0 , const real_T bp0 [ ] , const
real_T table [ ] , uint32_T prevIndex [ ] , uint32_T maxIndex ) ; extern
uint32_T binsearch_u32d_prevIdx ( real_T u , const real_T bp [ ] , uint32_T
startIndex , uint32_T maxIndex ) ; extern int32_T binsearch_s32d_prevIdx (
real_T u , const real_T bp [ ] , uint32_T startIndex , uint32_T maxIndex ) ;
extern void p1lgyippqt ( n2tntgetox * localB , la53pg24sw * localP ,
clzm13mi24 * localX ) ; extern void erguahjs45 ( la53pg24sw * localP ,
clzm13mi24 * localX ) ; extern void lrzgg20d41 ( SimStruct * rtS_p ,
p1vyesmn13 * localDW , lrakgivbxx * localXdis ) ; extern void dh3gvlf1g0 (
real_T fwgpsm452l , p1vyesmn13 * localDW , lrakgivbxx * localXdis ,
esw4djegcl * localXdot ) ; extern void bqgnqqodam ( real_T fwgpsm452l ,
p1vyesmn13 * localDW , la53pg24sw * localP , clzm13mi24 * localX , hzlzoncq5o
* localZCSV , real_T rtp_d_m ) ; extern void otgfwz1f5l ( p1vyesmn13 *
localDW ) ; extern void ofdpi4iot1 ( SimStruct * rtS_m , real_T fwgpsm452l ,
p1vyesmn13 * localDW , la53pg24sw * localP , clzm13mi24 * localX , real_T
rtp_d_m ) ; extern void jgkdl5leza ( SimStruct * rtS_i , boolean_T o2hqxwk35u
, n2tntgetox * localB , p1vyesmn13 * localDW , la53pg24sw * localP ,
clzm13mi24 * localX , real_T rtp_d_m , lrakgivbxx * localXdis ) ;
#if defined(MULTITASKING)
#error Models using the variable step solvers cannot define MULTITASKING
#endif
#endif
