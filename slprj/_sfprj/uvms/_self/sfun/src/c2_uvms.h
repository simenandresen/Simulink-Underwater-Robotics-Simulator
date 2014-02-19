#ifndef __c2_uvms_h__
#define __c2_uvms_h__

/* Include files */
#include "sfc_sf.h"
#include "sfc_mex.h"
#include "rtwtypes.h"

/* Type Definitions */
typedef struct {
  const char * context;
  const char * name;
  const char * dominantType;
  const char * resolved;
  uint32_T fileTimeLo;
  uint32_T fileTimeHi;
  uint32_T mFileTimeLo;
  uint32_T mFileTimeHi;
} c2_ResolvedFunctionInfo;

#ifndef struct_slBus1_tag
#define struct_slBus1_tag

typedef struct slBus1_tag
{
  real_T a[6];
  real_T d[6];
  real_T alpha[6];
} c2_slBus1;

#else

typedef struct slBus1_tag c2_slBus1;

#endif

#ifndef struct_slBus2_tag
#define struct_slBus2_tag

typedef struct slBus2_tag
{
  real_T gbi[96];
  real_T Rbi[54];
  real_T pbi[18];
  real_T Adgbi[216];
} c2_slBus2;

#else

typedef struct slBus2_tag c2_slBus2;

#endif

typedef struct {
  int32_T c2_sfEvent;
  boolean_T c2_isStable;
  boolean_T c2_doneDoubleBufferReInit;
  uint8_T c2_is_active_c2_uvms;
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
} SFc2_uvmsInstanceStruct;

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c2_uvms_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c2_uvms_get_check_sum(mxArray *plhs[]);
extern void c2_uvms_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
