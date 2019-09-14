#include "__cf_model.h"
#ifndef RTW_HEADER_model_h_
#define RTW_HEADER_model_h_
#include <string.h>
#include <stddef.h>
#include "rtw_modelmap.h"
#ifndef model_COMMON_INCLUDES_
#define model_COMMON_INCLUDES_
#include <stdlib.h>
#include "rtwtypes.h"
#include "simtarget/slSimTgtSigstreamRTW.h"
#include "simtarget/slSimTgtSlioCoreRTW.h"
#include "simtarget/slSimTgtSlioClientsRTW.h"
#include "simtarget/slSimTgtSlioSdiRTW.h"
#include "sigstream_rtw.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "raccel.h"
#include "slsv_diagnostic_codegen_c_api.h"
#include "rt_logging.h"
#include "dt_info.h"
#include "ext_work.h"
#endif
#include "model_types.h"
#include "multiword_types.h"
#include "mwmathutil.h"
#include "rtGetInf.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#define MODEL_NAME model
#define NSAMPLE_TIMES (4) 
#define NINPUTS (0)       
#define NOUTPUTS (0)     
#define NBLOCKIO (294) 
#define NUM_ZC_EVENTS (0) 
#ifndef NCSTATES
#define NCSTATES (31)   
#elif NCSTATES != 31
#error Invalid specification of NCSTATES defined in compiler command
#endif
#ifndef rtmGetDataMapInfo
#define rtmGetDataMapInfo(rtm) (*rt_dataMapInfoPtr)
#endif
#ifndef rtmSetDataMapInfo
#define rtmSetDataMapInfo(rtm, val) (rt_dataMapInfoPtr = &val)
#endif
#ifndef IN_RACCEL_MAIN
#endif
typedef struct { real_T bkh4ie4vlq ; } n2tntgetox ; typedef struct { int_T
cztgqg1pxv ; int8_T lzpni3vohm ; boolean_T hndz0ioosi ; } p1vyesmn13 ;
typedef struct { real_T b1gdrvpzrw ; } clzm13mi24 ; typedef struct { real_T
b1gdrvpzrw ; } esw4djegcl ; typedef struct { boolean_T b1gdrvpzrw ; }
lrakgivbxx ; typedef struct { real_T b1gdrvpzrw ; } a221ytlprn ; typedef
struct { real_T infz0h0a5x ; real_T ol42gnqx3d ; real_T lf0y5uqnvy ; }
hzlzoncq5o ; typedef struct { real_T dzs1soumuc [ 3 ] ; real_T islqk3d2pc [ 3
] ; real_T nliw1cuyp4 [ 3 ] ; real_T fnmpprt3rb [ 3 ] ; real_T n2gibbklhx [ 9
] ; real_T mycisuihic [ 9 ] ; real_T bxute4gwb3 [ 3 ] ; real_T ks25o2ves0 [ 3
] ; real_T ktmthpvsav ; real_T g0uv0nbjrn ; real_T hwshuznfry ; real_T
gyvp0nr1ic ; real_T fpjovq1wmk ; real_T ewye0ur1dg ; real_T fkybzc33mt ;
real_T b21axyrc0y ; real_T h0chbuggcq ; real_T odqt54fd3r ; real_T iwsvf4t0jp
; real_T ijj1ba05uy ; real_T ney5ntjpte ; real_T dx5g5jxszw [ 3 ] ; real_T
k3tn4bbpdh [ 3 ] ; real_T gtav0xroqm [ 3 ] ; real_T pg1uquivv5 ; real_T
optvc153u0 ; real_T ie5ujfwk1t ; real_T in1jikpuyp ; real_T lweizeobnn [ 2 ]
; real_T k1qm14mokl ; real_T pba0balycr ; real_T m4ioj5ifig ; real_T
bsrwvm2oyt ; real_T iw50kb54tc [ 4 ] ; real_T c0yzmpobn3 [ 4 ] ; real_T
apsbh2a4ml ; real_T p5dpqn0t0m ; real_T fkpy3ggxgw ; real_T lklogdjcfo ;
real_T bdqq1m4fup [ 2 ] ; real_T mdfbuebpbf [ 3 ] ; real_T i5asy1ic4l [ 3 ] ;
real_T jayfpbovsb ; real_T etz0t5ppwo ; real_T htbwrd0zad ; real_T kbexovbmwl
; real_T pwozxpkovz ; real_T hnfbrhdub5 [ 3 ] ; real_T na2v1kjbp5 [ 3 ] ;
real_T gtph1dwlhy [ 3 ] ; real_T cis0kg11y4 [ 3 ] ; real_T nzoyizvn0g [ 3 ] ;
real_T pnx4iii03b [ 3 ] ; real_T mrsrezbuqk [ 9 ] ; real_T jjyzm5cerc [ 3 ] ;
real_T k4efj0wbom ; real_T abq35lnui2 ; real_T pwkjv4lxgw ; real_T fhjxy5zb5a
; real_T aami4huvyy ; real_T bdaejykwvz ; real_T o54r3adnq1 [ 3 ] ; real_T
bwcottfiut [ 9 ] ; real_T j55tg2sijl [ 3 ] ; real_T dsk4lj4maj [ 9 ] ; real_T
e4f4cr5zbc [ 3 ] ; real_T a5q0gsfmw5 [ 9 ] ; real_T jymybd53fk [ 9 ] ; real_T
fwuesmfvmw [ 3 ] ; real_T ee4hwukkci ; real_T llhvjlhy3a ; real_T no1ukhz2or
; real_T lw3rqy0i2p ; real_T gzwn4wvhu5 ; real_T ltux4bsueq ; real_T
lcss4j1rsb ; real_T oovkaz423b ; real_T cdvlb44lh3 ; real_T ewv4vlunrf ;
real_T o402scsdlq ; real_T dsfnt4ckk0 ; real_T deyrabdk0p ; real_T ew4bp2hsh4
; real_T fghbljyvca ; real_T n0yew4kwsy ; real_T l1czztlzln ; real_T
kn3vx2wdwp ; real_T iv0iqohpcq ; real_T nqhs2mtakg ; real_T mddzbq4nmv ;
real_T c5nk0hb2bd ; real_T dkjk3aymc3 ; real_T k4vi5txoqv ; real_T jeow23fizp
[ 3 ] ; real_T g4ixw2ju0a [ 3 ] ; real_T clsso41xlk [ 9 ] ; real_T diwxdnf4dg
[ 3 ] ; real_T m43khr12tv [ 3 ] ; real_T oq23oeketq ; real_T ambckm20k4 ;
real_T if2tkmjk5a ; real_T jhnqdtipvy ; real_T mmnv4q2o2x ; real_T dr2gm5cuey
; real_T fhapciging [ 3 ] ; real_T b4ff4mfmin ; real_T huplh2ovz1 ; real_T
dtay24vczs ; real_T flfgzaiek3 ; real_T p0xy05kpqr ; real_T kuokdfsr0b [ 3 ]
; real_T muyb1go0zp [ 3 ] ; real_T haarcsgs3r [ 3 ] ; real_T gb1h1tviap [ 3 ]
; real_T bltg1ofzuh [ 9 ] ; real_T mddt1rvp3v [ 9 ] ; real_T mwuv02g011 ;
real_T d3um45fosu ; real_T nw0lnpybdj [ 2 ] ; real_T fy3whyspik ; real_T
nveqijgo2a ; real_T ewoylkmqxc [ 9 ] ; real_T dhy5sl1c4z ; real_T cdrl4nzwfz
; real_T h1rmkjrkmq ; real_T kp24wjtakv ; real_T hmgj5nsbpj [ 3 ] ; real_T
poq3sq0itr [ 3 ] ; real_T fui5djlzoo ; real_T kkxd3tikbn ; real_T hmi4l5cfx0
; real_T dtsa0qdpmd ; real_T n1pgu24wwz ; real_T adbita3g4i ; real_T
gb0mdchddg ; real_T gspj4vw5g2 ; real_T i12dfhokz1 [ 2 ] ; real_T aokxroo1bz
; real_T hyd1pi2bmq ; real_T csyxoinipa ; real_T adcuqjpjfk ; real_T
dfv5zlgscv ; real_T m0mnsmhzee ; real_T hqz5grr5x5 ; real_T nvp5xdnq4m ;
real_T aoguormswf [ 2 ] ; real_T ku2mt5oq34 ; real_T ok4uvdpxny [ 6 ] ;
real_T mvem5vfcmh ; real_T mqdmh5qxvd ; real_T jranmezdtp ; real_T elj1og2hw2
; real_T oykwjbf0l2 [ 6 ] ; real_T mjvjidnmqy [ 3 ] ; real_T d1znscnd2p [ 3 ]
; real_T bkeumodt1t [ 9 ] ; real_T mjh3qtkwwe [ 3 ] ; real_T kl54abxyyo [ 3 ]
; real_T na33cozjmh ; real_T gy531db5ab ; real_T n00wehaagy ; real_T
hsc0hjfp4c ; real_T ju4uigrkf5 ; real_T ikfhliwvmn ; real_T chj2lnrtdr [ 3 ]
; real_T d53l1o1puh [ 3 ] ; real_T khtpgpvqjl [ 3 ] ; real_T fkghwm5gsz [ 3 ]
; real_T cugpw2oaop [ 3 ] ; real_T f5hluqgotp [ 3 ] ; real_T hg2rkm0b0a ;
real_T eas3pz0d31 [ 3 ] ; real_T jewko3ql0j [ 3 ] ; real_T boldxgnyxd [ 3 ] ;
real_T ogjmkxrtzk ; real_T acnxtf0njr ; real_T apvxa3vvr5 ; real_T o5is4gwrz1
; real_T a2r2bsx5op ; real_T iknur005un ; real_T ltisnx0tk2 [ 3 ] ; real_T
hnflxg3oyc [ 3 ] ; real_T ahalic5glf [ 3 ] ; real_T gbi1feu30l [ 3 ] ; real_T
lsixin3gz1 [ 3 ] ; real_T bhsoq03twv [ 3 ] ; real_T ph3xybkpn3 [ 3 ] ; real_T
ooprpnnz1m [ 9 ] ; real_T hlwx1xld4v [ 3 ] ; real_T iglnjbiqey [ 9 ] ; real_T
iylzbmkgfi [ 9 ] ; real_T ntlxpgwfz1 [ 3 ] ; real_T er0wsgu0uz [ 9 ] ; real_T
nqqzwty3zs [ 9 ] ; real_T cavyfym52n [ 3 ] ; real_T lhmph3qfyb [ 3 ] ; real_T
jhpnbmxx5n [ 3 ] ; real_T cp032iv5kb ; real_T p5lvunc4gi [ 3 ] ; real_T
f3tffkcsn4 [ 3 ] ; real_T pytois5kxe ; real_T dj5opchr3c ; real_T hjgda4lsay
; real_T pf1sahzmz5 ; real_T j0zjfcbwwv ; real_T hogqcx5gkm ; real_T
pqmqi1ih0x [ 3 ] ; real_T orhueszosr [ 3 ] ; real_T iwoj22k0me [ 2 ] ; real_T
hwhw1vlr4q [ 2 ] ; real_T bhyqpcr3sv [ 3 ] ; real_T pfqekgkkul [ 3 ] ; real_T
m0012em1dm [ 3 ] ; real_T edfjbabvwj ; real_T h5wwlzhkjq ; real_T ocqymszfcg
[ 3 ] ; real_T mt2kbdde1u [ 2 ] ; real_T hlywm50421 [ 2 ] ; real_T bkjlztmjbx
[ 3 ] ; real_T g2ol2zgsoe [ 3 ] ; real_T lez1v1wcmt [ 2 ] ; real_T jtve1smewc
[ 2 ] ; real_T fwd0zho2dx [ 3 ] ; real_T pqzxc0jwxr [ 3 ] ; real_T n2ablemxjo
[ 3 ] ; real_T lgsfqf2gng ; real_T obpi4pygmr ; real_T bvoynuyjfa [ 3 ] ;
real_T p4yyhd2kug [ 2 ] ; real_T bv3tfatqfb [ 2 ] ; real_T eqg4nglih0 [ 3 ] ;
real_T gynkhxmcfk [ 3 ] ; real_T clyzpdujo2 [ 2 ] ; real_T nmo53ueedw [ 2 ] ;
real_T pcg1z1bmhq [ 2 ] ; real_T lq0mfgsqfo [ 2 ] ; real_T adrc4dh4xz [ 2 ] ;
real_T maka3wnq5n [ 2 ] ; real_T b4p0x5sch3 ; real_T cayuqvyp2b [ 2 ] ;
real_T on0w3ltr4i [ 2 ] ; real_T gunypeaovn [ 2 ] ; real_T jokuewxh0b [ 2 ] ;
real_T pxqxqpltfm [ 2 ] ; real_T fmyvw4bkag [ 2 ] ; real_T ivknkgdhps [ 2 ] ;
real_T mmtxyw115q [ 2 ] ; real_T oprrh1lrfg [ 2 ] ; real_T ealls03ntz [ 2 ] ;
real_T cmdkij32ho [ 2 ] ; real_T gdx0qpo30e [ 2 ] ; real_T bqywvwxy2u [ 2 ] ;
real_T md41g5fldt [ 2 ] ; real_T ke0ksubsuu [ 2 ] ; real_T fmytsanjo2 [ 2 ] ;
real_T joo0gvrcnf [ 2 ] ; real_T h2tissrusk [ 2 ] ; real_T beaa0ietcq [ 2 ] ;
real_T bph5jjv2nj [ 2 ] ; real_T jj1mymkjgz [ 2 ] ; real_T etpdtmtrnf [ 2 ] ;
real_T igi43iu4gc [ 2 ] ; real_T iihgtnzfrf [ 2 ] ; real_T j5rmezwb0e [ 2 ] ;
real_T fg2kqgg3ek [ 2 ] ; real_T fjkfysvnh3 [ 2 ] ; real_T fjfsy0b0jg ;
real_T b2e3g5hpyo [ 2 ] ; real_T lazwt4wtdp [ 2 ] ; real_T b1khfo1ad3 [ 2 ] ;
real_T fr0lgjauqr [ 2 ] ; real_T dt4hmrvy0i ; real_T oum15dzd35 [ 2 ] ;
real_T buysvvpcb4 ; real_T o1xsnq5r4j ; real_T cfsazsff55 [ 2 ] ; real_T
e40fmoqlfe [ 2 ] ; real_T gzz55ngh4d [ 2 ] ; real_T of5hnba1qi [ 2 ] ; real_T
cr4rspe1f1 [ 2 ] ; real_T mfxy45ba4c [ 2 ] ; real_T p3bdm41p1x ; real_T
hbksfryqsi [ 2 ] ; real_T juld5yz3om ; uint32_T guh13rgg0c ; uint32_T
kjfzsflye3 ; int32_T burumew3sb ; int32_T dpmiotlnvk ; int32_T kcp5vlmrhn ;
boolean_T b25nd1ut2t ; boolean_T oeyxyxnkxg ; boolean_T owpauozhbv ;
n2tntgetox fieqmbp0km ; n2tntgetox jgkdl5lezan ; } B ; typedef struct {
real_T e5dwuk5zfi [ 4 ] ; real_T lb14r5vg2a [ 9 ] ; struct { void *
LoggedData ; } j3aywkmo1f ; int32_T m0wkbsdvjm ; int32_T pfswjzddny ; int32_T
bweuyeryhh ; uint32_T ltv3hasgw5 ; uint32_T g4kd5mgehq ; uint32_T o2m0ho4ib0
[ 4 ] ; uint32_T cgeqxzgrnv ; int_T g4ktzwz3i1 ; int_T ofhki50iy1 ; int_T
ifz1r4v4pr ; int_T ia5fgrdrmk ; int_T oqzl4vaurj ; int_T jqsfntesyx ; int8_T
nx5ne33bex ; int8_T jusb02f5rj ; int8_T nhbi5jh4go ; int8_T ag2s0tuis0 ;
int8_T kpq2e44z2g ; int8_T amv55hlazd ; int8_T kpnxk2wxcb ; int8_T ir0jb20k33
; int8_T cnovvjoyyp ; int8_T pgykvwqmc3 ; int8_T ftwguoefpc ; int8_T
osdasmnnlg ; int8_T kscxtxtsbw ; int8_T feainkhr2c ; int8_T lj1lobgjwr ;
int8_T gs4wlth0q0 ; int8_T pfnakgwhvn ; int8_T ne00r4ogt0 ; int8_T jjjovfqaio
; int8_T euk35lqnv1 ; int8_T ceqnsrmeb1 ; int8_T fg0n3tzsij ; int8_T
cjrmyujqju ; int8_T ptevicn33b ; int8_T iu54wjtvx2 ; int8_T ddqyu2zcpv ;
int8_T nfawadvxsq ; int8_T pkkgwpmnt2 ; boolean_T ek25wc14yf ; boolean_T
ptxtk1nv30 ; boolean_T nhrxrmv3xz ; boolean_T gjeq11lqni ; boolean_T
dtbuv1dhzu ; boolean_T dsenq15ybl ; boolean_T ekhaunodew ; boolean_T
f3e4goswub ; p1vyesmn13 fieqmbp0km ; p1vyesmn13 jgkdl5lezan ; } DW ; typedef
struct { real_T gw2wykgqi1 [ 3 ] ; real_T k1ode521ap [ 3 ] ; real_T
iuemkmhnjl [ 3 ] ; real_T cjakaafmng [ 3 ] ; real_T pxrnvzd5eg [ 2 ] ; real_T
dolulbw4pb [ 2 ] ; real_T fbih5gck0s [ 2 ] ; real_T moa44kkouk [ 2 ] ; real_T
cnbgfejjbm [ 2 ] ; real_T dydkrcbic2 [ 2 ] ; real_T cgba0qyovs [ 2 ] ; real_T
f4qi5fjsdf [ 2 ] ; clzm13mi24 fieqmbp0km ; clzm13mi24 jgkdl5lezan ; real_T
bm4wjkp3hh ; } X ; typedef int_T PeriodicIndX [ 3 ] ; typedef real_T
PeriodicRngX [ 6 ] ; typedef struct { real_T gw2wykgqi1 [ 3 ] ; real_T
k1ode521ap [ 3 ] ; real_T iuemkmhnjl [ 3 ] ; real_T cjakaafmng [ 3 ] ; real_T
pxrnvzd5eg [ 2 ] ; real_T dolulbw4pb [ 2 ] ; real_T fbih5gck0s [ 2 ] ; real_T
moa44kkouk [ 2 ] ; real_T cnbgfejjbm [ 2 ] ; real_T dydkrcbic2 [ 2 ] ; real_T
cgba0qyovs [ 2 ] ; real_T f4qi5fjsdf [ 2 ] ; esw4djegcl fieqmbp0km ;
esw4djegcl jgkdl5lezan ; real_T bm4wjkp3hh ; } XDot ; typedef struct {
boolean_T gw2wykgqi1 [ 3 ] ; boolean_T k1ode521ap [ 3 ] ; boolean_T
iuemkmhnjl [ 3 ] ; boolean_T cjakaafmng [ 3 ] ; boolean_T pxrnvzd5eg [ 2 ] ;
boolean_T dolulbw4pb [ 2 ] ; boolean_T fbih5gck0s [ 2 ] ; boolean_T
moa44kkouk [ 2 ] ; boolean_T cnbgfejjbm [ 2 ] ; boolean_T dydkrcbic2 [ 2 ] ;
boolean_T cgba0qyovs [ 2 ] ; boolean_T f4qi5fjsdf [ 2 ] ; lrakgivbxx
fieqmbp0km ; lrakgivbxx jgkdl5lezan ; boolean_T bm4wjkp3hh ; } XDis ; typedef
struct { real_T gw2wykgqi1 [ 3 ] ; real_T k1ode521ap [ 3 ] ; real_T
iuemkmhnjl [ 3 ] ; real_T cjakaafmng [ 3 ] ; real_T pxrnvzd5eg [ 2 ] ; real_T
dolulbw4pb [ 2 ] ; real_T fbih5gck0s [ 2 ] ; real_T moa44kkouk [ 2 ] ; real_T
cnbgfejjbm [ 2 ] ; real_T dydkrcbic2 [ 2 ] ; real_T cgba0qyovs [ 2 ] ; real_T
f4qi5fjsdf [ 2 ] ; a221ytlprn fieqmbp0km ; a221ytlprn jgkdl5lezan ; real_T
bm4wjkp3hh ; } CStateAbsTol ; typedef struct { real_T b2kg42njue ; real_T
jpum5yibxj ; real_T gr5xaxjmde ; real_T dhhprfuhty ; real_T d4idjyzl44 ;
real_T dmnsxb2hh5 ; real_T fpe1d4ebxe ; real_T osja2jmxmf ; real_T fbzhg1da5b
; real_T jxxwmu2g4b [ 2 ] ; real_T drzgaixt5q [ 2 ] ; real_T i3a5htr4m5 ;
real_T lxy52t3qfy ; hzlzoncq5o fieqmbp0km ; hzlzoncq5o jgkdl5lezan ; real_T
brii3ajf2q ; real_T ixxi1jmjzk ; real_T hguajj4maw ; } ZCV ; typedef struct {
rtwCAPI_ModelMappingInfo mmi ; } DataMapInfo ; struct la53pg24sw_ { real_T
x_Y0 ; real_T DistanceintoGustxLimitedtogustlengthd_IC ; real_T
DistanceintoGustxLimitedtogustlengthd_LowerSat ; } ; struct P_ { real_T
DiscreteWindGustModel_Gx ; real_T DiscreteWindGustModel_Gy ; real_T
DiscreteWindGustModel_Gz ; real_T
DrydenWindTurbulenceModelContinuousqr_L_high ; real_T
AerodynamicForcesandMoments_S ; real_T
AerodynamicForcesandMoments_S_irg2e3bjgp ; real_T
AerodynamicForcesandMoments_S_haf3wauqag ; real_T
DrydenWindTurbulenceModelContinuousqr_Seed [ 4 ] ; real_T
DrydenWindTurbulenceModelContinuousqr_T_on ; real_T WhiteNoise_Ts ; real_T
DrydenWindTurbulenceModelContinuousqr_TurbProb ; real_T uDOFEulerAngles_Vm_0
[ 3 ] ; real_T DrydenWindTurbulenceModelContinuousqr_W20 ; real_T
WindShearModel_W_20 ; real_T DrydenWindTurbulenceModelContinuousqr_Wdeg ;
real_T WindShearModel_Wdeg ; real_T
DrydenWindTurbulenceModelContinuousqr_Wingspan ; real_T
AerodynamicForcesandMoments_b ; real_T
AerodynamicForcesandMoments_b_a2pcrfjg54 ; real_T
AerodynamicForcesandMoments_b_efeekaqk2w ; real_T
AerodynamicForcesandMoments_cbar ; real_T
AerodynamicForcesandMoments_cbar_h4kwacm43q ; real_T
AerodynamicForcesandMoments_cbar_miyvp11bgo ; real_T Distanceintogustx_d_m ;
real_T Distanceintogusty_d_m ; real_T Distanceintogustz_d_m ; real_T
DiscreteWindGustModel_d_m [ 3 ] ; real_T uDOFEulerAngles_eul_0 [ 3 ] ; real_T
uDOFEulerAngles_inertia [ 9 ] ; real_T uDOFEulerAngles_mass_0 ; real_T
uDOFEulerAngles_pm_0 [ 3 ] ; real_T WhiteNoise_pwr [ 4 ] ; real_T
DiscreteWindGustModel_t_0 ; real_T DiscreteWindGustModel_v_m [ 3 ] ; real_T
uDOFEulerAngles_xme_0 [ 3 ] ; real_T x_Y0 ; real_T
DistanceintoGustxLimitedtogustlengthd_IC ; real_T
DistanceintoGustxLimitedtogustlengthd_LowerSat ; real_T pgw_Y0 ; real_T
Constant1_Value ; real_T Constant2_Value ; real_T Constant3_Value ; real_T
pgw_p_IC ; real_T qgw_Y0 ; real_T qgw_p_IC ; real_T pi4_Gain ; real_T rgw_Y0
; real_T rgw_p_IC ; real_T pi3_Gain ; real_T ugw_Y0 ; real_T upi_Gain ;
real_T ug_p_IC ; real_T vgw_Y0 ; real_T upi_Gain_gy2nvc1rod ; real_T vg_p1_IC
; real_T vgw_p2_IC ; real_T sqrt3_Gain ; real_T wgw_Y0 ; real_T
upi_Gain_cv3kqumzgv ; real_T Constant_Value ; real_T wg_p1_IC ; real_T
wg_p2_IC ; real_T Gain_Gain ; real_T max_height_low_Value ; real_T
min_height_high_Value ; real_T Gain_Gain_hwyillaq5v ; real_T
max_height_low_Value_lykhpozz3y ; real_T min_height_high_Value_f0iqsahu4c ;
real_T Constant_Value_d1htqtqh1y [ 4 ] ; real_T
phithetapsi_WrappedStateUpperValue ; real_T
phithetapsi_WrappedStateLowerValue ; real_T SeaLevelTemperature_Value ;
real_T Limitaltitudetotroposhere_UpperSat ; real_T
Limitaltitudetotroposhere_LowerSat ; real_T LapseRate_Gain ; real_T uT0_Gain
; real_T Constant_Value_d2f1ederhe ; real_T AltitudeofTroposphere_Value ;
real_T LimitaltitudetoStratosphere_UpperSat ; real_T
LimitaltitudetoStratosphere_LowerSat ; real_T gR_Gain ; real_T rho0_Gain ;
real_T gammaR_Gain ; real_T u_Value ; real_T
LimitFunction10ftto1000ft_UpperSat ; real_T
LimitFunction10ftto1000ft_LowerSat ; real_T Lw_Gain ; real_T sigma_wg_Gain ;
real_T PreLookUpIndexSearchaltitude_BreakpointsData [ 12 ] ; real_T
PreLookUpIndexSearchprobofexceed_BreakpointsData [ 7 ] ; real_T
MediumHighAltitudeIntensity_Table [ 84 ] ; real_T WhiteNoise_Mean ; real_T
WhiteNoise_StdDev ; real_T LimitHeighth1000ft_UpperSat ; real_T
LimitHeighth1000ft_LowerSat ; real_T Lv_Gain ; real_T uftinf_UpperSat ;
real_T uftinf_LowerSat ; real_T hz0_Gain ; real_T ref_heightz0_Value ; real_T
Wdeg1_Value ; real_T Constant2_Value_nvqbu4imhl [ 9 ] ; real_T
Constant_Value_bjnypp3rh0 [ 9 ] ; real_T Constant1_Value_e4n53dlcvq ; real_T
Constant_Value_m5ji3jk5ts ; real_T Constant2_Value_pnmq1xmzoy ; real_T
Constant4_Value ; real_T Constant3_Value_py4vyr01be ; real_T u2rhoV2_Gain ;
real_T alpha_BreakpointsData [ 10 ] ; real_T Mach_BreakpointsData [ 4 ] ;
real_T altitude_BreakpointsData [ 8 ] ; real_T CD_Table [ 320 ] ; real_T
CYb_Table [ 320 ] ; real_T CL_Table [ 320 ] ; real_T coefAdjust_Gain [ 3 ] ;
real_T Constant1_Value_bllnswxjjm ; real_T Constant_Value_gvjlparkjc ; real_T
Constant2_Value_ewaxby0wwz ; real_T Constant4_Value_jw4i4dtkq1 ; real_T
Constant3_Value_aowcwxcrv4 ; real_T zero3_Value [ 3 ] ; real_T Clb_Table [
320 ] ; real_T Cm_Table [ 320 ] ; real_T Cnb_Table [ 320 ] ; real_T
Constant1_Value_dkxf1g33uf ; real_T Constant_Value_n2pgnoma5y ; real_T
Constant2_Value_a1organdvp ; real_T Constant4_Value_mowtqh2zd2 ; real_T
Constant3_Value_n2x4c42jkt ; real_T zero_Value ; real_T CYp_Table [ 320 ] ;
real_T u_Value_fiovphx5x3 ; real_T Constant_Value_lnzqsdhb20 ; real_T
u_Value_aardduo22y ; real_T Constant_Value_lqmbfph4ah ; real_T CLad_Table [
320 ] ; real_T CLq_Table [ 320 ] ; real_T Clp_Table [ 320 ] ; real_T
Clr_Table [ 320 ] ; real_T Cmq_Table [ 320 ] ; real_T Cmad_Table [ 320 ] ;
real_T Cnp_Table [ 320 ] ; real_T Cnr_Table [ 320 ] ; real_T Gain1_Gain [ 6 ]
; real_T u_Value_axd001kf0t ; real_T coefAdjust_Gain_d5gkknnahd [ 3 ] ;
real_T Constant1_Value_kfsbs5wuhz ; real_T Constant_Value_feqzr4eans ; real_T
Constant2_Value_agtqtjm4z1 ; real_T Constant4_Value_pnrru5m0fs ; real_T
Constant3_Value_lnoybacp11 ; real_T zero1_Value [ 3 ] ; real_T
Constant2_Value_pjsapbkri4 [ 6 ] ; real_T coefAdjust_Gain_i4hwujqkud [ 3 ] ;
real_T Constant1_Value_az5chewn2m [ 3 ] ; real_T Constant_Value_cbj5azvbu2 [
3 ] ; real_T Moments_Value [ 3 ] ; real_T Constant1_Value_cy5z4hcsl3 ; real_T
Constant_Value_ea5rkpodns ; real_T Constant2_Value_epbnzx0ky0 ; real_T
Constant4_Value_atc41zi2ir ; real_T Constant3_Value_jmheminny5 ; real_T
Constant1_Value_ndgxvb4zwb ; real_T Constant_Value_m1jhswm2a4 ; real_T
Constant2_Value_ogp3xqdtea ; real_T Constant4_Value_gcn5uwst2a ; real_T
Constant3_Value_oqhlderhny ; real_T ThrustX_tableData [ 7 ] ; real_T
ThrustX_bp01Data [ 7 ] ; real_T TyTz_Value [ 2 ] ; uint32_T
MediumHighAltitudeIntensity_maxIndex [ 2 ] ; uint32_T CD_dimSize [ 3 ] ;
uint32_T CYb_dimSize [ 3 ] ; uint32_T CL_dimSize [ 3 ] ; uint32_T Clb_dimSize
[ 3 ] ; uint32_T Cm_dimSize [ 3 ] ; uint32_T Cnb_dimSize [ 3 ] ; uint32_T
CYp_dimSize [ 3 ] ; uint32_T CLad_dimSize [ 3 ] ; uint32_T CLq_dimSize [ 3 ]
; uint32_T Clp_dimSize [ 3 ] ; uint32_T Clr_dimSize [ 3 ] ; uint32_T
Cmq_dimSize [ 3 ] ; uint32_T Cmad_dimSize [ 3 ] ; uint32_T Cnp_dimSize [ 3 ]
; uint32_T Cnr_dimSize [ 3 ] ; la53pg24sw fieqmbp0km ; la53pg24sw jgkdl5lezan
; } ; extern const char * RT_MEMORY_ALLOCATION_ERROR ; extern B rtB ; extern
X rtX ; extern DW rtDW ; extern P rtP ; extern const
rtwCAPI_ModelMappingStaticInfo * model_GetCAPIStaticMap ( void ) ; extern
SimStruct * const rtS ; extern const int_T gblNumToFiles ; extern const int_T
gblNumFrFiles ; extern const int_T gblNumFrWksBlocks ; extern rtInportTUtable
* gblInportTUtables ; extern const char * gblInportFileName ; extern const
int_T gblNumRootInportBlks ; extern const int_T gblNumModelInputs ; extern
const int_T gblInportDataTypeIdx [ ] ; extern const int_T gblInportDims [ ] ;
extern const int_T gblInportComplex [ ] ; extern const int_T
gblInportInterpoFlag [ ] ; extern const int_T gblInportContinuous [ ] ;
extern const int_T gblParameterTuningTid ; extern DataMapInfo *
rt_dataMapInfoPtr ; extern rtwCAPI_ModelMappingInfo * rt_modelMapInfoPtr ;
void MdlOutputs ( int_T tid ) ; void MdlOutputsParameterSampleTime ( int_T
tid ) ; void MdlUpdate ( int_T tid ) ; void MdlTerminate ( void ) ; void
MdlInitializeSizes ( void ) ; void MdlInitializeSampleTimes ( void ) ;
SimStruct * raccel_register_model ( void ) ;
#endif
