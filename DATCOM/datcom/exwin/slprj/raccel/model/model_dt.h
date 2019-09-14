#include "__cf_model.h"
#include "ext_types.h"
static DataTypeInfo rtDataTypeInfoTable [ ] = { { "real_T" , 0 , 8 } , {
"real32_T" , 1 , 4 } , { "int8_T" , 2 , 1 } , { "uint8_T" , 3 , 1 } , {
"int16_T" , 4 , 2 } , { "uint16_T" , 5 , 2 } , { "int32_T" , 6 , 4 } , {
"uint32_T" , 7 , 4 } , { "boolean_T" , 8 , 1 } , { "fcn_call_T" , 9 , 0 } , {
"int_T" , 10 , 4 } , { "pointer_T" , 11 , 8 } , { "action_T" , 12 , 8 } , {
"timer_uint32_pair_T" , 13 , 8 } } ; static uint_T rtDataTypeSizes [ ] = {
sizeof ( real_T ) , sizeof ( real32_T ) , sizeof ( int8_T ) , sizeof (
uint8_T ) , sizeof ( int16_T ) , sizeof ( uint16_T ) , sizeof ( int32_T ) ,
sizeof ( uint32_T ) , sizeof ( boolean_T ) , sizeof ( fcn_call_T ) , sizeof (
int_T ) , sizeof ( pointer_T ) , sizeof ( action_T ) , 2 * sizeof ( uint32_T
) } ; static const char_T * rtDataTypeNames [ ] = { "real_T" , "real32_T" ,
"int8_T" , "uint8_T" , "int16_T" , "uint16_T" , "int32_T" , "uint32_T" ,
"boolean_T" , "fcn_call_T" , "int_T" , "pointer_T" , "action_T" ,
"timer_uint32_pair_T" } ; static DataTypeTransition rtBTransitions [ ] = { {
( char_T * ) ( & rtB . dzs1soumuc [ 0 ] ) , 0 , 0 , 642 } , { ( char_T * ) (
& rtB . guh13rgg0c ) , 7 , 0 , 2 } , { ( char_T * ) ( & rtB . burumew3sb ) ,
6 , 0 , 3 } , { ( char_T * ) ( & rtB . b25nd1ut2t ) , 8 , 0 , 3 } , { (
char_T * ) ( & rtB . fieqmbp0km . bkh4ie4vlq ) , 0 , 0 , 1 } , { ( char_T * )
( & rtB . jgkdl5lezan . bkh4ie4vlq ) , 0 , 0 , 1 } , { ( char_T * ) ( & rtDW
. e5dwuk5zfi [ 0 ] ) , 0 , 0 , 13 } , { ( char_T * ) ( & rtDW . j3aywkmo1f .
LoggedData ) , 11 , 0 , 1 } , { ( char_T * ) ( & rtDW . m0wkbsdvjm ) , 6 , 0
, 3 } , { ( char_T * ) ( & rtDW . ltv3hasgw5 ) , 7 , 0 , 7 } , { ( char_T * )
( & rtDW . g4ktzwz3i1 ) , 10 , 0 , 6 } , { ( char_T * ) ( & rtDW . nx5ne33bex
) , 2 , 0 , 28 } , { ( char_T * ) ( & rtDW . ek25wc14yf ) , 8 , 0 , 8 } , { (
char_T * ) ( & rtDW . fieqmbp0km . cztgqg1pxv ) , 10 , 0 , 1 } , { ( char_T *
) ( & rtDW . fieqmbp0km . lzpni3vohm ) , 2 , 0 , 1 } , { ( char_T * ) ( &
rtDW . fieqmbp0km . hndz0ioosi ) , 8 , 0 , 1 } , { ( char_T * ) ( & rtDW .
jgkdl5lezan . cztgqg1pxv ) , 10 , 0 , 1 } , { ( char_T * ) ( & rtDW .
jgkdl5lezan . lzpni3vohm ) , 2 , 0 , 1 } , { ( char_T * ) ( & rtDW .
jgkdl5lezan . hndz0ioosi ) , 8 , 0 , 1 } } ; static DataTypeTransitionTable
rtBTransTable = { 19U , rtBTransitions } ; static DataTypeTransition
rtPTransitions [ ] = { { ( char_T * ) ( & rtP . DiscreteWindGustModel_Gx ) ,
0 , 0 , 5159 } , { ( char_T * ) ( & rtP .
MediumHighAltitudeIntensity_maxIndex [ 0 ] ) , 7 , 0 , 47 } , { ( char_T * )
( & rtP . fieqmbp0km . x_Y0 ) , 0 , 0 , 3 } , { ( char_T * ) ( & rtP .
jgkdl5lezan . x_Y0 ) , 0 , 0 , 3 } } ; static DataTypeTransitionTable
rtPTransTable = { 4U , rtPTransitions } ;
