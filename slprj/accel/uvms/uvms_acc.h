#include "__cf_uvms.h"
#ifndef RTW_HEADER_uvms_acc_h_
#define RTW_HEADER_uvms_acc_h_
#ifndef uvms_acc_COMMON_INCLUDES_
#define uvms_acc_COMMON_INCLUDES_
#include <stdlib.h>
#include <stddef.h>
#define S_FUNCTION_NAME simulink_only_sfcn 
#define S_FUNCTION_LEVEL 2
#define RTW_GENERATED_S_FUNCTION
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#endif
#include "uvms_acc_types.h"
typedef struct { slBus2 B_1_0_1 ; slBus1 B_2_0_0 ; real_T B_2_1_0 [ 6 ] ;
real_T B_0_0_1 ; } BlockIO_uvms ; struct Parameters_uvms_ { slBus1 P_0 ;
real_T P_1 [ 6 ] ; } ; extern Parameters_uvms uvms_rtDefaultParameters ;
#endif
