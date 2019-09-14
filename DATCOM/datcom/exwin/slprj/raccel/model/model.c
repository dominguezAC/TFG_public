#include "__cf_model.h"
#include "rt_logging_mmi.h"
#include "model_capi.h"
#include <math.h>
#include "model.h"
#include "model_private.h"
#include "model_dt.h"
extern void * CreateDiagnosticAsVoidPtr_wrapper ( const char * id , int nargs
, ... ) ; RTWExtModeInfo * gblRTWExtModeInfo = NULL ; extern boolean_T
gblExtModeStartPktReceived ; void raccelForceExtModeShutdown ( ) { if ( !
gblExtModeStartPktReceived ) { boolean_T stopRequested = false ;
rtExtModeWaitForStartPkt ( gblRTWExtModeInfo , 3 , & stopRequested ) ; }
rtExtModeShutdown ( 3 ) ; }
#include "slsv_diagnostic_codegen_c_api.h"
const int_T gblNumToFiles = 0 ; const int_T gblNumFrFiles = 0 ; const int_T
gblNumFrWksBlocks = 0 ;
#ifdef RSIM_WITH_SOLVER_MULTITASKING
boolean_T gbl_raccel_isMultitasking = 1 ;
#else
boolean_T gbl_raccel_isMultitasking = 0 ;
#endif
boolean_T gbl_raccel_tid01eq = 0 ; int_T gbl_raccel_NumST = 4 ; const char_T
* gbl_raccel_Version = "9.2 (R2018b) 24-May-2018" ; void
raccel_setup_MMIStateLog ( SimStruct * S ) {
#ifdef UseMMIDataLogging
rt_FillStateSigInfoFromMMI ( ssGetRTWLogInfo ( S ) , & ssGetErrorStatus ( S )
) ;
#else
UNUSED_PARAMETER ( S ) ;
#endif
} static DataMapInfo rt_dataMapInfo ; DataMapInfo * rt_dataMapInfoPtr = &
rt_dataMapInfo ; rtwCAPI_ModelMappingInfo * rt_modelMapInfoPtr = & (
rt_dataMapInfo . mmi ) ; const char * gblSlvrJacPatternFileName =
"slprj//raccel//model//model_Jpattern.mat" ; const int_T gblNumRootInportBlks
= 0 ; const int_T gblNumModelInputs = 0 ; extern rtInportTUtable *
gblInportTUtables ; extern const char * gblInportFileName ; const int_T
gblInportDataTypeIdx [ ] = { - 1 } ; const int_T gblInportDims [ ] = { - 1 }
; const int_T gblInportComplex [ ] = { - 1 } ; const int_T
gblInportInterpoFlag [ ] = { - 1 } ; const int_T gblInportContinuous [ ] = {
- 1 } ; int_T enableFcnCallFlag [ ] = { 1 , 1 , 1 , 1 } ;
#include "simstruc.h"
#include "fixedpoint.h"
B rtB ; X rtX ; PeriodicIndX rtPeriodicIndX ; PeriodicRngX rtPeriodicRngX ;
DW rtDW ; static SimStruct model_S ; SimStruct * const rtS = & model_S ;
uint32_T plook_bincpa ( real_T u , const real_T bp [ ] , uint32_T maxIndex ,
real_T * fraction , uint32_T * prevIndex ) { uint32_T bpIndex ; if ( u <= bp
[ 0U ] ) { bpIndex = 0U ; * fraction = 0.0 ; } else if ( u < bp [ maxIndex ]
) { bpIndex = binsearch_u32d_prevIdx ( u , bp , * prevIndex , maxIndex ) ; *
fraction = ( u - bp [ bpIndex ] ) / ( bp [ bpIndex + 1U ] - bp [ bpIndex ] )
; } else { bpIndex = maxIndex ; * fraction = 0.0 ; } * prevIndex = bpIndex ;
return bpIndex ; } real_T intrp2d_la_pw ( const uint32_T bpIndex [ ] , const
real_T frac [ ] , const real_T table [ ] , const uint32_T stride , const
uint32_T maxIndex [ ] ) { real_T y ; real_T yR_1d ; uint32_T offset_1d ;
offset_1d = bpIndex [ 1U ] * stride + bpIndex [ 0U ] ; if ( bpIndex [ 0U ] ==
maxIndex [ 0U ] ) { y = table [ offset_1d ] ; } else { y = ( table [
offset_1d + 1U ] - table [ offset_1d ] ) * frac [ 0U ] + table [ offset_1d ]
; } if ( bpIndex [ 1U ] == maxIndex [ 1U ] ) { } else { offset_1d += stride ;
if ( bpIndex [ 0U ] == maxIndex [ 0U ] ) { yR_1d = table [ offset_1d ] ; }
else { yR_1d = ( table [ offset_1d + 1U ] - table [ offset_1d ] ) * frac [ 0U
] + table [ offset_1d ] ; } y += ( yR_1d - y ) * frac [ 1U ] ; } return y ; }
int32_T plook_s32dd_bincp ( real_T u , const real_T bp [ ] , uint32_T
maxIndex , real_T * fraction , int32_T * prevIndex ) { int32_T bpIndex ; if (
u <= bp [ 0U ] ) { bpIndex = 0 ; * fraction = 0.0 ; } else if ( u < bp [
maxIndex ] ) { bpIndex = binsearch_s32d_prevIdx ( u , bp , ( uint32_T ) *
prevIndex , maxIndex ) ; * fraction = ( u - bp [ ( uint32_T ) bpIndex ] ) / (
bp [ bpIndex + 1U ] - bp [ ( uint32_T ) bpIndex ] ) ; } else { bpIndex = (
int32_T ) ( maxIndex - 1U ) ; * fraction = 1.0 ; } * prevIndex = bpIndex ;
return bpIndex ; } real_T look1_plinlcpw ( real_T u0 , const real_T bp0 [ ] ,
const real_T table [ ] , uint32_T prevIndex [ ] , uint32_T maxIndex ) {
real_T frac ; uint32_T bpIdx ; if ( u0 <= bp0 [ 0U ] ) { bpIdx = 0U ; frac =
0.0 ; } else if ( u0 < bp0 [ maxIndex ] ) { for ( bpIdx = prevIndex [ 0U ] ;
u0 < bp0 [ bpIdx ] ; bpIdx -- ) { } while ( u0 >= bp0 [ bpIdx + 1U ] ) {
bpIdx ++ ; } frac = ( u0 - bp0 [ bpIdx ] ) / ( bp0 [ bpIdx + 1U ] - bp0 [
bpIdx ] ) ; } else { bpIdx = maxIndex - 1U ; frac = 1.0 ; } prevIndex [ 0U ]
= bpIdx ; return ( table [ bpIdx + 1U ] - table [ bpIdx ] ) * frac + table [
bpIdx ] ; } uint32_T binsearch_u32d_prevIdx ( real_T u , const real_T bp [ ]
, uint32_T startIndex , uint32_T maxIndex ) { uint32_T bpIndex ; uint32_T
iRght ; uint32_T iLeft ; uint32_T found ; bpIndex = startIndex ; iLeft = 0U ;
iRght = maxIndex ; found = 0U ; while ( found == 0U ) { if ( u < bp [ bpIndex
] ) { iRght = bpIndex - 1U ; bpIndex = ( iRght + iLeft ) >> 1U ; } else if (
u < bp [ bpIndex + 1U ] ) { found = 1U ; } else { iLeft = bpIndex + 1U ;
bpIndex = ( iRght + iLeft ) >> 1U ; } } return bpIndex ; } int32_T
binsearch_s32d_prevIdx ( real_T u , const real_T bp [ ] , uint32_T startIndex
, uint32_T maxIndex ) { uint32_T iRght ; uint32_T iLeft ; uint32_T bpIdx ;
uint32_T found ; bpIdx = startIndex ; iLeft = 0U ; iRght = maxIndex ; found =
0U ; while ( found == 0U ) { if ( u < bp [ bpIdx ] ) { iRght = bpIdx - 1U ;
bpIdx = ( iRght + iLeft ) >> 1U ; } else if ( u < bp [ bpIdx + 1U ] ) { found
= 1U ; } else { iLeft = bpIdx + 1U ; bpIdx = ( iRght + iLeft ) >> 1U ; } }
return ( int32_T ) bpIdx ; } void p1lgyippqt ( n2tntgetox * localB ,
la53pg24sw * localP , clzm13mi24 * localX ) { localX -> b1gdrvpzrw = localP
-> DistanceintoGustxLimitedtogustlengthd_IC ; localB -> bkh4ie4vlq = localP
-> x_Y0 ; } void erguahjs45 ( la53pg24sw * localP , clzm13mi24 * localX ) {
localX -> b1gdrvpzrw = localP -> DistanceintoGustxLimitedtogustlengthd_IC ; }
void otgfwz1f5l ( p1vyesmn13 * localDW ) { localDW -> hndz0ioosi = false ; }
void lrzgg20d41 ( SimStruct * rtS_p , p1vyesmn13 * localDW , lrakgivbxx *
localXdis ) { localDW -> hndz0ioosi = false ;
ssSetBlockStateForSolverChangedAtMajorStep ( rtS_p ) ; localXdis ->
b1gdrvpzrw = 1 ; } void jgkdl5leza ( SimStruct * rtS_i , boolean_T o2hqxwk35u
, n2tntgetox * localB , p1vyesmn13 * localDW , la53pg24sw * localP ,
clzm13mi24 * localX , real_T rtp_d_m , lrakgivbxx * localXdis ) { if (
ssIsSampleHit ( rtS_i , 1 , 0 ) && ssIsMajorTimeStep ( rtS_i ) ) { if (
o2hqxwk35u ) { if ( ! localDW -> hndz0ioosi ) { if ( ssGetTaskTime ( rtS_i ,
1 ) != ssGetTStart ( rtS_i ) ) { ssSetBlockStateForSolverChangedAtMajorStep (
rtS_i ) ; } localXdis -> b1gdrvpzrw = 0 ; erguahjs45 ( localP , localX ) ;
localDW -> hndz0ioosi = true ; } } else { if ( localDW -> hndz0ioosi ) {
ssSetBlockStateForSolverChangedAtMajorStep ( rtS_i ) ; localXdis ->
b1gdrvpzrw = 1 ; otgfwz1f5l ( localDW ) ; } } } if ( localDW -> hndz0ioosi )
{ if ( ssIsMajorTimeStep ( rtS_i ) ) { if ( localX -> b1gdrvpzrw >= rtp_d_m )
{ localX -> b1gdrvpzrw = rtp_d_m ; } else { if ( localX -> b1gdrvpzrw <=
localP -> DistanceintoGustxLimitedtogustlengthd_LowerSat ) { localX ->
b1gdrvpzrw = localP -> DistanceintoGustxLimitedtogustlengthd_LowerSat ; } } }
localB -> bkh4ie4vlq = localX -> b1gdrvpzrw ; if ( ssIsMajorTimeStep ( rtS_i
) ) { srUpdateBC ( localDW -> lzpni3vohm ) ; } } } void ofdpi4iot1 (
SimStruct * rtS_m , real_T fwgpsm452l , p1vyesmn13 * localDW , la53pg24sw *
localP , clzm13mi24 * localX , real_T rtp_d_m ) { if ( localDW -> hndz0ioosi
) { if ( localX -> b1gdrvpzrw == rtp_d_m ) { switch ( localDW -> cztgqg1pxv )
{ case 3 : if ( fwgpsm452l < 0.0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( rtS_m ) ; localDW -> cztgqg1pxv
= 1 ; } break ; case 1 : if ( fwgpsm452l >= 0.0 ) { localDW -> cztgqg1pxv = 3
; ssSetBlockStateForSolverChangedAtMajorStep ( rtS_m ) ; } break ; default :
ssSetBlockStateForSolverChangedAtMajorStep ( rtS_m ) ; if ( fwgpsm452l < 0.0
) { localDW -> cztgqg1pxv = 1 ; } else { localDW -> cztgqg1pxv = 3 ; } break
; } } else if ( localX -> b1gdrvpzrw == localP ->
DistanceintoGustxLimitedtogustlengthd_LowerSat ) { switch ( localDW ->
cztgqg1pxv ) { case 4 : if ( fwgpsm452l > 0.0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( rtS_m ) ; localDW -> cztgqg1pxv
= 2 ; } break ; case 2 : if ( fwgpsm452l <= 0.0 ) { localDW -> cztgqg1pxv = 4
; ssSetBlockStateForSolverChangedAtMajorStep ( rtS_m ) ; } break ; default :
ssSetBlockStateForSolverChangedAtMajorStep ( rtS_m ) ; if ( fwgpsm452l > 0.0
) { localDW -> cztgqg1pxv = 2 ; } else { localDW -> cztgqg1pxv = 4 ; } break
; } } else { localDW -> cztgqg1pxv = 0 ; } } } void dh3gvlf1g0 ( real_T
fwgpsm452l , p1vyesmn13 * localDW , lrakgivbxx * localXdis , esw4djegcl *
localXdot ) { if ( localDW -> hndz0ioosi ) { if ( ( localDW -> cztgqg1pxv !=
3 ) && ( localDW -> cztgqg1pxv != 4 ) ) { localXdot -> b1gdrvpzrw =
fwgpsm452l ; localXdis -> b1gdrvpzrw = false ; } else { localXdot ->
b1gdrvpzrw = 0.0 ; if ( ( localDW -> cztgqg1pxv == 3 ) || ( localDW ->
cztgqg1pxv == 4 ) ) { localXdis -> b1gdrvpzrw = true ; } } } else { localXdot
-> b1gdrvpzrw = 0.0 ; } } void bqgnqqodam ( real_T fwgpsm452l , p1vyesmn13 *
localDW , la53pg24sw * localP , clzm13mi24 * localX , hzlzoncq5o * localZCSV
, real_T rtp_d_m ) { boolean_T anyStateSaturated ; if ( localDW -> hndz0ioosi
) { if ( ( localDW -> cztgqg1pxv == 1 ) && ( localX -> b1gdrvpzrw >= rtp_d_m
) ) { localZCSV -> infz0h0a5x = 0.0 ; } else { localZCSV -> infz0h0a5x =
localX -> b1gdrvpzrw - rtp_d_m ; } if ( ( localDW -> cztgqg1pxv == 2 ) && (
localX -> b1gdrvpzrw <= localP ->
DistanceintoGustxLimitedtogustlengthd_LowerSat ) ) { localZCSV -> ol42gnqx3d
= 0.0 ; } else { localZCSV -> ol42gnqx3d = localX -> b1gdrvpzrw - localP ->
DistanceintoGustxLimitedtogustlengthd_LowerSat ; } anyStateSaturated = false
; if ( ( localDW -> cztgqg1pxv == 3 ) || ( localDW -> cztgqg1pxv == 4 ) ) {
anyStateSaturated = true ; } if ( anyStateSaturated ) { localZCSV ->
lf0y5uqnvy = fwgpsm452l ; } else { localZCSV -> lf0y5uqnvy = 0.0 ; } } else {
{ real_T * zcsv = & ( localZCSV -> infz0h0a5x ) ; int_T i ; for ( i = 0 ; i <
3 ; i ++ ) { zcsv [ i ] = 0.0 ; } } } } real_T rt_urand_Upu32_Yd_f_pw_snf (
uint32_T * u ) { uint32_T lo ; uint32_T hi ; lo = * u % 127773U * 16807U ; hi
= * u / 127773U * 2836U ; if ( lo < hi ) { * u = 2147483647U - ( hi - lo ) ;
} else { * u = lo - hi ; } return ( real_T ) * u * 4.6566128752457969E-10 ; }
real_T rt_nrand_Upu32_Yd_f_pw_snf ( uint32_T * u ) { real_T y ; real_T sr ;
real_T si ; do { sr = 2.0 * rt_urand_Upu32_Yd_f_pw_snf ( u ) - 1.0 ; si = 2.0
* rt_urand_Upu32_Yd_f_pw_snf ( u ) - 1.0 ; si = sr * sr + si * si ; } while (
si > 1.0 ) ; y = muDoubleScalarSqrt ( - 2.0 * muDoubleScalarLog ( si ) / si )
* sr ; return y ; } void rt_mrdivide_U1d1x3_U2d3x3_Yd1x3_snf ( const real_T
u0 [ 3 ] , const real_T u1 [ 9 ] , real_T y [ 3 ] ) { real_T A [ 9 ] ;
int32_T r1 ; int32_T r2 ; int32_T r3 ; real_T maxval ; real_T a21 ; int32_T
rtemp ; memcpy ( & A [ 0 ] , & u1 [ 0 ] , 9U * sizeof ( real_T ) ) ; r1 = 0 ;
r2 = 1 ; r3 = 2 ; maxval = muDoubleScalarAbs ( u1 [ 0 ] ) ; a21 =
muDoubleScalarAbs ( u1 [ 1 ] ) ; if ( a21 > maxval ) { maxval = a21 ; r1 = 1
; r2 = 0 ; } if ( muDoubleScalarAbs ( u1 [ 2 ] ) > maxval ) { r1 = 2 ; r2 = 1
; r3 = 0 ; } A [ r2 ] = u1 [ r2 ] / u1 [ r1 ] ; A [ r3 ] /= A [ r1 ] ; A [ 3
+ r2 ] -= A [ 3 + r1 ] * A [ r2 ] ; A [ 3 + r3 ] -= A [ 3 + r1 ] * A [ r3 ] ;
A [ 6 + r2 ] -= A [ 6 + r1 ] * A [ r2 ] ; A [ 6 + r3 ] -= A [ 6 + r1 ] * A [
r3 ] ; if ( muDoubleScalarAbs ( A [ 3 + r3 ] ) > muDoubleScalarAbs ( A [ 3 +
r2 ] ) ) { rtemp = r2 + 1 ; r2 = r3 ; r3 = rtemp - 1 ; } A [ 3 + r3 ] /= A [
3 + r2 ] ; A [ 6 + r3 ] -= A [ 3 + r3 ] * A [ 6 + r2 ] ; y [ r1 ] = u0 [ 0 ]
/ A [ r1 ] ; y [ r2 ] = u0 [ 1 ] - A [ 3 + r1 ] * y [ r1 ] ; y [ r3 ] = u0 [
2 ] - A [ 6 + r1 ] * y [ r1 ] ; y [ r2 ] /= A [ 3 + r2 ] ; y [ r3 ] -= A [ 6
+ r2 ] * y [ r2 ] ; y [ r3 ] /= A [ 6 + r3 ] ; y [ r2 ] -= A [ 3 + r3 ] * y [
r3 ] ; y [ r1 ] -= y [ r3 ] * A [ r3 ] ; y [ r1 ] -= y [ r2 ] * A [ r2 ] ; }
void MdlInitialize ( void ) { uint32_T tseed ; int32_T r ; int32_T t ; real_T
tmp ; rtX . gw2wykgqi1 [ 0 ] = rtP . uDOFEulerAngles_Vm_0 [ 0 ] ; rtX .
k1ode521ap [ 0 ] = rtP . uDOFEulerAngles_eul_0 [ 0 ] ; rtX . iuemkmhnjl [ 0 ]
= rtP . uDOFEulerAngles_xme_0 [ 0 ] ; rtX . gw2wykgqi1 [ 1 ] = rtP .
uDOFEulerAngles_Vm_0 [ 1 ] ; rtX . k1ode521ap [ 1 ] = rtP .
uDOFEulerAngles_eul_0 [ 1 ] ; rtX . iuemkmhnjl [ 1 ] = rtP .
uDOFEulerAngles_xme_0 [ 1 ] ; rtX . gw2wykgqi1 [ 2 ] = rtP .
uDOFEulerAngles_Vm_0 [ 2 ] ; rtX . k1ode521ap [ 2 ] = rtP .
uDOFEulerAngles_eul_0 [ 2 ] ; rtX . iuemkmhnjl [ 2 ] = rtP .
uDOFEulerAngles_xme_0 [ 2 ] ; tmp = muDoubleScalarFloor ( rtP .
DrydenWindTurbulenceModelContinuousqr_Seed [ 0 ] ) ; if ( muDoubleScalarIsNaN
( tmp ) || muDoubleScalarIsInf ( tmp ) ) { tmp = 0.0 ; } else { tmp =
muDoubleScalarRem ( tmp , 4.294967296E+9 ) ; } tseed = tmp < 0.0 ? ( uint32_T
) - ( int32_T ) ( uint32_T ) - tmp : ( uint32_T ) tmp ; r = ( int32_T ) (
tseed >> 16U ) ; t = ( int32_T ) ( tseed & 32768U ) ; tseed = ( ( ( ( tseed -
( ( uint32_T ) r << 16U ) ) + t ) << 16U ) + t ) + r ; if ( tseed < 1U ) {
tseed = 1144108930U ; } else { if ( tseed > 2147483646U ) { tseed =
2147483646U ; } } rtDW . o2m0ho4ib0 [ 0 ] = tseed ; rtDW . e5dwuk5zfi [ 0 ] =
rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . o2m0ho4ib0 [ 0 ] ) * rtP .
WhiteNoise_StdDev + rtP . WhiteNoise_Mean ; tmp = muDoubleScalarFloor ( rtP .
DrydenWindTurbulenceModelContinuousqr_Seed [ 1 ] ) ; if ( muDoubleScalarIsNaN
( tmp ) || muDoubleScalarIsInf ( tmp ) ) { tmp = 0.0 ; } else { tmp =
muDoubleScalarRem ( tmp , 4.294967296E+9 ) ; } tseed = tmp < 0.0 ? ( uint32_T
) - ( int32_T ) ( uint32_T ) - tmp : ( uint32_T ) tmp ; r = ( int32_T ) (
tseed >> 16U ) ; t = ( int32_T ) ( tseed & 32768U ) ; tseed = ( ( ( ( tseed -
( ( uint32_T ) r << 16U ) ) + t ) << 16U ) + t ) + r ; if ( tseed < 1U ) {
tseed = 1144108930U ; } else { if ( tseed > 2147483646U ) { tseed =
2147483646U ; } } rtDW . o2m0ho4ib0 [ 1 ] = tseed ; rtDW . e5dwuk5zfi [ 1 ] =
rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . o2m0ho4ib0 [ 1 ] ) * rtP .
WhiteNoise_StdDev + rtP . WhiteNoise_Mean ; tmp = muDoubleScalarFloor ( rtP .
DrydenWindTurbulenceModelContinuousqr_Seed [ 2 ] ) ; if ( muDoubleScalarIsNaN
( tmp ) || muDoubleScalarIsInf ( tmp ) ) { tmp = 0.0 ; } else { tmp =
muDoubleScalarRem ( tmp , 4.294967296E+9 ) ; } tseed = tmp < 0.0 ? ( uint32_T
) - ( int32_T ) ( uint32_T ) - tmp : ( uint32_T ) tmp ; r = ( int32_T ) (
tseed >> 16U ) ; t = ( int32_T ) ( tseed & 32768U ) ; tseed = ( ( ( ( tseed -
( ( uint32_T ) r << 16U ) ) + t ) << 16U ) + t ) + r ; if ( tseed < 1U ) {
tseed = 1144108930U ; } else { if ( tseed > 2147483646U ) { tseed =
2147483646U ; } } rtDW . o2m0ho4ib0 [ 2 ] = tseed ; rtDW . e5dwuk5zfi [ 2 ] =
rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . o2m0ho4ib0 [ 2 ] ) * rtP .
WhiteNoise_StdDev + rtP . WhiteNoise_Mean ; tmp = muDoubleScalarFloor ( rtP .
DrydenWindTurbulenceModelContinuousqr_Seed [ 3 ] ) ; if ( muDoubleScalarIsNaN
( tmp ) || muDoubleScalarIsInf ( tmp ) ) { tmp = 0.0 ; } else { tmp =
muDoubleScalarRem ( tmp , 4.294967296E+9 ) ; } tseed = tmp < 0.0 ? ( uint32_T
) - ( int32_T ) ( uint32_T ) - tmp : ( uint32_T ) tmp ; r = ( int32_T ) (
tseed >> 16U ) ; t = ( int32_T ) ( tseed & 32768U ) ; tseed = ( ( ( ( tseed -
( ( uint32_T ) r << 16U ) ) + t ) << 16U ) + t ) + r ; if ( tseed < 1U ) {
tseed = 1144108930U ; } else { if ( tseed > 2147483646U ) { tseed =
2147483646U ; } } rtDW . o2m0ho4ib0 [ 3 ] = tseed ; rtDW . e5dwuk5zfi [ 3 ] =
rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . o2m0ho4ib0 [ 3 ] ) * rtP .
WhiteNoise_StdDev + rtP . WhiteNoise_Mean ; rtX . cjakaafmng [ 0 ] = rtP .
uDOFEulerAngles_pm_0 [ 0 ] ; rtX . cjakaafmng [ 1 ] = rtP .
uDOFEulerAngles_pm_0 [ 1 ] ; rtX . cjakaafmng [ 2 ] = rtP .
uDOFEulerAngles_pm_0 [ 2 ] ; rtX . bm4wjkp3hh = rtP .
DistanceintoGustxLimitedtogustlengthd_IC ; rtB . juld5yz3om = rtP . x_Y0 ;
p1lgyippqt ( & rtB . jgkdl5lezan , & rtP . jgkdl5lezan , & rtX . jgkdl5lezan
) ; p1lgyippqt ( & rtB . fieqmbp0km , & rtP . fieqmbp0km , & rtX . fieqmbp0km
) ; rtX . f4qi5fjsdf [ 0 ] = rtP . pgw_p_IC ; rtB . mfxy45ba4c [ 0 ] = rtP .
pgw_Y0 ; rtX . pxrnvzd5eg [ 0 ] = rtP . wg_p1_IC ; rtX . dolulbw4pb [ 0 ] =
rtP . wg_p2_IC ; rtB . gunypeaovn [ 0 ] = rtP . wgw_Y0 ; rtX . cgba0qyovs [ 0
] = rtP . qgw_p_IC ; rtB . oum15dzd35 [ 0 ] = rtP . qgw_Y0 ; rtX . fbih5gck0s
[ 0 ] = rtP . vg_p1_IC ; rtX . moa44kkouk [ 0 ] = rtP . vgw_p2_IC ; rtB .
joo0gvrcnf [ 0 ] = rtP . vgw_Y0 ; rtX . dydkrcbic2 [ 0 ] = rtP . rgw_p_IC ;
rtB . b2e3g5hpyo [ 0 ] = rtP . rgw_Y0 ; rtX . cnbgfejjbm [ 0 ] = rtP .
ug_p_IC ; rtB . iihgtnzfrf [ 0 ] = rtP . ugw_Y0 ; rtX . f4qi5fjsdf [ 1 ] =
rtP . pgw_p_IC ; rtB . mfxy45ba4c [ 1 ] = rtP . pgw_Y0 ; rtX . pxrnvzd5eg [ 1
] = rtP . wg_p1_IC ; rtX . dolulbw4pb [ 1 ] = rtP . wg_p2_IC ; rtB .
gunypeaovn [ 1 ] = rtP . wgw_Y0 ; rtX . cgba0qyovs [ 1 ] = rtP . qgw_p_IC ;
rtB . oum15dzd35 [ 1 ] = rtP . qgw_Y0 ; rtX . fbih5gck0s [ 1 ] = rtP .
vg_p1_IC ; rtX . moa44kkouk [ 1 ] = rtP . vgw_p2_IC ; rtB . joo0gvrcnf [ 1 ]
= rtP . vgw_Y0 ; rtX . dydkrcbic2 [ 1 ] = rtP . rgw_p_IC ; rtB . b2e3g5hpyo [
1 ] = rtP . rgw_Y0 ; rtX . cnbgfejjbm [ 1 ] = rtP . ug_p_IC ; rtB .
iihgtnzfrf [ 1 ] = rtP . ugw_Y0 ; { int_T rootPeriodicContStateIndices [ 3 ]
= { 3 , 4 , 5 } ; real_T rootPeriodicContStateRanges [ 6 ] = { -
3.1415926535897931 , 3.1415926535897931 , - 3.1415926535897931 ,
3.1415926535897931 , - 3.1415926535897931 , 3.1415926535897931 } ; ( void )
memcpy ( ( void * ) rtPeriodicIndX , rootPeriodicContStateIndices , 3 *
sizeof ( int_T ) ) ; ( void ) memcpy ( ( void * ) rtPeriodicRngX ,
rootPeriodicContStateRanges , 6 * sizeof ( real_T ) ) ; } } void MdlStart (
void ) { { void * * slioCatalogueAddr = rt_slioCatalogueAddr ( ) ; void * r2
= ( NULL ) ; void * * pOSigstreamManagerAddr = ( NULL ) ; const int
maxErrorBufferSize = 16384 ; char errMsgCreatingOSigstreamManager [ 16384 ] ;
bool errorCreatingOSigstreamManager = false ; const char *
errorAddingR2SharedResource = ( NULL ) ; * slioCatalogueAddr =
rtwGetNewSlioCatalogue ( rt_GetMatSigLogSelectorFileName ( ) ) ;
errorAddingR2SharedResource = rtwAddR2SharedResource (
rtwGetPointerFromUniquePtr ( rt_slioCatalogue ( ) ) , 1 ) ; if (
errorAddingR2SharedResource != ( NULL ) ) { rtwTerminateSlioCatalogue (
slioCatalogueAddr ) ; * slioCatalogueAddr = ( NULL ) ; ssSetErrorStatus ( rtS
, errorAddingR2SharedResource ) ; return ; } r2 = rtwGetR2SharedResource (
rtwGetPointerFromUniquePtr ( rt_slioCatalogue ( ) ) ) ;
pOSigstreamManagerAddr = rt_GetOSigstreamManagerAddr ( ) ;
errorCreatingOSigstreamManager = rtwOSigstreamManagerCreateInstance (
rt_GetMatSigLogSelectorFileName ( ) , r2 , pOSigstreamManagerAddr ,
errMsgCreatingOSigstreamManager , maxErrorBufferSize ) ; if (
errorCreatingOSigstreamManager ) { * pOSigstreamManagerAddr = ( NULL ) ;
ssSetErrorStatus ( rtS , errMsgCreatingOSigstreamManager ) ; return ; } } {
bool externalInputIsInDatasetFormat = false ; void * pISigstreamManager =
rt_GetISigstreamManager ( ) ; rtwISigstreamManagerGetInputIsInDatasetFormat (
pISigstreamManager , & externalInputIsInDatasetFormat ) ; if (
externalInputIsInDatasetFormat ) { } } rtDW . nx5ne33bex = 0 ; rtDW .
f3e4goswub = false ; ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; ( (
XDis * ) ssGetContStateDisabled ( rtS ) ) -> bm4wjkp3hh = 1 ; lrzgg20d41 (
rtS , & rtDW . jgkdl5lezan , & ( ( XDis * ) ssGetContStateDisabled ( rtS ) )
-> jgkdl5lezan ) ; lrzgg20d41 ( rtS , & rtDW . fieqmbp0km , & ( ( XDis * )
ssGetContStateDisabled ( rtS ) ) -> fieqmbp0km ) ; rtDW . jusb02f5rj = 0 ;
rtDW . nhbi5jh4go = 0 ; rtDW . ag2s0tuis0 = 0 ; rtDW . ekhaunodew = false ;
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; ( void ) memset ( & ( (
( XDis * ) ssGetContStateDisabled ( rtS ) ) -> f4qi5fjsdf ) , 1 , 2 * sizeof
( boolean_T ) ) ; rtDW . ptxtk1nv30 = false ;
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; ( void ) memset ( & ( (
( XDis * ) ssGetContStateDisabled ( rtS ) ) -> pxrnvzd5eg ) , 1 , 4 * sizeof
( boolean_T ) ) ; rtDW . jjjovfqaio = 0 ; rtDW . euk35lqnv1 = 0 ; rtDW .
dsenq15ybl = false ; ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; (
void ) memset ( & ( ( ( XDis * ) ssGetContStateDisabled ( rtS ) ) ->
cgba0qyovs ) , 1 , 2 * sizeof ( boolean_T ) ) ; rtDW . nhrxrmv3xz = false ;
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; ( void ) memset ( & ( (
( XDis * ) ssGetContStateDisabled ( rtS ) ) -> fbih5gck0s ) , 1 , 4 * sizeof
( boolean_T ) ) ; rtDW . fg0n3tzsij = 0 ; rtDW . dtbuv1dhzu = false ;
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; ( void ) memset ( & ( (
( XDis * ) ssGetContStateDisabled ( rtS ) ) -> dydkrcbic2 ) , 1 , 2 * sizeof
( boolean_T ) ) ; rtDW . gjeq11lqni = false ;
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; ( void ) memset ( & ( (
( XDis * ) ssGetContStateDisabled ( rtS ) ) -> cnbgfejjbm ) , 1 , 2 * sizeof
( boolean_T ) ) ; rtDW . ptevicn33b = 0 ; rtDW . kpq2e44z2g = - 1 ; rtDW .
amv55hlazd = - 1 ; rtDW . kpnxk2wxcb = 0 ; rtDW . ir0jb20k33 = 0 ; rtDW .
cnovvjoyyp = 0 ; rtDW . pgykvwqmc3 = 0 ; rtDW . ftwguoefpc = 0 ;
MdlInitialize ( ) ; } void MdlOutputs ( int_T tid ) { real_T d1bmmtsdzs ;
real_T lvewqzupwi ; real_T ivguwgcntv ; int8_T rtPrevAction ; int8_T rtAction
; real_T aotvmzw3cy [ 3 ] ; real_T huam1midmw [ 3 ] ; real_T frac [ 2 ] ;
uint32_T bpIndex [ 2 ] ; real_T tmp [ 9 ] ; real_T tmp_p [ 9 ] ; real_T tmp_e
[ 9 ] ; real_T tmp_i [ 9 ] ; real_T tmp_m [ 9 ] ; real_T m3fe2punjq_p ;
int32_T bpIndex_idx_0 ; int32_T bpIndex_idx_1 ; int32_T bpIndex_idx_2 ;
real_T ebyjfs5k0n_idx_0 ; real_T ebyjfs5k0n_idx_1 ; real_T efn34wlu0x_idx_1 ;
srClearBC ( rtDW . pkkgwpmnt2 ) ; srClearBC ( rtDW . jgkdl5lezan . lzpni3vohm
) ; srClearBC ( rtDW . nfawadvxsq ) ; srClearBC ( rtDW . ddqyu2zcpv ) ;
srClearBC ( rtDW . iu54wjtvx2 ) ; srClearBC ( rtDW . cjrmyujqju ) ; srClearBC
( rtDW . ceqnsrmeb1 ) ; srClearBC ( rtDW . ne00r4ogt0 ) ; srClearBC ( rtDW .
pfnakgwhvn ) ; srClearBC ( rtDW . gs4wlth0q0 ) ; srClearBC ( rtDW .
lj1lobgjwr ) ; srClearBC ( rtDW . feainkhr2c ) ; srClearBC ( rtDW .
kscxtxtsbw ) ; srClearBC ( rtDW . osdasmnnlg ) ; rtB . dzs1soumuc [ 0 ] = rtX
. gw2wykgqi1 [ 0 ] ; rtB . islqk3d2pc [ 0 ] = rtB . dzs1soumuc [ 0 ] ; rtB .
dzs1soumuc [ 1 ] = rtX . gw2wykgqi1 [ 1 ] ; rtB . islqk3d2pc [ 1 ] = rtB .
dzs1soumuc [ 1 ] ; rtB . dzs1soumuc [ 2 ] = rtX . gw2wykgqi1 [ 2 ] ; rtB .
islqk3d2pc [ 2 ] = rtB . dzs1soumuc [ 2 ] ; rtB . nliw1cuyp4 [ 0 ] = rtX .
k1ode521ap [ 0 ] ; rtB . nliw1cuyp4 [ 1 ] = rtX . k1ode521ap [ 1 ] ; rtB .
nliw1cuyp4 [ 2 ] = rtX . k1ode521ap [ 2 ] ; rtB . fnmpprt3rb [ 0 ] = rtB .
nliw1cuyp4 [ 2 ] ; rtB . fnmpprt3rb [ 1 ] = rtB . nliw1cuyp4 [ 1 ] ; rtB .
fnmpprt3rb [ 2 ] = rtB . nliw1cuyp4 [ 0 ] ; muDoubleScalarSinCos ( rtB .
fnmpprt3rb [ 0 ] , & huam1midmw [ 0 ] , & aotvmzw3cy [ 0 ] ) ;
muDoubleScalarSinCos ( rtB . fnmpprt3rb [ 1 ] , & huam1midmw [ 1 ] , &
aotvmzw3cy [ 1 ] ) ; muDoubleScalarSinCos ( rtB . fnmpprt3rb [ 2 ] , &
huam1midmw [ 2 ] , & aotvmzw3cy [ 2 ] ) ; rtB . n2gibbklhx [ 0 ] = aotvmzw3cy
[ 1 ] * aotvmzw3cy [ 0 ] ; rtB . n2gibbklhx [ 1 ] = huam1midmw [ 2 ] *
huam1midmw [ 1 ] * aotvmzw3cy [ 0 ] - aotvmzw3cy [ 2 ] * huam1midmw [ 0 ] ;
rtB . n2gibbklhx [ 2 ] = aotvmzw3cy [ 2 ] * huam1midmw [ 1 ] * aotvmzw3cy [ 0
] + huam1midmw [ 2 ] * huam1midmw [ 0 ] ; rtB . n2gibbklhx [ 3 ] = aotvmzw3cy
[ 1 ] * huam1midmw [ 0 ] ; rtB . n2gibbklhx [ 4 ] = huam1midmw [ 2 ] *
huam1midmw [ 1 ] * huam1midmw [ 0 ] + aotvmzw3cy [ 2 ] * aotvmzw3cy [ 0 ] ;
rtB . n2gibbklhx [ 5 ] = aotvmzw3cy [ 2 ] * huam1midmw [ 1 ] * huam1midmw [ 0
] - huam1midmw [ 2 ] * aotvmzw3cy [ 0 ] ; rtB . n2gibbklhx [ 6 ] = -
huam1midmw [ 1 ] ; rtB . n2gibbklhx [ 7 ] = huam1midmw [ 2 ] * aotvmzw3cy [ 1
] ; rtB . n2gibbklhx [ 8 ] = aotvmzw3cy [ 2 ] * aotvmzw3cy [ 1 ] ; for (
bpIndex_idx_0 = 0 ; bpIndex_idx_0 < 3 ; bpIndex_idx_0 ++ ) { rtB . mycisuihic
[ 3 * bpIndex_idx_0 ] = rtB . n2gibbklhx [ bpIndex_idx_0 ] ; rtB . mycisuihic
[ 1 + 3 * bpIndex_idx_0 ] = rtB . n2gibbklhx [ bpIndex_idx_0 + 3 ] ; rtB .
mycisuihic [ 2 + 3 * bpIndex_idx_0 ] = rtB . n2gibbklhx [ bpIndex_idx_0 + 6 ]
; } m3fe2punjq_p = 0.0 ; for ( bpIndex_idx_0 = 0 ; bpIndex_idx_0 < 3 ;
bpIndex_idx_0 ++ ) { rtB . bxute4gwb3 [ bpIndex_idx_0 ] = 0.0 ; rtB .
bxute4gwb3 [ bpIndex_idx_0 ] += rtB . mycisuihic [ bpIndex_idx_0 ] * rtB .
dzs1soumuc [ 0 ] ; rtB . bxute4gwb3 [ bpIndex_idx_0 ] += rtB . mycisuihic [
bpIndex_idx_0 + 3 ] * rtB . dzs1soumuc [ 1 ] ; rtB . bxute4gwb3 [
bpIndex_idx_0 ] += rtB . mycisuihic [ bpIndex_idx_0 + 6 ] * rtB . dzs1soumuc
[ 2 ] ; m3fe2punjq_p += rtB . bxute4gwb3 [ bpIndex_idx_0 ] * rtB . bxute4gwb3
[ bpIndex_idx_0 ] ; rtB . ks25o2ves0 [ bpIndex_idx_0 ] = rtX . iuemkmhnjl [
bpIndex_idx_0 ] ; } if ( ssIsMajorTimeStep ( rtS ) ) { rtDW . g4ktzwz3i1 =
rtB . ks25o2ves0 [ 2 ] >= rtP . Limitaltitudetotroposhere_UpperSat ? 1 : rtB
. ks25o2ves0 [ 2 ] > rtP . Limitaltitudetotroposhere_LowerSat ? 0 : - 1 ; }
rtB . ktmthpvsav = rtDW . g4ktzwz3i1 == 1 ? rtP .
Limitaltitudetotroposhere_UpperSat : rtDW . g4ktzwz3i1 == - 1 ? rtP .
Limitaltitudetotroposhere_LowerSat : rtB . ks25o2ves0 [ 2 ] ; rtB .
g0uv0nbjrn = rtP . LapseRate_Gain * rtB . ktmthpvsav ; rtB . hwshuznfry = rtP
. SeaLevelTemperature_Value - rtB . g0uv0nbjrn ; rtB . gyvp0nr1ic = rtP .
uT0_Gain * rtB . hwshuznfry ; rtB . fpjovq1wmk = rtP .
AltitudeofTroposphere_Value - rtB . ks25o2ves0 [ 2 ] ; if ( ssIsMajorTimeStep
( rtS ) ) { rtDW . ofhki50iy1 = rtB . fpjovq1wmk >= rtP .
LimitaltitudetoStratosphere_UpperSat ? 1 : rtB . fpjovq1wmk > rtP .
LimitaltitudetoStratosphere_LowerSat ? 0 : - 1 ; } rtB . ewye0ur1dg = rtDW .
ofhki50iy1 == 1 ? rtP . LimitaltitudetoStratosphere_UpperSat : rtDW .
ofhki50iy1 == - 1 ? rtP . LimitaltitudetoStratosphere_LowerSat : rtB .
fpjovq1wmk ; if ( ( rtB . gyvp0nr1ic < 0.0 ) && ( rtP .
Constant_Value_d2f1ederhe > muDoubleScalarFloor ( rtP .
Constant_Value_d2f1ederhe ) ) ) { d1bmmtsdzs = - muDoubleScalarPower ( - rtB
. gyvp0nr1ic , rtP . Constant_Value_d2f1ederhe ) ; } else { d1bmmtsdzs =
muDoubleScalarPower ( rtB . gyvp0nr1ic , rtP . Constant_Value_d2f1ederhe ) ;
} rtB . fkybzc33mt = d1bmmtsdzs / rtB . gyvp0nr1ic ; rtB . b21axyrc0y = rtP .
gR_Gain * rtB . ewye0ur1dg ; rtB . h0chbuggcq = 1.0 / rtB . hwshuznfry * rtB
. b21axyrc0y ; rtB . odqt54fd3r = rtP . rho0_Gain * rtB . fkybzc33mt ; rtB .
iwsvf4t0jp = rtB . odqt54fd3r * muDoubleScalarExp ( rtB . h0chbuggcq ) ; rtB
. ijj1ba05uy = rtP . gammaR_Gain * rtB . hwshuznfry ; if ( ssIsMajorTimeStep
( rtS ) ) { if ( rtDW . nx5ne33bex != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; rtDW . nx5ne33bex = 0 ;
} lvewqzupwi = muDoubleScalarSqrt ( rtB . ijj1ba05uy ) ; } else { if ( rtB .
ijj1ba05uy < 0.0 ) { lvewqzupwi = - muDoubleScalarSqrt ( muDoubleScalarAbs (
rtB . ijj1ba05uy ) ) ; } else { lvewqzupwi = muDoubleScalarSqrt ( rtB .
ijj1ba05uy ) ; } if ( rtB . ijj1ba05uy < 0.0 ) { rtDW . nx5ne33bex = 1 ; } }
rtB . ney5ntjpte = ssGetT ( rtS ) ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { if
( ssIsMajorTimeStep ( rtS ) ) { rtDW . ek25wc14yf = ( rtB . ney5ntjpte >= rtP
. DiscreteWindGustModel_t_0 ) ; } ivguwgcntv = rtDW . ek25wc14yf ; rtB .
b25nd1ut2t = ( rtDW . ek25wc14yf && ( rtP . DiscreteWindGustModel_Gx != 0.0 )
) ; if ( ssIsMajorTimeStep ( rtS ) ) { if ( rtB . b25nd1ut2t ) { if ( ! rtDW
. f3e4goswub ) { if ( ssGetTaskTime ( rtS , 1 ) != ssGetTStart ( rtS ) ) {
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } ( ( XDis * )
ssGetContStateDisabled ( rtS ) ) -> bm4wjkp3hh = 0 ; rtX . bm4wjkp3hh = rtP .
DistanceintoGustxLimitedtogustlengthd_IC ; rtDW . f3e4goswub = true ; } }
else { if ( rtDW . f3e4goswub ) { ssSetBlockStateForSolverChangedAtMajorStep
( rtS ) ; ( ( XDis * ) ssGetContStateDisabled ( rtS ) ) -> bm4wjkp3hh = 1 ;
rtDW . f3e4goswub = false ; } } } } if ( rtDW . f3e4goswub ) { if (
ssIsMajorTimeStep ( rtS ) ) { if ( rtX . bm4wjkp3hh >= rtP .
Distanceintogustx_d_m ) { rtX . bm4wjkp3hh = rtP . Distanceintogustx_d_m ; }
else { if ( rtX . bm4wjkp3hh <= rtP .
DistanceintoGustxLimitedtogustlengthd_LowerSat ) { rtX . bm4wjkp3hh = rtP .
DistanceintoGustxLimitedtogustlengthd_LowerSat ; } } } rtB . juld5yz3om = rtX
. bm4wjkp3hh ; if ( ssIsMajorTimeStep ( rtS ) ) { srUpdateBC ( rtDW .
pkkgwpmnt2 ) ; } } if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { rtB . oeyxyxnkxg =
( ( ivguwgcntv != 0.0 ) && ( rtP . DiscreteWindGustModel_Gy != 0.0 ) ) ; }
jgkdl5leza ( rtS , rtB . oeyxyxnkxg , & rtB . jgkdl5lezan , & rtDW .
jgkdl5lezan , & rtP . jgkdl5lezan , & rtX . jgkdl5lezan , rtP .
Distanceintogusty_d_m , & ( ( XDis * ) ssGetContStateDisabled ( rtS ) ) ->
jgkdl5lezan ) ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { rtB . owpauozhbv = ( (
ivguwgcntv != 0.0 ) && ( rtP . DiscreteWindGustModel_Gz != 0.0 ) ) ; }
jgkdl5leza ( rtS , rtB . owpauozhbv , & rtB . fieqmbp0km , & rtDW .
fieqmbp0km , & rtP . fieqmbp0km , & rtX . fieqmbp0km , rtP .
Distanceintogustz_d_m , & ( ( XDis * ) ssGetContStateDisabled ( rtS ) ) ->
fieqmbp0km ) ; rtB . dx5g5jxszw [ 0 ] = 3.1415926535897931 / rtP .
DiscreteWindGustModel_d_m [ 0 ] * rtB . juld5yz3om ; rtB . dx5g5jxszw [ 1 ] =
3.1415926535897931 / rtP . DiscreteWindGustModel_d_m [ 1 ] * rtB .
jgkdl5lezan . bkh4ie4vlq ; rtB . dx5g5jxszw [ 2 ] = 3.1415926535897931 / rtP
. DiscreteWindGustModel_d_m [ 2 ] * rtB . fieqmbp0km . bkh4ie4vlq ; rtB .
k3tn4bbpdh [ 0 ] = rtP . u_Value - muDoubleScalarCos ( rtB . dx5g5jxszw [ 0 ]
) ; rtB . gtav0xroqm [ 0 ] = rtP . DiscreteWindGustModel_v_m [ 0 ] / 2.0 *
rtB . k3tn4bbpdh [ 0 ] ; rtB . k3tn4bbpdh [ 1 ] = rtP . u_Value -
muDoubleScalarCos ( rtB . dx5g5jxszw [ 1 ] ) ; rtB . gtav0xroqm [ 1 ] = rtP .
DiscreteWindGustModel_v_m [ 1 ] / 2.0 * rtB . k3tn4bbpdh [ 1 ] ; rtB .
k3tn4bbpdh [ 2 ] = rtP . u_Value - muDoubleScalarCos ( rtB . dx5g5jxszw [ 2 ]
) ; rtB . gtav0xroqm [ 2 ] = rtP . DiscreteWindGustModel_v_m [ 2 ] / 2.0 *
rtB . k3tn4bbpdh [ 2 ] ; rtB . optvc153u0 = 3.280839895013123 * rtB .
ks25o2ves0 [ 2 ] ; if ( ssIsMajorTimeStep ( rtS ) ) { rtDW . ifz1r4v4pr = rtB
. optvc153u0 >= rtP . LimitFunction10ftto1000ft_UpperSat ? 1 : rtB .
optvc153u0 > rtP . LimitFunction10ftto1000ft_LowerSat ? 0 : - 1 ; } rtB .
ie5ujfwk1t = rtDW . ifz1r4v4pr == 1 ? rtP .
LimitFunction10ftto1000ft_UpperSat : rtDW . ifz1r4v4pr == - 1 ? rtP .
LimitFunction10ftto1000ft_LowerSat : rtB . optvc153u0 ; rtB . lweizeobnn [ 0
] = rtP . Lw_Gain * rtB . ie5ujfwk1t ; rtB . lweizeobnn [ 1 ] = rtP . Lw_Gain
* rtB . in1jikpuyp ; rtB . guh13rgg0c = plook_bincpa ( rtB . optvc153u0 , rtP
. PreLookUpIndexSearchaltitude_BreakpointsData , 11U , & rtB . pba0balycr , &
rtDW . ltv3hasgw5 ) ; frac [ 0 ] = rtB . pba0balycr ; frac [ 1 ] = rtB .
m4ioj5ifig ; bpIndex [ 0 ] = rtB . guh13rgg0c ; bpIndex [ 1 ] = rtB .
kjfzsflye3 ; rtB . bsrwvm2oyt = intrp2d_la_pw ( bpIndex , frac , rtP .
MediumHighAltitudeIntensity_Table , 12U , rtP .
MediumHighAltitudeIntensity_maxIndex ) ; if ( ssIsSampleHit ( rtS , 2 , 0 ) )
{ rtB . c0yzmpobn3 [ 0 ] = rtB . iw50kb54tc [ 0 ] * rtDW . e5dwuk5zfi [ 0 ] ;
rtB . c0yzmpobn3 [ 1 ] = rtB . iw50kb54tc [ 1 ] * rtDW . e5dwuk5zfi [ 1 ] ;
rtB . c0yzmpobn3 [ 2 ] = rtB . iw50kb54tc [ 2 ] * rtDW . e5dwuk5zfi [ 2 ] ;
rtB . c0yzmpobn3 [ 3 ] = rtB . iw50kb54tc [ 3 ] * rtDW . e5dwuk5zfi [ 3 ] ; }
if ( ssIsMajorTimeStep ( rtS ) ) { if ( rtDW . ag2s0tuis0 != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; rtDW . ag2s0tuis0 = 0 ;
} rtB . apsbh2a4ml = muDoubleScalarSqrt ( m3fe2punjq_p ) ; } else if (
m3fe2punjq_p < 0.0 ) { rtB . apsbh2a4ml = - muDoubleScalarSqrt (
muDoubleScalarAbs ( m3fe2punjq_p ) ) ; rtDW . ag2s0tuis0 = 1 ; } else { rtB .
apsbh2a4ml = muDoubleScalarSqrt ( m3fe2punjq_p ) ; } m3fe2punjq_p =
3.280839895013123 * rtB . apsbh2a4ml ; if ( ssIsSampleHit ( rtS , 1 , 0 ) &&
ssIsMajorTimeStep ( rtS ) ) { if ( rtP .
DrydenWindTurbulenceModelContinuousqr_T_on > 0.0 ) { if ( ! rtDW . ekhaunodew
) { if ( ssGetTaskTime ( rtS , 1 ) != ssGetTStart ( rtS ) ) {
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } ( void ) memset ( & (
( ( XDis * ) ssGetContStateDisabled ( rtS ) ) -> f4qi5fjsdf ) , 0 , 2 *
sizeof ( boolean_T ) ) ; rtX . f4qi5fjsdf [ 0 ] = rtP . pgw_p_IC ; rtX .
f4qi5fjsdf [ 1 ] = rtP . pgw_p_IC ; rtDW . ekhaunodew = true ; } } else { if
( rtDW . ekhaunodew ) { ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ;
( void ) memset ( & ( ( ( XDis * ) ssGetContStateDisabled ( rtS ) ) ->
f4qi5fjsdf ) , 1 , 2 * sizeof ( boolean_T ) ) ; rtB . mfxy45ba4c [ 0 ] = rtP
. pgw_Y0 ; rtB . mfxy45ba4c [ 1 ] = rtP . pgw_Y0 ; rtDW . ekhaunodew = false
; } } } if ( rtDW . ekhaunodew ) { ivguwgcntv = 0.8 / m3fe2punjq_p ; if (
ivguwgcntv < 0.0 ) { ivguwgcntv = - muDoubleScalarSqrt ( - ivguwgcntv ) ; }
else { ivguwgcntv = muDoubleScalarSqrt ( ivguwgcntv ) ; } if ( ( rtB .
lweizeobnn [ 0 ] < 0.0 ) && ( rtP . Constant1_Value > muDoubleScalarFloor (
rtP . Constant1_Value ) ) ) { d1bmmtsdzs = - muDoubleScalarPower ( - rtB .
lweizeobnn [ 0 ] , rtP . Constant1_Value ) ; } else { d1bmmtsdzs =
muDoubleScalarPower ( rtB . lweizeobnn [ 0 ] , rtP . Constant1_Value ) ; }
rtB . cfsazsff55 [ 0 ] = ivguwgcntv / d1bmmtsdzs ; rtB . e40fmoqlfe [ 0 ] =
rtB . o1xsnq5r4j * rtB . cfsazsff55 [ 0 ] ; rtB . gzz55ngh4d [ 0 ] = rtB .
e40fmoqlfe [ 0 ] * rtB . c0yzmpobn3 [ 3 ] ; rtB . of5hnba1qi [ 0 ] = rtX .
f4qi5fjsdf [ 0 ] ; rtB . cr4rspe1f1 [ 0 ] = rtB . gzz55ngh4d [ 0 ] - rtB .
of5hnba1qi [ 0 ] ; if ( ( rtB . lweizeobnn [ 1 ] < 0.0 ) && ( rtP .
Constant1_Value > muDoubleScalarFloor ( rtP . Constant1_Value ) ) ) {
d1bmmtsdzs = - muDoubleScalarPower ( - rtB . lweizeobnn [ 1 ] , rtP .
Constant1_Value ) ; } else { d1bmmtsdzs = muDoubleScalarPower ( rtB .
lweizeobnn [ 1 ] , rtP . Constant1_Value ) ; } rtB . cfsazsff55 [ 1 ] =
ivguwgcntv / d1bmmtsdzs ; rtB . e40fmoqlfe [ 1 ] = rtB . o1xsnq5r4j * rtB .
cfsazsff55 [ 1 ] ; rtB . gzz55ngh4d [ 1 ] = rtB . e40fmoqlfe [ 1 ] * rtB .
c0yzmpobn3 [ 3 ] ; rtB . of5hnba1qi [ 1 ] = rtX . f4qi5fjsdf [ 1 ] ; rtB .
cr4rspe1f1 [ 1 ] = rtB . gzz55ngh4d [ 1 ] - rtB . of5hnba1qi [ 1 ] ; rtB .
mfxy45ba4c [ 0 ] = rtB . k1qm14mokl * rtB . of5hnba1qi [ 0 ] ; rtB .
mfxy45ba4c [ 1 ] = rtB . bsrwvm2oyt * rtB . of5hnba1qi [ 1 ] ; rtB .
p3bdm41p1x = m3fe2punjq_p * rtB . buysvvpcb4 ; rtB . hbksfryqsi [ 0 ] = rtB .
p3bdm41p1x * rtB . cr4rspe1f1 [ 0 ] ; rtB . hbksfryqsi [ 1 ] = rtB .
p3bdm41p1x * rtB . cr4rspe1f1 [ 1 ] ; if ( ssIsMajorTimeStep ( rtS ) ) {
srUpdateBC ( rtDW . nfawadvxsq ) ; } } if ( ssIsSampleHit ( rtS , 1 , 0 ) &&
ssIsMajorTimeStep ( rtS ) ) { if ( rtP .
DrydenWindTurbulenceModelContinuousqr_T_on > 0.0 ) { if ( ! rtDW . ptxtk1nv30
) { if ( ssGetTaskTime ( rtS , 1 ) != ssGetTStart ( rtS ) ) {
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } ( void ) memset ( & (
( ( XDis * ) ssGetContStateDisabled ( rtS ) ) -> pxrnvzd5eg ) , 0 , 4 *
sizeof ( boolean_T ) ) ; rtX . pxrnvzd5eg [ 0 ] = rtP . wg_p1_IC ; rtX .
dolulbw4pb [ 0 ] = rtP . wg_p2_IC ; rtX . pxrnvzd5eg [ 1 ] = rtP . wg_p1_IC ;
rtX . dolulbw4pb [ 1 ] = rtP . wg_p2_IC ; rtDW . ptxtk1nv30 = true ; } } else
{ if ( rtDW . ptxtk1nv30 ) { ssSetBlockStateForSolverChangedAtMajorStep ( rtS
) ; ( void ) memset ( & ( ( ( XDis * ) ssGetContStateDisabled ( rtS ) ) ->
pxrnvzd5eg ) , 1 , 4 * sizeof ( boolean_T ) ) ; rtB . gunypeaovn [ 0 ] = rtP
. wgw_Y0 ; rtB . gunypeaovn [ 1 ] = rtP . wgw_Y0 ; rtDW . ptxtk1nv30 = false
; } } } if ( rtDW . ptxtk1nv30 ) { rtB . clyzpdujo2 [ 0 ] = rtB . lweizeobnn
[ 0 ] / m3fe2punjq_p ; rtB . nmo53ueedw [ 0 ] = rtP . upi_Gain_cv3kqumzgv *
rtB . clyzpdujo2 [ 0 ] ; rtB . clyzpdujo2 [ 1 ] = rtB . lweizeobnn [ 1 ] /
m3fe2punjq_p ; rtB . nmo53ueedw [ 1 ] = rtP . upi_Gain_cv3kqumzgv * rtB .
clyzpdujo2 [ 1 ] ; if ( ssIsMajorTimeStep ( rtS ) ) { if ( rtDW . jjjovfqaio
!= 0 ) { ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; rtDW .
jjjovfqaio = 0 ; } frac [ 0 ] = muDoubleScalarSqrt ( rtB . nmo53ueedw [ 0 ] )
; frac [ 1 ] = muDoubleScalarSqrt ( rtB . nmo53ueedw [ 1 ] ) ; } else { if (
rtB . nmo53ueedw [ 0 ] < 0.0 ) { frac [ 0 ] = - muDoubleScalarSqrt (
muDoubleScalarAbs ( rtB . nmo53ueedw [ 0 ] ) ) ; } else { frac [ 0 ] =
muDoubleScalarSqrt ( rtB . nmo53ueedw [ 0 ] ) ; } if ( rtB . nmo53ueedw [ 0 ]
< 0.0 ) { rtDW . jjjovfqaio = 1 ; } if ( rtB . nmo53ueedw [ 1 ] < 0.0 ) {
frac [ 1 ] = - muDoubleScalarSqrt ( muDoubleScalarAbs ( rtB . nmo53ueedw [ 1
] ) ) ; } else { frac [ 1 ] = muDoubleScalarSqrt ( rtB . nmo53ueedw [ 1 ] ) ;
} if ( rtB . nmo53ueedw [ 1 ] < 0.0 ) { rtDW . jjjovfqaio = 1 ; } } rtB .
pcg1z1bmhq [ 0 ] = frac [ 0 ] * rtB . c0yzmpobn3 [ 2 ] ; rtB . lq0mfgsqfo [ 0
] = rtX . pxrnvzd5eg [ 0 ] ; rtB . adrc4dh4xz [ 0 ] = rtB . pcg1z1bmhq [ 0 ]
- rtB . lq0mfgsqfo [ 0 ] ; rtB . maka3wnq5n [ 0 ] = rtB . adrc4dh4xz [ 0 ] /
rtB . clyzpdujo2 [ 0 ] ; rtB . cayuqvyp2b [ 0 ] = rtB . maka3wnq5n [ 0 ] *
rtB . b4p0x5sch3 * rtB . clyzpdujo2 [ 0 ] ; rtB . on0w3ltr4i [ 0 ] = rtX .
dolulbw4pb [ 0 ] ; rtB . jokuewxh0b [ 0 ] = ( rtB . lq0mfgsqfo [ 0 ] - rtB .
on0w3ltr4i [ 0 ] ) + rtB . cayuqvyp2b [ 0 ] ; rtB . pxqxqpltfm [ 0 ] = rtB .
jokuewxh0b [ 0 ] / rtB . clyzpdujo2 [ 0 ] ; rtB . pcg1z1bmhq [ 1 ] = frac [ 1
] * rtB . c0yzmpobn3 [ 2 ] ; rtB . lq0mfgsqfo [ 1 ] = rtX . pxrnvzd5eg [ 1 ]
; rtB . adrc4dh4xz [ 1 ] = rtB . pcg1z1bmhq [ 1 ] - rtB . lq0mfgsqfo [ 1 ] ;
rtB . maka3wnq5n [ 1 ] = rtB . adrc4dh4xz [ 1 ] / rtB . clyzpdujo2 [ 1 ] ;
rtB . cayuqvyp2b [ 1 ] = rtB . maka3wnq5n [ 1 ] * rtB . b4p0x5sch3 * rtB .
clyzpdujo2 [ 1 ] ; rtB . on0w3ltr4i [ 1 ] = rtX . dolulbw4pb [ 1 ] ; rtB .
jokuewxh0b [ 1 ] = ( rtB . lq0mfgsqfo [ 1 ] - rtB . on0w3ltr4i [ 1 ] ) + rtB
. cayuqvyp2b [ 1 ] ; rtB . pxqxqpltfm [ 1 ] = rtB . jokuewxh0b [ 1 ] / rtB .
clyzpdujo2 [ 1 ] ; rtB . gunypeaovn [ 0 ] = rtB . k1qm14mokl * rtB .
on0w3ltr4i [ 0 ] ; rtB . gunypeaovn [ 1 ] = rtB . bsrwvm2oyt * rtB .
on0w3ltr4i [ 1 ] ; if ( ssIsMajorTimeStep ( rtS ) ) { srUpdateBC ( rtDW .
ne00r4ogt0 ) ; } } if ( ssIsSampleHit ( rtS , 1 , 0 ) && ssIsMajorTimeStep (
rtS ) ) { if ( rtP . DrydenWindTurbulenceModelContinuousqr_T_on > 0.0 ) { if
( ! rtDW . dsenq15ybl ) { if ( ssGetTaskTime ( rtS , 1 ) != ssGetTStart ( rtS
) ) { ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } ( void ) memset
( & ( ( ( XDis * ) ssGetContStateDisabled ( rtS ) ) -> cgba0qyovs ) , 0 , 2 *
sizeof ( boolean_T ) ) ; rtX . cgba0qyovs [ 0 ] = rtP . qgw_p_IC ; rtX .
cgba0qyovs [ 1 ] = rtP . qgw_p_IC ; rtDW . dsenq15ybl = true ; } } else { if
( rtDW . dsenq15ybl ) { ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ;
( void ) memset ( & ( ( ( XDis * ) ssGetContStateDisabled ( rtS ) ) ->
cgba0qyovs ) , 1 , 2 * sizeof ( boolean_T ) ) ; rtB . oum15dzd35 [ 0 ] = rtP
. qgw_Y0 ; rtB . oum15dzd35 [ 1 ] = rtP . qgw_Y0 ; rtDW . dsenq15ybl = false
; } } } if ( rtDW . dsenq15ybl ) { rtB . dt4hmrvy0i = rtP . pi4_Gain *
m3fe2punjq_p ; rtB . lazwt4wtdp [ 0 ] = rtB . gunypeaovn [ 0 ] / m3fe2punjq_p
; rtB . b1khfo1ad3 [ 0 ] = rtX . cgba0qyovs [ 0 ] ; rtB . fr0lgjauqr [ 0 ] =
rtB . lazwt4wtdp [ 0 ] - rtB . b1khfo1ad3 [ 0 ] ; rtB . oum15dzd35 [ 0 ] =
rtB . dt4hmrvy0i / rtB . p5dpqn0t0m * rtB . fr0lgjauqr [ 0 ] ; rtB .
lazwt4wtdp [ 1 ] = rtB . gunypeaovn [ 1 ] / m3fe2punjq_p ; rtB . b1khfo1ad3 [
1 ] = rtX . cgba0qyovs [ 1 ] ; rtB . fr0lgjauqr [ 1 ] = rtB . lazwt4wtdp [ 1
] - rtB . b1khfo1ad3 [ 1 ] ; rtB . oum15dzd35 [ 1 ] = rtB . dt4hmrvy0i / rtB
. p5dpqn0t0m * rtB . fr0lgjauqr [ 1 ] ; if ( ssIsMajorTimeStep ( rtS ) ) {
srUpdateBC ( rtDW . ddqyu2zcpv ) ; } } if ( ssIsMajorTimeStep ( rtS ) ) {
rtDW . ia5fgrdrmk = rtB . optvc153u0 >= rtP . LimitHeighth1000ft_UpperSat ? 1
: rtB . optvc153u0 > rtP . LimitHeighth1000ft_LowerSat ? 0 : - 1 ; } rtB .
fkpy3ggxgw = rtDW . ia5fgrdrmk == 1 ? rtP . LimitHeighth1000ft_UpperSat :
rtDW . ia5fgrdrmk == - 1 ? rtP . LimitHeighth1000ft_LowerSat : rtB .
optvc153u0 ; ivguwgcntv = 0.000823 * rtB . fkpy3ggxgw + 0.177 ; if (
ivguwgcntv < 0.0 ) { ivguwgcntv = - muDoubleScalarPower ( - ivguwgcntv , 0.4
) ; } else { ivguwgcntv = muDoubleScalarPower ( ivguwgcntv , 0.4 ) ; } rtB .
lklogdjcfo = 1.0 / ivguwgcntv * rtB . k1qm14mokl ; ivguwgcntv = 0.000823 *
rtB . ie5ujfwk1t + 0.177 ; if ( ivguwgcntv < 0.0 ) { ivguwgcntv = -
muDoubleScalarPower ( - ivguwgcntv , 1.2 ) ; } else { ivguwgcntv =
muDoubleScalarPower ( ivguwgcntv , 1.2 ) ; } ivguwgcntv = rtB . ie5ujfwk1t /
ivguwgcntv ; rtB . bdqq1m4fup [ 0 ] = rtP . Lv_Gain * ivguwgcntv ; rtB .
bdqq1m4fup [ 1 ] = rtP . Lv_Gain * rtB . in1jikpuyp ; if ( ssIsSampleHit (
rtS , 1 , 0 ) && ssIsMajorTimeStep ( rtS ) ) { if ( rtP .
DrydenWindTurbulenceModelContinuousqr_T_on > 0.0 ) { if ( ! rtDW . nhrxrmv3xz
) { if ( ssGetTaskTime ( rtS , 1 ) != ssGetTStart ( rtS ) ) {
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } ( void ) memset ( & (
( ( XDis * ) ssGetContStateDisabled ( rtS ) ) -> fbih5gck0s ) , 0 , 4 *
sizeof ( boolean_T ) ) ; rtX . fbih5gck0s [ 0 ] = rtP . vg_p1_IC ; rtX .
moa44kkouk [ 0 ] = rtP . vgw_p2_IC ; rtX . fbih5gck0s [ 1 ] = rtP . vg_p1_IC
; rtX . moa44kkouk [ 1 ] = rtP . vgw_p2_IC ; rtDW . nhrxrmv3xz = true ; } }
else { if ( rtDW . nhrxrmv3xz ) { ssSetBlockStateForSolverChangedAtMajorStep
( rtS ) ; ( void ) memset ( & ( ( ( XDis * ) ssGetContStateDisabled ( rtS ) )
-> fbih5gck0s ) , 1 , 4 * sizeof ( boolean_T ) ) ; rtB . joo0gvrcnf [ 0 ] =
rtP . vgw_Y0 ; rtB . joo0gvrcnf [ 1 ] = rtP . vgw_Y0 ; rtDW . nhrxrmv3xz =
false ; } } } if ( rtDW . nhrxrmv3xz ) { rtB . fmyvw4bkag [ 0 ] = rtB .
bdqq1m4fup [ 0 ] / m3fe2punjq_p ; rtB . ivknkgdhps [ 0 ] = rtP .
upi_Gain_gy2nvc1rod * rtB . fmyvw4bkag [ 0 ] ; rtB . fmyvw4bkag [ 1 ] = rtB .
bdqq1m4fup [ 1 ] / m3fe2punjq_p ; rtB . ivknkgdhps [ 1 ] = rtP .
upi_Gain_gy2nvc1rod * rtB . fmyvw4bkag [ 1 ] ; if ( ssIsMajorTimeStep ( rtS )
) { if ( rtDW . fg0n3tzsij != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; rtDW . fg0n3tzsij = 0 ;
} frac [ 0 ] = muDoubleScalarSqrt ( rtB . ivknkgdhps [ 0 ] ) ; frac [ 1 ] =
muDoubleScalarSqrt ( rtB . ivknkgdhps [ 1 ] ) ; } else { if ( rtB .
ivknkgdhps [ 0 ] < 0.0 ) { frac [ 0 ] = - muDoubleScalarSqrt (
muDoubleScalarAbs ( rtB . ivknkgdhps [ 0 ] ) ) ; } else { frac [ 0 ] =
muDoubleScalarSqrt ( rtB . ivknkgdhps [ 0 ] ) ; } if ( rtB . ivknkgdhps [ 0 ]
< 0.0 ) { rtDW . fg0n3tzsij = 1 ; } if ( rtB . ivknkgdhps [ 1 ] < 0.0 ) {
frac [ 1 ] = - muDoubleScalarSqrt ( muDoubleScalarAbs ( rtB . ivknkgdhps [ 1
] ) ) ; } else { frac [ 1 ] = muDoubleScalarSqrt ( rtB . ivknkgdhps [ 1 ] ) ;
} if ( rtB . ivknkgdhps [ 1 ] < 0.0 ) { rtDW . fg0n3tzsij = 1 ; } } rtB .
mmtxyw115q [ 0 ] = frac [ 0 ] * rtB . c0yzmpobn3 [ 1 ] ; rtB . oprrh1lrfg [ 0
] = rtX . fbih5gck0s [ 0 ] ; rtB . ealls03ntz [ 0 ] = rtB . mmtxyw115q [ 0 ]
- rtB . oprrh1lrfg [ 0 ] ; rtB . cmdkij32ho [ 0 ] = rtB . ealls03ntz [ 0 ] /
rtB . fmyvw4bkag [ 0 ] ; rtB . gdx0qpo30e [ 0 ] = rtB . cmdkij32ho [ 0 ] *
rtB . fmyvw4bkag [ 0 ] ; rtB . bqywvwxy2u [ 0 ] = rtX . moa44kkouk [ 0 ] ;
rtB . md41g5fldt [ 0 ] = rtP . sqrt3_Gain * rtB . gdx0qpo30e [ 0 ] ; rtB .
ke0ksubsuu [ 0 ] = ( rtB . oprrh1lrfg [ 0 ] - rtB . bqywvwxy2u [ 0 ] ) + rtB
. md41g5fldt [ 0 ] ; rtB . fmytsanjo2 [ 0 ] = rtB . ke0ksubsuu [ 0 ] / rtB .
fmyvw4bkag [ 0 ] ; rtB . mmtxyw115q [ 1 ] = frac [ 1 ] * rtB . c0yzmpobn3 [ 1
] ; rtB . oprrh1lrfg [ 1 ] = rtX . fbih5gck0s [ 1 ] ; rtB . ealls03ntz [ 1 ]
= rtB . mmtxyw115q [ 1 ] - rtB . oprrh1lrfg [ 1 ] ; rtB . cmdkij32ho [ 1 ] =
rtB . ealls03ntz [ 1 ] / rtB . fmyvw4bkag [ 1 ] ; rtB . gdx0qpo30e [ 1 ] =
rtB . cmdkij32ho [ 1 ] * rtB . fmyvw4bkag [ 1 ] ; rtB . bqywvwxy2u [ 1 ] =
rtX . moa44kkouk [ 1 ] ; rtB . md41g5fldt [ 1 ] = rtP . sqrt3_Gain * rtB .
gdx0qpo30e [ 1 ] ; rtB . ke0ksubsuu [ 1 ] = ( rtB . oprrh1lrfg [ 1 ] - rtB .
bqywvwxy2u [ 1 ] ) + rtB . md41g5fldt [ 1 ] ; rtB . fmytsanjo2 [ 1 ] = rtB .
ke0ksubsuu [ 1 ] / rtB . fmyvw4bkag [ 1 ] ; rtB . joo0gvrcnf [ 0 ] = rtB .
lklogdjcfo * rtB . bqywvwxy2u [ 0 ] ; rtB . joo0gvrcnf [ 1 ] = rtB .
bsrwvm2oyt * rtB . bqywvwxy2u [ 1 ] ; if ( ssIsMajorTimeStep ( rtS ) ) {
srUpdateBC ( rtDW . ceqnsrmeb1 ) ; } } if ( ssIsSampleHit ( rtS , 1 , 0 ) &&
ssIsMajorTimeStep ( rtS ) ) { if ( rtP .
DrydenWindTurbulenceModelContinuousqr_T_on > 0.0 ) { if ( ! rtDW . dtbuv1dhzu
) { if ( ssGetTaskTime ( rtS , 1 ) != ssGetTStart ( rtS ) ) {
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } ( void ) memset ( & (
( ( XDis * ) ssGetContStateDisabled ( rtS ) ) -> dydkrcbic2 ) , 0 , 2 *
sizeof ( boolean_T ) ) ; rtX . dydkrcbic2 [ 0 ] = rtP . rgw_p_IC ; rtX .
dydkrcbic2 [ 1 ] = rtP . rgw_p_IC ; rtDW . dtbuv1dhzu = true ; } } else { if
( rtDW . dtbuv1dhzu ) { ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ;
( void ) memset ( & ( ( ( XDis * ) ssGetContStateDisabled ( rtS ) ) ->
dydkrcbic2 ) , 1 , 2 * sizeof ( boolean_T ) ) ; rtB . b2e3g5hpyo [ 0 ] = rtP
. rgw_Y0 ; rtB . b2e3g5hpyo [ 1 ] = rtP . rgw_Y0 ; rtDW . dtbuv1dhzu = false
; } } } if ( rtDW . dtbuv1dhzu ) { rtB . fjfsy0b0jg = rtP . pi3_Gain *
m3fe2punjq_p ; rtB . j5rmezwb0e [ 0 ] = rtB . joo0gvrcnf [ 0 ] / m3fe2punjq_p
; rtB . fg2kqgg3ek [ 0 ] = rtX . dydkrcbic2 [ 0 ] ; rtB . fjkfysvnh3 [ 0 ] =
rtB . j5rmezwb0e [ 0 ] - rtB . fg2kqgg3ek [ 0 ] ; rtB . b2e3g5hpyo [ 0 ] =
rtB . fjfsy0b0jg / rtB . p5dpqn0t0m * rtB . fjkfysvnh3 [ 0 ] ; rtB .
j5rmezwb0e [ 1 ] = rtB . joo0gvrcnf [ 1 ] / m3fe2punjq_p ; rtB . fg2kqgg3ek [
1 ] = rtX . dydkrcbic2 [ 1 ] ; rtB . fjkfysvnh3 [ 1 ] = rtB . j5rmezwb0e [ 1
] - rtB . fg2kqgg3ek [ 1 ] ; rtB . b2e3g5hpyo [ 1 ] = rtB . fjfsy0b0jg / rtB
. p5dpqn0t0m * rtB . fjkfysvnh3 [ 1 ] ; if ( ssIsMajorTimeStep ( rtS ) ) {
srUpdateBC ( rtDW . iu54wjtvx2 ) ; } } if ( ssIsSampleHit ( rtS , 1 , 0 ) &&
ssIsMajorTimeStep ( rtS ) ) { if ( rtP .
DrydenWindTurbulenceModelContinuousqr_T_on > 0.0 ) { if ( ! rtDW . gjeq11lqni
) { if ( ssGetTaskTime ( rtS , 1 ) != ssGetTStart ( rtS ) ) {
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } ( void ) memset ( & (
( ( XDis * ) ssGetContStateDisabled ( rtS ) ) -> cnbgfejjbm ) , 0 , 2 *
sizeof ( boolean_T ) ) ; rtX . cnbgfejjbm [ 0 ] = rtP . ug_p_IC ; rtX .
cnbgfejjbm [ 1 ] = rtP . ug_p_IC ; rtDW . gjeq11lqni = true ; } } else { if (
rtDW . gjeq11lqni ) { ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; (
void ) memset ( & ( ( ( XDis * ) ssGetContStateDisabled ( rtS ) ) ->
cnbgfejjbm ) , 1 , 2 * sizeof ( boolean_T ) ) ; rtB . iihgtnzfrf [ 0 ] = rtP
. ugw_Y0 ; rtB . iihgtnzfrf [ 1 ] = rtP . ugw_Y0 ; rtDW . gjeq11lqni = false
; } } } if ( rtDW . gjeq11lqni ) { rtB . h2tissrusk [ 0 ] = ivguwgcntv /
m3fe2punjq_p ; rtB . h2tissrusk [ 1 ] = rtB . in1jikpuyp / m3fe2punjq_p ; rtB
. beaa0ietcq [ 0 ] = rtP . upi_Gain * rtB . h2tissrusk [ 0 ] ; rtB .
beaa0ietcq [ 1 ] = rtP . upi_Gain * rtB . h2tissrusk [ 1 ] ; if (
ssIsMajorTimeStep ( rtS ) ) { if ( rtDW . ptevicn33b != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; rtDW . ptevicn33b = 0 ;
} frac [ 0 ] = muDoubleScalarSqrt ( rtB . beaa0ietcq [ 0 ] ) ; frac [ 1 ] =
muDoubleScalarSqrt ( rtB . beaa0ietcq [ 1 ] ) ; } else { if ( rtB .
beaa0ietcq [ 0 ] < 0.0 ) { frac [ 0 ] = - muDoubleScalarSqrt (
muDoubleScalarAbs ( rtB . beaa0ietcq [ 0 ] ) ) ; } else { frac [ 0 ] =
muDoubleScalarSqrt ( rtB . beaa0ietcq [ 0 ] ) ; } if ( rtB . beaa0ietcq [ 0 ]
< 0.0 ) { rtDW . ptevicn33b = 1 ; } if ( rtB . beaa0ietcq [ 1 ] < 0.0 ) {
frac [ 1 ] = - muDoubleScalarSqrt ( muDoubleScalarAbs ( rtB . beaa0ietcq [ 1
] ) ) ; } else { frac [ 1 ] = muDoubleScalarSqrt ( rtB . beaa0ietcq [ 1 ] ) ;
} if ( rtB . beaa0ietcq [ 1 ] < 0.0 ) { rtDW . ptevicn33b = 1 ; } } rtB .
bph5jjv2nj [ 0 ] = frac [ 0 ] * rtB . c0yzmpobn3 [ 0 ] ; rtB . jj1mymkjgz [ 0
] = rtX . cnbgfejjbm [ 0 ] ; rtB . etpdtmtrnf [ 0 ] = rtB . bph5jjv2nj [ 0 ]
- rtB . jj1mymkjgz [ 0 ] ; rtB . igi43iu4gc [ 0 ] = rtB . etpdtmtrnf [ 0 ] /
rtB . h2tissrusk [ 0 ] ; rtB . bph5jjv2nj [ 1 ] = frac [ 1 ] * rtB .
c0yzmpobn3 [ 0 ] ; rtB . jj1mymkjgz [ 1 ] = rtX . cnbgfejjbm [ 1 ] ; rtB .
etpdtmtrnf [ 1 ] = rtB . bph5jjv2nj [ 1 ] - rtB . jj1mymkjgz [ 1 ] ; rtB .
igi43iu4gc [ 1 ] = rtB . etpdtmtrnf [ 1 ] / rtB . h2tissrusk [ 1 ] ; rtB .
iihgtnzfrf [ 0 ] = rtB . jj1mymkjgz [ 0 ] * rtB . lklogdjcfo ; rtB .
iihgtnzfrf [ 1 ] = rtB . jj1mymkjgz [ 1 ] * rtB . bsrwvm2oyt ; if (
ssIsMajorTimeStep ( rtS ) ) { srUpdateBC ( rtDW . cjrmyujqju ) ; } }
rtPrevAction = rtDW . kpq2e44z2g ; if ( ssIsMajorTimeStep ( rtS ) ) { if (
rtB . optvc153u0 <= 1000.0 ) { rtAction = 0 ; } else if ( rtB . optvc153u0 >=
2000.0 ) { rtAction = 1 ; } else { rtAction = 2 ; } rtDW . kpq2e44z2g =
rtAction ; } else { rtAction = rtDW . kpq2e44z2g ; } if ( rtPrevAction !=
rtAction ) { switch ( rtPrevAction ) { case 0 :
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; break ; case 1 :
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; break ; case 2 :
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; break ; } } switch (
rtAction ) { case 0 : if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime (
rtS , 0 ) != ssGetTStart ( rtS ) ) {
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } } rtB . eqg4nglih0 [ 2
] = rtB . b2e3g5hpyo [ 0 ] ; muDoubleScalarSinCos ( rtB . pg1uquivv5 , &
m3fe2punjq_p , & ivguwgcntv ) ; rtB . p4yyhd2kug [ 0 ] = rtB . mfxy45ba4c [ 0
] * ivguwgcntv ; rtB . p4yyhd2kug [ 1 ] = rtB . oum15dzd35 [ 0 ] * ivguwgcntv
; rtB . bv3tfatqfb [ 0 ] = m3fe2punjq_p * rtB . mfxy45ba4c [ 0 ] ; rtB .
bv3tfatqfb [ 1 ] = m3fe2punjq_p * rtB . oum15dzd35 [ 0 ] ; rtB . eqg4nglih0 [
0 ] = rtB . p4yyhd2kug [ 0 ] - rtB . bv3tfatqfb [ 1 ] ; rtB . eqg4nglih0 [ 1
] = rtB . p4yyhd2kug [ 1 ] + rtB . bv3tfatqfb [ 0 ] ; for ( bpIndex_idx_0 = 0
; bpIndex_idx_0 < 3 ; bpIndex_idx_0 ++ ) { rtB . gynkhxmcfk [ bpIndex_idx_0 ]
= 0.0 ; rtB . gynkhxmcfk [ bpIndex_idx_0 ] += rtB . n2gibbklhx [
bpIndex_idx_0 ] * rtB . eqg4nglih0 [ 0 ] ; rtB . gynkhxmcfk [ bpIndex_idx_0 ]
+= rtB . n2gibbklhx [ bpIndex_idx_0 + 3 ] * rtB . eqg4nglih0 [ 1 ] ; rtB .
gynkhxmcfk [ bpIndex_idx_0 ] += rtB . n2gibbklhx [ bpIndex_idx_0 + 6 ] * rtB
. eqg4nglih0 [ 2 ] ; rtB . mdfbuebpbf [ bpIndex_idx_0 ] = rtB . gynkhxmcfk [
bpIndex_idx_0 ] ; } if ( ssIsMajorTimeStep ( rtS ) ) { srUpdateBC ( rtDW .
pfnakgwhvn ) ; } break ; case 1 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( rtS , 0 ) != ssGetTStart ( rtS ) ) {
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } } rtB . mdfbuebpbf [ 0
] = rtP . Gain_Gain * rtB . mfxy45ba4c [ 1 ] ; rtB . mdfbuebpbf [ 1 ] = rtP .
Gain_Gain * rtB . oum15dzd35 [ 1 ] ; rtB . mdfbuebpbf [ 2 ] = rtP . Gain_Gain
* rtB . b2e3g5hpyo [ 1 ] ; if ( ssIsMajorTimeStep ( rtS ) ) { srUpdateBC (
rtDW . gs4wlth0q0 ) ; } break ; case 2 : if ( rtAction != rtPrevAction ) { if
( ssGetTaskTime ( rtS , 0 ) != ssGetTStart ( rtS ) ) {
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } } muDoubleScalarSinCos
( rtB . pg1uquivv5 , & m3fe2punjq_p , & ivguwgcntv ) ; rtB . lez1v1wcmt [ 0 ]
= rtB . mfxy45ba4c [ 0 ] * ivguwgcntv ; rtB . lez1v1wcmt [ 1 ] = rtB .
oum15dzd35 [ 0 ] * ivguwgcntv ; rtB . jtve1smewc [ 0 ] = m3fe2punjq_p * rtB .
mfxy45ba4c [ 0 ] ; rtB . jtve1smewc [ 1 ] = m3fe2punjq_p * rtB . oum15dzd35 [
0 ] ; rtB . fwd0zho2dx [ 0 ] = rtB . lez1v1wcmt [ 0 ] - rtB . jtve1smewc [ 1
] ; rtB . fwd0zho2dx [ 1 ] = rtB . lez1v1wcmt [ 1 ] + rtB . jtve1smewc [ 0 ]
; rtB . fwd0zho2dx [ 2 ] = rtB . b2e3g5hpyo [ 0 ] ; for ( bpIndex_idx_0 = 0 ;
bpIndex_idx_0 < 3 ; bpIndex_idx_0 ++ ) { rtB . pqzxc0jwxr [ bpIndex_idx_0 ] =
0.0 ; rtB . pqzxc0jwxr [ bpIndex_idx_0 ] += rtB . n2gibbklhx [ bpIndex_idx_0
] * rtB . fwd0zho2dx [ 0 ] ; rtB . pqzxc0jwxr [ bpIndex_idx_0 ] += rtB .
n2gibbklhx [ bpIndex_idx_0 + 3 ] * rtB . fwd0zho2dx [ 1 ] ; rtB . pqzxc0jwxr
[ bpIndex_idx_0 ] += rtB . n2gibbklhx [ bpIndex_idx_0 + 6 ] * rtB .
fwd0zho2dx [ 2 ] ; } rtB . n2ablemxjo [ 0 ] = rtB . mfxy45ba4c [ 1 ] - rtB .
pqzxc0jwxr [ 0 ] ; rtB . n2ablemxjo [ 1 ] = rtB . oum15dzd35 [ 1 ] - rtB .
pqzxc0jwxr [ 1 ] ; rtB . n2ablemxjo [ 2 ] = rtB . b2e3g5hpyo [ 1 ] - rtB .
pqzxc0jwxr [ 2 ] ; rtB . lgsfqf2gng = rtB . optvc153u0 - rtP .
max_height_low_Value ; rtB . bvoynuyjfa [ 0 ] = rtB . n2ablemxjo [ 0 ] * rtB
. lgsfqf2gng / rtB . obpi4pygmr ; rtB . mdfbuebpbf [ 0 ] = rtB . pqzxc0jwxr [
0 ] + rtB . bvoynuyjfa [ 0 ] ; rtB . bvoynuyjfa [ 1 ] = rtB . n2ablemxjo [ 1
] * rtB . lgsfqf2gng / rtB . obpi4pygmr ; rtB . mdfbuebpbf [ 1 ] = rtB .
pqzxc0jwxr [ 1 ] + rtB . bvoynuyjfa [ 1 ] ; rtB . bvoynuyjfa [ 2 ] = rtB .
n2ablemxjo [ 2 ] * rtB . lgsfqf2gng / rtB . obpi4pygmr ; rtB . mdfbuebpbf [ 2
] = rtB . pqzxc0jwxr [ 2 ] + rtB . bvoynuyjfa [ 2 ] ; if ( ssIsMajorTimeStep
( rtS ) ) { srUpdateBC ( rtDW . lj1lobgjwr ) ; } break ; } rtPrevAction =
rtDW . amv55hlazd ; if ( ssIsMajorTimeStep ( rtS ) ) { if ( rtB . optvc153u0
<= 1000.0 ) { rtAction = 0 ; } else if ( rtB . optvc153u0 >= 2000.0 ) {
rtAction = 1 ; } else { rtAction = 2 ; } rtDW . amv55hlazd = rtAction ; }
else { rtAction = rtDW . amv55hlazd ; } if ( rtPrevAction != rtAction ) {
switch ( rtPrevAction ) { case 0 : ssSetBlockStateForSolverChangedAtMajorStep
( rtS ) ; break ; case 1 : ssSetBlockStateForSolverChangedAtMajorStep ( rtS )
; break ; case 2 : ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; break
; } } switch ( rtAction ) { case 0 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( rtS , 0 ) != ssGetTStart ( rtS ) ) {
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } } rtB . bkjlztmjbx [ 2
] = rtB . gunypeaovn [ 0 ] ; muDoubleScalarSinCos ( rtB . pg1uquivv5 , &
m3fe2punjq_p , & ivguwgcntv ) ; rtB . mt2kbdde1u [ 0 ] = rtB . iihgtnzfrf [ 0
] * ivguwgcntv ; rtB . mt2kbdde1u [ 1 ] = rtB . joo0gvrcnf [ 0 ] * ivguwgcntv
; rtB . hlywm50421 [ 0 ] = m3fe2punjq_p * rtB . iihgtnzfrf [ 0 ] ; rtB .
hlywm50421 [ 1 ] = m3fe2punjq_p * rtB . joo0gvrcnf [ 0 ] ; rtB . bkjlztmjbx [
0 ] = rtB . mt2kbdde1u [ 0 ] - rtB . hlywm50421 [ 1 ] ; rtB . bkjlztmjbx [ 1
] = rtB . mt2kbdde1u [ 1 ] + rtB . hlywm50421 [ 0 ] ; for ( bpIndex_idx_0 = 0
; bpIndex_idx_0 < 3 ; bpIndex_idx_0 ++ ) { rtB . g2ol2zgsoe [ bpIndex_idx_0 ]
= 0.0 ; rtB . g2ol2zgsoe [ bpIndex_idx_0 ] += rtB . n2gibbklhx [
bpIndex_idx_0 ] * rtB . bkjlztmjbx [ 0 ] ; rtB . g2ol2zgsoe [ bpIndex_idx_0 ]
+= rtB . n2gibbklhx [ bpIndex_idx_0 + 3 ] * rtB . bkjlztmjbx [ 1 ] ; rtB .
g2ol2zgsoe [ bpIndex_idx_0 ] += rtB . n2gibbklhx [ bpIndex_idx_0 + 6 ] * rtB
. bkjlztmjbx [ 2 ] ; rtB . i5asy1ic4l [ bpIndex_idx_0 ] = rtB . g2ol2zgsoe [
bpIndex_idx_0 ] ; } if ( ssIsMajorTimeStep ( rtS ) ) { srUpdateBC ( rtDW .
feainkhr2c ) ; } break ; case 1 : if ( rtAction != rtPrevAction ) { if (
ssGetTaskTime ( rtS , 0 ) != ssGetTStart ( rtS ) ) {
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } } rtB . i5asy1ic4l [ 0
] = rtP . Gain_Gain_hwyillaq5v * rtB . iihgtnzfrf [ 1 ] ; rtB . i5asy1ic4l [
1 ] = rtP . Gain_Gain_hwyillaq5v * rtB . joo0gvrcnf [ 1 ] ; rtB . i5asy1ic4l
[ 2 ] = rtP . Gain_Gain_hwyillaq5v * rtB . gunypeaovn [ 1 ] ; if (
ssIsMajorTimeStep ( rtS ) ) { srUpdateBC ( rtDW . kscxtxtsbw ) ; } break ;
case 2 : if ( rtAction != rtPrevAction ) { if ( ssGetTaskTime ( rtS , 0 ) !=
ssGetTStart ( rtS ) ) { ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ;
} } muDoubleScalarSinCos ( rtB . pg1uquivv5 , & m3fe2punjq_p , & ivguwgcntv )
; rtB . iwoj22k0me [ 0 ] = rtB . iihgtnzfrf [ 0 ] * ivguwgcntv ; rtB .
iwoj22k0me [ 1 ] = rtB . joo0gvrcnf [ 0 ] * ivguwgcntv ; rtB . hwhw1vlr4q [ 0
] = m3fe2punjq_p * rtB . iihgtnzfrf [ 0 ] ; rtB . hwhw1vlr4q [ 1 ] =
m3fe2punjq_p * rtB . joo0gvrcnf [ 0 ] ; rtB . bhyqpcr3sv [ 0 ] = rtB .
iwoj22k0me [ 0 ] - rtB . hwhw1vlr4q [ 1 ] ; rtB . bhyqpcr3sv [ 1 ] = rtB .
iwoj22k0me [ 1 ] + rtB . hwhw1vlr4q [ 0 ] ; rtB . bhyqpcr3sv [ 2 ] = rtB .
gunypeaovn [ 0 ] ; for ( bpIndex_idx_0 = 0 ; bpIndex_idx_0 < 3 ;
bpIndex_idx_0 ++ ) { rtB . pfqekgkkul [ bpIndex_idx_0 ] = 0.0 ; rtB .
pfqekgkkul [ bpIndex_idx_0 ] += rtB . n2gibbklhx [ bpIndex_idx_0 ] * rtB .
bhyqpcr3sv [ 0 ] ; rtB . pfqekgkkul [ bpIndex_idx_0 ] += rtB . n2gibbklhx [
bpIndex_idx_0 + 3 ] * rtB . bhyqpcr3sv [ 1 ] ; rtB . pfqekgkkul [
bpIndex_idx_0 ] += rtB . n2gibbklhx [ bpIndex_idx_0 + 6 ] * rtB . bhyqpcr3sv
[ 2 ] ; } rtB . m0012em1dm [ 0 ] = rtB . iihgtnzfrf [ 1 ] - rtB . pfqekgkkul
[ 0 ] ; rtB . m0012em1dm [ 1 ] = rtB . joo0gvrcnf [ 1 ] - rtB . pfqekgkkul [
1 ] ; rtB . m0012em1dm [ 2 ] = rtB . gunypeaovn [ 1 ] - rtB . pfqekgkkul [ 2
] ; rtB . edfjbabvwj = rtB . optvc153u0 - rtP .
max_height_low_Value_lykhpozz3y ; rtB . ocqymszfcg [ 0 ] = rtB . m0012em1dm [
0 ] * rtB . edfjbabvwj / rtB . h5wwlzhkjq ; rtB . i5asy1ic4l [ 0 ] = rtB .
pfqekgkkul [ 0 ] + rtB . ocqymszfcg [ 0 ] ; rtB . ocqymszfcg [ 1 ] = rtB .
m0012em1dm [ 1 ] * rtB . edfjbabvwj / rtB . h5wwlzhkjq ; rtB . i5asy1ic4l [ 1
] = rtB . pfqekgkkul [ 1 ] + rtB . ocqymszfcg [ 1 ] ; rtB . ocqymszfcg [ 2 ]
= rtB . m0012em1dm [ 2 ] * rtB . edfjbabvwj / rtB . h5wwlzhkjq ; rtB .
i5asy1ic4l [ 2 ] = rtB . pfqekgkkul [ 2 ] + rtB . ocqymszfcg [ 2 ] ; if (
ssIsMajorTimeStep ( rtS ) ) { srUpdateBC ( rtDW . osdasmnnlg ) ; } break ; }
aotvmzw3cy [ 0 ] = 0.3048 * rtB . i5asy1ic4l [ 0 ] ; aotvmzw3cy [ 1 ] =
0.3048 * rtB . i5asy1ic4l [ 1 ] ; aotvmzw3cy [ 2 ] = 0.3048 * rtB .
i5asy1ic4l [ 2 ] ; rtB . jayfpbovsb = 3.280839895013123 * rtB . ks25o2ves0 [
2 ] ; if ( ssIsMajorTimeStep ( rtS ) ) { rtDW . oqzl4vaurj = rtB . jayfpbovsb
>= rtP . uftinf_UpperSat ? 1 : rtB . jayfpbovsb > rtP . uftinf_LowerSat ? 0 :
- 1 ; } rtB . etz0t5ppwo = rtDW . oqzl4vaurj == 1 ? rtP . uftinf_UpperSat :
rtDW . oqzl4vaurj == - 1 ? rtP . uftinf_LowerSat : rtB . jayfpbovsb ; rtB .
htbwrd0zad = rtP . hz0_Gain * rtB . etz0t5ppwo ; ivguwgcntv = rtB .
htbwrd0zad ; if ( ssIsMajorTimeStep ( rtS ) ) { if ( rtDW . kpnxk2wxcb != 0 )
{ ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; rtDW . kpnxk2wxcb = 0
; } } else { if ( rtB . htbwrd0zad < 0.0 ) { ivguwgcntv = 0.0 ; rtDW .
kpnxk2wxcb = 1 ; } } rtB . pwozxpkovz = muDoubleScalarLog ( ivguwgcntv ) /
rtB . kbexovbmwl ; rtB . na2v1kjbp5 [ 0 ] = rtB . pwozxpkovz * rtB .
hnfbrhdub5 [ 0 ] ; rtB . na2v1kjbp5 [ 1 ] = rtB . pwozxpkovz * rtB .
hnfbrhdub5 [ 1 ] ; rtB . na2v1kjbp5 [ 2 ] = rtB . pwozxpkovz * rtB .
hnfbrhdub5 [ 2 ] ; for ( bpIndex_idx_0 = 0 ; bpIndex_idx_0 < 3 ;
bpIndex_idx_0 ++ ) { rtB . gtph1dwlhy [ bpIndex_idx_0 ] = 0.0 ; rtB .
gtph1dwlhy [ bpIndex_idx_0 ] += rtB . n2gibbklhx [ bpIndex_idx_0 ] * rtB .
na2v1kjbp5 [ 0 ] ; rtB . gtph1dwlhy [ bpIndex_idx_0 ] += rtB . n2gibbklhx [
bpIndex_idx_0 + 3 ] * rtB . na2v1kjbp5 [ 1 ] ; rtB . gtph1dwlhy [
bpIndex_idx_0 ] += rtB . n2gibbklhx [ bpIndex_idx_0 + 6 ] * rtB . na2v1kjbp5
[ 2 ] ; rtB . cis0kg11y4 [ bpIndex_idx_0 ] = ( rtB . gtph1dwlhy [
bpIndex_idx_0 ] + aotvmzw3cy [ bpIndex_idx_0 ] ) + rtB . gtav0xroqm [
bpIndex_idx_0 ] ; rtB . nzoyizvn0g [ bpIndex_idx_0 ] = rtX . cjakaafmng [
bpIndex_idx_0 ] ; } muDoubleScalarSinCos ( rtB . nliw1cuyp4 [ 0 ] , &
aotvmzw3cy [ 0 ] , & huam1midmw [ 0 ] ) ; muDoubleScalarSinCos ( rtB .
nliw1cuyp4 [ 1 ] , & aotvmzw3cy [ 1 ] , & huam1midmw [ 1 ] ) ;
muDoubleScalarSinCos ( rtB . nliw1cuyp4 [ 2 ] , & aotvmzw3cy [ 2 ] , &
huam1midmw [ 2 ] ) ; rtB . pnx4iii03b [ 0 ] = ( rtB . nzoyizvn0g [ 1 ] *
aotvmzw3cy [ 0 ] + rtB . nzoyizvn0g [ 2 ] * huam1midmw [ 0 ] ) * ( aotvmzw3cy
[ 1 ] / huam1midmw [ 1 ] ) + rtB . nzoyizvn0g [ 0 ] ; rtB . pnx4iii03b [ 1 ]
= rtB . nzoyizvn0g [ 1 ] * huam1midmw [ 0 ] - rtB . nzoyizvn0g [ 2 ] *
aotvmzw3cy [ 0 ] ; for ( bpIndex_idx_0 = 0 ; bpIndex_idx_0 < 3 ;
bpIndex_idx_0 ++ ) { tmp [ bpIndex_idx_0 ] = rtB . nzoyizvn0g [ bpIndex_idx_0
] ; tmp [ bpIndex_idx_0 + 3 ] = aotvmzw3cy [ bpIndex_idx_0 ] ; tmp [
bpIndex_idx_0 + 6 ] = huam1midmw [ bpIndex_idx_0 ] ; tmp_p [ bpIndex_idx_0 ]
= rtB . nzoyizvn0g [ bpIndex_idx_0 ] ; tmp_p [ bpIndex_idx_0 + 3 ] =
aotvmzw3cy [ bpIndex_idx_0 ] ; tmp_p [ bpIndex_idx_0 + 6 ] = huam1midmw [
bpIndex_idx_0 ] ; tmp_e [ bpIndex_idx_0 ] = rtB . nzoyizvn0g [ bpIndex_idx_0
] ; tmp_e [ bpIndex_idx_0 + 3 ] = aotvmzw3cy [ bpIndex_idx_0 ] ; tmp_e [
bpIndex_idx_0 + 6 ] = huam1midmw [ bpIndex_idx_0 ] ; tmp_i [ bpIndex_idx_0 ]
= rtB . nzoyizvn0g [ bpIndex_idx_0 ] ; tmp_i [ bpIndex_idx_0 + 3 ] =
aotvmzw3cy [ bpIndex_idx_0 ] ; tmp_i [ bpIndex_idx_0 + 6 ] = huam1midmw [
bpIndex_idx_0 ] ; tmp_m [ bpIndex_idx_0 ] = rtB . nzoyizvn0g [ bpIndex_idx_0
] ; tmp_m [ bpIndex_idx_0 + 3 ] = aotvmzw3cy [ bpIndex_idx_0 ] ; tmp_m [
bpIndex_idx_0 + 6 ] = huam1midmw [ bpIndex_idx_0 ] ; rtB . jjyzm5cerc [
bpIndex_idx_0 ] = 0.0 ; rtB . j55tg2sijl [ bpIndex_idx_0 ] = 0.0 ; rtB .
e4f4cr5zbc [ bpIndex_idx_0 ] = 0.0 ; rtB . jjyzm5cerc [ bpIndex_idx_0 ] +=
rtB . mrsrezbuqk [ bpIndex_idx_0 ] * rtB . nzoyizvn0g [ 0 ] ; rtB .
j55tg2sijl [ bpIndex_idx_0 ] += rtB . bwcottfiut [ bpIndex_idx_0 ] * rtB .
nzoyizvn0g [ 0 ] ; rtB . e4f4cr5zbc [ bpIndex_idx_0 ] += rtB . dsk4lj4maj [
bpIndex_idx_0 ] * rtB . islqk3d2pc [ 0 ] ; rtB . jjyzm5cerc [ bpIndex_idx_0 ]
+= rtB . mrsrezbuqk [ bpIndex_idx_0 + 3 ] * rtB . nzoyizvn0g [ 1 ] ; rtB .
j55tg2sijl [ bpIndex_idx_0 ] += rtB . bwcottfiut [ bpIndex_idx_0 + 3 ] * rtB
. nzoyizvn0g [ 1 ] ; rtB . e4f4cr5zbc [ bpIndex_idx_0 ] += rtB . dsk4lj4maj [
bpIndex_idx_0 + 3 ] * rtB . islqk3d2pc [ 1 ] ; rtB . jjyzm5cerc [
bpIndex_idx_0 ] += rtB . mrsrezbuqk [ bpIndex_idx_0 + 6 ] * rtB . nzoyizvn0g
[ 2 ] ; rtB . j55tg2sijl [ bpIndex_idx_0 ] += rtB . bwcottfiut [
bpIndex_idx_0 + 6 ] * rtB . nzoyizvn0g [ 2 ] ; rtB . e4f4cr5zbc [
bpIndex_idx_0 ] += rtB . dsk4lj4maj [ bpIndex_idx_0 + 6 ] * rtB . islqk3d2pc
[ 2 ] ; aotvmzw3cy [ bpIndex_idx_0 ] = 3.280839895013123 * rtB . e4f4cr5zbc [
bpIndex_idx_0 ] ; } rtB . pnx4iii03b [ 2 ] = ( tmp [ 1 ] * tmp_p [ 3 ] +
tmp_e [ 2 ] * tmp_i [ 6 ] ) / tmp_m [ 7 ] ; rtB . k4efj0wbom = rtB .
nzoyizvn0g [ 0 ] * rtB . jjyzm5cerc [ 1 ] ; rtB . abq35lnui2 = rtB .
nzoyizvn0g [ 1 ] * rtB . jjyzm5cerc [ 2 ] ; rtB . pwkjv4lxgw = rtB .
nzoyizvn0g [ 2 ] * rtB . jjyzm5cerc [ 0 ] ; rtB . fhjxy5zb5a = rtB .
nzoyizvn0g [ 0 ] * rtB . jjyzm5cerc [ 2 ] ; rtB . aami4huvyy = rtB .
nzoyizvn0g [ 1 ] * rtB . jjyzm5cerc [ 0 ] ; rtB . bdaejykwvz = rtB .
nzoyizvn0g [ 2 ] * rtB . jjyzm5cerc [ 1 ] ; rtB . o54r3adnq1 [ 0 ] = rtB .
abq35lnui2 - rtB . bdaejykwvz ; rtB . o54r3adnq1 [ 1 ] = rtB . pwkjv4lxgw -
rtB . fhjxy5zb5a ; rtB . o54r3adnq1 [ 2 ] = rtB . k4efj0wbom - rtB .
aami4huvyy ; muDoubleScalarSinCos ( muDoubleScalarAtan2 ( aotvmzw3cy [ 2 ] ,
aotvmzw3cy [ 0 ] ) , & m3fe2punjq_p , & ivguwgcntv ) ; rtB . a5q0gsfmw5 [ 0 ]
= ivguwgcntv ; rtB . a5q0gsfmw5 [ 1 ] = rtP . Constant1_Value_e4n53dlcvq ;
rtB . a5q0gsfmw5 [ 2 ] = - m3fe2punjq_p ; rtB . a5q0gsfmw5 [ 3 ] = rtP .
Constant_Value_m5ji3jk5ts ; rtB . a5q0gsfmw5 [ 4 ] = rtP .
Constant2_Value_pnmq1xmzoy ; rtB . a5q0gsfmw5 [ 5 ] = rtP . Constant4_Value ;
rtB . a5q0gsfmw5 [ 6 ] = m3fe2punjq_p ; rtB . a5q0gsfmw5 [ 7 ] = rtP .
Constant3_Value_py4vyr01be ; rtB . a5q0gsfmw5 [ 8 ] = ivguwgcntv ; for (
bpIndex_idx_0 = 0 ; bpIndex_idx_0 < 3 ; bpIndex_idx_0 ++ ) { rtB . jymybd53fk
[ 3 * bpIndex_idx_0 ] = rtB . a5q0gsfmw5 [ bpIndex_idx_0 ] ; rtB . jymybd53fk
[ 1 + 3 * bpIndex_idx_0 ] = rtB . a5q0gsfmw5 [ bpIndex_idx_0 + 3 ] ; rtB .
jymybd53fk [ 2 + 3 * bpIndex_idx_0 ] = rtB . a5q0gsfmw5 [ bpIndex_idx_0 + 6 ]
; rtB . fwuesmfvmw [ bpIndex_idx_0 ] = rtB . islqk3d2pc [ bpIndex_idx_0 ] -
rtB . cis0kg11y4 [ bpIndex_idx_0 ] ; } rtB . ee4hwukkci = rtB . fwuesmfvmw [
0 ] * rtB . fwuesmfvmw [ 0 ] ; rtB . llhvjlhy3a = rtB . fwuesmfvmw [ 1 ] *
rtB . fwuesmfvmw [ 1 ] ; rtB . no1ukhz2or = rtB . fwuesmfvmw [ 2 ] * rtB .
fwuesmfvmw [ 2 ] ; rtB . lw3rqy0i2p = ( rtB . ee4hwukkci + rtB . llhvjlhy3a )
+ rtB . no1ukhz2or ; rtB . gzwn4wvhu5 = rtB . lw3rqy0i2p * rtB . iwsvf4t0jp ;
rtB . ltux4bsueq = rtP . u2rhoV2_Gain * rtB . gzwn4wvhu5 ; m3fe2punjq_p =
0.020885434233150126 * rtB . ltux4bsueq ; rtB . lcss4j1rsb = rtP .
AerodynamicForcesandMoments_S * m3fe2punjq_p ; rtB . burumew3sb =
plook_s32dd_bincp ( 57.295779513082323 * muDoubleScalarAtan2 ( rtB .
fwuesmfvmw [ 2 ] , rtB . fwuesmfvmw [ 0 ] ) , rtP . alpha_BreakpointsData ,
9U , & rtB . oovkaz423b , & rtDW . m0wkbsdvjm ) ; rtB . cdvlb44lh3 = rtB .
fwuesmfvmw [ 0 ] * rtB . fwuesmfvmw [ 0 ] ; rtB . ewv4vlunrf = rtB .
fwuesmfvmw [ 1 ] * rtB . fwuesmfvmw [ 1 ] ; rtB . o402scsdlq = rtB .
fwuesmfvmw [ 2 ] * rtB . fwuesmfvmw [ 2 ] ; rtB . dsfnt4ckk0 = ( rtB .
cdvlb44lh3 + rtB . ewv4vlunrf ) + rtB . o402scsdlq ; if ( ssIsMajorTimeStep (
rtS ) ) { if ( rtDW . cnovvjoyyp != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; rtDW . cnovvjoyyp = 0 ;
} ivguwgcntv = muDoubleScalarSqrt ( rtB . dsfnt4ckk0 ) ; } else { if ( rtB .
dsfnt4ckk0 < 0.0 ) { ivguwgcntv = - muDoubleScalarSqrt ( muDoubleScalarAbs (
rtB . dsfnt4ckk0 ) ) ; } else { ivguwgcntv = muDoubleScalarSqrt ( rtB .
dsfnt4ckk0 ) ; } if ( rtB . dsfnt4ckk0 < 0.0 ) { rtDW . cnovvjoyyp = 1 ; } }
rtB . deyrabdk0p = ivguwgcntv / lvewqzupwi ; rtB . dpmiotlnvk =
plook_s32dd_bincp ( rtB . deyrabdk0p , rtP . Mach_BreakpointsData , 3U , &
rtB . ew4bp2hsh4 , & rtDW . pfswjzddny ) ; rtB . kcp5vlmrhn =
plook_s32dd_bincp ( 3.280839895013123 * rtB . ks25o2ves0 [ 2 ] , rtP .
altitude_BreakpointsData , 7U , & rtB . fghbljyvca , & rtDW . bweuyeryhh ) ;
bpIndex_idx_0 = rtB . burumew3sb ; bpIndex_idx_1 = rtB . dpmiotlnvk ;
bpIndex_idx_2 = rtB . kcp5vlmrhn ; if ( ( ( uint32_T ) rtB . burumew3sb == 8U
) && ( rtB . oovkaz423b >= 1.0 ) ) { bpIndex_idx_0 = rtB . burumew3sb + 1 ; }
if ( ( ( uint32_T ) rtB . dpmiotlnvk == 2U ) && ( rtB . ew4bp2hsh4 >= 1.0 ) )
{ bpIndex_idx_1 = rtB . dpmiotlnvk + 1 ; } if ( ( ( uint32_T ) rtB .
kcp5vlmrhn == 6U ) && ( rtB . fghbljyvca >= 1.0 ) ) { bpIndex_idx_2 = rtB .
kcp5vlmrhn + 1 ; } rtB . n0yew4kwsy = rtP . CD_Table [ ( ( uint32_T ) (
bpIndex_idx_1 * 10 ) + bpIndex_idx_0 ) + bpIndex_idx_2 * 40 ] ; bpIndex_idx_0
= rtB . burumew3sb ; bpIndex_idx_1 = rtB . dpmiotlnvk ; bpIndex_idx_2 = rtB .
kcp5vlmrhn ; if ( ( ( uint32_T ) rtB . burumew3sb == 8U ) && ( rtB .
oovkaz423b >= 1.0 ) ) { bpIndex_idx_0 = rtB . burumew3sb + 1 ; } if ( ( (
uint32_T ) rtB . dpmiotlnvk == 2U ) && ( rtB . ew4bp2hsh4 >= 1.0 ) ) {
bpIndex_idx_1 = rtB . dpmiotlnvk + 1 ; } if ( ( ( uint32_T ) rtB . kcp5vlmrhn
== 6U ) && ( rtB . fghbljyvca >= 1.0 ) ) { bpIndex_idx_2 = rtB . kcp5vlmrhn +
1 ; } rtB . l1czztlzln = rtP . CYb_Table [ ( ( uint32_T ) ( bpIndex_idx_1 *
10 ) + bpIndex_idx_0 ) + bpIndex_idx_2 * 40 ] ; rtB . kn3vx2wdwp = rtB .
fwuesmfvmw [ 0 ] * rtB . fwuesmfvmw [ 0 ] ; rtB . iv0iqohpcq = rtB .
fwuesmfvmw [ 1 ] * rtB . fwuesmfvmw [ 1 ] ; rtB . nqhs2mtakg = rtB .
fwuesmfvmw [ 2 ] * rtB . fwuesmfvmw [ 2 ] ; rtB . mddzbq4nmv = ( rtB .
kn3vx2wdwp + rtB . iv0iqohpcq ) + rtB . nqhs2mtakg ; if ( ssIsMajorTimeStep (
rtS ) ) { if ( rtDW . pgykvwqmc3 != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; rtDW . pgykvwqmc3 = 0 ;
} lvewqzupwi = muDoubleScalarSqrt ( rtB . mddzbq4nmv ) ; } else { if ( rtB .
mddzbq4nmv < 0.0 ) { lvewqzupwi = - muDoubleScalarSqrt ( muDoubleScalarAbs (
rtB . mddzbq4nmv ) ) ; } else { lvewqzupwi = muDoubleScalarSqrt ( rtB .
mddzbq4nmv ) ; } if ( rtB . mddzbq4nmv < 0.0 ) { rtDW . pgykvwqmc3 = 1 ; } }
rtB . c5nk0hb2bd = rtB . fwuesmfvmw [ 1 ] / lvewqzupwi ; if ( rtB .
c5nk0hb2bd > 1.0 ) { d1bmmtsdzs = 1.0 ; } else if ( rtB . c5nk0hb2bd < - 1.0
) { d1bmmtsdzs = - 1.0 ; } else { d1bmmtsdzs = rtB . c5nk0hb2bd ; }
lvewqzupwi = 57.295779513082323 * muDoubleScalarAsin ( d1bmmtsdzs ) ; rtB .
dkjk3aymc3 = rtB . l1czztlzln * lvewqzupwi ; bpIndex_idx_0 = rtB . burumew3sb
; bpIndex_idx_1 = rtB . dpmiotlnvk ; bpIndex_idx_2 = rtB . kcp5vlmrhn ; if (
( ( uint32_T ) rtB . burumew3sb == 8U ) && ( rtB . oovkaz423b >= 1.0 ) ) {
bpIndex_idx_0 = rtB . burumew3sb + 1 ; } if ( ( ( uint32_T ) rtB . dpmiotlnvk
== 2U ) && ( rtB . ew4bp2hsh4 >= 1.0 ) ) { bpIndex_idx_1 = rtB . dpmiotlnvk +
1 ; } if ( ( ( uint32_T ) rtB . kcp5vlmrhn == 6U ) && ( rtB . fghbljyvca >=
1.0 ) ) { bpIndex_idx_2 = rtB . kcp5vlmrhn + 1 ; } rtB . k4vi5txoqv = rtP .
CL_Table [ ( ( uint32_T ) ( bpIndex_idx_1 * 10 ) + bpIndex_idx_0 ) +
bpIndex_idx_2 * 40 ] ; rtB . jeow23fizp [ 0 ] = rtP . coefAdjust_Gain [ 0 ] *
rtB . n0yew4kwsy ; rtB . jeow23fizp [ 1 ] = rtP . coefAdjust_Gain [ 1 ] * rtB
. dkjk3aymc3 ; rtB . jeow23fizp [ 2 ] = rtP . coefAdjust_Gain [ 2 ] * rtB .
k4vi5txoqv ; rtB . g4ixw2ju0a [ 0 ] = rtB . lcss4j1rsb * rtB . jeow23fizp [ 0
] ; rtB . g4ixw2ju0a [ 1 ] = rtB . lcss4j1rsb * rtB . jeow23fizp [ 1 ] ; rtB
. g4ixw2ju0a [ 2 ] = rtB . lcss4j1rsb * rtB . jeow23fizp [ 2 ] ;
muDoubleScalarSinCos ( muDoubleScalarAtan2 ( aotvmzw3cy [ 2 ] , aotvmzw3cy [
0 ] ) , & ivguwgcntv , & d1bmmtsdzs ) ; rtB . clsso41xlk [ 0 ] = d1bmmtsdzs ;
rtB . clsso41xlk [ 1 ] = rtP . Constant1_Value_bllnswxjjm ; rtB . clsso41xlk
[ 2 ] = - ivguwgcntv ; rtB . clsso41xlk [ 3 ] = rtP .
Constant_Value_gvjlparkjc ; rtB . clsso41xlk [ 4 ] = rtP .
Constant2_Value_ewaxby0wwz ; rtB . clsso41xlk [ 5 ] = rtP .
Constant4_Value_jw4i4dtkq1 ; rtB . clsso41xlk [ 6 ] = ivguwgcntv ; rtB .
clsso41xlk [ 7 ] = rtP . Constant3_Value_aowcwxcrv4 ; rtB . clsso41xlk [ 8 ]
= d1bmmtsdzs ; for ( bpIndex_idx_0 = 0 ; bpIndex_idx_0 < 3 ; bpIndex_idx_0 ++
) { rtB . m43khr12tv [ bpIndex_idx_0 ] = 0.0 ; rtB . m43khr12tv [
bpIndex_idx_0 ] += rtB . clsso41xlk [ bpIndex_idx_0 ] * rtB . diwxdnf4dg [ 0
] ; rtB . m43khr12tv [ bpIndex_idx_0 ] += rtB . clsso41xlk [ bpIndex_idx_0 +
3 ] * rtB . diwxdnf4dg [ 1 ] ; rtB . m43khr12tv [ bpIndex_idx_0 ] += rtB .
clsso41xlk [ bpIndex_idx_0 + 6 ] * rtB . diwxdnf4dg [ 2 ] ; } rtB .
oq23oeketq = rtB . g4ixw2ju0a [ 1 ] * rtB . m43khr12tv [ 2 ] ; rtB .
ambckm20k4 = rtB . g4ixw2ju0a [ 2 ] * rtB . m43khr12tv [ 0 ] ; rtB .
if2tkmjk5a = rtB . g4ixw2ju0a [ 0 ] * rtB . m43khr12tv [ 1 ] ; rtB .
jhnqdtipvy = rtB . g4ixw2ju0a [ 2 ] * rtB . m43khr12tv [ 1 ] ; rtB .
mmnv4q2o2x = rtB . g4ixw2ju0a [ 0 ] * rtB . m43khr12tv [ 2 ] ; rtB .
dr2gm5cuey = rtB . g4ixw2ju0a [ 1 ] * rtB . m43khr12tv [ 0 ] ; rtB .
fhapciging [ 0 ] = rtB . oq23oeketq - rtB . jhnqdtipvy ; rtB . fhapciging [ 1
] = rtB . ambckm20k4 - rtB . mmnv4q2o2x ; rtB . fhapciging [ 2 ] = rtB .
if2tkmjk5a - rtB . dr2gm5cuey ; bpIndex_idx_0 = rtB . burumew3sb ;
bpIndex_idx_1 = rtB . dpmiotlnvk ; bpIndex_idx_2 = rtB . kcp5vlmrhn ; if ( (
( uint32_T ) rtB . burumew3sb == 8U ) && ( rtB . oovkaz423b >= 1.0 ) ) {
bpIndex_idx_0 = rtB . burumew3sb + 1 ; } if ( ( ( uint32_T ) rtB . dpmiotlnvk
== 2U ) && ( rtB . ew4bp2hsh4 >= 1.0 ) ) { bpIndex_idx_1 = rtB . dpmiotlnvk +
1 ; } if ( ( ( uint32_T ) rtB . kcp5vlmrhn == 6U ) && ( rtB . fghbljyvca >=
1.0 ) ) { bpIndex_idx_2 = rtB . kcp5vlmrhn + 1 ; } rtB . b4ff4mfmin = rtP .
Clb_Table [ ( ( uint32_T ) ( bpIndex_idx_1 * 10 ) + bpIndex_idx_0 ) +
bpIndex_idx_2 * 40 ] ; rtB . huplh2ovz1 = rtB . b4ff4mfmin * lvewqzupwi ;
bpIndex_idx_0 = rtB . burumew3sb ; bpIndex_idx_1 = rtB . dpmiotlnvk ;
bpIndex_idx_2 = rtB . kcp5vlmrhn ; if ( ( ( uint32_T ) rtB . burumew3sb == 8U
) && ( rtB . oovkaz423b >= 1.0 ) ) { bpIndex_idx_0 = rtB . burumew3sb + 1 ; }
if ( ( ( uint32_T ) rtB . dpmiotlnvk == 2U ) && ( rtB . ew4bp2hsh4 >= 1.0 ) )
{ bpIndex_idx_1 = rtB . dpmiotlnvk + 1 ; } if ( ( ( uint32_T ) rtB .
kcp5vlmrhn == 6U ) && ( rtB . fghbljyvca >= 1.0 ) ) { bpIndex_idx_2 = rtB .
kcp5vlmrhn + 1 ; } rtB . dtay24vczs = rtP . Cm_Table [ ( ( uint32_T ) (
bpIndex_idx_1 * 10 ) + bpIndex_idx_0 ) + bpIndex_idx_2 * 40 ] ; bpIndex_idx_0
= rtB . burumew3sb ; bpIndex_idx_1 = rtB . dpmiotlnvk ; bpIndex_idx_2 = rtB .
kcp5vlmrhn ; if ( ( ( uint32_T ) rtB . burumew3sb == 8U ) && ( rtB .
oovkaz423b >= 1.0 ) ) { bpIndex_idx_0 = rtB . burumew3sb + 1 ; } if ( ( (
uint32_T ) rtB . dpmiotlnvk == 2U ) && ( rtB . ew4bp2hsh4 >= 1.0 ) ) {
bpIndex_idx_1 = rtB . dpmiotlnvk + 1 ; } if ( ( ( uint32_T ) rtB . kcp5vlmrhn
== 6U ) && ( rtB . fghbljyvca >= 1.0 ) ) { bpIndex_idx_2 = rtB . kcp5vlmrhn +
1 ; } rtB . flfgzaiek3 = rtP . Cnb_Table [ ( ( uint32_T ) ( bpIndex_idx_1 *
10 ) + bpIndex_idx_0 ) + bpIndex_idx_2 * 40 ] ; rtB . p0xy05kpqr = rtB .
flfgzaiek3 * lvewqzupwi ; rtB . kuokdfsr0b [ 0 ] = rtP .
AerodynamicForcesandMoments_b * rtB . lcss4j1rsb ; rtB . kuokdfsr0b [ 1 ] =
rtP . AerodynamicForcesandMoments_cbar * rtB . lcss4j1rsb ; rtB . kuokdfsr0b
[ 2 ] = rtP . AerodynamicForcesandMoments_b * rtB . lcss4j1rsb ; rtB .
muyb1go0zp [ 0 ] = rtB . huplh2ovz1 * rtB . kuokdfsr0b [ 0 ] ; rtB .
muyb1go0zp [ 1 ] = rtB . dtay24vczs * rtB . kuokdfsr0b [ 1 ] ; rtB .
muyb1go0zp [ 2 ] = rtB . p0xy05kpqr * rtB . kuokdfsr0b [ 2 ] ; rtB .
haarcsgs3r [ 0 ] = rtB . fhapciging [ 0 ] + rtB . muyb1go0zp [ 0 ] ; rtB .
haarcsgs3r [ 1 ] = rtB . fhapciging [ 1 ] + rtB . muyb1go0zp [ 1 ] ; rtB .
haarcsgs3r [ 2 ] = rtB . fhapciging [ 2 ] + rtB . muyb1go0zp [ 2 ] ; for (
bpIndex_idx_0 = 0 ; bpIndex_idx_0 < 3 ; bpIndex_idx_0 ++ ) { rtB . gb1h1tviap
[ bpIndex_idx_0 ] = 0.0 ; rtB . gb1h1tviap [ bpIndex_idx_0 ] += rtB .
jymybd53fk [ bpIndex_idx_0 ] * rtB . haarcsgs3r [ 0 ] ; rtB . gb1h1tviap [
bpIndex_idx_0 ] += rtB . jymybd53fk [ bpIndex_idx_0 + 3 ] * rtB . haarcsgs3r
[ 1 ] ; rtB . gb1h1tviap [ bpIndex_idx_0 ] += rtB . jymybd53fk [
bpIndex_idx_0 + 6 ] * rtB . haarcsgs3r [ 2 ] ; } muDoubleScalarSinCos (
muDoubleScalarAtan2 ( aotvmzw3cy [ 2 ] , aotvmzw3cy [ 0 ] ) , & lvewqzupwi ,
& ivguwgcntv ) ; rtB . bltg1ofzuh [ 0 ] = ivguwgcntv ; rtB . bltg1ofzuh [ 1 ]
= rtP . Constant1_Value_dkxf1g33uf ; rtB . bltg1ofzuh [ 2 ] = - lvewqzupwi ;
rtB . bltg1ofzuh [ 3 ] = rtP . Constant_Value_n2pgnoma5y ; rtB . bltg1ofzuh [
4 ] = rtP . Constant2_Value_a1organdvp ; rtB . bltg1ofzuh [ 5 ] = rtP .
Constant4_Value_mowtqh2zd2 ; rtB . bltg1ofzuh [ 6 ] = lvewqzupwi ; rtB .
bltg1ofzuh [ 7 ] = rtP . Constant3_Value_n2x4c42jkt ; rtB . bltg1ofzuh [ 8 ]
= ivguwgcntv ; for ( bpIndex_idx_0 = 0 ; bpIndex_idx_0 < 3 ; bpIndex_idx_0 ++
) { rtB . mddt1rvp3v [ 3 * bpIndex_idx_0 ] = rtB . bltg1ofzuh [ bpIndex_idx_0
] ; rtB . mddt1rvp3v [ 1 + 3 * bpIndex_idx_0 ] = rtB . bltg1ofzuh [
bpIndex_idx_0 + 3 ] ; rtB . mddt1rvp3v [ 2 + 3 * bpIndex_idx_0 ] = rtB .
bltg1ofzuh [ bpIndex_idx_0 + 6 ] ; } rtB . mwuv02g011 = rtP .
AerodynamicForcesandMoments_S_irg2e3bjgp * m3fe2punjq_p ; bpIndex_idx_0 = rtB
. burumew3sb ; bpIndex_idx_1 = rtB . dpmiotlnvk ; bpIndex_idx_2 = rtB .
kcp5vlmrhn ; if ( ( ( uint32_T ) rtB . burumew3sb == 8U ) && ( rtB .
oovkaz423b >= 1.0 ) ) { bpIndex_idx_0 = rtB . burumew3sb + 1 ; } if ( ( (
uint32_T ) rtB . dpmiotlnvk == 2U ) && ( rtB . ew4bp2hsh4 >= 1.0 ) ) {
bpIndex_idx_1 = rtB . dpmiotlnvk + 1 ; } if ( ( ( uint32_T ) rtB . kcp5vlmrhn
== 6U ) && ( rtB . fghbljyvca >= 1.0 ) ) { bpIndex_idx_2 = rtB . kcp5vlmrhn +
1 ; } rtB . d3um45fosu = rtP . CYp_Table [ ( ( uint32_T ) ( bpIndex_idx_1 *
10 ) + bpIndex_idx_0 ) + bpIndex_idx_2 * 40 ] ; lvewqzupwi =
muDoubleScalarAtan2 ( aotvmzw3cy [ 2 ] , aotvmzw3cy [ 0 ] ) ; rtB .
nw0lnpybdj [ 0 ] = lvewqzupwi ; rtB . nw0lnpybdj [ 1 ] = rtP .
u_Value_fiovphx5x3 ; muDoubleScalarSinCos ( rtB . nw0lnpybdj [ 0 ] , &
ivguwgcntv , & ebyjfs5k0n_idx_0 ) ; muDoubleScalarSinCos ( rtB . nw0lnpybdj [
1 ] , & efn34wlu0x_idx_1 , & ebyjfs5k0n_idx_1 ) ; rtB . ewoylkmqxc [ 0 ] =
ebyjfs5k0n_idx_0 * ebyjfs5k0n_idx_1 ; rtB . fy3whyspik = efn34wlu0x_idx_1 *
ebyjfs5k0n_idx_0 ; rtB . ewoylkmqxc [ 1 ] = - rtB . fy3whyspik ; rtB .
ewoylkmqxc [ 2 ] = - ivguwgcntv ; rtB . ewoylkmqxc [ 3 ] = efn34wlu0x_idx_1 ;
rtB . ewoylkmqxc [ 4 ] = ebyjfs5k0n_idx_1 ; rtB . ewoylkmqxc [ 5 ] = rtP .
Constant_Value_lnzqsdhb20 ; rtB . ewoylkmqxc [ 6 ] = ivguwgcntv *
ebyjfs5k0n_idx_1 ; rtB . nveqijgo2a = ivguwgcntv * efn34wlu0x_idx_1 ; rtB .
ewoylkmqxc [ 7 ] = - rtB . nveqijgo2a ; rtB . ewoylkmqxc [ 8 ] =
ebyjfs5k0n_idx_0 ; muDoubleScalarSinCos ( lvewqzupwi , & m3fe2punjq_p , &
ivguwgcntv ) ; rtB . dhy5sl1c4z = rtP . u_Value_aardduo22y * m3fe2punjq_p ;
rtB . kp24wjtakv = rtP . u_Value_aardduo22y * ivguwgcntv ; rtB . hmgj5nsbpj [
0 ] = 57.295779513082323 * rtB . nzoyizvn0g [ 0 ] * 0.017453292519943295 + -
rtB . dhy5sl1c4z ; rtB . hmgj5nsbpj [ 1 ] = 57.295779513082323 * rtB .
nzoyizvn0g [ 1 ] * 0.017453292519943295 + rtB . h1rmkjrkmq ; rtB . hmgj5nsbpj
[ 2 ] = 57.295779513082323 * rtB . nzoyizvn0g [ 2 ] * 0.017453292519943295 +
rtB . kp24wjtakv ; for ( bpIndex_idx_0 = 0 ; bpIndex_idx_0 < 3 ;
bpIndex_idx_0 ++ ) { rtB . poq3sq0itr [ bpIndex_idx_0 ] = 0.0 ; rtB .
poq3sq0itr [ bpIndex_idx_0 ] += rtB . ewoylkmqxc [ bpIndex_idx_0 ] * rtB .
hmgj5nsbpj [ 0 ] ; rtB . poq3sq0itr [ bpIndex_idx_0 ] += rtB . ewoylkmqxc [
bpIndex_idx_0 + 3 ] * rtB . hmgj5nsbpj [ 1 ] ; rtB . poq3sq0itr [
bpIndex_idx_0 ] += rtB . ewoylkmqxc [ bpIndex_idx_0 + 6 ] * rtB . hmgj5nsbpj
[ 2 ] ; huam1midmw [ bpIndex_idx_0 ] = 57.295779513082323 * rtB . poq3sq0itr
[ bpIndex_idx_0 ] ; } rtB . fui5djlzoo = rtB . d3um45fosu * huam1midmw [ 0 ]
; bpIndex_idx_0 = rtB . burumew3sb ; bpIndex_idx_1 = rtB . dpmiotlnvk ;
bpIndex_idx_2 = rtB . kcp5vlmrhn ; if ( ( ( uint32_T ) rtB . burumew3sb == 8U
) && ( rtB . oovkaz423b >= 1.0 ) ) { bpIndex_idx_0 = rtB . burumew3sb + 1 ; }
if ( ( ( uint32_T ) rtB . dpmiotlnvk == 2U ) && ( rtB . ew4bp2hsh4 >= 1.0 ) )
{ bpIndex_idx_1 = rtB . dpmiotlnvk + 1 ; } if ( ( ( uint32_T ) rtB .
kcp5vlmrhn == 6U ) && ( rtB . fghbljyvca >= 1.0 ) ) { bpIndex_idx_2 = rtB .
kcp5vlmrhn + 1 ; } rtB . kkxd3tikbn = rtP . CLad_Table [ ( ( uint32_T ) (
bpIndex_idx_1 * 10 ) + bpIndex_idx_0 ) + bpIndex_idx_2 * 40 ] ; rtB .
hmi4l5cfx0 = rtB . kkxd3tikbn * rtB . cdrl4nzwfz ; bpIndex_idx_0 = rtB .
burumew3sb ; bpIndex_idx_1 = rtB . dpmiotlnvk ; bpIndex_idx_2 = rtB .
kcp5vlmrhn ; if ( ( ( uint32_T ) rtB . burumew3sb == 8U ) && ( rtB .
oovkaz423b >= 1.0 ) ) { bpIndex_idx_0 = rtB . burumew3sb + 1 ; } if ( ( (
uint32_T ) rtB . dpmiotlnvk == 2U ) && ( rtB . ew4bp2hsh4 >= 1.0 ) ) {
bpIndex_idx_1 = rtB . dpmiotlnvk + 1 ; } if ( ( ( uint32_T ) rtB . kcp5vlmrhn
== 6U ) && ( rtB . fghbljyvca >= 1.0 ) ) { bpIndex_idx_2 = rtB . kcp5vlmrhn +
1 ; } rtB . dtsa0qdpmd = rtP . CLq_Table [ ( ( uint32_T ) ( bpIndex_idx_1 *
10 ) + bpIndex_idx_0 ) + bpIndex_idx_2 * 40 ] ; rtB . n1pgu24wwz = rtB .
dtsa0qdpmd * huam1midmw [ 1 ] ; rtB . adbita3g4i = rtB . hmi4l5cfx0 + rtB .
n1pgu24wwz ; bpIndex_idx_0 = rtB . burumew3sb ; bpIndex_idx_1 = rtB .
dpmiotlnvk ; bpIndex_idx_2 = rtB . kcp5vlmrhn ; if ( ( ( uint32_T ) rtB .
burumew3sb == 8U ) && ( rtB . oovkaz423b >= 1.0 ) ) { bpIndex_idx_0 = rtB .
burumew3sb + 1 ; } if ( ( ( uint32_T ) rtB . dpmiotlnvk == 2U ) && ( rtB .
ew4bp2hsh4 >= 1.0 ) ) { bpIndex_idx_1 = rtB . dpmiotlnvk + 1 ; } if ( ( (
uint32_T ) rtB . kcp5vlmrhn == 6U ) && ( rtB . fghbljyvca >= 1.0 ) ) {
bpIndex_idx_2 = rtB . kcp5vlmrhn + 1 ; } rtB . gb0mdchddg = rtP . Clp_Table [
( ( uint32_T ) ( bpIndex_idx_1 * 10 ) + bpIndex_idx_0 ) + bpIndex_idx_2 * 40
] ; bpIndex_idx_0 = rtB . burumew3sb ; bpIndex_idx_1 = rtB . dpmiotlnvk ;
bpIndex_idx_2 = rtB . kcp5vlmrhn ; if ( ( ( uint32_T ) rtB . burumew3sb == 8U
) && ( rtB . oovkaz423b >= 1.0 ) ) { bpIndex_idx_0 = rtB . burumew3sb + 1 ; }
if ( ( ( uint32_T ) rtB . dpmiotlnvk == 2U ) && ( rtB . ew4bp2hsh4 >= 1.0 ) )
{ bpIndex_idx_1 = rtB . dpmiotlnvk + 1 ; } if ( ( ( uint32_T ) rtB .
kcp5vlmrhn == 6U ) && ( rtB . fghbljyvca >= 1.0 ) ) { bpIndex_idx_2 = rtB .
kcp5vlmrhn + 1 ; } rtB . gspj4vw5g2 = rtP . Clr_Table [ ( ( uint32_T ) (
bpIndex_idx_1 * 10 ) + bpIndex_idx_0 ) + bpIndex_idx_2 * 40 ] ; rtB .
i12dfhokz1 [ 0 ] = rtB . gb0mdchddg * huam1midmw [ 0 ] ; rtB . i12dfhokz1 [ 1
] = rtB . gspj4vw5g2 * huam1midmw [ 2 ] ; rtB . aokxroo1bz = rtB . i12dfhokz1
[ 0 ] + rtB . i12dfhokz1 [ 1 ] ; bpIndex_idx_0 = rtB . burumew3sb ;
bpIndex_idx_1 = rtB . dpmiotlnvk ; bpIndex_idx_2 = rtB . kcp5vlmrhn ; if ( (
( uint32_T ) rtB . burumew3sb == 8U ) && ( rtB . oovkaz423b >= 1.0 ) ) {
bpIndex_idx_0 = rtB . burumew3sb + 1 ; } if ( ( ( uint32_T ) rtB . dpmiotlnvk
== 2U ) && ( rtB . ew4bp2hsh4 >= 1.0 ) ) { bpIndex_idx_1 = rtB . dpmiotlnvk +
1 ; } if ( ( ( uint32_T ) rtB . kcp5vlmrhn == 6U ) && ( rtB . fghbljyvca >=
1.0 ) ) { bpIndex_idx_2 = rtB . kcp5vlmrhn + 1 ; } rtB . hyd1pi2bmq = rtP .
Cmq_Table [ ( ( uint32_T ) ( bpIndex_idx_1 * 10 ) + bpIndex_idx_0 ) +
bpIndex_idx_2 * 40 ] ; rtB . csyxoinipa = rtB . hyd1pi2bmq * huam1midmw [ 1 ]
; bpIndex_idx_0 = rtB . burumew3sb ; bpIndex_idx_1 = rtB . dpmiotlnvk ;
bpIndex_idx_2 = rtB . kcp5vlmrhn ; if ( ( ( uint32_T ) rtB . burumew3sb == 8U
) && ( rtB . oovkaz423b >= 1.0 ) ) { bpIndex_idx_0 = rtB . burumew3sb + 1 ; }
if ( ( ( uint32_T ) rtB . dpmiotlnvk == 2U ) && ( rtB . ew4bp2hsh4 >= 1.0 ) )
{ bpIndex_idx_1 = rtB . dpmiotlnvk + 1 ; } if ( ( ( uint32_T ) rtB .
kcp5vlmrhn == 6U ) && ( rtB . fghbljyvca >= 1.0 ) ) { bpIndex_idx_2 = rtB .
kcp5vlmrhn + 1 ; } rtB . adcuqjpjfk = rtP . Cmad_Table [ ( ( uint32_T ) (
bpIndex_idx_1 * 10 ) + bpIndex_idx_0 ) + bpIndex_idx_2 * 40 ] ; rtB .
dfv5zlgscv = rtB . adcuqjpjfk * rtB . cdrl4nzwfz ; rtB . m0mnsmhzee = rtB .
csyxoinipa + rtB . dfv5zlgscv ; bpIndex_idx_0 = rtB . burumew3sb ;
bpIndex_idx_1 = rtB . dpmiotlnvk ; bpIndex_idx_2 = rtB . kcp5vlmrhn ; if ( (
( uint32_T ) rtB . burumew3sb == 8U ) && ( rtB . oovkaz423b >= 1.0 ) ) {
bpIndex_idx_0 = rtB . burumew3sb + 1 ; } if ( ( ( uint32_T ) rtB . dpmiotlnvk
== 2U ) && ( rtB . ew4bp2hsh4 >= 1.0 ) ) { bpIndex_idx_1 = rtB . dpmiotlnvk +
1 ; } if ( ( ( uint32_T ) rtB . kcp5vlmrhn == 6U ) && ( rtB . fghbljyvca >=
1.0 ) ) { bpIndex_idx_2 = rtB . kcp5vlmrhn + 1 ; } rtB . hqz5grr5x5 = rtP .
Cnp_Table [ ( ( uint32_T ) ( bpIndex_idx_1 * 10 ) + bpIndex_idx_0 ) +
bpIndex_idx_2 * 40 ] ; bpIndex_idx_0 = rtB . burumew3sb ; bpIndex_idx_1 = rtB
. dpmiotlnvk ; bpIndex_idx_2 = rtB . kcp5vlmrhn ; if ( ( ( uint32_T ) rtB .
burumew3sb == 8U ) && ( rtB . oovkaz423b >= 1.0 ) ) { bpIndex_idx_0 = rtB .
burumew3sb + 1 ; } if ( ( ( uint32_T ) rtB . dpmiotlnvk == 2U ) && ( rtB .
ew4bp2hsh4 >= 1.0 ) ) { bpIndex_idx_1 = rtB . dpmiotlnvk + 1 ; } if ( ( (
uint32_T ) rtB . kcp5vlmrhn == 6U ) && ( rtB . fghbljyvca >= 1.0 ) ) {
bpIndex_idx_2 = rtB . kcp5vlmrhn + 1 ; } rtB . nvp5xdnq4m = rtP . Cnr_Table [
( ( uint32_T ) ( bpIndex_idx_1 * 10 ) + bpIndex_idx_0 ) + bpIndex_idx_2 * 40
] ; rtB . aoguormswf [ 0 ] = rtB . hqz5grr5x5 * huam1midmw [ 0 ] ; rtB .
aoguormswf [ 1 ] = rtB . nvp5xdnq4m * huam1midmw [ 2 ] ; rtB . ku2mt5oq34 =
rtB . aoguormswf [ 0 ] + rtB . aoguormswf [ 1 ] ; rtB . ok4uvdpxny [ 0 ] =
rtP . Gain1_Gain [ 0 ] * rtP . zero_Value ; rtB . ok4uvdpxny [ 1 ] = rtP .
Gain1_Gain [ 1 ] * rtB . fui5djlzoo ; rtB . ok4uvdpxny [ 2 ] = rtP .
Gain1_Gain [ 2 ] * rtB . adbita3g4i ; rtB . ok4uvdpxny [ 3 ] = rtP .
Gain1_Gain [ 3 ] * rtB . aokxroo1bz ; rtB . ok4uvdpxny [ 4 ] = rtP .
Gain1_Gain [ 4 ] * rtB . m0mnsmhzee ; rtB . ok4uvdpxny [ 5 ] = rtP .
Gain1_Gain [ 5 ] * rtB . ku2mt5oq34 ; rtB . mvem5vfcmh = aotvmzw3cy [ 0 ] *
aotvmzw3cy [ 0 ] ; rtB . mqdmh5qxvd = aotvmzw3cy [ 1 ] * aotvmzw3cy [ 1 ] ;
rtB . jranmezdtp = aotvmzw3cy [ 2 ] * aotvmzw3cy [ 2 ] ; rtB . elj1og2hw2 = (
rtB . mvem5vfcmh + rtB . mqdmh5qxvd ) + rtB . jranmezdtp ; if (
ssIsMajorTimeStep ( rtS ) ) { if ( rtDW . ftwguoefpc != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; rtDW . ftwguoefpc = 0 ;
} lvewqzupwi = muDoubleScalarSqrt ( rtB . elj1og2hw2 ) ; } else { if ( rtB .
elj1og2hw2 < 0.0 ) { lvewqzupwi = - muDoubleScalarSqrt ( muDoubleScalarAbs (
rtB . elj1og2hw2 ) ) ; } else { lvewqzupwi = muDoubleScalarSqrt ( rtB .
elj1og2hw2 ) ; } if ( rtB . elj1og2hw2 < 0.0 ) { rtDW . ftwguoefpc = 1 ; } }
for ( bpIndex_idx_0 = 0 ; bpIndex_idx_0 < 6 ; bpIndex_idx_0 ++ ) { rtB .
oykwjbf0l2 [ bpIndex_idx_0 ] = rtB . ok4uvdpxny [ bpIndex_idx_0 ] / rtP .
u_Value_axd001kf0t / lvewqzupwi ; } rtB . mjvjidnmqy [ 0 ] = rtP .
coefAdjust_Gain_d5gkknnahd [ 0 ] * rtB . oykwjbf0l2 [ 0 ] ; rtB . d1znscnd2p
[ 0 ] = rtB . mwuv02g011 * rtB . mjvjidnmqy [ 0 ] ; rtB . mjvjidnmqy [ 1 ] =
rtP . coefAdjust_Gain_d5gkknnahd [ 1 ] * rtB . oykwjbf0l2 [ 1 ] ; rtB .
d1znscnd2p [ 1 ] = rtB . mwuv02g011 * rtB . mjvjidnmqy [ 1 ] ; rtB .
mjvjidnmqy [ 2 ] = rtP . coefAdjust_Gain_d5gkknnahd [ 2 ] * rtB . oykwjbf0l2
[ 2 ] ; rtB . d1znscnd2p [ 2 ] = rtB . mwuv02g011 * rtB . mjvjidnmqy [ 2 ] ;
muDoubleScalarSinCos ( muDoubleScalarAtan2 ( aotvmzw3cy [ 2 ] , aotvmzw3cy [
0 ] ) , & lvewqzupwi , & m3fe2punjq_p ) ; rtB . bkeumodt1t [ 0 ] =
m3fe2punjq_p ; rtB . bkeumodt1t [ 1 ] = rtP . Constant1_Value_kfsbs5wuhz ;
rtB . bkeumodt1t [ 2 ] = - lvewqzupwi ; rtB . bkeumodt1t [ 3 ] = rtP .
Constant_Value_feqzr4eans ; rtB . bkeumodt1t [ 4 ] = rtP .
Constant2_Value_agtqtjm4z1 ; rtB . bkeumodt1t [ 5 ] = rtP .
Constant4_Value_pnrru5m0fs ; rtB . bkeumodt1t [ 6 ] = lvewqzupwi ; rtB .
bkeumodt1t [ 7 ] = rtP . Constant3_Value_lnoybacp11 ; rtB . bkeumodt1t [ 8 ]
= m3fe2punjq_p ; for ( bpIndex_idx_0 = 0 ; bpIndex_idx_0 < 3 ; bpIndex_idx_0
++ ) { rtB . kl54abxyyo [ bpIndex_idx_0 ] = 0.0 ; rtB . kl54abxyyo [
bpIndex_idx_0 ] += rtB . bkeumodt1t [ bpIndex_idx_0 ] * rtB . mjh3qtkwwe [ 0
] ; rtB . kl54abxyyo [ bpIndex_idx_0 ] += rtB . bkeumodt1t [ bpIndex_idx_0 +
3 ] * rtB . mjh3qtkwwe [ 1 ] ; rtB . kl54abxyyo [ bpIndex_idx_0 ] += rtB .
bkeumodt1t [ bpIndex_idx_0 + 6 ] * rtB . mjh3qtkwwe [ 2 ] ; } rtB .
na33cozjmh = rtB . d1znscnd2p [ 1 ] * rtB . kl54abxyyo [ 2 ] ; rtB .
gy531db5ab = rtB . d1znscnd2p [ 2 ] * rtB . kl54abxyyo [ 0 ] ; rtB .
n00wehaagy = rtB . d1znscnd2p [ 0 ] * rtB . kl54abxyyo [ 1 ] ; rtB .
hsc0hjfp4c = rtB . d1znscnd2p [ 2 ] * rtB . kl54abxyyo [ 1 ] ; rtB .
ju4uigrkf5 = rtB . d1znscnd2p [ 0 ] * rtB . kl54abxyyo [ 2 ] ; rtB .
ikfhliwvmn = rtB . d1znscnd2p [ 1 ] * rtB . kl54abxyyo [ 0 ] ; rtB .
chj2lnrtdr [ 0 ] = rtB . na33cozjmh - rtB . hsc0hjfp4c ; rtB . chj2lnrtdr [ 1
] = rtB . gy531db5ab - rtB . ju4uigrkf5 ; rtB . chj2lnrtdr [ 2 ] = rtB .
n00wehaagy - rtB . ikfhliwvmn ; rtB . d53l1o1puh [ 0 ] = rtP .
AerodynamicForcesandMoments_b_a2pcrfjg54 * rtB . mwuv02g011 ; rtB .
d53l1o1puh [ 1 ] = rtP . AerodynamicForcesandMoments_cbar_h4kwacm43q * rtB .
mwuv02g011 ; rtB . d53l1o1puh [ 2 ] = rtP .
AerodynamicForcesandMoments_b_a2pcrfjg54 * rtB . mwuv02g011 ; rtB .
khtpgpvqjl [ 0 ] = rtB . oykwjbf0l2 [ 3 ] * rtB . d53l1o1puh [ 0 ] ; rtB .
fkghwm5gsz [ 0 ] = rtB . chj2lnrtdr [ 0 ] + rtB . khtpgpvqjl [ 0 ] ; rtB .
khtpgpvqjl [ 1 ] = rtB . oykwjbf0l2 [ 4 ] * rtB . d53l1o1puh [ 1 ] ; rtB .
fkghwm5gsz [ 1 ] = rtB . chj2lnrtdr [ 1 ] + rtB . khtpgpvqjl [ 1 ] ; rtB .
khtpgpvqjl [ 2 ] = rtB . oykwjbf0l2 [ 5 ] * rtB . d53l1o1puh [ 2 ] ; rtB .
fkghwm5gsz [ 2 ] = rtB . chj2lnrtdr [ 2 ] + rtB . khtpgpvqjl [ 2 ] ; rtB .
hg2rkm0b0a = rtP . AerodynamicForcesandMoments_S_haf3wauqag * rtB .
ltux4bsueq ; for ( bpIndex_idx_0 = 0 ; bpIndex_idx_0 < 3 ; bpIndex_idx_0 ++ )
{ rtB . cugpw2oaop [ bpIndex_idx_0 ] = 0.0 ; rtB . cugpw2oaop [ bpIndex_idx_0
] += rtB . mddt1rvp3v [ bpIndex_idx_0 ] * rtB . fkghwm5gsz [ 0 ] ; rtB .
cugpw2oaop [ bpIndex_idx_0 ] += rtB . mddt1rvp3v [ bpIndex_idx_0 + 3 ] * rtB
. fkghwm5gsz [ 1 ] ; rtB . cugpw2oaop [ bpIndex_idx_0 ] += rtB . mddt1rvp3v [
bpIndex_idx_0 + 6 ] * rtB . fkghwm5gsz [ 2 ] ; rtB . f5hluqgotp [
bpIndex_idx_0 ] = rtB . gb1h1tviap [ bpIndex_idx_0 ] + rtB . cugpw2oaop [
bpIndex_idx_0 ] ; rtB . jewko3ql0j [ bpIndex_idx_0 ] = rtB . hg2rkm0b0a * rtB
. eas3pz0d31 [ bpIndex_idx_0 ] ; } rtB . ogjmkxrtzk = rtB . jewko3ql0j [ 1 ]
* rtB . boldxgnyxd [ 2 ] ; rtB . acnxtf0njr = rtB . jewko3ql0j [ 2 ] * rtB .
boldxgnyxd [ 0 ] ; rtB . apvxa3vvr5 = rtB . jewko3ql0j [ 0 ] * rtB .
boldxgnyxd [ 1 ] ; rtB . o5is4gwrz1 = rtB . jewko3ql0j [ 2 ] * rtB .
boldxgnyxd [ 1 ] ; rtB . a2r2bsx5op = rtB . jewko3ql0j [ 0 ] * rtB .
boldxgnyxd [ 2 ] ; rtB . iknur005un = rtB . jewko3ql0j [ 1 ] * rtB .
boldxgnyxd [ 0 ] ; rtB . ltisnx0tk2 [ 0 ] = rtB . ogjmkxrtzk - rtB .
o5is4gwrz1 ; rtB . ltisnx0tk2 [ 1 ] = rtB . acnxtf0njr - rtB . a2r2bsx5op ;
rtB . ltisnx0tk2 [ 2 ] = rtB . apvxa3vvr5 - rtB . iknur005un ; rtB .
hnflxg3oyc [ 0 ] = rtP . AerodynamicForcesandMoments_b_efeekaqk2w * rtB .
hg2rkm0b0a ; rtB . hnflxg3oyc [ 1 ] = rtP .
AerodynamicForcesandMoments_cbar_miyvp11bgo * rtB . hg2rkm0b0a ; rtB .
hnflxg3oyc [ 2 ] = rtP . AerodynamicForcesandMoments_b_efeekaqk2w * rtB .
hg2rkm0b0a ; rtB . ahalic5glf [ 0 ] = rtP . Constant2_Value_pjsapbkri4 [ 3 ]
* rtB . hnflxg3oyc [ 0 ] ; rtB . gbi1feu30l [ 0 ] = rtB . ltisnx0tk2 [ 0 ] +
rtB . ahalic5glf [ 0 ] ; rtB . lsixin3gz1 [ 0 ] = 1.3558179483314003 * rtB .
f5hluqgotp [ 0 ] + rtB . gbi1feu30l [ 0 ] ; rtB . bhsoq03twv [ 0 ] = rtB .
lsixin3gz1 [ 0 ] + rtP . Moments_Value [ 0 ] ; rtB . ph3xybkpn3 [ 0 ] = ( rtB
. bhsoq03twv [ 0 ] - rtB . j55tg2sijl [ 0 ] ) - rtB . o54r3adnq1 [ 0 ] ; rtB
. ahalic5glf [ 1 ] = rtP . Constant2_Value_pjsapbkri4 [ 4 ] * rtB .
hnflxg3oyc [ 1 ] ; rtB . gbi1feu30l [ 1 ] = rtB . ltisnx0tk2 [ 1 ] + rtB .
ahalic5glf [ 1 ] ; rtB . lsixin3gz1 [ 1 ] = 1.3558179483314003 * rtB .
f5hluqgotp [ 1 ] + rtB . gbi1feu30l [ 1 ] ; rtB . bhsoq03twv [ 1 ] = rtB .
lsixin3gz1 [ 1 ] + rtP . Moments_Value [ 1 ] ; rtB . ph3xybkpn3 [ 1 ] = ( rtB
. bhsoq03twv [ 1 ] - rtB . j55tg2sijl [ 1 ] ) - rtB . o54r3adnq1 [ 1 ] ; rtB
. ahalic5glf [ 2 ] = rtP . Constant2_Value_pjsapbkri4 [ 5 ] * rtB .
hnflxg3oyc [ 2 ] ; rtB . gbi1feu30l [ 2 ] = rtB . ltisnx0tk2 [ 2 ] + rtB .
ahalic5glf [ 2 ] ; rtB . lsixin3gz1 [ 2 ] = 1.3558179483314003 * rtB .
f5hluqgotp [ 2 ] + rtB . gbi1feu30l [ 2 ] ; rtB . bhsoq03twv [ 2 ] = rtB .
lsixin3gz1 [ 2 ] + rtP . Moments_Value [ 2 ] ; rtB . ph3xybkpn3 [ 2 ] = ( rtB
. bhsoq03twv [ 2 ] - rtB . j55tg2sijl [ 2 ] ) - rtB . o54r3adnq1 [ 2 ] ;
rt_mrdivide_U1d1x3_U2d3x3_Yd1x3_snf ( rtB . ph3xybkpn3 , rtB . ooprpnnz1m ,
rtB . hlwx1xld4v ) ; muDoubleScalarSinCos ( muDoubleScalarAtan2 ( aotvmzw3cy
[ 2 ] , aotvmzw3cy [ 0 ] ) , & lvewqzupwi , & m3fe2punjq_p ) ; rtB .
iglnjbiqey [ 0 ] = m3fe2punjq_p ; rtB . iglnjbiqey [ 1 ] = rtP .
Constant1_Value_cy5z4hcsl3 ; rtB . iglnjbiqey [ 2 ] = - lvewqzupwi ; rtB .
iglnjbiqey [ 3 ] = rtP . Constant_Value_ea5rkpodns ; rtB . iglnjbiqey [ 4 ] =
rtP . Constant2_Value_epbnzx0ky0 ; rtB . iglnjbiqey [ 5 ] = rtP .
Constant4_Value_atc41zi2ir ; rtB . iglnjbiqey [ 6 ] = lvewqzupwi ; rtB .
iglnjbiqey [ 7 ] = rtP . Constant3_Value_jmheminny5 ; rtB . iglnjbiqey [ 8 ]
= m3fe2punjq_p ; for ( bpIndex_idx_0 = 0 ; bpIndex_idx_0 < 3 ; bpIndex_idx_0
++ ) { rtB . iylzbmkgfi [ 3 * bpIndex_idx_0 ] = rtB . iglnjbiqey [
bpIndex_idx_0 ] ; rtB . iylzbmkgfi [ 1 + 3 * bpIndex_idx_0 ] = rtB .
iglnjbiqey [ bpIndex_idx_0 + 3 ] ; rtB . iylzbmkgfi [ 2 + 3 * bpIndex_idx_0 ]
= rtB . iglnjbiqey [ bpIndex_idx_0 + 6 ] ; } for ( bpIndex_idx_0 = 0 ;
bpIndex_idx_0 < 3 ; bpIndex_idx_0 ++ ) { rtB . ntlxpgwfz1 [ bpIndex_idx_0 ] =
0.0 ; rtB . ntlxpgwfz1 [ bpIndex_idx_0 ] += rtB . iylzbmkgfi [ bpIndex_idx_0
] * rtB . g4ixw2ju0a [ 0 ] ; rtB . ntlxpgwfz1 [ bpIndex_idx_0 ] += rtB .
iylzbmkgfi [ bpIndex_idx_0 + 3 ] * rtB . g4ixw2ju0a [ 1 ] ; rtB . ntlxpgwfz1
[ bpIndex_idx_0 ] += rtB . iylzbmkgfi [ bpIndex_idx_0 + 6 ] * rtB .
g4ixw2ju0a [ 2 ] ; } muDoubleScalarSinCos ( muDoubleScalarAtan2 ( aotvmzw3cy
[ 2 ] , aotvmzw3cy [ 0 ] ) , & lvewqzupwi , & m3fe2punjq_p ) ; rtB .
er0wsgu0uz [ 0 ] = m3fe2punjq_p ; rtB . er0wsgu0uz [ 1 ] = rtP .
Constant1_Value_ndgxvb4zwb ; rtB . er0wsgu0uz [ 2 ] = - lvewqzupwi ; rtB .
er0wsgu0uz [ 3 ] = rtP . Constant_Value_m1jhswm2a4 ; rtB . er0wsgu0uz [ 4 ] =
rtP . Constant2_Value_ogp3xqdtea ; rtB . er0wsgu0uz [ 5 ] = rtP .
Constant4_Value_gcn5uwst2a ; rtB . er0wsgu0uz [ 6 ] = lvewqzupwi ; rtB .
er0wsgu0uz [ 7 ] = rtP . Constant3_Value_oqhlderhny ; rtB . er0wsgu0uz [ 8 ]
= m3fe2punjq_p ; for ( bpIndex_idx_0 = 0 ; bpIndex_idx_0 < 3 ; bpIndex_idx_0
++ ) { rtB . nqqzwty3zs [ 3 * bpIndex_idx_0 ] = rtB . er0wsgu0uz [
bpIndex_idx_0 ] ; rtB . nqqzwty3zs [ 1 + 3 * bpIndex_idx_0 ] = rtB .
er0wsgu0uz [ bpIndex_idx_0 + 3 ] ; rtB . nqqzwty3zs [ 2 + 3 * bpIndex_idx_0 ]
= rtB . er0wsgu0uz [ bpIndex_idx_0 + 6 ] ; } for ( bpIndex_idx_0 = 0 ;
bpIndex_idx_0 < 3 ; bpIndex_idx_0 ++ ) { rtB . cavyfym52n [ bpIndex_idx_0 ] =
0.0 ; rtB . cavyfym52n [ bpIndex_idx_0 ] += rtB . nqqzwty3zs [ bpIndex_idx_0
] * rtB . d1znscnd2p [ 0 ] ; rtB . cavyfym52n [ bpIndex_idx_0 ] += rtB .
nqqzwty3zs [ bpIndex_idx_0 + 3 ] * rtB . d1znscnd2p [ 1 ] ; rtB . cavyfym52n
[ bpIndex_idx_0 ] += rtB . nqqzwty3zs [ bpIndex_idx_0 + 6 ] * rtB .
d1znscnd2p [ 2 ] ; rtB . lhmph3qfyb [ bpIndex_idx_0 ] = rtB . ntlxpgwfz1 [
bpIndex_idx_0 ] + rtB . cavyfym52n [ bpIndex_idx_0 ] ; rtB . jhpnbmxx5n [
bpIndex_idx_0 ] = 4.4482216152605005 * rtB . lhmph3qfyb [ bpIndex_idx_0 ] +
rtB . jewko3ql0j [ bpIndex_idx_0 ] ; } rtB . p5lvunc4gi [ 0 ] = rtB .
jhpnbmxx5n [ 0 ] + rtB . cp032iv5kb ; rtB . p5lvunc4gi [ 1 ] = rtB .
jhpnbmxx5n [ 1 ] + rtP . TyTz_Value [ 0 ] ; rtB . p5lvunc4gi [ 2 ] = rtB .
jhpnbmxx5n [ 2 ] + rtP . TyTz_Value [ 1 ] ; rtB . pytois5kxe = rtB .
dzs1soumuc [ 1 ] * rtB . nzoyizvn0g [ 2 ] ; rtB . dj5opchr3c = rtB .
dzs1soumuc [ 2 ] * rtB . nzoyizvn0g [ 0 ] ; rtB . hjgda4lsay = rtB .
dzs1soumuc [ 0 ] * rtB . nzoyizvn0g [ 1 ] ; rtB . pf1sahzmz5 = rtB .
dzs1soumuc [ 2 ] * rtB . nzoyizvn0g [ 1 ] ; rtB . j0zjfcbwwv = rtB .
dzs1soumuc [ 0 ] * rtB . nzoyizvn0g [ 2 ] ; rtB . hogqcx5gkm = rtB .
dzs1soumuc [ 1 ] * rtB . nzoyizvn0g [ 0 ] ; rtB . pqmqi1ih0x [ 0 ] = rtB .
pytois5kxe - rtB . pf1sahzmz5 ; rtB . pqmqi1ih0x [ 1 ] = rtB . dj5opchr3c -
rtB . j0zjfcbwwv ; rtB . pqmqi1ih0x [ 2 ] = rtB . hjgda4lsay - rtB .
hogqcx5gkm ; rtB . f3tffkcsn4 [ 0 ] = rtB . p5lvunc4gi [ 0 ] / rtP .
uDOFEulerAngles_mass_0 ; rtB . orhueszosr [ 0 ] = rtB . f3tffkcsn4 [ 0 ] +
rtB . pqmqi1ih0x [ 0 ] ; rtB . f3tffkcsn4 [ 1 ] = rtB . p5lvunc4gi [ 1 ] /
rtP . uDOFEulerAngles_mass_0 ; rtB . orhueszosr [ 1 ] = rtB . f3tffkcsn4 [ 1
] + rtB . pqmqi1ih0x [ 1 ] ; rtB . f3tffkcsn4 [ 2 ] = rtB . p5lvunc4gi [ 2 ]
/ rtP . uDOFEulerAngles_mass_0 ; rtB . orhueszosr [ 2 ] = rtB . f3tffkcsn4 [
2 ] + rtB . pqmqi1ih0x [ 2 ] ; UNUSED_PARAMETER ( tid ) ; } void
MdlOutputsTID3 ( int_T tid ) { real_T gl4obxah00 ; real_T niowyw3xnh [ 18 ] ;
int32_T i ; real_T p13fjzwkx3_idx_0 ; real_T p13fjzwkx3_idx_1 ; real_T
p13fjzwkx3_idx_2 ; real_T p13fjzwkx3_idx_3 ; rtB . pg1uquivv5 =
0.017453292519943295 * rtP . DrydenWindTurbulenceModelContinuousqr_Wdeg ; rtB
. in1jikpuyp = 3.280839895013123 * rtP .
DrydenWindTurbulenceModelContinuousqr_L_high ; rtB . k1qm14mokl =
3.280839895013123 * rtP . DrydenWindTurbulenceModelContinuousqr_W20 * rtP .
sigma_wg_Gain ; rtB . kjfzsflye3 = plook_bincpa ( rtP .
DrydenWindTurbulenceModelContinuousqr_TurbProb , rtP .
PreLookUpIndexSearchprobofexceed_BreakpointsData , 6U , & rtB . m4ioj5ifig ,
& rtDW . g4kd5mgehq ) ; if ( ssIsMajorTimeStep ( rtS ) ) { if ( rtDW .
jusb02f5rj != 0 ) { ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; rtDW
. jusb02f5rj = 0 ; } p13fjzwkx3_idx_0 = muDoubleScalarSqrt ( rtP .
WhiteNoise_pwr [ 0 ] ) ; p13fjzwkx3_idx_1 = muDoubleScalarSqrt ( rtP .
WhiteNoise_pwr [ 1 ] ) ; p13fjzwkx3_idx_2 = muDoubleScalarSqrt ( rtP .
WhiteNoise_pwr [ 2 ] ) ; p13fjzwkx3_idx_3 = muDoubleScalarSqrt ( rtP .
WhiteNoise_pwr [ 3 ] ) ; if ( rtDW . nhbi5jh4go != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; rtDW . nhbi5jh4go = 0 ;
} gl4obxah00 = muDoubleScalarSqrt ( rtP . WhiteNoise_Ts ) ; } else { if ( rtP
. WhiteNoise_pwr [ 0 ] < 0.0 ) { p13fjzwkx3_idx_0 = - muDoubleScalarSqrt (
muDoubleScalarAbs ( rtP . WhiteNoise_pwr [ 0 ] ) ) ; rtDW . jusb02f5rj = 1 ;
} else { p13fjzwkx3_idx_0 = muDoubleScalarSqrt ( rtP . WhiteNoise_pwr [ 0 ] )
; } if ( rtP . WhiteNoise_pwr [ 1 ] < 0.0 ) { p13fjzwkx3_idx_1 = -
muDoubleScalarSqrt ( muDoubleScalarAbs ( rtP . WhiteNoise_pwr [ 1 ] ) ) ;
rtDW . jusb02f5rj = 1 ; } else { p13fjzwkx3_idx_1 = muDoubleScalarSqrt ( rtP
. WhiteNoise_pwr [ 1 ] ) ; } if ( rtP . WhiteNoise_pwr [ 2 ] < 0.0 ) {
p13fjzwkx3_idx_2 = - muDoubleScalarSqrt ( muDoubleScalarAbs ( rtP .
WhiteNoise_pwr [ 2 ] ) ) ; rtDW . jusb02f5rj = 1 ; } else { p13fjzwkx3_idx_2
= muDoubleScalarSqrt ( rtP . WhiteNoise_pwr [ 2 ] ) ; } if ( rtP .
WhiteNoise_pwr [ 3 ] < 0.0 ) { p13fjzwkx3_idx_3 = - muDoubleScalarSqrt (
muDoubleScalarAbs ( rtP . WhiteNoise_pwr [ 3 ] ) ) ; rtDW . jusb02f5rj = 1 ;
} else { p13fjzwkx3_idx_3 = muDoubleScalarSqrt ( rtP . WhiteNoise_pwr [ 3 ] )
; } if ( rtP . WhiteNoise_Ts < 0.0 ) { gl4obxah00 = - muDoubleScalarSqrt (
muDoubleScalarAbs ( rtP . WhiteNoise_Ts ) ) ; rtDW . nhbi5jh4go = 1 ; } else
{ gl4obxah00 = muDoubleScalarSqrt ( rtP . WhiteNoise_Ts ) ; } } rtB .
iw50kb54tc [ 0 ] = p13fjzwkx3_idx_0 / gl4obxah00 ; rtB . iw50kb54tc [ 1 ] =
p13fjzwkx3_idx_1 / gl4obxah00 ; rtB . iw50kb54tc [ 2 ] = p13fjzwkx3_idx_2 /
gl4obxah00 ; rtB . iw50kb54tc [ 3 ] = p13fjzwkx3_idx_3 / gl4obxah00 ; rtB .
p5dpqn0t0m = 3.280839895013123 * rtP .
DrydenWindTurbulenceModelContinuousqr_Wingspan ; rtB . buysvvpcb4 = rtP .
Constant3_Value / rtB . p5dpqn0t0m ; if ( ( rtB . buysvvpcb4 < 0.0 ) && ( rtP
. Constant2_Value > muDoubleScalarFloor ( rtP . Constant2_Value ) ) ) { rtB .
o1xsnq5r4j = - muDoubleScalarPower ( - rtB . buysvvpcb4 , rtP .
Constant2_Value ) ; } else { rtB . o1xsnq5r4j = muDoubleScalarPower ( rtB .
buysvvpcb4 , rtP . Constant2_Value ) ; } if ( ssIsMajorTimeStep ( rtS ) ) {
srUpdateBC ( rtDW . nfawadvxsq ) ; if ( rtDW . euk35lqnv1 != 0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; rtDW . euk35lqnv1 = 0 ;
} rtB . b4p0x5sch3 = muDoubleScalarSqrt ( rtP . Constant_Value ) ; srUpdateBC
( rtDW . ne00r4ogt0 ) ; } else if ( rtP . Constant_Value < 0.0 ) { rtB .
b4p0x5sch3 = - muDoubleScalarSqrt ( muDoubleScalarAbs ( rtP . Constant_Value
) ) ; rtDW . euk35lqnv1 = 1 ; } else { rtB . b4p0x5sch3 = muDoubleScalarSqrt
( rtP . Constant_Value ) ; } rtB . obpi4pygmr = rtP . min_height_high_Value -
rtP . max_height_low_Value ; rtB . h5wwlzhkjq = rtP .
min_height_high_Value_f0iqsahu4c - rtP . max_height_low_Value_lykhpozz3y ;
gl4obxah00 = rtP . ref_heightz0_Value ; if ( ssIsMajorTimeStep ( rtS ) ) { if
( rtDW . ir0jb20k33 != 0 ) { ssSetBlockStateForSolverChangedAtMajorStep ( rtS
) ; rtDW . ir0jb20k33 = 0 ; } } else { if ( rtP . ref_heightz0_Value < 0.0 )
{ gl4obxah00 = 0.0 ; rtDW . ir0jb20k33 = 1 ; } } rtB . kbexovbmwl =
muDoubleScalarLog ( gl4obxah00 ) ; muDoubleScalarSinCos (
0.017453292519943295 * rtP . WindShearModel_Wdeg , & gl4obxah00 , &
p13fjzwkx3_idx_0 ) ; rtB . hnfbrhdub5 [ 0 ] = - rtP . WindShearModel_W_20 *
p13fjzwkx3_idx_0 ; rtB . hnfbrhdub5 [ 1 ] = - rtP . WindShearModel_W_20 *
gl4obxah00 ; rtB . hnfbrhdub5 [ 2 ] = - rtP . WindShearModel_W_20 * rtP .
Wdeg1_Value ; rtB . cdrl4nzwfz = 57.295779513082323 * rtP .
Constant_Value_lqmbfph4ah ; rtB . h1rmkjrkmq = - ( 0.017453292519943295 * rtB
. cdrl4nzwfz ) ; for ( i = 0 ; i < 3 ; i ++ ) { rtB . diwxdnf4dg [ i ] = rtP
. zero3_Value [ i ] - rtP . zero3_Value [ i ] ; rtB . mjh3qtkwwe [ i ] = rtP
. zero1_Value [ i ] - rtP . zero3_Value [ i ] ; rtB . eas3pz0d31 [ i ] = rtP
. coefAdjust_Gain_i4hwujqkud [ i ] * rtP . Constant2_Value_pjsapbkri4 [ i ] ;
rtB . boldxgnyxd [ i ] = rtP . Constant1_Value_az5chewn2m [ i ] - rtP .
Constant_Value_cbj5azvbu2 [ i ] ; niowyw3xnh [ 6 * i ] = rtP .
uDOFEulerAngles_inertia [ 3 * i ] ; niowyw3xnh [ 3 + 6 * i ] = rtP .
Constant2_Value_nvqbu4imhl [ 3 * i ] ; rtB . mrsrezbuqk [ 3 * i ] =
niowyw3xnh [ 6 * i ] ; rtB . bwcottfiut [ 3 * i ] = niowyw3xnh [ 6 * i + 3 ]
; rtB . dsk4lj4maj [ 3 * i ] = rtP . Constant_Value_bjnypp3rh0 [ i ] ; rtB .
ooprpnnz1m [ 3 * i ] = niowyw3xnh [ 6 * i ] ; niowyw3xnh [ 1 + 6 * i ] = rtP
. uDOFEulerAngles_inertia [ 3 * i + 1 ] ; niowyw3xnh [ 4 + 6 * i ] = rtP .
Constant2_Value_nvqbu4imhl [ 3 * i + 1 ] ; rtB . mrsrezbuqk [ 1 + 3 * i ] =
niowyw3xnh [ 6 * i + 1 ] ; rtB . bwcottfiut [ 1 + 3 * i ] = niowyw3xnh [ 6 *
i + 4 ] ; rtB . dsk4lj4maj [ 1 + 3 * i ] = rtP . Constant_Value_bjnypp3rh0 [
i + 3 ] ; rtB . ooprpnnz1m [ 1 + 3 * i ] = niowyw3xnh [ 6 * i + 1 ] ;
niowyw3xnh [ 2 + 6 * i ] = rtP . uDOFEulerAngles_inertia [ 3 * i + 2 ] ;
niowyw3xnh [ 5 + 6 * i ] = rtP . Constant2_Value_nvqbu4imhl [ 3 * i + 2 ] ;
rtB . mrsrezbuqk [ 2 + 3 * i ] = niowyw3xnh [ 6 * i + 2 ] ; rtB . bwcottfiut
[ 2 + 3 * i ] = niowyw3xnh [ 6 * i + 5 ] ; rtB . dsk4lj4maj [ 2 + 3 * i ] =
rtP . Constant_Value_bjnypp3rh0 [ i + 6 ] ; rtB . ooprpnnz1m [ 2 + 3 * i ] =
niowyw3xnh [ 6 * i + 2 ] ; } rtB . cp032iv5kb = look1_plinlcpw ( rtP .
Constant_Value_d1htqtqh1y [ 3 ] , rtP . ThrustX_bp01Data , rtP .
ThrustX_tableData , & rtDW . cgeqxzgrnv , 6U ) ; UNUSED_PARAMETER ( tid ) ; }
void MdlUpdate ( int_T tid ) { if ( rtDW . f3e4goswub ) { if ( rtX .
bm4wjkp3hh == rtP . Distanceintogustx_d_m ) { switch ( rtDW . jqsfntesyx ) {
case 3 : if ( rtB . apsbh2a4ml < 0.0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; rtDW . jqsfntesyx = 1 ;
} break ; case 1 : if ( rtB . apsbh2a4ml >= 0.0 ) { rtDW . jqsfntesyx = 3 ;
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } break ; default :
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; if ( rtB . apsbh2a4ml <
0.0 ) { rtDW . jqsfntesyx = 1 ; } else { rtDW . jqsfntesyx = 3 ; } break ; }
} else if ( rtX . bm4wjkp3hh == rtP .
DistanceintoGustxLimitedtogustlengthd_LowerSat ) { switch ( rtDW . jqsfntesyx
) { case 4 : if ( rtB . apsbh2a4ml > 0.0 ) {
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; rtDW . jqsfntesyx = 2 ;
} break ; case 2 : if ( rtB . apsbh2a4ml <= 0.0 ) { rtDW . jqsfntesyx = 4 ;
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; } break ; default :
ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; if ( rtB . apsbh2a4ml >
0.0 ) { rtDW . jqsfntesyx = 2 ; } else { rtDW . jqsfntesyx = 4 ; } break ; }
} else { rtDW . jqsfntesyx = 0 ; } } ofdpi4iot1 ( rtS , rtB . apsbh2a4ml , &
rtDW . jgkdl5lezan , & rtP . jgkdl5lezan , & rtX . jgkdl5lezan , rtP .
Distanceintogusty_d_m ) ; ofdpi4iot1 ( rtS , rtB . apsbh2a4ml , & rtDW .
fieqmbp0km , & rtP . fieqmbp0km , & rtX . fieqmbp0km , rtP .
Distanceintogustz_d_m ) ; if ( ssIsSampleHit ( rtS , 2 , 0 ) ) { rtDW .
e5dwuk5zfi [ 0 ] = rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . o2m0ho4ib0 [ 0 ] ) *
rtP . WhiteNoise_StdDev + rtP . WhiteNoise_Mean ; rtDW . e5dwuk5zfi [ 1 ] =
rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . o2m0ho4ib0 [ 1 ] ) * rtP .
WhiteNoise_StdDev + rtP . WhiteNoise_Mean ; rtDW . e5dwuk5zfi [ 2 ] =
rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . o2m0ho4ib0 [ 2 ] ) * rtP .
WhiteNoise_StdDev + rtP . WhiteNoise_Mean ; rtDW . e5dwuk5zfi [ 3 ] =
rt_nrand_Upu32_Yd_f_pw_snf ( & rtDW . o2m0ho4ib0 [ 3 ] ) * rtP .
WhiteNoise_StdDev + rtP . WhiteNoise_Mean ; } UNUSED_PARAMETER ( tid ) ; }
void MdlUpdateTID3 ( int_T tid ) { UNUSED_PARAMETER ( tid ) ; } void
MdlDerivatives ( void ) { XDot * _rtXdot ; XDis * _rtXdis ; _rtXdis = ( (
XDis * ) ssGetContStateDisabled ( rtS ) ) ; _rtXdot = ( ( XDot * ) ssGetdX (
rtS ) ) ; _rtXdot -> gw2wykgqi1 [ 0 ] = rtB . orhueszosr [ 0 ] ; _rtXdot ->
k1ode521ap [ 0 ] = rtB . pnx4iii03b [ 0 ] ; _rtXdot -> iuemkmhnjl [ 0 ] = rtB
. bxute4gwb3 [ 0 ] ; _rtXdot -> gw2wykgqi1 [ 1 ] = rtB . orhueszosr [ 1 ] ;
_rtXdot -> k1ode521ap [ 1 ] = rtB . pnx4iii03b [ 1 ] ; _rtXdot -> iuemkmhnjl
[ 1 ] = rtB . bxute4gwb3 [ 1 ] ; _rtXdot -> gw2wykgqi1 [ 2 ] = rtB .
orhueszosr [ 2 ] ; _rtXdot -> k1ode521ap [ 2 ] = rtB . pnx4iii03b [ 2 ] ;
_rtXdot -> iuemkmhnjl [ 2 ] = rtB . bxute4gwb3 [ 2 ] ; if ( rtDW . f3e4goswub
) { if ( ( rtDW . jqsfntesyx != 3 ) && ( rtDW . jqsfntesyx != 4 ) ) { _rtXdot
-> bm4wjkp3hh = rtB . apsbh2a4ml ; _rtXdis -> bm4wjkp3hh = false ; } else {
_rtXdot -> bm4wjkp3hh = 0.0 ; if ( ( rtDW . jqsfntesyx == 3 ) || ( rtDW .
jqsfntesyx == 4 ) ) { _rtXdis -> bm4wjkp3hh = true ; } } } else { ( ( XDot *
) ssGetdX ( rtS ) ) -> bm4wjkp3hh = 0.0 ; } dh3gvlf1g0 ( rtB . apsbh2a4ml , &
rtDW . jgkdl5lezan , & _rtXdis -> jgkdl5lezan , & _rtXdot -> jgkdl5lezan ) ;
dh3gvlf1g0 ( rtB . apsbh2a4ml , & rtDW . fieqmbp0km , & _rtXdis -> fieqmbp0km
, & _rtXdot -> fieqmbp0km ) ; if ( rtDW . ekhaunodew ) { _rtXdot ->
f4qi5fjsdf [ 0 ] = rtB . hbksfryqsi [ 0 ] ; _rtXdot -> f4qi5fjsdf [ 1 ] = rtB
. hbksfryqsi [ 1 ] ; } else { { real_T * dx ; int_T i ; dx = & ( ( ( XDot * )
ssGetdX ( rtS ) ) -> f4qi5fjsdf [ 0 ] ) ; for ( i = 0 ; i < 2 ; i ++ ) { dx [
i ] = 0.0 ; } } } if ( rtDW . ptxtk1nv30 ) { _rtXdot -> pxrnvzd5eg [ 0 ] =
rtB . maka3wnq5n [ 0 ] ; _rtXdot -> dolulbw4pb [ 0 ] = rtB . pxqxqpltfm [ 0 ]
; _rtXdot -> pxrnvzd5eg [ 1 ] = rtB . maka3wnq5n [ 1 ] ; _rtXdot ->
dolulbw4pb [ 1 ] = rtB . pxqxqpltfm [ 1 ] ; } else { { real_T * dx ; int_T i
; dx = & ( ( ( XDot * ) ssGetdX ( rtS ) ) -> pxrnvzd5eg [ 0 ] ) ; for ( i = 0
; i < 4 ; i ++ ) { dx [ i ] = 0.0 ; } } } if ( rtDW . dsenq15ybl ) { _rtXdot
-> cgba0qyovs [ 0 ] = rtB . oum15dzd35 [ 0 ] ; _rtXdot -> cgba0qyovs [ 1 ] =
rtB . oum15dzd35 [ 1 ] ; } else { { real_T * dx ; int_T i ; dx = & ( ( ( XDot
* ) ssGetdX ( rtS ) ) -> cgba0qyovs [ 0 ] ) ; for ( i = 0 ; i < 2 ; i ++ ) {
dx [ i ] = 0.0 ; } } } if ( rtDW . nhrxrmv3xz ) { _rtXdot -> fbih5gck0s [ 0 ]
= rtB . cmdkij32ho [ 0 ] ; _rtXdot -> moa44kkouk [ 0 ] = rtB . fmytsanjo2 [ 0
] ; _rtXdot -> fbih5gck0s [ 1 ] = rtB . cmdkij32ho [ 1 ] ; _rtXdot ->
moa44kkouk [ 1 ] = rtB . fmytsanjo2 [ 1 ] ; } else { { real_T * dx ; int_T i
; dx = & ( ( ( XDot * ) ssGetdX ( rtS ) ) -> fbih5gck0s [ 0 ] ) ; for ( i = 0
; i < 4 ; i ++ ) { dx [ i ] = 0.0 ; } } } if ( rtDW . dtbuv1dhzu ) { _rtXdot
-> dydkrcbic2 [ 0 ] = rtB . b2e3g5hpyo [ 0 ] ; _rtXdot -> dydkrcbic2 [ 1 ] =
rtB . b2e3g5hpyo [ 1 ] ; } else { { real_T * dx ; int_T i ; dx = & ( ( ( XDot
* ) ssGetdX ( rtS ) ) -> dydkrcbic2 [ 0 ] ) ; for ( i = 0 ; i < 2 ; i ++ ) {
dx [ i ] = 0.0 ; } } } if ( rtDW . gjeq11lqni ) { _rtXdot -> cnbgfejjbm [ 0 ]
= rtB . igi43iu4gc [ 0 ] ; _rtXdot -> cnbgfejjbm [ 1 ] = rtB . igi43iu4gc [ 1
] ; } else { { real_T * dx ; int_T i ; dx = & ( ( ( XDot * ) ssGetdX ( rtS )
) -> cnbgfejjbm [ 0 ] ) ; for ( i = 0 ; i < 2 ; i ++ ) { dx [ i ] = 0.0 ; } }
} _rtXdot -> cjakaafmng [ 0 ] = rtB . hlwx1xld4v [ 0 ] ; _rtXdot ->
cjakaafmng [ 1 ] = rtB . hlwx1xld4v [ 1 ] ; _rtXdot -> cjakaafmng [ 2 ] = rtB
. hlwx1xld4v [ 2 ] ; } void MdlProjection ( void ) { } void MdlZeroCrossings
( void ) { boolean_T anyStateSaturated ; ZCV * _rtZCSV ; _rtZCSV = ( ( ZCV *
) ssGetSolverZcSignalVector ( rtS ) ) ; _rtZCSV -> b2kg42njue = rtB .
ks25o2ves0 [ 2 ] - rtP . Limitaltitudetotroposhere_UpperSat ; _rtZCSV ->
jpum5yibxj = rtB . ks25o2ves0 [ 2 ] - rtP .
Limitaltitudetotroposhere_LowerSat ; _rtZCSV -> gr5xaxjmde = rtB . fpjovq1wmk
- rtP . LimitaltitudetoStratosphere_UpperSat ; _rtZCSV -> dhhprfuhty = rtB .
fpjovq1wmk - rtP . LimitaltitudetoStratosphere_LowerSat ; _rtZCSV ->
d4idjyzl44 = rtB . ney5ntjpte - rtP . DiscreteWindGustModel_t_0 ; if ( rtDW .
f3e4goswub ) { if ( ( rtDW . jqsfntesyx == 1 ) && ( rtX . bm4wjkp3hh >= rtP .
Distanceintogustx_d_m ) ) { _rtZCSV -> brii3ajf2q = 0.0 ; } else { _rtZCSV ->
brii3ajf2q = rtX . bm4wjkp3hh - rtP . Distanceintogustx_d_m ; } if ( ( rtDW .
jqsfntesyx == 2 ) && ( rtX . bm4wjkp3hh <= rtP .
DistanceintoGustxLimitedtogustlengthd_LowerSat ) ) { _rtZCSV -> ixxi1jmjzk =
0.0 ; } else { _rtZCSV -> ixxi1jmjzk = rtX . bm4wjkp3hh - rtP .
DistanceintoGustxLimitedtogustlengthd_LowerSat ; } anyStateSaturated = false
; if ( ( rtDW . jqsfntesyx == 3 ) || ( rtDW . jqsfntesyx == 4 ) ) {
anyStateSaturated = true ; } if ( anyStateSaturated ) { _rtZCSV -> hguajj4maw
= rtB . apsbh2a4ml ; } else { _rtZCSV -> hguajj4maw = 0.0 ; } } else { {
real_T * zcsv = & ( ( ( ZCV * ) ssGetSolverZcSignalVector ( rtS ) ) ->
brii3ajf2q ) ; int_T i ; for ( i = 0 ; i < 3 ; i ++ ) { zcsv [ i ] = 0.0 ; }
} } bqgnqqodam ( rtB . apsbh2a4ml , & rtDW . jgkdl5lezan , & rtP .
jgkdl5lezan , & rtX . jgkdl5lezan , & _rtZCSV -> jgkdl5lezan , rtP .
Distanceintogusty_d_m ) ; bqgnqqodam ( rtB . apsbh2a4ml , & rtDW . fieqmbp0km
, & rtP . fieqmbp0km , & rtX . fieqmbp0km , & _rtZCSV -> fieqmbp0km , rtP .
Distanceintogustz_d_m ) ; _rtZCSV -> dmnsxb2hh5 = rtB . optvc153u0 - rtP .
LimitFunction10ftto1000ft_UpperSat ; _rtZCSV -> fpe1d4ebxe = rtB . optvc153u0
- rtP . LimitFunction10ftto1000ft_LowerSat ; _rtZCSV -> osja2jmxmf = rtB .
optvc153u0 - rtP . LimitHeighth1000ft_UpperSat ; _rtZCSV -> fbzhg1da5b = rtB
. optvc153u0 - rtP . LimitHeighth1000ft_LowerSat ; _rtZCSV -> jxxwmu2g4b [ 0
] = 0.0 ; _rtZCSV -> jxxwmu2g4b [ 1 ] = 0.0 ; if ( rtB . optvc153u0 <= 1000.0
) { _rtZCSV -> jxxwmu2g4b [ 0 ] = 1.0 ; } else { if ( rtB . optvc153u0 >=
2000.0 ) { _rtZCSV -> jxxwmu2g4b [ 1 ] = 1.0 ; } } _rtZCSV -> drzgaixt5q [ 0
] = 0.0 ; _rtZCSV -> drzgaixt5q [ 1 ] = 0.0 ; if ( rtB . optvc153u0 <= 1000.0
) { _rtZCSV -> drzgaixt5q [ 0 ] = 1.0 ; } else { if ( rtB . optvc153u0 >=
2000.0 ) { _rtZCSV -> drzgaixt5q [ 1 ] = 1.0 ; } } _rtZCSV -> i3a5htr4m5 =
rtB . jayfpbovsb - rtP . uftinf_UpperSat ; _rtZCSV -> lxy52t3qfy = rtB .
jayfpbovsb - rtP . uftinf_LowerSat ; } void MdlTerminate ( void ) { if (
rt_slioCatalogue ( ) != ( NULL ) ) { void * * slioCatalogueAddr =
rt_slioCatalogueAddr ( ) ; rtwSaveDatasetsToMatFile (
rtwGetPointerFromUniquePtr ( rt_slioCatalogue ( ) ) ,
rt_GetMatSigstreamLoggingFileName ( ) ) ; rtwTerminateSlioCatalogue (
slioCatalogueAddr ) ; * slioCatalogueAddr = NULL ; } } void
MdlInitializeSizes ( void ) { ssSetNumContStates ( rtS , 31 ) ;
ssSetNumPeriodicContStates ( rtS , 3 ) ; ssSetNumY ( rtS , 0 ) ; ssSetNumU (
rtS , 0 ) ; ssSetDirectFeedThrough ( rtS , 0 ) ; ssSetNumSampleTimes ( rtS ,
3 ) ; ssSetNumBlocks ( rtS , 544 ) ; ssSetNumBlockIO ( rtS , 294 ) ;
ssSetNumBlockParams ( rtS , 5212 ) ; } void MdlInitializeSampleTimes ( void )
{ ssSetSampleTime ( rtS , 0 , 0.0 ) ; ssSetSampleTime ( rtS , 1 , 0.0 ) ;
ssSetSampleTime ( rtS , 2 , 0.1 ) ; ssSetOffsetTime ( rtS , 0 , 0.0 ) ;
ssSetOffsetTime ( rtS , 1 , 1.0 ) ; ssSetOffsetTime ( rtS , 2 , 0.0 ) ; }
void raccel_set_checksum ( ) { ssSetChecksumVal ( rtS , 0 , 444972961U ) ;
ssSetChecksumVal ( rtS , 1 , 4146120540U ) ; ssSetChecksumVal ( rtS , 2 ,
2950918377U ) ; ssSetChecksumVal ( rtS , 3 , 2309469585U ) ; }
#if defined(_MSC_VER)
#pragma optimize( "", off )
#endif
SimStruct * raccel_register_model ( void ) { static struct _ssMdlInfo mdlInfo
; ( void ) memset ( ( char * ) rtS , 0 , sizeof ( SimStruct ) ) ; ( void )
memset ( ( char * ) & mdlInfo , 0 , sizeof ( struct _ssMdlInfo ) ) ;
ssSetMdlInfoPtr ( rtS , & mdlInfo ) ; { static time_T mdlPeriod [
NSAMPLE_TIMES ] ; static time_T mdlOffset [ NSAMPLE_TIMES ] ; static time_T
mdlTaskTimes [ NSAMPLE_TIMES ] ; static int_T mdlTsMap [ NSAMPLE_TIMES ] ;
static int_T mdlSampleHits [ NSAMPLE_TIMES ] ; static boolean_T
mdlTNextWasAdjustedPtr [ NSAMPLE_TIMES ] ; static int_T mdlPerTaskSampleHits
[ NSAMPLE_TIMES * NSAMPLE_TIMES ] ; static time_T mdlTimeOfNextSampleHit [
NSAMPLE_TIMES ] ; { int_T i ; for ( i = 0 ; i < NSAMPLE_TIMES ; i ++ ) {
mdlPeriod [ i ] = 0.0 ; mdlOffset [ i ] = 0.0 ; mdlTaskTimes [ i ] = 0.0 ;
mdlTsMap [ i ] = i ; mdlSampleHits [ i ] = 1 ; } } ssSetSampleTimePtr ( rtS ,
& mdlPeriod [ 0 ] ) ; ssSetOffsetTimePtr ( rtS , & mdlOffset [ 0 ] ) ;
ssSetSampleTimeTaskIDPtr ( rtS , & mdlTsMap [ 0 ] ) ; ssSetTPtr ( rtS , &
mdlTaskTimes [ 0 ] ) ; ssSetSampleHitPtr ( rtS , & mdlSampleHits [ 0 ] ) ;
ssSetTNextWasAdjustedPtr ( rtS , & mdlTNextWasAdjustedPtr [ 0 ] ) ;
ssSetPerTaskSampleHitsPtr ( rtS , & mdlPerTaskSampleHits [ 0 ] ) ;
ssSetTimeOfNextSampleHitPtr ( rtS , & mdlTimeOfNextSampleHit [ 0 ] ) ; }
ssSetSolverMode ( rtS , SOLVER_MODE_SINGLETASKING ) ; { ssSetBlockIO ( rtS ,
( ( void * ) & rtB ) ) ; ( void ) memset ( ( ( void * ) & rtB ) , 0 , sizeof
( B ) ) ; } { real_T * x = ( real_T * ) & rtX ; ssSetContStates ( rtS , x ) ;
( void ) memset ( ( void * ) x , 0 , sizeof ( X ) ) ; } { void * dwork = (
void * ) & rtDW ; ssSetRootDWork ( rtS , dwork ) ; ( void ) memset ( dwork ,
0 , sizeof ( DW ) ) ; } { static DataTypeTransInfo dtInfo ; ( void ) memset (
( char_T * ) & dtInfo , 0 , sizeof ( dtInfo ) ) ; ssSetModelMappingInfo ( rtS
, & dtInfo ) ; dtInfo . numDataTypes = 14 ; dtInfo . dataTypeSizes = &
rtDataTypeSizes [ 0 ] ; dtInfo . dataTypeNames = & rtDataTypeNames [ 0 ] ;
dtInfo . BTransTable = & rtBTransTable ; dtInfo . PTransTable = &
rtPTransTable ; dtInfo . dataTypeInfoTable = rtDataTypeInfoTable ; }
model_InitializeDataMapInfo ( ) ; ssSetIsRapidAcceleratorActive ( rtS , true
) ; ssSetRootSS ( rtS , rtS ) ; ssSetVersion ( rtS , SIMSTRUCT_VERSION_LEVEL2
) ; ssSetModelName ( rtS , "model" ) ; ssSetPath ( rtS , "model" ) ;
ssSetTStart ( rtS , 0.0 ) ; ssSetTFinal ( rtS , 100.0 ) ; { static RTWLogInfo
rt_DataLoggingInfo ; rt_DataLoggingInfo . loggingInterval = NULL ;
ssSetRTWLogInfo ( rtS , & rt_DataLoggingInfo ) ; } { rtliSetLogXSignalInfo (
ssGetRTWLogInfo ( rtS ) , ( NULL ) ) ; rtliSetLogXSignalPtrs (
ssGetRTWLogInfo ( rtS ) , ( NULL ) ) ; rtliSetLogT ( ssGetRTWLogInfo ( rtS )
, "tout" ) ; rtliSetLogX ( ssGetRTWLogInfo ( rtS ) , "" ) ; rtliSetLogXFinal
( ssGetRTWLogInfo ( rtS ) , "" ) ; rtliSetLogVarNameModifier (
ssGetRTWLogInfo ( rtS ) , "none" ) ; rtliSetLogFormat ( ssGetRTWLogInfo ( rtS
) , 4 ) ; rtliSetLogMaxRows ( ssGetRTWLogInfo ( rtS ) , 0 ) ;
rtliSetLogDecimation ( ssGetRTWLogInfo ( rtS ) , 1 ) ; rtliSetLogY (
ssGetRTWLogInfo ( rtS ) , "" ) ; rtliSetLogYSignalInfo ( ssGetRTWLogInfo (
rtS ) , ( NULL ) ) ; rtliSetLogYSignalPtrs ( ssGetRTWLogInfo ( rtS ) , ( NULL
) ) ; } { static struct _ssStatesInfo2 statesInfo2 ; ssSetStatesInfo2 ( rtS ,
& statesInfo2 ) ; } { static ssPeriodicStatesInfo periodicStatesInfo ;
ssSetPeriodicStatesInfo ( rtS , & periodicStatesInfo ) ;
ssSetPeriodicContStateIndices ( rtS , rtPeriodicIndX ) ; ( void ) memset ( (
void * ) rtPeriodicIndX , 0 , 3 * sizeof ( int_T ) ) ;
ssSetPeriodicContStateRanges ( rtS , rtPeriodicRngX ) ; ( void ) memset ( (
void * ) rtPeriodicRngX , 0 , 6 * sizeof ( real_T ) ) ; } { static
ssSolverInfo slvrInfo ; static boolean_T contStatesDisabled [ 31 ] ; static
real_T absTol [ 31 ] = { 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6
, 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 ,
1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 ,
1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 ,
1.0E-6 } ; static uint8_T absTolControl [ 31 ] = { 0U , 0U , 0U , 0U , 0U ,
0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U
, 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U } ; static uint8_T
zcAttributes [ 24 ] = { ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL
) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL )
, ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) ,
( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , (
ZC_EVENT_ALL_UP ) , ( ZC_EVENT_ALL_DN ) , ( ZC_EVENT_ALL ) , (
ZC_EVENT_ALL_UP ) , ( ZC_EVENT_ALL_DN ) , ( ZC_EVENT_ALL ) , (
ZC_EVENT_ALL_UP ) , ( ZC_EVENT_ALL_DN ) , ( ZC_EVENT_ALL ) } ; static
ssNonContDerivSigInfo nonContDerivSigInfo [ 1 ] = { { 4 * sizeof ( real_T ) ,
( char * ) ( & rtB . c0yzmpobn3 [ 0 ] ) , ( NULL ) } } ; ssSetSolverRelTol (
rtS , 0.001 ) ; ssSetStepSize ( rtS , 0.0 ) ; ssSetMinStepSize ( rtS , 0.0 )
; ssSetMaxNumMinSteps ( rtS , - 1 ) ; ssSetMinStepViolatedError ( rtS , 0 ) ;
ssSetMaxStepSize ( rtS , 0.1 ) ; ssSetSolverMaxOrder ( rtS , - 1 ) ;
ssSetSolverRefineFactor ( rtS , 1 ) ; ssSetOutputTimes ( rtS , ( NULL ) ) ;
ssSetNumOutputTimes ( rtS , 0 ) ; ssSetOutputTimesOnly ( rtS , 0 ) ;
ssSetOutputTimesIndex ( rtS , 0 ) ; ssSetZCCacheNeedsReset ( rtS , 0 ) ;
ssSetDerivCacheNeedsReset ( rtS , 0 ) ; ssSetNumNonContDerivSigInfos ( rtS ,
1 ) ; ssSetNonContDerivSigInfos ( rtS , nonContDerivSigInfo ) ;
ssSetSolverInfo ( rtS , & slvrInfo ) ; ssSetSolverName ( rtS ,
"VariableStepAuto" ) ; ssSetVariableStepSolver ( rtS , 1 ) ;
ssSetSolverConsistencyChecking ( rtS , 0 ) ; ssSetSolverAdaptiveZcDetection (
rtS , 0 ) ; ssSetSolverRobustResetMethod ( rtS , 0 ) ; ssSetAbsTolVector (
rtS , absTol ) ; ssSetAbsTolControlVector ( rtS , absTolControl ) ;
ssSetSolverAbsTol_Obsolete ( rtS , absTol ) ;
ssSetSolverAbsTolControl_Obsolete ( rtS , absTolControl ) ;
ssSetSolverStateProjection ( rtS , 0 ) ; ssSetSolverMassMatrixType ( rtS , (
ssMatrixType ) 0 ) ; ssSetSolverMassMatrixNzMax ( rtS , 0 ) ;
ssSetModelOutputs ( rtS , MdlOutputs ) ; ssSetModelLogData ( rtS ,
rt_UpdateTXYLogVars ) ; ssSetModelLogDataIfInInterval ( rtS ,
rt_UpdateTXXFYLogVars ) ; ssSetModelUpdate ( rtS , MdlUpdate ) ;
ssSetModelDerivatives ( rtS , MdlDerivatives ) ; ssSetSolverZcSignalAttrib (
rtS , zcAttributes ) ; ssSetSolverNumZcSignals ( rtS , 24 ) ;
ssSetModelZeroCrossings ( rtS , MdlZeroCrossings ) ;
ssSetSolverConsecutiveZCsStepRelTol ( rtS , 2.8421709430404007E-13 ) ;
ssSetSolverMaxConsecutiveZCs ( rtS , 1000 ) ; ssSetSolverConsecutiveZCsError
( rtS , 2 ) ; ssSetSolverMaskedZcDiagnostic ( rtS , 1 ) ;
ssSetSolverIgnoredZcDiagnostic ( rtS , 1 ) ; ssSetSolverMaxConsecutiveMinStep
( rtS , 1 ) ; ssSetSolverShapePreserveControl ( rtS , 2 ) ; ssSetTNextTid (
rtS , INT_MIN ) ; ssSetTNext ( rtS , rtMinusInf ) ; ssSetSolverNeedsReset (
rtS ) ; ssSetNumNonsampledZCs ( rtS , 24 ) ; ssSetContStateDisabled ( rtS ,
contStatesDisabled ) ; ssSetSolverMaxConsecutiveMinStep ( rtS , 1 ) ; }
ssSetChecksumVal ( rtS , 0 , 444972961U ) ; ssSetChecksumVal ( rtS , 1 ,
4146120540U ) ; ssSetChecksumVal ( rtS , 2 , 2950918377U ) ; ssSetChecksumVal
( rtS , 3 , 2309469585U ) ; { static const sysRanDType rtAlwaysEnabled =
SUBSYS_RAN_BC_ENABLE ; static RTWExtModeInfo rt_ExtModeInfo ; static const
sysRanDType * systemRan [ 16 ] ; gblRTWExtModeInfo = & rt_ExtModeInfo ;
ssSetRTWExtModeInfo ( rtS , & rt_ExtModeInfo ) ;
rteiSetSubSystemActiveVectorAddresses ( & rt_ExtModeInfo , systemRan ) ;
systemRan [ 0 ] = & rtAlwaysEnabled ; systemRan [ 1 ] = ( sysRanDType * ) &
rtDW . pkkgwpmnt2 ; systemRan [ 2 ] = ( sysRanDType * ) & rtDW . jgkdl5lezan
. lzpni3vohm ; systemRan [ 3 ] = ( sysRanDType * ) & rtDW . fieqmbp0km .
lzpni3vohm ; systemRan [ 4 ] = ( sysRanDType * ) & rtDW . nfawadvxsq ;
systemRan [ 5 ] = ( sysRanDType * ) & rtDW . ddqyu2zcpv ; systemRan [ 6 ] = (
sysRanDType * ) & rtDW . iu54wjtvx2 ; systemRan [ 7 ] = ( sysRanDType * ) &
rtDW . cjrmyujqju ; systemRan [ 8 ] = ( sysRanDType * ) & rtDW . ceqnsrmeb1 ;
systemRan [ 9 ] = ( sysRanDType * ) & rtDW . ne00r4ogt0 ; systemRan [ 10 ] =
( sysRanDType * ) & rtDW . lj1lobgjwr ; systemRan [ 11 ] = ( sysRanDType * )
& rtDW . pfnakgwhvn ; systemRan [ 12 ] = ( sysRanDType * ) & rtDW .
gs4wlth0q0 ; systemRan [ 13 ] = ( sysRanDType * ) & rtDW . osdasmnnlg ;
systemRan [ 14 ] = ( sysRanDType * ) & rtDW . feainkhr2c ; systemRan [ 15 ] =
( sysRanDType * ) & rtDW . kscxtxtsbw ; rteiSetModelMappingInfoPtr (
ssGetRTWExtModeInfo ( rtS ) , & ssGetModelMappingInfo ( rtS ) ) ;
rteiSetChecksumsPtr ( ssGetRTWExtModeInfo ( rtS ) , ssGetChecksums ( rtS ) )
; rteiSetTPtr ( ssGetRTWExtModeInfo ( rtS ) , ssGetTPtr ( rtS ) ) ; } rtP .
uftinf_UpperSat = rtInf ; return rtS ; }
#if defined(_MSC_VER)
#pragma optimize( "", on )
#endif
const int_T gblParameterTuningTid = 3 ; void MdlOutputsParameterSampleTime (
int_T tid ) { MdlOutputsTID3 ( tid ) ; }
