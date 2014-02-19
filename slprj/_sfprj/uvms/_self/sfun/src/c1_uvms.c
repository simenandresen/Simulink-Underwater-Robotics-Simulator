/* Include files */

#include "blascompat32.h"
#include "uvms_sfun.h"
#include "c1_uvms.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "uvms_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c1_debug_family_names[4] = { "nargin", "nargout", "Tbi", "y"
};

/* Function Declarations */
static void initialize_c1_uvms(SFc1_uvmsInstanceStruct *chartInstance);
static void initialize_params_c1_uvms(SFc1_uvmsInstanceStruct *chartInstance);
static void enable_c1_uvms(SFc1_uvmsInstanceStruct *chartInstance);
static void disable_c1_uvms(SFc1_uvmsInstanceStruct *chartInstance);
static void c1_update_debugger_state_c1_uvms(SFc1_uvmsInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c1_uvms(SFc1_uvmsInstanceStruct
  *chartInstance);
static void set_sim_state_c1_uvms(SFc1_uvmsInstanceStruct *chartInstance, const
  mxArray *c1_st);
static void finalize_c1_uvms(SFc1_uvmsInstanceStruct *chartInstance);
static void sf_c1_uvms(SFc1_uvmsInstanceStruct *chartInstance);
static void initSimStructsc1_uvms(SFc1_uvmsInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber);
static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData);
static real_T c1_emlrt_marshallIn(SFc1_uvmsInstanceStruct *chartInstance, const
  mxArray *c1_y, const char_T *c1_identifier);
static real_T c1_b_emlrt_marshallIn(SFc1_uvmsInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static int32_T c1_c_emlrt_marshallIn(SFc1_uvmsInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_Tbi_bus_io(void *chartInstanceVoid, void *c1_pData);
static uint8_T c1_d_emlrt_marshallIn(SFc1_uvmsInstanceStruct *chartInstance,
  const mxArray *c1_b_is_active_c1_uvms, const char_T *c1_identifier);
static uint8_T c1_e_emlrt_marshallIn(SFc1_uvmsInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void init_dsm_address_info(SFc1_uvmsInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c1_uvms(SFc1_uvmsInstanceStruct *chartInstance)
{
  chartInstance->c1_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c1_is_active_c1_uvms = 0U;
}

static void initialize_params_c1_uvms(SFc1_uvmsInstanceStruct *chartInstance)
{
}

static void enable_c1_uvms(SFc1_uvmsInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c1_uvms(SFc1_uvmsInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c1_update_debugger_state_c1_uvms(SFc1_uvmsInstanceStruct
  *chartInstance)
{
}

static const mxArray *get_sim_state_c1_uvms(SFc1_uvmsInstanceStruct
  *chartInstance)
{
  const mxArray *c1_st;
  const mxArray *c1_y = NULL;
  real_T c1_hoistedGlobal;
  real_T c1_u;
  const mxArray *c1_b_y = NULL;
  uint8_T c1_b_hoistedGlobal;
  uint8_T c1_b_u;
  const mxArray *c1_c_y = NULL;
  real_T *c1_d_y;
  c1_d_y = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c1_st = NULL;
  c1_st = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_createcellarray(2), FALSE);
  c1_hoistedGlobal = *c1_d_y;
  c1_u = c1_hoistedGlobal;
  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 0, c1_b_y);
  c1_b_hoistedGlobal = chartInstance->c1_is_active_c1_uvms;
  c1_b_u = c1_b_hoistedGlobal;
  c1_c_y = NULL;
  sf_mex_assign(&c1_c_y, sf_mex_create("y", &c1_b_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 1, c1_c_y);
  sf_mex_assign(&c1_st, c1_y, FALSE);
  return c1_st;
}

static void set_sim_state_c1_uvms(SFc1_uvmsInstanceStruct *chartInstance, const
  mxArray *c1_st)
{
  const mxArray *c1_u;
  real_T *c1_y;
  c1_y = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c1_doneDoubleBufferReInit = TRUE;
  c1_u = sf_mex_dup(c1_st);
  *c1_y = c1_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 0)),
    "y");
  chartInstance->c1_is_active_c1_uvms = c1_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 1)), "is_active_c1_uvms");
  sf_mex_destroy(&c1_u);
  c1_update_debugger_state_c1_uvms(chartInstance);
  sf_mex_destroy(&c1_st);
}

static void finalize_c1_uvms(SFc1_uvmsInstanceStruct *chartInstance)
{
}

static void sf_c1_uvms(SFc1_uvmsInstanceStruct *chartInstance)
{
  int32_T c1_i0;
  int32_T c1_i1;
  int32_T c1_i2;
  int32_T c1_i3;
  int32_T c1_i4;
  c1_slBus2 c1_Tbi;
  int32_T c1_i5;
  int32_T c1_i6;
  int32_T c1_i7;
  int32_T c1_i8;
  int32_T c1_i9;
  int32_T c1_i10;
  int32_T c1_i11;
  int32_T c1_i12;
  int32_T c1_i13;
  int32_T c1_i14;
  int32_T c1_i15;
  int32_T c1_i16;
  int32_T c1_i17;
  uint32_T c1_debug_family_var_map[4];
  real_T c1_nargin = 1.0;
  real_T c1_nargout = 1.0;
  real_T c1_y;
  real_T *c1_b_y;
  c1_slBus2 *c1_b_Tbi;
  c1_b_y = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c1_b_Tbi = (c1_slBus2 *)ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  _SFD_DATA_RANGE_CHECK(*c1_b_y, 1U);
  chartInstance->c1_sfEvent = CALL_EVENT;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  c1_i0 = 0;
  for (c1_i1 = 0; c1_i1 < 6; c1_i1++) {
    c1_i2 = 0;
    for (c1_i3 = 0; c1_i3 < 4; c1_i3++) {
      for (c1_i4 = 0; c1_i4 < 4; c1_i4++) {
        c1_Tbi.gbi[(c1_i4 + c1_i2) + c1_i0] = ((real_T *)((char_T *)c1_b_Tbi + 0))
          [(c1_i4 + c1_i2) + c1_i0];
      }

      c1_i2 += 4;
    }

    c1_i0 += 16;
  }

  c1_i5 = 0;
  for (c1_i6 = 0; c1_i6 < 6; c1_i6++) {
    c1_i7 = 0;
    for (c1_i8 = 0; c1_i8 < 3; c1_i8++) {
      for (c1_i9 = 0; c1_i9 < 3; c1_i9++) {
        c1_Tbi.Rbi[(c1_i9 + c1_i7) + c1_i5] = ((real_T *)((char_T *)c1_b_Tbi +
          768))[(c1_i9 + c1_i7) + c1_i5];
      }

      c1_i7 += 3;
    }

    c1_i5 += 9;
  }

  c1_i10 = 0;
  for (c1_i11 = 0; c1_i11 < 6; c1_i11++) {
    for (c1_i12 = 0; c1_i12 < 3; c1_i12++) {
      c1_Tbi.pbi[c1_i12 + c1_i10] = ((real_T *)((char_T *)c1_b_Tbi + 1200))
        [c1_i12 + c1_i10];
    }

    c1_i10 += 3;
  }

  c1_i13 = 0;
  for (c1_i14 = 0; c1_i14 < 6; c1_i14++) {
    c1_i15 = 0;
    for (c1_i16 = 0; c1_i16 < 6; c1_i16++) {
      for (c1_i17 = 0; c1_i17 < 6; c1_i17++) {
        c1_Tbi.Adgbi[(c1_i17 + c1_i15) + c1_i13] = ((real_T *)((char_T *)
          c1_b_Tbi + 1344))[(c1_i17 + c1_i15) + c1_i13];
      }

      c1_i15 += 6;
    }

    c1_i13 += 36;
  }

  sf_debug_symbol_scope_push_eml(0U, 4U, 4U, c1_debug_family_names,
    c1_debug_family_var_map);
  sf_debug_symbol_scope_add_eml_importable(&c1_nargin, 0U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c1_nargout, 1U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(&c1_Tbi, 2U, c1_b_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c1_y, 3U, c1_sf_marshallOut,
    c1_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 4);
  c1_y = 1.0;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, -4);
  sf_debug_symbol_scope_pop();
  *c1_b_y = c1_y;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  sf_debug_check_for_state_inconsistency(_uvmsMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void initSimStructsc1_uvms(SFc1_uvmsInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber)
{
}

static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_uvmsInstanceStruct *chartInstance;
  chartInstance = (SFc1_uvmsInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static real_T c1_emlrt_marshallIn(SFc1_uvmsInstanceStruct *chartInstance, const
  mxArray *c1_y, const char_T *c1_identifier)
{
  real_T c1_b_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_b_y = c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_y), &c1_thisId);
  sf_mex_destroy(&c1_y);
  return c1_b_y;
}

static real_T c1_b_emlrt_marshallIn(SFc1_uvmsInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d0;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d0, 1, 0, 0U, 0, 0U, 0);
  c1_y = c1_d0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_y;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_b_y;
  SFc1_uvmsInstanceStruct *chartInstance;
  chartInstance = (SFc1_uvmsInstanceStruct *)chartInstanceVoid;
  c1_y = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_b_y = c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_y), &c1_thisId);
  sf_mex_destroy(&c1_y);
  *(real_T *)c1_outData = c1_b_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  c1_slBus2 c1_u;
  const mxArray *c1_y = NULL;
  int32_T c1_i18;
  real_T c1_b_u[96];
  const mxArray *c1_b_y = NULL;
  int32_T c1_i19;
  real_T c1_c_u[54];
  const mxArray *c1_c_y = NULL;
  int32_T c1_i20;
  real_T c1_d_u[18];
  const mxArray *c1_d_y = NULL;
  int32_T c1_i21;
  real_T c1_e_u[216];
  const mxArray *c1_e_y = NULL;
  SFc1_uvmsInstanceStruct *chartInstance;
  chartInstance = (SFc1_uvmsInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(c1_slBus2 *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_createstruct("structure", 2, 1, 1), FALSE);
  for (c1_i18 = 0; c1_i18 < 96; c1_i18++) {
    c1_b_u[c1_i18] = c1_u.gbi[c1_i18];
  }

  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", c1_b_u, 0, 0U, 1U, 0U, 3, 4, 4, 6),
                FALSE);
  sf_mex_addfield(c1_y, c1_b_y, "gbi", "gbi", 0);
  for (c1_i19 = 0; c1_i19 < 54; c1_i19++) {
    c1_c_u[c1_i19] = c1_u.Rbi[c1_i19];
  }

  c1_c_y = NULL;
  sf_mex_assign(&c1_c_y, sf_mex_create("y", c1_c_u, 0, 0U, 1U, 0U, 3, 3, 3, 6),
                FALSE);
  sf_mex_addfield(c1_y, c1_c_y, "Rbi", "Rbi", 0);
  for (c1_i20 = 0; c1_i20 < 18; c1_i20++) {
    c1_d_u[c1_i20] = c1_u.pbi[c1_i20];
  }

  c1_d_y = NULL;
  sf_mex_assign(&c1_d_y, sf_mex_create("y", c1_d_u, 0, 0U, 1U, 0U, 3, 3, 1, 6),
                FALSE);
  sf_mex_addfield(c1_y, c1_d_y, "pbi", "pbi", 0);
  for (c1_i21 = 0; c1_i21 < 216; c1_i21++) {
    c1_e_u[c1_i21] = c1_u.Adgbi[c1_i21];
  }

  c1_e_y = NULL;
  sf_mex_assign(&c1_e_y, sf_mex_create("y", c1_e_u, 0, 0U, 1U, 0U, 3, 6, 6, 6),
                FALSE);
  sf_mex_addfield(c1_y, c1_e_y, "Adgbi", "Adgbi", 0);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

const mxArray *sf_c1_uvms_get_eml_resolved_functions_info(void)
{
  const mxArray *c1_nameCaptureInfo = NULL;
  c1_nameCaptureInfo = NULL;
  sf_mex_assign(&c1_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), FALSE);
  return c1_nameCaptureInfo;
}

static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_uvmsInstanceStruct *chartInstance;
  chartInstance = (SFc1_uvmsInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(int32_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static int32_T c1_c_emlrt_marshallIn(SFc1_uvmsInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  int32_T c1_y;
  int32_T c1_i22;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_i22, 1, 6, 0U, 0, 0U, 0);
  c1_y = c1_i22;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_sfEvent;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  int32_T c1_y;
  SFc1_uvmsInstanceStruct *chartInstance;
  chartInstance = (SFc1_uvmsInstanceStruct *)chartInstanceVoid;
  c1_b_sfEvent = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_sfEvent),
    &c1_thisId);
  sf_mex_destroy(&c1_b_sfEvent);
  *(int32_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_Tbi_bus_io(void *chartInstanceVoid, void *c1_pData)
{
  const mxArray *c1_mxVal = NULL;
  int32_T c1_i23;
  int32_T c1_i24;
  int32_T c1_i25;
  int32_T c1_i26;
  int32_T c1_i27;
  c1_slBus2 c1_tmp;
  int32_T c1_i28;
  int32_T c1_i29;
  int32_T c1_i30;
  int32_T c1_i31;
  int32_T c1_i32;
  int32_T c1_i33;
  int32_T c1_i34;
  int32_T c1_i35;
  int32_T c1_i36;
  int32_T c1_i37;
  int32_T c1_i38;
  int32_T c1_i39;
  int32_T c1_i40;
  SFc1_uvmsInstanceStruct *chartInstance;
  chartInstance = (SFc1_uvmsInstanceStruct *)chartInstanceVoid;
  c1_mxVal = NULL;
  c1_i23 = 0;
  for (c1_i24 = 0; c1_i24 < 6; c1_i24++) {
    c1_i25 = 0;
    for (c1_i26 = 0; c1_i26 < 4; c1_i26++) {
      for (c1_i27 = 0; c1_i27 < 4; c1_i27++) {
        c1_tmp.gbi[(c1_i27 + c1_i25) + c1_i23] = ((real_T *)((char_T *)c1_pData
          + 0))[(c1_i27 + c1_i25) + c1_i23];
      }

      c1_i25 += 4;
    }

    c1_i23 += 16;
  }

  c1_i28 = 0;
  for (c1_i29 = 0; c1_i29 < 6; c1_i29++) {
    c1_i30 = 0;
    for (c1_i31 = 0; c1_i31 < 3; c1_i31++) {
      for (c1_i32 = 0; c1_i32 < 3; c1_i32++) {
        c1_tmp.Rbi[(c1_i32 + c1_i30) + c1_i28] = ((real_T *)((char_T *)c1_pData
          + 768))[(c1_i32 + c1_i30) + c1_i28];
      }

      c1_i30 += 3;
    }

    c1_i28 += 9;
  }

  c1_i33 = 0;
  for (c1_i34 = 0; c1_i34 < 6; c1_i34++) {
    for (c1_i35 = 0; c1_i35 < 3; c1_i35++) {
      c1_tmp.pbi[c1_i35 + c1_i33] = ((real_T *)((char_T *)c1_pData + 1200))
        [c1_i35 + c1_i33];
    }

    c1_i33 += 3;
  }

  c1_i36 = 0;
  for (c1_i37 = 0; c1_i37 < 6; c1_i37++) {
    c1_i38 = 0;
    for (c1_i39 = 0; c1_i39 < 6; c1_i39++) {
      for (c1_i40 = 0; c1_i40 < 6; c1_i40++) {
        c1_tmp.Adgbi[(c1_i40 + c1_i38) + c1_i36] = ((real_T *)((char_T *)
          c1_pData + 1344))[(c1_i40 + c1_i38) + c1_i36];
      }

      c1_i38 += 6;
    }

    c1_i36 += 36;
  }

  sf_mex_assign(&c1_mxVal, c1_b_sf_marshallOut(chartInstance, &c1_tmp), FALSE);
  return c1_mxVal;
}

static uint8_T c1_d_emlrt_marshallIn(SFc1_uvmsInstanceStruct *chartInstance,
  const mxArray *c1_b_is_active_c1_uvms, const char_T *c1_identifier)
{
  uint8_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_is_active_c1_uvms),
    &c1_thisId);
  sf_mex_destroy(&c1_b_is_active_c1_uvms);
  return c1_y;
}

static uint8_T c1_e_emlrt_marshallIn(SFc1_uvmsInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint8_T c1_y;
  uint8_T c1_u0;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_u0, 1, 3, 0U, 0, 0U, 0);
  c1_y = c1_u0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void init_dsm_address_info(SFc1_uvmsInstanceStruct *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c1_uvms_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2081716812U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(716066935U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3154219991U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1055062830U);
}

mxArray *sf_c1_uvms_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("cPh9xp35d4onBBcEjXOvQF");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(13));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

static const mxArray *sf_get_sim_state_info_c1_uvms(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[5],T\"y\",},{M[8],M[0],T\"is_active_c1_uvms\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c1_uvms_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc1_uvmsInstanceStruct *chartInstance;
    chartInstance = (SFc1_uvmsInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart(_uvmsMachineNumber_,
          1,
          1,
          1,
          2,
          0,
          0,
          0,
          0,
          0,
          &(chartInstance->chartNumber),
          &(chartInstance->instanceNumber),
          ssGetPath(S),
          (void *)S);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          init_script_number_translation(_uvmsMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting(_uvmsMachineNumber_,
            chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(_uvmsMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"Tbi");
          _SFD_SET_DATA_PROPS(1,2,0,1,"y");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,44);
        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(0,SF_STRUCT,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_Tbi_bus_io,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_sf_marshallOut,(MexInFcnForType)c1_sf_marshallIn);

        {
          c1_slBus2 *c1_Tbi;
          real_T *c1_y;
          c1_y = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          c1_Tbi = (c1_slBus2 *)ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, c1_Tbi);
          _SFD_SET_DATA_VALUE_PTR(1U, c1_y);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(_uvmsMachineNumber_,
        chartInstance->chartNumber,chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization()
{
  return "zcZQJG4U7Kq5zsmTmThpf";
}

static void sf_opaque_initialize_c1_uvms(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc1_uvmsInstanceStruct*) chartInstanceVar)->S,0);
  initialize_params_c1_uvms((SFc1_uvmsInstanceStruct*) chartInstanceVar);
  initialize_c1_uvms((SFc1_uvmsInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c1_uvms(void *chartInstanceVar)
{
  enable_c1_uvms((SFc1_uvmsInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c1_uvms(void *chartInstanceVar)
{
  disable_c1_uvms((SFc1_uvmsInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c1_uvms(void *chartInstanceVar)
{
  sf_c1_uvms((SFc1_uvmsInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c1_uvms(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c1_uvms((SFc1_uvmsInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_uvms();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

extern void sf_internal_set_sim_state_c1_uvms(SimStruct* S, const mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_uvms();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c1_uvms((SFc1_uvmsInstanceStruct*)chartInfo->chartInstance,
                        mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c1_uvms(SimStruct* S)
{
  return sf_internal_get_sim_state_c1_uvms(S);
}

static void sf_opaque_set_sim_state_c1_uvms(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c1_uvms(S, st);
}

static void sf_opaque_terminate_c1_uvms(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc1_uvmsInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c1_uvms((SFc1_uvmsInstanceStruct*) chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }

  unload_uvms_optimization_info();
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc1_uvms((SFc1_uvmsInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c1_uvms(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c1_uvms((SFc1_uvmsInstanceStruct*)(((ChartInfoStruct *)
      ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c1_uvms(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_uvms_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      1);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,1,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,1,
      "gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,1,1);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,1,1);
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,1);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(3313851419U));
  ssSetChecksum1(S,(3835643471U));
  ssSetChecksum2(S,(1638372800U));
  ssSetChecksum3(S,(2449100601U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c1_uvms(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c1_uvms(SimStruct *S)
{
  SFc1_uvmsInstanceStruct *chartInstance;
  chartInstance = (SFc1_uvmsInstanceStruct *)malloc(sizeof
    (SFc1_uvmsInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc1_uvmsInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c1_uvms;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c1_uvms;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c1_uvms;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c1_uvms;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c1_uvms;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c1_uvms;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c1_uvms;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c1_uvms;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c1_uvms;
  chartInstance->chartInfo.mdlStart = mdlStart_c1_uvms;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c1_uvms;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->S = S;
  ssSetUserData(S,(void *)(&(chartInstance->chartInfo)));/* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c1_uvms_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c1_uvms(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c1_uvms(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c1_uvms(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c1_uvms_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
