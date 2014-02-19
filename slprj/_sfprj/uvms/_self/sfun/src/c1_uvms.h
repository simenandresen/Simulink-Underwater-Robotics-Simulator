#ifndef __c1_uvms_h__
#define __c1_uvms_h__

/* Include files */
#include "sfc_sf.h"
#include "sfc_mex.h"
#include "rtwtypes.h"

/* Type Definitions */
#ifndef struct_slBus2_tag
#define struct_slBus2_tag

typedef struct slBus2_tag
{
  real_T gbi[96];
  real_T Rbi[54];
  real_T pbi[18];
  real_T Adgbi[216];
} c1_slBus2;

#else

typedef struct slBus2_tag c1_slBus2;

#endif

typedef struct {
  int32_T c1_sfEvent;
  boolean_T c1_isStable;
  boolean_T c1_doneDoubleBufferReInit;
  uint8_T c1_is_active_c1_uvms;
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
} SFc1_uvmsInstanceStruct;

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c1_uvms_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c1_uvms_get_check_sum(mxArray *plhs[]);
extern void c1_uvms_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
