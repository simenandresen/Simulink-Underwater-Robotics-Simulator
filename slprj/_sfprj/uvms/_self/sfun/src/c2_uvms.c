/* Include files */

#include "blascompat32.h"
#include "uvms_sfun.h"
#include "c2_uvms.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "uvms_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c2_debug_family_names[7] = { "n", "g", "nargin", "nargout",
  "q", "DH", "Tbi" };

static const char * c2_b_debug_family_names[10] = { "alpha", "a", "d", "theta",
  "nargin", "nargout", "q", "DH", "i", "mat" };

static const char * c2_c_debug_family_names[4] = { "nargin", "nargout", "g",
  "mat" };

static const char * c2_d_debug_family_names[4] = { "nargin", "nargout", "g",
  "vec" };

static const char * c2_e_debug_family_names[4] = { "nargin", "nargout", "vec",
  "mat" };

static const char * c2_f_debug_family_names[6] = { "ps", "nargin", "nargout",
  "R", "p", "mat" };

/* Function Declarations */
static void initialize_c2_uvms(SFc2_uvmsInstanceStruct *chartInstance);
static void initialize_params_c2_uvms(SFc2_uvmsInstanceStruct *chartInstance);
static void enable_c2_uvms(SFc2_uvmsInstanceStruct *chartInstance);
static void disable_c2_uvms(SFc2_uvmsInstanceStruct *chartInstance);
static void c2_update_debugger_state_c2_uvms(SFc2_uvmsInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c2_uvms(SFc2_uvmsInstanceStruct
  *chartInstance);
static void set_sim_state_c2_uvms(SFc2_uvmsInstanceStruct *chartInstance, const
  mxArray *c2_st);
static void finalize_c2_uvms(SFc2_uvmsInstanceStruct *chartInstance);
static void sf_c2_uvms(SFc2_uvmsInstanceStruct *chartInstance);
static void c2_chartstep_c2_uvms(SFc2_uvmsInstanceStruct *chartInstance);
static void initSimStructsc2_uvms(SFc2_uvmsInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber);
static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData);
static void c2_emlrt_marshallIn(SFc2_uvmsInstanceStruct *chartInstance, const
  mxArray *c2_Tbi, const char_T *c2_identifier, c2_slBus2 *c2_y);
static void c2_b_emlrt_marshallIn(SFc2_uvmsInstanceStruct *chartInstance, const
  mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, c2_slBus2 *c2_y);
static void c2_c_emlrt_marshallIn(SFc2_uvmsInstanceStruct *chartInstance, const
  mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[96]);
static void c2_d_emlrt_marshallIn(SFc2_uvmsInstanceStruct *chartInstance, const
  mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[54]);
static void c2_e_emlrt_marshallIn(SFc2_uvmsInstanceStruct *chartInstance, const
  mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[18]);
static void c2_f_emlrt_marshallIn(SFc2_uvmsInstanceStruct *chartInstance, const
  mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[216]);
static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static real_T c2_g_emlrt_marshallIn(SFc2_uvmsInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_h_emlrt_marshallIn(SFc2_uvmsInstanceStruct *chartInstance, const
  mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[16]);
static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_i_emlrt_marshallIn(SFc2_uvmsInstanceStruct *chartInstance, const
  mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, c2_slBus1 *c2_y);
static void c2_j_emlrt_marshallIn(SFc2_uvmsInstanceStruct *chartInstance, const
  mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[6]);
static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_k_emlrt_marshallIn(SFc2_uvmsInstanceStruct *chartInstance, const
  mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[6]);
static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_l_emlrt_marshallIn(SFc2_uvmsInstanceStruct *chartInstance, const
  mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[9]);
static void c2_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_g_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_m_emlrt_marshallIn(SFc2_uvmsInstanceStruct *chartInstance, const
  mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[3]);
static void c2_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_h_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_n_emlrt_marshallIn(SFc2_uvmsInstanceStruct *chartInstance, const
  mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[36]);
static void c2_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_info_helper(c2_ResolvedFunctionInfo c2_info[28]);
static void c2_eye(SFc2_uvmsInstanceStruct *chartInstance, real_T c2_I[16]);
static void c2_eml_int_forloop_overflow_check(SFc2_uvmsInstanceStruct
  *chartInstance);
static void c2_getHom(SFc2_uvmsInstanceStruct *chartInstance, real_T c2_q[6],
                      c2_slBus1 *c2_DH, real_T c2_i, real_T c2_mat[16]);
static void c2_eml_scalar_eg(SFc2_uvmsInstanceStruct *chartInstance);
static void c2_getAdgbi(SFc2_uvmsInstanceStruct *chartInstance, real_T c2_R[9],
  real_T c2_p[3], real_T c2_mat[36]);
static void c2_b_eml_scalar_eg(SFc2_uvmsInstanceStruct *chartInstance);
static const mxArray *c2_i_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int32_T c2_o_emlrt_marshallIn(SFc2_uvmsInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_DH_bus_io(void *chartInstanceVoid, void *c2_pData);
static const mxArray *c2_Tbi_bus_io(void *chartInstanceVoid, void *c2_pData);
static uint8_T c2_p_emlrt_marshallIn(SFc2_uvmsInstanceStruct *chartInstance,
  const mxArray *c2_b_is_active_c2_uvms, const char_T *c2_identifier);
static uint8_T c2_q_emlrt_marshallIn(SFc2_uvmsInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void init_dsm_address_info(SFc2_uvmsInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c2_uvms(SFc2_uvmsInstanceStruct *chartInstance)
{
  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c2_is_active_c2_uvms = 0U;
}

static void initialize_params_c2_uvms(SFc2_uvmsInstanceStruct *chartInstance)
{
}

static void enable_c2_uvms(SFc2_uvmsInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c2_uvms(SFc2_uvmsInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c2_update_debugger_state_c2_uvms(SFc2_uvmsInstanceStruct
  *chartInstance)
{
}

static const mxArray *get_sim_state_c2_uvms(SFc2_uvmsInstanceStruct
  *chartInstance)
{
  const mxArray *c2_st;
  const mxArray *c2_y = NULL;
  int32_T c2_i0;
  int32_T c2_i1;
  int32_T c2_i2;
  int32_T c2_i3;
  int32_T c2_i4;
  c2_slBus2 c2_u;
  int32_T c2_i5;
  int32_T c2_i6;
  int32_T c2_i7;
  int32_T c2_i8;
  int32_T c2_i9;
  int32_T c2_i10;
  int32_T c2_i11;
  int32_T c2_i12;
  int32_T c2_i13;
  int32_T c2_i14;
  int32_T c2_i15;
  int32_T c2_i16;
  int32_T c2_i17;
  const mxArray *c2_b_y = NULL;
  int32_T c2_i18;
  real_T c2_b_u[96];
  const mxArray *c2_c_y = NULL;
  int32_T c2_i19;
  real_T c2_c_u[54];
  const mxArray *c2_d_y = NULL;
  int32_T c2_i20;
  real_T c2_d_u[18];
  const mxArray *c2_e_y = NULL;
  int32_T c2_i21;
  real_T c2_e_u[216];
  const mxArray *c2_f_y = NULL;
  uint8_T c2_hoistedGlobal;
  uint8_T c2_f_u;
  const mxArray *c2_g_y = NULL;
  c2_slBus2 *c2_Tbi;
  c2_Tbi = (c2_slBus2 *)ssGetOutputPortSignal(chartInstance->S, 1);
  c2_st = NULL;
  c2_st = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createcellarray(2), FALSE);
  c2_i0 = 0;
  for (c2_i1 = 0; c2_i1 < 6; c2_i1++) {
    c2_i2 = 0;
    for (c2_i3 = 0; c2_i3 < 4; c2_i3++) {
      for (c2_i4 = 0; c2_i4 < 4; c2_i4++) {
        c2_u.gbi[(c2_i4 + c2_i2) + c2_i0] = ((real_T *)((char_T *)c2_Tbi + 0))
          [(c2_i4 + c2_i2) + c2_i0];
      }

      c2_i2 += 4;
    }

    c2_i0 += 16;
  }

  c2_i5 = 0;
  for (c2_i6 = 0; c2_i6 < 6; c2_i6++) {
    c2_i7 = 0;
    for (c2_i8 = 0; c2_i8 < 3; c2_i8++) {
      for (c2_i9 = 0; c2_i9 < 3; c2_i9++) {
        c2_u.Rbi[(c2_i9 + c2_i7) + c2_i5] = ((real_T *)((char_T *)c2_Tbi + 768))
          [(c2_i9 + c2_i7) + c2_i5];
      }

      c2_i7 += 3;
    }

    c2_i5 += 9;
  }

  c2_i10 = 0;
  for (c2_i11 = 0; c2_i11 < 6; c2_i11++) {
    for (c2_i12 = 0; c2_i12 < 3; c2_i12++) {
      c2_u.pbi[c2_i12 + c2_i10] = ((real_T *)((char_T *)c2_Tbi + 1200))[c2_i12 +
        c2_i10];
    }

    c2_i10 += 3;
  }

  c2_i13 = 0;
  for (c2_i14 = 0; c2_i14 < 6; c2_i14++) {
    c2_i15 = 0;
    for (c2_i16 = 0; c2_i16 < 6; c2_i16++) {
      for (c2_i17 = 0; c2_i17 < 6; c2_i17++) {
        c2_u.Adgbi[(c2_i17 + c2_i15) + c2_i13] = ((real_T *)((char_T *)c2_Tbi +
          1344))[(c2_i17 + c2_i15) + c2_i13];
      }

      c2_i15 += 6;
    }

    c2_i13 += 36;
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_createstruct("structure", 2, 1, 1), FALSE);
  for (c2_i18 = 0; c2_i18 < 96; c2_i18++) {
    c2_b_u[c2_i18] = c2_u.gbi[c2_i18];
  }

  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", c2_b_u, 0, 0U, 1U, 0U, 3, 4, 4, 6),
                FALSE);
  sf_mex_addfield(c2_b_y, c2_c_y, "gbi", "gbi", 0);
  for (c2_i19 = 0; c2_i19 < 54; c2_i19++) {
    c2_c_u[c2_i19] = c2_u.Rbi[c2_i19];
  }

  c2_d_y = NULL;
  sf_mex_assign(&c2_d_y, sf_mex_create("y", c2_c_u, 0, 0U, 1U, 0U, 3, 3, 3, 6),
                FALSE);
  sf_mex_addfield(c2_b_y, c2_d_y, "Rbi", "Rbi", 0);
  for (c2_i20 = 0; c2_i20 < 18; c2_i20++) {
    c2_d_u[c2_i20] = c2_u.pbi[c2_i20];
  }

  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_d_u, 0, 0U, 1U, 0U, 3, 3, 1, 6),
                FALSE);
  sf_mex_addfield(c2_b_y, c2_e_y, "pbi", "pbi", 0);
  for (c2_i21 = 0; c2_i21 < 216; c2_i21++) {
    c2_e_u[c2_i21] = c2_u.Adgbi[c2_i21];
  }

  c2_f_y = NULL;
  sf_mex_assign(&c2_f_y, sf_mex_create("y", c2_e_u, 0, 0U, 1U, 0U, 3, 6, 6, 6),
                FALSE);
  sf_mex_addfield(c2_b_y, c2_f_y, "Adgbi", "Adgbi", 0);
  sf_mex_setcell(c2_y, 0, c2_b_y);
  c2_hoistedGlobal = chartInstance->c2_is_active_c2_uvms;
  c2_f_u = c2_hoistedGlobal;
  c2_g_y = NULL;
  sf_mex_assign(&c2_g_y, sf_mex_create("y", &c2_f_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c2_y, 1, c2_g_y);
  sf_mex_assign(&c2_st, c2_y, FALSE);
  return c2_st;
}

static void set_sim_state_c2_uvms(SFc2_uvmsInstanceStruct *chartInstance, const
  mxArray *c2_st)
{
  const mxArray *c2_u;
  c2_slBus2 c2_r0;
  int32_T c2_i22;
  int32_T c2_i23;
  int32_T c2_i24;
  int32_T c2_i25;
  int32_T c2_i26;
  int32_T c2_i27;
  int32_T c2_i28;
  int32_T c2_i29;
  int32_T c2_i30;
  int32_T c2_i31;
  int32_T c2_i32;
  int32_T c2_i33;
  int32_T c2_i34;
  int32_T c2_i35;
  int32_T c2_i36;
  int32_T c2_i37;
  int32_T c2_i38;
  int32_T c2_i39;
  c2_slBus2 *c2_Tbi;
  c2_Tbi = (c2_slBus2 *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c2_doneDoubleBufferReInit = TRUE;
  c2_u = sf_mex_dup(c2_st);
  c2_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c2_u, 0)), "Tbi",
                      &c2_r0);
  c2_i22 = 0;
  for (c2_i23 = 0; c2_i23 < 6; c2_i23++) {
    c2_i24 = 0;
    for (c2_i25 = 0; c2_i25 < 4; c2_i25++) {
      for (c2_i26 = 0; c2_i26 < 4; c2_i26++) {
        ((real_T *)((char_T *)c2_Tbi + 0))[(c2_i26 + c2_i24) + c2_i22] =
          c2_r0.gbi[(c2_i26 + c2_i24) + c2_i22];
      }

      c2_i24 += 4;
    }

    c2_i22 += 16;
  }

  c2_i27 = 0;
  for (c2_i28 = 0; c2_i28 < 6; c2_i28++) {
    c2_i29 = 0;
    for (c2_i30 = 0; c2_i30 < 3; c2_i30++) {
      for (c2_i31 = 0; c2_i31 < 3; c2_i31++) {
        ((real_T *)((char_T *)c2_Tbi + 768))[(c2_i31 + c2_i29) + c2_i27] =
          c2_r0.Rbi[(c2_i31 + c2_i29) + c2_i27];
      }

      c2_i29 += 3;
    }

    c2_i27 += 9;
  }

  c2_i32 = 0;
  for (c2_i33 = 0; c2_i33 < 6; c2_i33++) {
    for (c2_i34 = 0; c2_i34 < 3; c2_i34++) {
      ((real_T *)((char_T *)c2_Tbi + 1200))[c2_i34 + c2_i32] = c2_r0.pbi[c2_i34
        + c2_i32];
    }

    c2_i32 += 3;
  }

  c2_i35 = 0;
  for (c2_i36 = 0; c2_i36 < 6; c2_i36++) {
    c2_i37 = 0;
    for (c2_i38 = 0; c2_i38 < 6; c2_i38++) {
      for (c2_i39 = 0; c2_i39 < 6; c2_i39++) {
        ((real_T *)((char_T *)c2_Tbi + 1344))[(c2_i39 + c2_i37) + c2_i35] =
          c2_r0.Adgbi[(c2_i39 + c2_i37) + c2_i35];
      }

      c2_i37 += 6;
    }

    c2_i35 += 36;
  }

  chartInstance->c2_is_active_c2_uvms = c2_p_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c2_u, 1)), "is_active_c2_uvms");
  sf_mex_destroy(&c2_u);
  c2_update_debugger_state_c2_uvms(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_uvms(SFc2_uvmsInstanceStruct *chartInstance)
{
}

static void sf_c2_uvms(SFc2_uvmsInstanceStruct *chartInstance)
{
  int32_T c2_i40;
  real_T (*c2_q)[6];
  c2_q = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  for (c2_i40 = 0; c2_i40 < 6; c2_i40++) {
    _SFD_DATA_RANGE_CHECK((*c2_q)[c2_i40], 0U);
  }

  chartInstance->c2_sfEvent = CALL_EVENT;
  c2_chartstep_c2_uvms(chartInstance);
  sf_debug_check_for_state_inconsistency(_uvmsMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c2_chartstep_c2_uvms(SFc2_uvmsInstanceStruct *chartInstance)
{
  int32_T c2_i41;
  real_T c2_q[6];
  int32_T c2_i42;
  c2_slBus1 c2_DH;
  int32_T c2_i43;
  int32_T c2_i44;
  uint32_T c2_debug_family_var_map[7];
  real_T c2_n;
  real_T c2_g[16];
  real_T c2_nargin = 2.0;
  real_T c2_nargout = 1.0;
  c2_slBus2 c2_Tbi;
  static c2_slBus2 c2_r1 = { { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 }, { 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0 } };

  real_T c2_dv0[16];
  int32_T c2_i45;
  int32_T c2_i;
  real_T c2_b_i;
  int32_T c2_i46;
  real_T c2_a[16];
  int32_T c2_i47;
  real_T c2_b_q[6];
  c2_slBus1 c2_b_DH;
  real_T c2_b[16];
  int32_T c2_i48;
  int32_T c2_i49;
  int32_T c2_i50;
  real_T c2_y[16];
  int32_T c2_i51;
  int32_T c2_i52;
  int32_T c2_c_i;
  int32_T c2_i53;
  int32_T c2_i54;
  int32_T c2_d_i;
  int32_T c2_i55;
  int32_T c2_i56;
  real_T c2_b_g[16];
  uint32_T c2_b_debug_family_var_map[4];
  real_T c2_b_nargin = 1.0;
  real_T c2_b_nargout = 1.0;
  real_T c2_mat[9];
  int32_T c2_i57;
  int32_T c2_i58;
  int32_T c2_i59;
  int32_T c2_i60;
  int32_T c2_e_i;
  int32_T c2_i61;
  int32_T c2_i62;
  int32_T c2_f_i;
  int32_T c2_i63;
  int32_T c2_i64;
  real_T c2_c_g[16];
  real_T c2_c_nargin = 1.0;
  real_T c2_c_nargout = 1.0;
  real_T c2_vec[3];
  int32_T c2_i65;
  int32_T c2_g_i;
  int32_T c2_i66;
  int32_T c2_h_i;
  int32_T c2_i67;
  int32_T c2_i68;
  real_T c2_b_Tbi[9];
  int32_T c2_i_i;
  int32_T c2_i69;
  real_T c2_c_Tbi[3];
  real_T c2_dv1[36];
  int32_T c2_j_i;
  int32_T c2_i70;
  int32_T c2_i71;
  int32_T c2_k_i;
  int32_T c2_i72;
  int32_T c2_i73;
  int32_T c2_i74;
  int32_T c2_i75;
  int32_T c2_i76;
  real_T c2_u[36];
  const mxArray *c2_b_y = NULL;
  int32_T c2_i77;
  int32_T c2_i78;
  int32_T c2_i79;
  int32_T c2_i80;
  int32_T c2_i81;
  int32_T c2_i82;
  int32_T c2_i83;
  int32_T c2_i84;
  int32_T c2_i85;
  int32_T c2_i86;
  int32_T c2_i87;
  int32_T c2_i88;
  int32_T c2_i89;
  int32_T c2_i90;
  int32_T c2_i91;
  int32_T c2_i92;
  int32_T c2_i93;
  int32_T c2_i94;
  real_T (*c2_c_q)[6];
  c2_slBus1 *c2_c_DH;
  c2_slBus2 *c2_d_Tbi;
  c2_d_Tbi = (c2_slBus2 *)ssGetOutputPortSignal(chartInstance->S, 1);
  c2_c_DH = (c2_slBus1 *)ssGetInputPortSignal(chartInstance->S, 1);
  c2_c_q = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  for (c2_i41 = 0; c2_i41 < 6; c2_i41++) {
    c2_q[c2_i41] = (*c2_c_q)[c2_i41];
  }

  for (c2_i42 = 0; c2_i42 < 6; c2_i42++) {
    c2_DH.a[c2_i42] = ((real_T *)((char_T *)c2_c_DH + 0))[c2_i42];
  }

  for (c2_i43 = 0; c2_i43 < 6; c2_i43++) {
    c2_DH.d[c2_i43] = ((real_T *)((char_T *)c2_c_DH + 48))[c2_i43];
  }

  for (c2_i44 = 0; c2_i44 < 6; c2_i44++) {
    c2_DH.alpha[c2_i44] = ((real_T *)((char_T *)c2_c_DH + 96))[c2_i44];
  }

  sf_debug_symbol_scope_push_eml(0U, 7U, 7U, c2_debug_family_names,
    c2_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c2_n, 0U, c2_d_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(c2_g, 1U, c2_e_sf_marshallOut,
    c2_c_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargin, 2U, c2_d_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargout, 3U, c2_d_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml(c2_q, 4U, c2_c_sf_marshallOut);
  sf_debug_symbol_scope_add_eml(&c2_DH, 5U, c2_b_sf_marshallOut);
  sf_debug_symbol_scope_add_eml_importable(&c2_Tbi, 6U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 3);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 4);
  c2_n = 6.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 5);
  c2_Tbi = c2_r1;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 8);
  c2_eye(chartInstance, c2_dv0);
  for (c2_i45 = 0; c2_i45 < 16; c2_i45++) {
    c2_g[c2_i45] = c2_dv0[c2_i45];
  }

  c2_i = 0;
  while (c2_i < 6) {
    c2_b_i = 1.0 + (real_T)c2_i;
    CV_EML_FOR(0, 1, 0, 1);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 10);
    for (c2_i46 = 0; c2_i46 < 16; c2_i46++) {
      c2_a[c2_i46] = c2_g[c2_i46];
    }

    for (c2_i47 = 0; c2_i47 < 6; c2_i47++) {
      c2_b_q[c2_i47] = c2_q[c2_i47];
    }

    c2_b_DH = c2_DH;
    c2_getHom(chartInstance, c2_b_q, &c2_b_DH, c2_b_i, c2_b);
    c2_eml_scalar_eg(chartInstance);
    c2_eml_scalar_eg(chartInstance);
    for (c2_i48 = 0; c2_i48 < 4; c2_i48++) {
      c2_i49 = 0;
      for (c2_i50 = 0; c2_i50 < 4; c2_i50++) {
        c2_y[c2_i49 + c2_i48] = 0.0;
        c2_i51 = 0;
        for (c2_i52 = 0; c2_i52 < 4; c2_i52++) {
          c2_y[c2_i49 + c2_i48] += c2_a[c2_i51 + c2_i48] * c2_b[c2_i52 + c2_i49];
          c2_i51 += 4;
        }

        c2_i49 += 4;
      }
    }

    c2_c_i = _SFD_EML_ARRAY_BOUNDS_CHECK("Tbi.gbi", (int32_T)_SFD_INTEGER_CHECK(
      "i", c2_b_i), 1, 6, 3, 0) - 1;
    for (c2_i53 = 0; c2_i53 < 4; c2_i53++) {
      for (c2_i54 = 0; c2_i54 < 4; c2_i54++) {
        c2_Tbi.gbi[(c2_i54 + (c2_i53 << 2)) + (c2_c_i << 4)] = c2_y[c2_i54 +
          (c2_i53 << 2)];
      }
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 11);
    c2_d_i = _SFD_EML_ARRAY_BOUNDS_CHECK("Tbi.gbi", (int32_T)_SFD_INTEGER_CHECK(
      "i", c2_b_i), 1, 6, 3, 0) - 1;
    for (c2_i55 = 0; c2_i55 < 4; c2_i55++) {
      for (c2_i56 = 0; c2_i56 < 4; c2_i56++) {
        c2_b_g[c2_i56 + (c2_i55 << 2)] = c2_Tbi.gbi[(c2_i56 + (c2_i55 << 2)) +
          (c2_d_i << 4)];
      }
    }

    sf_debug_symbol_scope_push_eml(0U, 4U, 4U, c2_c_debug_family_names,
      c2_b_debug_family_var_map);
    sf_debug_symbol_scope_add_eml_importable(&c2_b_nargin, 0U,
      c2_d_sf_marshallOut, c2_b_sf_marshallIn);
    sf_debug_symbol_scope_add_eml_importable(&c2_b_nargout, 1U,
      c2_d_sf_marshallOut, c2_b_sf_marshallIn);
    sf_debug_symbol_scope_add_eml_importable(c2_b_g, 2U, c2_e_sf_marshallOut,
      c2_c_sf_marshallIn);
    sf_debug_symbol_scope_add_eml_importable(c2_mat, 3U, c2_f_sf_marshallOut,
      c2_f_sf_marshallIn);
    CV_EML_FCN(0, 3);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 85);
    c2_i57 = 0;
    c2_i58 = 0;
    for (c2_i59 = 0; c2_i59 < 3; c2_i59++) {
      for (c2_i60 = 0; c2_i60 < 3; c2_i60++) {
        c2_mat[c2_i60 + c2_i57] = c2_b_g[c2_i60 + c2_i58];
      }

      c2_i57 += 3;
      c2_i58 += 4;
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -85);
    sf_debug_symbol_scope_pop();
    c2_e_i = _SFD_EML_ARRAY_BOUNDS_CHECK("Tbi.Rbi", (int32_T)_SFD_INTEGER_CHECK(
      "i", c2_b_i), 1, 6, 3, 0) - 1;
    for (c2_i61 = 0; c2_i61 < 3; c2_i61++) {
      for (c2_i62 = 0; c2_i62 < 3; c2_i62++) {
        c2_Tbi.Rbi[(c2_i62 + 3 * c2_i61) + 9 * c2_e_i] = c2_mat[c2_i62 + 3 *
          c2_i61];
      }
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 12);
    c2_f_i = _SFD_EML_ARRAY_BOUNDS_CHECK("Tbi.gbi", (int32_T)_SFD_INTEGER_CHECK(
      "i", c2_b_i), 1, 6, 3, 0) - 1;
    for (c2_i63 = 0; c2_i63 < 4; c2_i63++) {
      for (c2_i64 = 0; c2_i64 < 4; c2_i64++) {
        c2_c_g[c2_i64 + (c2_i63 << 2)] = c2_Tbi.gbi[(c2_i64 + (c2_i63 << 2)) +
          (c2_f_i << 4)];
      }
    }

    sf_debug_symbol_scope_push_eml(0U, 4U, 4U, c2_d_debug_family_names,
      c2_b_debug_family_var_map);
    sf_debug_symbol_scope_add_eml_importable(&c2_c_nargin, 0U,
      c2_d_sf_marshallOut, c2_b_sf_marshallIn);
    sf_debug_symbol_scope_add_eml_importable(&c2_c_nargout, 1U,
      c2_d_sf_marshallOut, c2_b_sf_marshallIn);
    sf_debug_symbol_scope_add_eml_importable(c2_c_g, 2U, c2_e_sf_marshallOut,
      c2_c_sf_marshallIn);
    sf_debug_symbol_scope_add_eml_importable(c2_vec, 3U, c2_g_sf_marshallOut,
      c2_g_sf_marshallIn);
    CV_EML_FCN(0, 2);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 78);
    for (c2_i65 = 0; c2_i65 < 3; c2_i65++) {
      c2_vec[c2_i65] = c2_c_g[c2_i65 + 12];
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -78);
    sf_debug_symbol_scope_pop();
    c2_g_i = _SFD_EML_ARRAY_BOUNDS_CHECK("Tbi.pbi", (int32_T)_SFD_INTEGER_CHECK(
      "i", c2_b_i), 1, 6, 3, 0) - 1;
    for (c2_i66 = 0; c2_i66 < 3; c2_i66++) {
      c2_Tbi.pbi[c2_i66 + 3 * c2_g_i] = c2_vec[c2_i66];
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 13);
    c2_h_i = _SFD_EML_ARRAY_BOUNDS_CHECK("Tbi.Rbi", (int32_T)_SFD_INTEGER_CHECK(
      "i", c2_b_i), 1, 6, 3, 0) - 1;
    for (c2_i67 = 0; c2_i67 < 3; c2_i67++) {
      for (c2_i68 = 0; c2_i68 < 3; c2_i68++) {
        c2_b_Tbi[c2_i68 + 3 * c2_i67] = c2_Tbi.Rbi[(c2_i68 + 3 * c2_i67) + 9 *
          c2_h_i];
      }
    }

    c2_i_i = _SFD_EML_ARRAY_BOUNDS_CHECK("Tbi.pbi", (int32_T)_SFD_INTEGER_CHECK(
      "i", c2_b_i), 1, 6, 3, 0) - 1;
    for (c2_i69 = 0; c2_i69 < 3; c2_i69++) {
      c2_c_Tbi[c2_i69] = c2_Tbi.pbi[c2_i69 + 3 * c2_i_i];
    }

    c2_getAdgbi(chartInstance, c2_b_Tbi, c2_c_Tbi, c2_dv1);
    c2_j_i = _SFD_EML_ARRAY_BOUNDS_CHECK("Tbi.Adgbi", (int32_T)
      _SFD_INTEGER_CHECK("i", c2_b_i), 1, 6, 3, 0) - 1;
    for (c2_i70 = 0; c2_i70 < 6; c2_i70++) {
      for (c2_i71 = 0; c2_i71 < 6; c2_i71++) {
        c2_Tbi.Adgbi[(c2_i71 + 6 * c2_i70) + 36 * c2_j_i] = c2_dv1[c2_i71 + 6 *
          c2_i70];
      }
    }

    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 15);
    c2_k_i = _SFD_EML_ARRAY_BOUNDS_CHECK("Tbi.gbi", (int32_T)_SFD_INTEGER_CHECK(
      "i", c2_b_i), 1, 6, 3, 0) - 1;
    for (c2_i72 = 0; c2_i72 < 4; c2_i72++) {
      for (c2_i73 = 0; c2_i73 < 4; c2_i73++) {
        c2_g[c2_i73 + (c2_i72 << 2)] = c2_Tbi.gbi[(c2_i73 + (c2_i72 << 2)) +
          (c2_k_i << 4)];
      }
    }

    c2_i++;
    sf_mex_listen_for_ctrl_c(chartInstance->S);
  }

  CV_EML_FOR(0, 1, 0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 52);
  c2_i74 = 0;
  for (c2_i75 = 0; c2_i75 < 6; c2_i75++) {
    for (c2_i76 = 0; c2_i76 < 6; c2_i76++) {
      c2_u[c2_i76 + c2_i74] = c2_Tbi.Adgbi[(c2_i76 + c2_i74) + 180];
    }

    c2_i74 += 6;
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 6, 6), FALSE);
  sf_mex_call_debug("disp", 0U, 1U, 14, c2_b_y);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -52);
  sf_debug_symbol_scope_pop();
  c2_i77 = 0;
  for (c2_i78 = 0; c2_i78 < 6; c2_i78++) {
    c2_i79 = 0;
    for (c2_i80 = 0; c2_i80 < 4; c2_i80++) {
      for (c2_i81 = 0; c2_i81 < 4; c2_i81++) {
        ((real_T *)((char_T *)c2_d_Tbi + 0))[(c2_i81 + c2_i79) + c2_i77] =
          c2_Tbi.gbi[(c2_i81 + c2_i79) + c2_i77];
      }

      c2_i79 += 4;
    }

    c2_i77 += 16;
  }

  c2_i82 = 0;
  for (c2_i83 = 0; c2_i83 < 6; c2_i83++) {
    c2_i84 = 0;
    for (c2_i85 = 0; c2_i85 < 3; c2_i85++) {
      for (c2_i86 = 0; c2_i86 < 3; c2_i86++) {
        ((real_T *)((char_T *)c2_d_Tbi + 768))[(c2_i86 + c2_i84) + c2_i82] =
          c2_Tbi.Rbi[(c2_i86 + c2_i84) + c2_i82];
      }

      c2_i84 += 3;
    }

    c2_i82 += 9;
  }

  c2_i87 = 0;
  for (c2_i88 = 0; c2_i88 < 6; c2_i88++) {
    for (c2_i89 = 0; c2_i89 < 3; c2_i89++) {
      ((real_T *)((char_T *)c2_d_Tbi + 1200))[c2_i89 + c2_i87] =
        c2_Tbi.pbi[c2_i89 + c2_i87];
    }

    c2_i87 += 3;
  }

  c2_i90 = 0;
  for (c2_i91 = 0; c2_i91 < 6; c2_i91++) {
    c2_i92 = 0;
    for (c2_i93 = 0; c2_i93 < 6; c2_i93++) {
      for (c2_i94 = 0; c2_i94 < 6; c2_i94++) {
        ((real_T *)((char_T *)c2_d_Tbi + 1344))[(c2_i94 + c2_i92) + c2_i90] =
          c2_Tbi.Adgbi[(c2_i94 + c2_i92) + c2_i90];
      }

      c2_i92 += 6;
    }

    c2_i90 += 36;
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
}

static void initSimStructsc2_uvms(SFc2_uvmsInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber)
{
}

static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  c2_slBus2 c2_u;
  const mxArray *c2_y = NULL;
  int32_T c2_i95;
  real_T c2_b_u[96];
  const mxArray *c2_b_y = NULL;
  int32_T c2_i96;
  real_T c2_c_u[54];
  const mxArray *c2_c_y = NULL;
  int32_T c2_i97;
  real_T c2_d_u[18];
  const mxArray *c2_d_y = NULL;
  int32_T c2_i98;
  real_T c2_e_u[216];
  const mxArray *c2_e_y = NULL;
  SFc2_uvmsInstanceStruct *chartInstance;
  chartInstance = (SFc2_uvmsInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(c2_slBus2 *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createstruct("structure", 2, 1, 1), FALSE);
  for (c2_i95 = 0; c2_i95 < 96; c2_i95++) {
    c2_b_u[c2_i95] = c2_u.gbi[c2_i95];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_b_u, 0, 0U, 1U, 0U, 3, 4, 4, 6),
                FALSE);
  sf_mex_addfield(c2_y, c2_b_y, "gbi", "gbi", 0);
  for (c2_i96 = 0; c2_i96 < 54; c2_i96++) {
    c2_c_u[c2_i96] = c2_u.Rbi[c2_i96];
  }

  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", c2_c_u, 0, 0U, 1U, 0U, 3, 3, 3, 6),
                FALSE);
  sf_mex_addfield(c2_y, c2_c_y, "Rbi", "Rbi", 0);
  for (c2_i97 = 0; c2_i97 < 18; c2_i97++) {
    c2_d_u[c2_i97] = c2_u.pbi[c2_i97];
  }

  c2_d_y = NULL;
  sf_mex_assign(&c2_d_y, sf_mex_create("y", c2_d_u, 0, 0U, 1U, 0U, 3, 3, 1, 6),
                FALSE);
  sf_mex_addfield(c2_y, c2_d_y, "pbi", "pbi", 0);
  for (c2_i98 = 0; c2_i98 < 216; c2_i98++) {
    c2_e_u[c2_i98] = c2_u.Adgbi[c2_i98];
  }

  c2_e_y = NULL;
  sf_mex_assign(&c2_e_y, sf_mex_create("y", c2_e_u, 0, 0U, 1U, 0U, 3, 6, 6, 6),
                FALSE);
  sf_mex_addfield(c2_y, c2_e_y, "Adgbi", "Adgbi", 0);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_emlrt_marshallIn(SFc2_uvmsInstanceStruct *chartInstance, const
  mxArray *c2_Tbi, const char_T *c2_identifier, c2_slBus2 *c2_y)
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_Tbi), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_Tbi);
}

static void c2_b_emlrt_marshallIn(SFc2_uvmsInstanceStruct *chartInstance, const
  mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, c2_slBus2 *c2_y)
{
  emlrtMsgIdentifier c2_thisId;
  static const char * c2_fieldNames[4] = { "gbi", "Rbi", "pbi", "Adgbi" };

  c2_thisId.fParent = c2_parentId;
  sf_mex_check_struct(c2_parentId, c2_u, 4, c2_fieldNames, 0U, 0);
  c2_thisId.fIdentifier = "gbi";
  c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c2_u, "gbi",
    "gbi", 0)), &c2_thisId, c2_y->gbi);
  c2_thisId.fIdentifier = "Rbi";
  c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c2_u, "Rbi",
    "Rbi", 0)), &c2_thisId, c2_y->Rbi);
  c2_thisId.fIdentifier = "pbi";
  c2_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c2_u, "pbi",
    "pbi", 0)), &c2_thisId, c2_y->pbi);
  c2_thisId.fIdentifier = "Adgbi";
  c2_f_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c2_u, "Adgbi",
    "Adgbi", 0)), &c2_thisId, c2_y->Adgbi);
  sf_mex_destroy(&c2_u);
}

static void c2_c_emlrt_marshallIn(SFc2_uvmsInstanceStruct *chartInstance, const
  mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[96])
{
  real_T c2_dv2[96];
  int32_T c2_i99;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv2, 1, 0, 0U, 1, 0U, 3, 4, 4,
                6);
  for (c2_i99 = 0; c2_i99 < 96; c2_i99++) {
    c2_y[c2_i99] = c2_dv2[c2_i99];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_d_emlrt_marshallIn(SFc2_uvmsInstanceStruct *chartInstance, const
  mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[54])
{
  real_T c2_dv3[54];
  int32_T c2_i100;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv3, 1, 0, 0U, 1, 0U, 3, 3, 3,
                6);
  for (c2_i100 = 0; c2_i100 < 54; c2_i100++) {
    c2_y[c2_i100] = c2_dv3[c2_i100];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_e_emlrt_marshallIn(SFc2_uvmsInstanceStruct *chartInstance, const
  mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[18])
{
  real_T c2_dv4[18];
  int32_T c2_i101;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv4, 1, 0, 0U, 1, 0U, 3, 3, 1,
                6);
  for (c2_i101 = 0; c2_i101 < 18; c2_i101++) {
    c2_y[c2_i101] = c2_dv4[c2_i101];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_f_emlrt_marshallIn(SFc2_uvmsInstanceStruct *chartInstance, const
  mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[216])
{
  real_T c2_dv5[216];
  int32_T c2_i102;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv5, 1, 0, 0U, 1, 0U, 3, 6, 6,
                6);
  for (c2_i102 = 0; c2_i102 < 216; c2_i102++) {
    c2_y[c2_i102] = c2_dv5[c2_i102];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_Tbi;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  c2_slBus2 c2_y;
  SFc2_uvmsInstanceStruct *chartInstance;
  chartInstance = (SFc2_uvmsInstanceStruct *)chartInstanceVoid;
  c2_Tbi = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_Tbi), &c2_thisId, &c2_y);
  sf_mex_destroy(&c2_Tbi);
  *(c2_slBus2 *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  c2_slBus1 c2_u;
  const mxArray *c2_y = NULL;
  int32_T c2_i103;
  real_T c2_b_u[6];
  const mxArray *c2_b_y = NULL;
  int32_T c2_i104;
  real_T c2_c_u[6];
  const mxArray *c2_c_y = NULL;
  int32_T c2_i105;
  real_T c2_d_u[6];
  const mxArray *c2_d_y = NULL;
  SFc2_uvmsInstanceStruct *chartInstance;
  chartInstance = (SFc2_uvmsInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(c2_slBus1 *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createstruct("structure", 2, 1, 1), FALSE);
  for (c2_i103 = 0; c2_i103 < 6; c2_i103++) {
    c2_b_u[c2_i103] = c2_u.a[c2_i103];
  }

  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_b_u, 0, 0U, 1U, 0U, 2, 6, 1),
                FALSE);
  sf_mex_addfield(c2_y, c2_b_y, "a", "a", 0);
  for (c2_i104 = 0; c2_i104 < 6; c2_i104++) {
    c2_c_u[c2_i104] = c2_u.d[c2_i104];
  }

  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", c2_c_u, 0, 0U, 1U, 0U, 2, 6, 1),
                FALSE);
  sf_mex_addfield(c2_y, c2_c_y, "d", "d", 0);
  for (c2_i105 = 0; c2_i105 < 6; c2_i105++) {
    c2_d_u[c2_i105] = c2_u.alpha[c2_i105];
  }

  c2_d_y = NULL;
  sf_mex_assign(&c2_d_y, sf_mex_create("y", c2_d_u, 0, 0U, 1U, 0U, 2, 6, 1),
                FALSE);
  sf_mex_addfield(c2_y, c2_d_y, "alpha", "alpha", 0);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i106;
  real_T c2_b_inData[6];
  int32_T c2_i107;
  real_T c2_u[6];
  const mxArray *c2_y = NULL;
  SFc2_uvmsInstanceStruct *chartInstance;
  chartInstance = (SFc2_uvmsInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i106 = 0; c2_i106 < 6; c2_i106++) {
    c2_b_inData[c2_i106] = (*(real_T (*)[6])c2_inData)[c2_i106];
  }

  for (c2_i107 = 0; c2_i107 < 6; c2_i107++) {
    c2_u[c2_i107] = c2_b_inData[c2_i107];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 6), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static const mxArray *c2_d_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_uvmsInstanceStruct *chartInstance;
  chartInstance = (SFc2_uvmsInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(real_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static real_T c2_g_emlrt_marshallIn(SFc2_uvmsInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_y;
  real_T c2_d0;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_d0, 1, 0, 0U, 0, 0U, 0);
  c2_y = c2_d0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_nargout;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y;
  SFc2_uvmsInstanceStruct *chartInstance;
  chartInstance = (SFc2_uvmsInstanceStruct *)chartInstanceVoid;
  c2_nargout = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_nargout), &c2_thisId);
  sf_mex_destroy(&c2_nargout);
  *(real_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_e_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i108;
  int32_T c2_i109;
  int32_T c2_i110;
  real_T c2_b_inData[16];
  int32_T c2_i111;
  int32_T c2_i112;
  int32_T c2_i113;
  real_T c2_u[16];
  const mxArray *c2_y = NULL;
  SFc2_uvmsInstanceStruct *chartInstance;
  chartInstance = (SFc2_uvmsInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i108 = 0;
  for (c2_i109 = 0; c2_i109 < 4; c2_i109++) {
    for (c2_i110 = 0; c2_i110 < 4; c2_i110++) {
      c2_b_inData[c2_i110 + c2_i108] = (*(real_T (*)[16])c2_inData)[c2_i110 +
        c2_i108];
    }

    c2_i108 += 4;
  }

  c2_i111 = 0;
  for (c2_i112 = 0; c2_i112 < 4; c2_i112++) {
    for (c2_i113 = 0; c2_i113 < 4; c2_i113++) {
      c2_u[c2_i113 + c2_i111] = c2_b_inData[c2_i113 + c2_i111];
    }

    c2_i111 += 4;
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 4, 4), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_h_emlrt_marshallIn(SFc2_uvmsInstanceStruct *chartInstance, const
  mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[16])
{
  real_T c2_dv6[16];
  int32_T c2_i114;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv6, 1, 0, 0U, 1, 0U, 2, 4, 4);
  for (c2_i114 = 0; c2_i114 < 16; c2_i114++) {
    c2_y[c2_i114] = c2_dv6[c2_i114];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_g;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[16];
  int32_T c2_i115;
  int32_T c2_i116;
  int32_T c2_i117;
  SFc2_uvmsInstanceStruct *chartInstance;
  chartInstance = (SFc2_uvmsInstanceStruct *)chartInstanceVoid;
  c2_g = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_g), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_g);
  c2_i115 = 0;
  for (c2_i116 = 0; c2_i116 < 4; c2_i116++) {
    for (c2_i117 = 0; c2_i117 < 4; c2_i117++) {
      (*(real_T (*)[16])c2_outData)[c2_i117 + c2_i115] = c2_y[c2_i117 + c2_i115];
    }

    c2_i115 += 4;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static void c2_i_emlrt_marshallIn(SFc2_uvmsInstanceStruct *chartInstance, const
  mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, c2_slBus1 *c2_y)
{
  emlrtMsgIdentifier c2_thisId;
  static const char * c2_fieldNames[3] = { "a", "d", "alpha" };

  c2_thisId.fParent = c2_parentId;
  sf_mex_check_struct(c2_parentId, c2_u, 3, c2_fieldNames, 0U, 0);
  c2_thisId.fIdentifier = "a";
  c2_j_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c2_u, "a", "a",
    0)), &c2_thisId, c2_y->a);
  c2_thisId.fIdentifier = "d";
  c2_j_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c2_u, "d", "d",
    0)), &c2_thisId, c2_y->d);
  c2_thisId.fIdentifier = "alpha";
  c2_j_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getfield(c2_u, "alpha",
    "alpha", 0)), &c2_thisId, c2_y->alpha);
  sf_mex_destroy(&c2_u);
}

static void c2_j_emlrt_marshallIn(SFc2_uvmsInstanceStruct *chartInstance, const
  mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[6])
{
  real_T c2_dv7[6];
  int32_T c2_i118;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv7, 1, 0, 0U, 1, 0U, 2, 6, 1);
  for (c2_i118 = 0; c2_i118 < 6; c2_i118++) {
    c2_y[c2_i118] = c2_dv7[c2_i118];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_DH;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  c2_slBus1 c2_y;
  SFc2_uvmsInstanceStruct *chartInstance;
  chartInstance = (SFc2_uvmsInstanceStruct *)chartInstanceVoid;
  c2_DH = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_i_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_DH), &c2_thisId, &c2_y);
  sf_mex_destroy(&c2_DH);
  *(c2_slBus1 *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static void c2_k_emlrt_marshallIn(SFc2_uvmsInstanceStruct *chartInstance, const
  mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[6])
{
  real_T c2_dv8[6];
  int32_T c2_i119;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv8, 1, 0, 0U, 1, 0U, 1, 6);
  for (c2_i119 = 0; c2_i119 < 6; c2_i119++) {
    c2_y[c2_i119] = c2_dv8[c2_i119];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_q;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[6];
  int32_T c2_i120;
  SFc2_uvmsInstanceStruct *chartInstance;
  chartInstance = (SFc2_uvmsInstanceStruct *)chartInstanceVoid;
  c2_q = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_k_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_q), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_q);
  for (c2_i120 = 0; c2_i120 < 6; c2_i120++) {
    (*(real_T (*)[6])c2_outData)[c2_i120] = c2_y[c2_i120];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_f_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i121;
  int32_T c2_i122;
  int32_T c2_i123;
  real_T c2_b_inData[9];
  int32_T c2_i124;
  int32_T c2_i125;
  int32_T c2_i126;
  real_T c2_u[9];
  const mxArray *c2_y = NULL;
  SFc2_uvmsInstanceStruct *chartInstance;
  chartInstance = (SFc2_uvmsInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i121 = 0;
  for (c2_i122 = 0; c2_i122 < 3; c2_i122++) {
    for (c2_i123 = 0; c2_i123 < 3; c2_i123++) {
      c2_b_inData[c2_i123 + c2_i121] = (*(real_T (*)[9])c2_inData)[c2_i123 +
        c2_i121];
    }

    c2_i121 += 3;
  }

  c2_i124 = 0;
  for (c2_i125 = 0; c2_i125 < 3; c2_i125++) {
    for (c2_i126 = 0; c2_i126 < 3; c2_i126++) {
      c2_u[c2_i126 + c2_i124] = c2_b_inData[c2_i126 + c2_i124];
    }

    c2_i124 += 3;
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 3, 3), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_l_emlrt_marshallIn(SFc2_uvmsInstanceStruct *chartInstance, const
  mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[9])
{
  real_T c2_dv9[9];
  int32_T c2_i127;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv9, 1, 0, 0U, 1, 0U, 2, 3, 3);
  for (c2_i127 = 0; c2_i127 < 9; c2_i127++) {
    c2_y[c2_i127] = c2_dv9[c2_i127];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_mat;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[9];
  int32_T c2_i128;
  int32_T c2_i129;
  int32_T c2_i130;
  SFc2_uvmsInstanceStruct *chartInstance;
  chartInstance = (SFc2_uvmsInstanceStruct *)chartInstanceVoid;
  c2_mat = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_mat), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_mat);
  c2_i128 = 0;
  for (c2_i129 = 0; c2_i129 < 3; c2_i129++) {
    for (c2_i130 = 0; c2_i130 < 3; c2_i130++) {
      (*(real_T (*)[9])c2_outData)[c2_i130 + c2_i128] = c2_y[c2_i130 + c2_i128];
    }

    c2_i128 += 3;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_g_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i131;
  real_T c2_b_inData[3];
  int32_T c2_i132;
  real_T c2_u[3];
  const mxArray *c2_y = NULL;
  SFc2_uvmsInstanceStruct *chartInstance;
  chartInstance = (SFc2_uvmsInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  for (c2_i131 = 0; c2_i131 < 3; c2_i131++) {
    c2_b_inData[c2_i131] = (*(real_T (*)[3])c2_inData)[c2_i131];
  }

  for (c2_i132 = 0; c2_i132 < 3; c2_i132++) {
    c2_u[c2_i132] = c2_b_inData[c2_i132];
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 1, 3), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_m_emlrt_marshallIn(SFc2_uvmsInstanceStruct *chartInstance, const
  mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[3])
{
  real_T c2_dv10[3];
  int32_T c2_i133;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv10, 1, 0, 0U, 1, 0U, 1, 3);
  for (c2_i133 = 0; c2_i133 < 3; c2_i133++) {
    c2_y[c2_i133] = c2_dv10[c2_i133];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_vec;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[3];
  int32_T c2_i134;
  SFc2_uvmsInstanceStruct *chartInstance;
  chartInstance = (SFc2_uvmsInstanceStruct *)chartInstanceVoid;
  c2_vec = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_m_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_vec), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_vec);
  for (c2_i134 = 0; c2_i134 < 3; c2_i134++) {
    (*(real_T (*)[3])c2_outData)[c2_i134] = c2_y[c2_i134];
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_h_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i135;
  int32_T c2_i136;
  int32_T c2_i137;
  real_T c2_b_inData[36];
  int32_T c2_i138;
  int32_T c2_i139;
  int32_T c2_i140;
  real_T c2_u[36];
  const mxArray *c2_y = NULL;
  SFc2_uvmsInstanceStruct *chartInstance;
  chartInstance = (SFc2_uvmsInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i135 = 0;
  for (c2_i136 = 0; c2_i136 < 6; c2_i136++) {
    for (c2_i137 = 0; c2_i137 < 6; c2_i137++) {
      c2_b_inData[c2_i137 + c2_i135] = (*(real_T (*)[36])c2_inData)[c2_i137 +
        c2_i135];
    }

    c2_i135 += 6;
  }

  c2_i138 = 0;
  for (c2_i139 = 0; c2_i139 < 6; c2_i139++) {
    for (c2_i140 = 0; c2_i140 < 6; c2_i140++) {
      c2_u[c2_i140 + c2_i138] = c2_b_inData[c2_i140 + c2_i138];
    }

    c2_i138 += 6;
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 2, 6, 6), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_n_emlrt_marshallIn(SFc2_uvmsInstanceStruct *chartInstance, const
  mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[36])
{
  real_T c2_dv11[36];
  int32_T c2_i141;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv11, 1, 0, 0U, 1, 0U, 2, 6, 6);
  for (c2_i141 = 0; c2_i141 < 36; c2_i141++) {
    c2_y[c2_i141] = c2_dv11[c2_i141];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_mat;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y[36];
  int32_T c2_i142;
  int32_T c2_i143;
  int32_T c2_i144;
  SFc2_uvmsInstanceStruct *chartInstance;
  chartInstance = (SFc2_uvmsInstanceStruct *)chartInstanceVoid;
  c2_mat = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_n_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_mat), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_mat);
  c2_i142 = 0;
  for (c2_i143 = 0; c2_i143 < 6; c2_i143++) {
    for (c2_i144 = 0; c2_i144 < 6; c2_i144++) {
      (*(real_T (*)[36])c2_outData)[c2_i144 + c2_i142] = c2_y[c2_i144 + c2_i142];
    }

    c2_i142 += 6;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

const mxArray *sf_c2_uvms_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo;
  c2_ResolvedFunctionInfo c2_info[28];
  const mxArray *c2_m0 = NULL;
  int32_T c2_i145;
  c2_ResolvedFunctionInfo *c2_r2;
  c2_nameCaptureInfo = NULL;
  c2_nameCaptureInfo = NULL;
  c2_info_helper(c2_info);
  sf_mex_assign(&c2_m0, sf_mex_createstruct("nameCaptureInfo", 1, 28), FALSE);
  for (c2_i145 = 0; c2_i145 < 28; c2_i145++) {
    c2_r2 = &c2_info[c2_i145];
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r2->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c2_r2->context)), "context", "nameCaptureInfo",
                    c2_i145);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r2->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c2_r2->name)), "name", "nameCaptureInfo", c2_i145);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r2->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c2_r2->dominantType)), "dominantType",
                    "nameCaptureInfo", c2_i145);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", c2_r2->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c2_r2->resolved)), "resolved", "nameCaptureInfo",
                    c2_i145);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r2->fileTimeLo,
      7, 0U, 0U, 0U, 0), "fileTimeLo", "nameCaptureInfo", c2_i145);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r2->fileTimeHi,
      7, 0U, 0U, 0U, 0), "fileTimeHi", "nameCaptureInfo", c2_i145);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r2->mFileTimeLo,
      7, 0U, 0U, 0U, 0), "mFileTimeLo", "nameCaptureInfo", c2_i145);
    sf_mex_addfield(c2_m0, sf_mex_create("nameCaptureInfo", &c2_r2->mFileTimeHi,
      7, 0U, 0U, 0U, 0), "mFileTimeHi", "nameCaptureInfo", c2_i145);
  }

  sf_mex_assign(&c2_nameCaptureInfo, c2_m0, FALSE);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c2_nameCaptureInfo);
  return c2_nameCaptureInfo;
}

static void c2_info_helper(c2_ResolvedFunctionInfo c2_info[28])
{
  c2_info[0].context = "";
  c2_info[0].name = "eye";
  c2_info[0].dominantType = "double";
  c2_info[0].resolved =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/eye.m";
  c2_info[0].fileTimeLo = 1286818688U;
  c2_info[0].fileTimeHi = 0U;
  c2_info[0].mFileTimeLo = 0U;
  c2_info[0].mFileTimeHi = 0U;
  c2_info[1].context =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c2_info[1].name = "eml_assert_valid_size_arg";
  c2_info[1].dominantType = "double";
  c2_info[1].resolved =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c2_info[1].fileTimeLo = 1286818694U;
  c2_info[1].fileTimeHi = 0U;
  c2_info[1].mFileTimeLo = 0U;
  c2_info[1].mFileTimeHi = 0U;
  c2_info[2].context =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!isintegral";
  c2_info[2].name = "isinf";
  c2_info[2].dominantType = "double";
  c2_info[2].resolved =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/isinf.m";
  c2_info[2].fileTimeLo = 1286818760U;
  c2_info[2].fileTimeHi = 0U;
  c2_info[2].mFileTimeLo = 0U;
  c2_info[2].mFileTimeHi = 0U;
  c2_info[3].context =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m!numel_for_size";
  c2_info[3].name = "mtimes";
  c2_info[3].dominantType = "double";
  c2_info[3].resolved =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[3].fileTimeLo = 1289519692U;
  c2_info[3].fileTimeHi = 0U;
  c2_info[3].mFileTimeLo = 0U;
  c2_info[3].mFileTimeHi = 0U;
  c2_info[4].context =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c2_info[4].name = "eml_index_class";
  c2_info[4].dominantType = "";
  c2_info[4].resolved =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[4].fileTimeLo = 1286818778U;
  c2_info[4].fileTimeHi = 0U;
  c2_info[4].mFileTimeLo = 0U;
  c2_info[4].mFileTimeHi = 0U;
  c2_info[5].context =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_assert_valid_size_arg.m";
  c2_info[5].name = "intmax";
  c2_info[5].dominantType = "char";
  c2_info[5].resolved =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/intmax.m";
  c2_info[5].fileTimeLo = 1311255316U;
  c2_info[5].fileTimeHi = 0U;
  c2_info[5].mFileTimeLo = 0U;
  c2_info[5].mFileTimeHi = 0U;
  c2_info[6].context =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c2_info[6].name = "eml_is_float_class";
  c2_info[6].dominantType = "char";
  c2_info[6].resolved =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_is_float_class.m";
  c2_info[6].fileTimeLo = 1286818782U;
  c2_info[6].fileTimeHi = 0U;
  c2_info[6].mFileTimeLo = 0U;
  c2_info[6].mFileTimeHi = 0U;
  c2_info[7].context =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c2_info[7].name = "min";
  c2_info[7].dominantType = "double";
  c2_info[7].resolved =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/datafun/min.m";
  c2_info[7].fileTimeLo = 1311255318U;
  c2_info[7].fileTimeHi = 0U;
  c2_info[7].mFileTimeLo = 0U;
  c2_info[7].mFileTimeHi = 0U;
  c2_info[8].context =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/datafun/min.m";
  c2_info[8].name = "eml_min_or_max";
  c2_info[8].dominantType = "char";
  c2_info[8].resolved =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_min_or_max.m";
  c2_info[8].fileTimeLo = 1303146212U;
  c2_info[8].fileTimeHi = 0U;
  c2_info[8].mFileTimeLo = 0U;
  c2_info[8].mFileTimeHi = 0U;
  c2_info[9].context =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c2_info[9].name = "eml_scalar_eg";
  c2_info[9].dominantType = "double";
  c2_info[9].resolved =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c2_info[9].fileTimeLo = 1286818796U;
  c2_info[9].fileTimeHi = 0U;
  c2_info[9].mFileTimeLo = 0U;
  c2_info[9].mFileTimeHi = 0U;
  c2_info[10].context =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c2_info[10].name = "eml_scalexp_alloc";
  c2_info[10].dominantType = "double";
  c2_info[10].resolved =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m";
  c2_info[10].fileTimeLo = 1286818796U;
  c2_info[10].fileTimeHi = 0U;
  c2_info[10].mFileTimeLo = 0U;
  c2_info[10].mFileTimeHi = 0U;
  c2_info[11].context =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum";
  c2_info[11].name = "eml_index_class";
  c2_info[11].dominantType = "";
  c2_info[11].resolved =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[11].fileTimeLo = 1286818778U;
  c2_info[11].fileTimeHi = 0U;
  c2_info[11].mFileTimeLo = 0U;
  c2_info[11].mFileTimeHi = 0U;
  c2_info[12].context =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum";
  c2_info[12].name = "eml_scalar_eg";
  c2_info[12].dominantType = "double";
  c2_info[12].resolved =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c2_info[12].fileTimeLo = 1286818796U;
  c2_info[12].fileTimeHi = 0U;
  c2_info[12].mFileTimeLo = 0U;
  c2_info[12].mFileTimeHi = 0U;
  c2_info[13].context =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c2_info[13].name = "eml_index_class";
  c2_info[13].dominantType = "";
  c2_info[13].resolved =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[13].fileTimeLo = 1286818778U;
  c2_info[13].fileTimeHi = 0U;
  c2_info[13].mFileTimeLo = 0U;
  c2_info[13].mFileTimeHi = 0U;
  c2_info[14].context =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/eye.m!eye_internal";
  c2_info[14].name = "eml_int_forloop_overflow_check";
  c2_info[14].dominantType = "";
  c2_info[14].resolved =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m";
  c2_info[14].fileTimeLo = 1311255316U;
  c2_info[14].fileTimeHi = 0U;
  c2_info[14].mFileTimeLo = 0U;
  c2_info[14].mFileTimeHi = 0U;
  c2_info[15].context =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper";
  c2_info[15].name = "intmax";
  c2_info[15].dominantType = "char";
  c2_info[15].resolved =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/elmat/intmax.m";
  c2_info[15].fileTimeLo = 1311255316U;
  c2_info[15].fileTimeHi = 0U;
  c2_info[15].mFileTimeLo = 0U;
  c2_info[15].mFileTimeHi = 0U;
  c2_info[16].context = "";
  c2_info[16].name = "cos";
  c2_info[16].dominantType = "double";
  c2_info[16].resolved =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/elfun/cos.m";
  c2_info[16].fileTimeLo = 1286818706U;
  c2_info[16].fileTimeHi = 0U;
  c2_info[16].mFileTimeLo = 0U;
  c2_info[16].mFileTimeHi = 0U;
  c2_info[17].context =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/elfun/cos.m";
  c2_info[17].name = "eml_scalar_cos";
  c2_info[17].dominantType = "double";
  c2_info[17].resolved =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m";
  c2_info[17].fileTimeLo = 1286818722U;
  c2_info[17].fileTimeHi = 0U;
  c2_info[17].mFileTimeLo = 0U;
  c2_info[17].mFileTimeHi = 0U;
  c2_info[18].context = "";
  c2_info[18].name = "sin";
  c2_info[18].dominantType = "double";
  c2_info[18].resolved =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/elfun/sin.m";
  c2_info[18].fileTimeLo = 1286818750U;
  c2_info[18].fileTimeHi = 0U;
  c2_info[18].mFileTimeLo = 0U;
  c2_info[18].mFileTimeHi = 0U;
  c2_info[19].context =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/elfun/sin.m";
  c2_info[19].name = "eml_scalar_sin";
  c2_info[19].dominantType = "double";
  c2_info[19].resolved =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m";
  c2_info[19].fileTimeLo = 1286818736U;
  c2_info[19].fileTimeHi = 0U;
  c2_info[19].mFileTimeLo = 0U;
  c2_info[19].mFileTimeHi = 0U;
  c2_info[20].context = "";
  c2_info[20].name = "mtimes";
  c2_info[20].dominantType = "double";
  c2_info[20].resolved =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[20].fileTimeLo = 1289519692U;
  c2_info[20].fileTimeHi = 0U;
  c2_info[20].mFileTimeLo = 0U;
  c2_info[20].mFileTimeHi = 0U;
  c2_info[21].context =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[21].name = "eml_index_class";
  c2_info[21].dominantType = "";
  c2_info[21].resolved =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c2_info[21].fileTimeLo = 1286818778U;
  c2_info[21].fileTimeHi = 0U;
  c2_info[21].mFileTimeLo = 0U;
  c2_info[21].mFileTimeHi = 0U;
  c2_info[22].context =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[22].name = "eml_scalar_eg";
  c2_info[22].dominantType = "double";
  c2_info[22].resolved =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c2_info[22].fileTimeLo = 1286818796U;
  c2_info[22].fileTimeHi = 0U;
  c2_info[22].mFileTimeLo = 0U;
  c2_info[22].mFileTimeHi = 0U;
  c2_info[23].context =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[23].name = "eml_xgemm";
  c2_info[23].dominantType = "int32";
  c2_info[23].resolved =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c2_info[23].fileTimeLo = 1299076772U;
  c2_info[23].fileTimeHi = 0U;
  c2_info[23].mFileTimeLo = 0U;
  c2_info[23].mFileTimeHi = 0U;
  c2_info[24].context =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/eml_xgemm.m";
  c2_info[24].name = "eml_blas_inline";
  c2_info[24].dominantType = "";
  c2_info[24].resolved =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/eml_blas_inline.m";
  c2_info[24].fileTimeLo = 1299076768U;
  c2_info[24].fileTimeHi = 0U;
  c2_info[24].mFileTimeLo = 0U;
  c2_info[24].mFileTimeHi = 0U;
  c2_info[25].context =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m!below_threshold";
  c2_info[25].name = "mtimes";
  c2_info[25].dominantType = "double";
  c2_info[25].resolved =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/ops/mtimes.m";
  c2_info[25].fileTimeLo = 1289519692U;
  c2_info[25].fileTimeHi = 0U;
  c2_info[25].mFileTimeLo = 0U;
  c2_info[25].mFileTimeHi = 0U;
  c2_info[26].context =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c2_info[26].name = "eml_scalar_eg";
  c2_info[26].dominantType = "double";
  c2_info[26].resolved =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c2_info[26].fileTimeLo = 1286818796U;
  c2_info[26].fileTimeHi = 0U;
  c2_info[26].mFileTimeLo = 0U;
  c2_info[26].mFileTimeHi = 0U;
  c2_info[27].context =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xgemm.m";
  c2_info[27].name = "eml_refblas_xgemm";
  c2_info[27].dominantType = "int32";
  c2_info[27].resolved =
    "[ILXE]/usr/local/MATLAB/R2012a/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xgemm.m";
  c2_info[27].fileTimeLo = 1299076774U;
  c2_info[27].fileTimeHi = 0U;
  c2_info[27].mFileTimeLo = 0U;
  c2_info[27].mFileTimeHi = 0U;
}

static void c2_eye(SFc2_uvmsInstanceStruct *chartInstance, real_T c2_I[16])
{
  int32_T c2_i146;
  int32_T c2_i;
  int32_T c2_b_i;
  for (c2_i146 = 0; c2_i146 < 16; c2_i146++) {
    c2_I[c2_i146] = 0.0;
  }

  c2_eml_int_forloop_overflow_check(chartInstance);
  for (c2_i = 1; c2_i < 5; c2_i++) {
    c2_b_i = c2_i;
    c2_I[(_SFD_EML_ARRAY_BOUNDS_CHECK("", (int32_T)_SFD_INTEGER_CHECK("",
            (real_T)c2_b_i), 1, 4, 1, 0) + ((_SFD_EML_ARRAY_BOUNDS_CHECK("",
             (int32_T)_SFD_INTEGER_CHECK("", (real_T)c2_b_i), 1, 4, 2, 0) - 1) <<
           2)) - 1] = 1.0;
  }
}

static void c2_eml_int_forloop_overflow_check(SFc2_uvmsInstanceStruct
  *chartInstance)
{
}

static void c2_getHom(SFc2_uvmsInstanceStruct *chartInstance, real_T c2_q[6],
                      c2_slBus1 *c2_DH, real_T c2_i, real_T c2_mat[16])
{
  uint32_T c2_debug_family_var_map[10];
  real_T c2_alpha;
  real_T c2_a;
  real_T c2_d;
  real_T c2_theta;
  real_T c2_nargin = 3.0;
  real_T c2_nargout = 1.0;
  real_T c2_dv12[16];
  int32_T c2_i147;
  real_T c2_x;
  real_T c2_b_x;
  real_T c2_c_x;
  real_T c2_d_x;
  real_T c2_e_x;
  real_T c2_f_x;
  real_T c2_b_a;
  real_T c2_b;
  real_T c2_y;
  real_T c2_g_x;
  real_T c2_h_x;
  real_T c2_i_x;
  real_T c2_j_x;
  real_T c2_c_a;
  real_T c2_b_b;
  real_T c2_b_y;
  real_T c2_k_x;
  real_T c2_l_x;
  real_T c2_d_a;
  real_T c2_c_b;
  real_T c2_c_y;
  real_T c2_m_x;
  real_T c2_n_x;
  real_T c2_o_x;
  real_T c2_p_x;
  real_T c2_q_x;
  real_T c2_r_x;
  real_T c2_e_a;
  real_T c2_d_b;
  real_T c2_d_y;
  real_T c2_s_x;
  real_T c2_t_x;
  real_T c2_u_x;
  real_T c2_v_x;
  real_T c2_f_a;
  real_T c2_e_b;
  real_T c2_e_y;
  real_T c2_w_x;
  real_T c2_x_x;
  real_T c2_g_a;
  real_T c2_f_b;
  real_T c2_f_y;
  real_T c2_y_x;
  real_T c2_ab_x;
  real_T c2_bb_x;
  real_T c2_cb_x;
  int32_T c2_i148;
  int32_T c2_i149;
  static real_T c2_dv13[4] = { 0.0, 0.0, 0.0, 1.0 };

  sf_debug_symbol_scope_push_eml(0U, 10U, 10U, c2_b_debug_family_names,
    c2_debug_family_var_map);
  sf_debug_symbol_scope_add_eml_importable(&c2_alpha, 0U, c2_d_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_a, 1U, c2_d_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_d, 2U, c2_d_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_theta, 3U, c2_d_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargin, 4U, c2_d_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargout, 5U, c2_d_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_q, 6U, c2_c_sf_marshallOut,
    c2_e_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_DH, 7U, c2_b_sf_marshallOut,
    c2_d_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_i, 8U, c2_d_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_mat, 9U, c2_e_sf_marshallOut,
    c2_c_sf_marshallIn);
  CV_EML_FCN(0, 1);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 62);
  c2_alpha = c2_DH->alpha[_SFD_EML_ARRAY_BOUNDS_CHECK("DH.alpha", (int32_T)
    _SFD_INTEGER_CHECK("i", c2_i), 1, 6, 1, 0) - 1];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 63);
  c2_a = c2_DH->a[_SFD_EML_ARRAY_BOUNDS_CHECK("DH.a", (int32_T)
    _SFD_INTEGER_CHECK("i", c2_i), 1, 6, 1, 0) - 1];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 64);
  c2_d = c2_DH->d[_SFD_EML_ARRAY_BOUNDS_CHECK("DH.d", (int32_T)
    _SFD_INTEGER_CHECK("i", c2_i), 1, 6, 1, 0) - 1];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 65);
  c2_theta = c2_q[_SFD_EML_ARRAY_BOUNDS_CHECK("q", (int32_T)_SFD_INTEGER_CHECK(
    "i", c2_i), 1, 6, 1, 0) - 1];
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 66);
  c2_eye(chartInstance, c2_dv12);
  for (c2_i147 = 0; c2_i147 < 16; c2_i147++) {
    c2_mat[c2_i147] = c2_dv12[c2_i147];
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 67);
  c2_x = c2_theta;
  c2_b_x = c2_x;
  c2_b_x = muDoubleScalarCos(c2_b_x);
  c2_c_x = c2_theta;
  c2_d_x = c2_c_x;
  c2_d_x = muDoubleScalarSin(c2_d_x);
  c2_e_x = c2_alpha;
  c2_f_x = c2_e_x;
  c2_f_x = muDoubleScalarCos(c2_f_x);
  c2_b_a = -c2_d_x;
  c2_b = c2_f_x;
  c2_y = c2_b_a * c2_b;
  c2_g_x = c2_theta;
  c2_h_x = c2_g_x;
  c2_h_x = muDoubleScalarSin(c2_h_x);
  c2_i_x = c2_alpha;
  c2_j_x = c2_i_x;
  c2_j_x = muDoubleScalarSin(c2_j_x);
  c2_c_a = c2_h_x;
  c2_b_b = c2_j_x;
  c2_b_y = c2_c_a * c2_b_b;
  c2_k_x = c2_theta;
  c2_l_x = c2_k_x;
  c2_l_x = muDoubleScalarCos(c2_l_x);
  c2_d_a = c2_a;
  c2_c_b = c2_l_x;
  c2_c_y = c2_d_a * c2_c_b;
  c2_m_x = c2_theta;
  c2_n_x = c2_m_x;
  c2_n_x = muDoubleScalarSin(c2_n_x);
  c2_o_x = c2_theta;
  c2_p_x = c2_o_x;
  c2_p_x = muDoubleScalarCos(c2_p_x);
  c2_q_x = c2_alpha;
  c2_r_x = c2_q_x;
  c2_r_x = muDoubleScalarCos(c2_r_x);
  c2_e_a = c2_p_x;
  c2_d_b = c2_r_x;
  c2_d_y = c2_e_a * c2_d_b;
  c2_s_x = c2_theta;
  c2_t_x = c2_s_x;
  c2_t_x = muDoubleScalarCos(c2_t_x);
  c2_u_x = c2_alpha;
  c2_v_x = c2_u_x;
  c2_v_x = muDoubleScalarSin(c2_v_x);
  c2_f_a = -c2_t_x;
  c2_e_b = c2_v_x;
  c2_e_y = c2_f_a * c2_e_b;
  c2_w_x = c2_theta;
  c2_x_x = c2_w_x;
  c2_x_x = muDoubleScalarSin(c2_x_x);
  c2_g_a = c2_a;
  c2_f_b = c2_x_x;
  c2_f_y = c2_g_a * c2_f_b;
  c2_y_x = c2_alpha;
  c2_ab_x = c2_y_x;
  c2_ab_x = muDoubleScalarSin(c2_ab_x);
  c2_bb_x = c2_alpha;
  c2_cb_x = c2_bb_x;
  c2_cb_x = muDoubleScalarCos(c2_cb_x);
  c2_mat[0] = c2_b_x;
  c2_mat[4] = c2_y;
  c2_mat[8] = c2_b_y;
  c2_mat[12] = c2_c_y;
  c2_mat[1] = c2_n_x;
  c2_mat[5] = c2_d_y;
  c2_mat[9] = c2_e_y;
  c2_mat[13] = c2_f_y;
  c2_mat[2] = 0.0;
  c2_mat[6] = c2_ab_x;
  c2_mat[10] = c2_cb_x;
  c2_mat[14] = c2_d;
  c2_i148 = 0;
  for (c2_i149 = 0; c2_i149 < 4; c2_i149++) {
    c2_mat[c2_i148 + 3] = c2_dv13[c2_i149];
    c2_i148 += 4;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -67);
  sf_debug_symbol_scope_pop();
}

static void c2_eml_scalar_eg(SFc2_uvmsInstanceStruct *chartInstance)
{
}

static void c2_getAdgbi(SFc2_uvmsInstanceStruct *chartInstance, real_T c2_R[9],
  real_T c2_p[3], real_T c2_mat[36])
{
  uint32_T c2_debug_family_var_map[6];
  real_T c2_ps[9];
  real_T c2_nargin = 2.0;
  real_T c2_nargout = 1.0;
  int32_T c2_i150;
  int32_T c2_i151;
  real_T c2_vec[3];
  uint32_T c2_b_debug_family_var_map[4];
  real_T c2_b_nargin = 1.0;
  real_T c2_b_nargout = 1.0;
  int32_T c2_i152;
  real_T c2_a[9];
  int32_T c2_i153;
  real_T c2_b[9];
  int32_T c2_i154;
  int32_T c2_i155;
  int32_T c2_i156;
  real_T c2_y[9];
  int32_T c2_i157;
  int32_T c2_i158;
  int32_T c2_i159;
  int32_T c2_i160;
  int32_T c2_i161;
  int32_T c2_i162;
  int32_T c2_i163;
  int32_T c2_i164;
  int32_T c2_i165;
  int32_T c2_i166;
  int32_T c2_i167;
  int32_T c2_i168;
  int32_T c2_i169;
  int32_T c2_i170;
  int32_T c2_i171;
  int32_T c2_i172;
  int32_T c2_i173;
  sf_debug_symbol_scope_push_eml(0U, 6U, 6U, c2_f_debug_family_names,
    c2_debug_family_var_map);
  sf_debug_symbol_scope_add_eml_importable(c2_ps, 0U, c2_f_sf_marshallOut,
    c2_f_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargin, 1U, c2_d_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_nargout, 2U, c2_d_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_R, 3U, c2_f_sf_marshallOut,
    c2_f_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_p, 4U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_mat, 5U, c2_h_sf_marshallOut,
    c2_h_sf_marshallIn);
  CV_EML_FCN(0, 4);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 90);
  for (c2_i150 = 0; c2_i150 < 36; c2_i150++) {
    c2_mat[c2_i150] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 91);
  for (c2_i151 = 0; c2_i151 < 3; c2_i151++) {
    c2_vec[c2_i151] = c2_p[c2_i151];
  }

  sf_debug_symbol_scope_push_eml(0U, 4U, 4U, c2_e_debug_family_names,
    c2_b_debug_family_var_map);
  sf_debug_symbol_scope_add_eml_importable(&c2_b_nargin, 0U, c2_d_sf_marshallOut,
    c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(&c2_b_nargout, 1U,
    c2_d_sf_marshallOut, c2_b_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_vec, 2U, c2_g_sf_marshallOut,
    c2_g_sf_marshallIn);
  sf_debug_symbol_scope_add_eml_importable(c2_ps, 3U, c2_f_sf_marshallOut,
    c2_f_sf_marshallIn);
  CV_EML_FCN(0, 5);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 98);
  c2_ps[0] = 0.0;
  c2_ps[3] = -c2_vec[2];
  c2_ps[6] = c2_vec[1];
  c2_ps[1] = c2_vec[2];
  c2_ps[4] = 0.0;
  c2_ps[7] = c2_vec[0];
  c2_ps[2] = -c2_vec[1];
  c2_ps[5] = c2_vec[0];
  c2_ps[8] = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -98);
  sf_debug_symbol_scope_pop();
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 92);
  for (c2_i152 = 0; c2_i152 < 9; c2_i152++) {
    c2_a[c2_i152] = c2_ps[c2_i152];
  }

  for (c2_i153 = 0; c2_i153 < 9; c2_i153++) {
    c2_b[c2_i153] = c2_R[c2_i153];
  }

  c2_b_eml_scalar_eg(chartInstance);
  c2_b_eml_scalar_eg(chartInstance);
  for (c2_i154 = 0; c2_i154 < 3; c2_i154++) {
    c2_i155 = 0;
    for (c2_i156 = 0; c2_i156 < 3; c2_i156++) {
      c2_y[c2_i155 + c2_i154] = 0.0;
      c2_i157 = 0;
      for (c2_i158 = 0; c2_i158 < 3; c2_i158++) {
        c2_y[c2_i155 + c2_i154] += c2_a[c2_i157 + c2_i154] * c2_b[c2_i158 +
          c2_i155];
        c2_i157 += 3;
      }

      c2_i155 += 3;
    }
  }

  c2_i159 = 0;
  c2_i160 = 0;
  for (c2_i161 = 0; c2_i161 < 3; c2_i161++) {
    for (c2_i162 = 0; c2_i162 < 3; c2_i162++) {
      c2_mat[c2_i162 + c2_i159] = c2_R[c2_i162 + c2_i160];
    }

    c2_i159 += 6;
    c2_i160 += 3;
  }

  c2_i163 = 0;
  c2_i164 = 0;
  for (c2_i165 = 0; c2_i165 < 3; c2_i165++) {
    for (c2_i166 = 0; c2_i166 < 3; c2_i166++) {
      c2_mat[(c2_i166 + c2_i163) + 18] = c2_y[c2_i166 + c2_i164];
    }

    c2_i163 += 6;
    c2_i164 += 3;
  }

  c2_i167 = 0;
  for (c2_i168 = 0; c2_i168 < 3; c2_i168++) {
    for (c2_i169 = 0; c2_i169 < 3; c2_i169++) {
      c2_mat[(c2_i169 + c2_i167) + 3] = 0.0;
    }

    c2_i167 += 6;
  }

  c2_i170 = 0;
  c2_i171 = 0;
  for (c2_i172 = 0; c2_i172 < 3; c2_i172++) {
    for (c2_i173 = 0; c2_i173 < 3; c2_i173++) {
      c2_mat[(c2_i173 + c2_i170) + 21] = c2_R[c2_i173 + c2_i171];
    }

    c2_i170 += 6;
    c2_i171 += 3;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -92);
  sf_debug_symbol_scope_pop();
}

static void c2_b_eml_scalar_eg(SFc2_uvmsInstanceStruct *chartInstance)
{
}

static const mxArray *c2_i_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_uvmsInstanceStruct *chartInstance;
  chartInstance = (SFc2_uvmsInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(int32_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static int32_T c2_o_emlrt_marshallIn(SFc2_uvmsInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  int32_T c2_y;
  int32_T c2_i174;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_i174, 1, 6, 0U, 0, 0U, 0);
  c2_y = c2_i174;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_sfEvent;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_y;
  SFc2_uvmsInstanceStruct *chartInstance;
  chartInstance = (SFc2_uvmsInstanceStruct *)chartInstanceVoid;
  c2_b_sfEvent = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_o_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_sfEvent),
    &c2_thisId);
  sf_mex_destroy(&c2_b_sfEvent);
  *(int32_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_DH_bus_io(void *chartInstanceVoid, void *c2_pData)
{
  const mxArray *c2_mxVal = NULL;
  int32_T c2_i175;
  c2_slBus1 c2_tmp;
  int32_T c2_i176;
  int32_T c2_i177;
  SFc2_uvmsInstanceStruct *chartInstance;
  chartInstance = (SFc2_uvmsInstanceStruct *)chartInstanceVoid;
  c2_mxVal = NULL;
  for (c2_i175 = 0; c2_i175 < 6; c2_i175++) {
    c2_tmp.a[c2_i175] = ((real_T *)((char_T *)c2_pData + 0))[c2_i175];
  }

  for (c2_i176 = 0; c2_i176 < 6; c2_i176++) {
    c2_tmp.d[c2_i176] = ((real_T *)((char_T *)c2_pData + 48))[c2_i176];
  }

  for (c2_i177 = 0; c2_i177 < 6; c2_i177++) {
    c2_tmp.alpha[c2_i177] = ((real_T *)((char_T *)c2_pData + 96))[c2_i177];
  }

  sf_mex_assign(&c2_mxVal, c2_b_sf_marshallOut(chartInstance, &c2_tmp), FALSE);
  return c2_mxVal;
}

static const mxArray *c2_Tbi_bus_io(void *chartInstanceVoid, void *c2_pData)
{
  const mxArray *c2_mxVal = NULL;
  int32_T c2_i178;
  int32_T c2_i179;
  int32_T c2_i180;
  int32_T c2_i181;
  int32_T c2_i182;
  c2_slBus2 c2_tmp;
  int32_T c2_i183;
  int32_T c2_i184;
  int32_T c2_i185;
  int32_T c2_i186;
  int32_T c2_i187;
  int32_T c2_i188;
  int32_T c2_i189;
  int32_T c2_i190;
  int32_T c2_i191;
  int32_T c2_i192;
  int32_T c2_i193;
  int32_T c2_i194;
  int32_T c2_i195;
  SFc2_uvmsInstanceStruct *chartInstance;
  chartInstance = (SFc2_uvmsInstanceStruct *)chartInstanceVoid;
  c2_mxVal = NULL;
  c2_i178 = 0;
  for (c2_i179 = 0; c2_i179 < 6; c2_i179++) {
    c2_i180 = 0;
    for (c2_i181 = 0; c2_i181 < 4; c2_i181++) {
      for (c2_i182 = 0; c2_i182 < 4; c2_i182++) {
        c2_tmp.gbi[(c2_i182 + c2_i180) + c2_i178] = ((real_T *)((char_T *)
          c2_pData + 0))[(c2_i182 + c2_i180) + c2_i178];
      }

      c2_i180 += 4;
    }

    c2_i178 += 16;
  }

  c2_i183 = 0;
  for (c2_i184 = 0; c2_i184 < 6; c2_i184++) {
    c2_i185 = 0;
    for (c2_i186 = 0; c2_i186 < 3; c2_i186++) {
      for (c2_i187 = 0; c2_i187 < 3; c2_i187++) {
        c2_tmp.Rbi[(c2_i187 + c2_i185) + c2_i183] = ((real_T *)((char_T *)
          c2_pData + 768))[(c2_i187 + c2_i185) + c2_i183];
      }

      c2_i185 += 3;
    }

    c2_i183 += 9;
  }

  c2_i188 = 0;
  for (c2_i189 = 0; c2_i189 < 6; c2_i189++) {
    for (c2_i190 = 0; c2_i190 < 3; c2_i190++) {
      c2_tmp.pbi[c2_i190 + c2_i188] = ((real_T *)((char_T *)c2_pData + 1200))
        [c2_i190 + c2_i188];
    }

    c2_i188 += 3;
  }

  c2_i191 = 0;
  for (c2_i192 = 0; c2_i192 < 6; c2_i192++) {
    c2_i193 = 0;
    for (c2_i194 = 0; c2_i194 < 6; c2_i194++) {
      for (c2_i195 = 0; c2_i195 < 6; c2_i195++) {
        c2_tmp.Adgbi[(c2_i195 + c2_i193) + c2_i191] = ((real_T *)((char_T *)
          c2_pData + 1344))[(c2_i195 + c2_i193) + c2_i191];
      }

      c2_i193 += 6;
    }

    c2_i191 += 36;
  }

  sf_mex_assign(&c2_mxVal, c2_sf_marshallOut(chartInstance, &c2_tmp), FALSE);
  return c2_mxVal;
}

static uint8_T c2_p_emlrt_marshallIn(SFc2_uvmsInstanceStruct *chartInstance,
  const mxArray *c2_b_is_active_c2_uvms, const char_T *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_q_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_is_active_c2_uvms),
    &c2_thisId);
  sf_mex_destroy(&c2_b_is_active_c2_uvms);
  return c2_y;
}

static uint8_T c2_q_emlrt_marshallIn(SFc2_uvmsInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u0;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_u0, 1, 3, 0U, 0, 0U, 0);
  c2_y = c2_u0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void init_dsm_address_info(SFc2_uvmsInstanceStruct *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c2_uvms_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(4157050884U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(4120658905U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(174906981U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3540394542U);
}

mxArray *sf_c2_uvms_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("w4FonlYIYGQpZyZywIE92D");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(6);
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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(13));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));
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
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(13));
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

static const mxArray *sf_get_sim_state_info_c2_uvms(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x2'type','srcId','name','auxInfo'{{M[1],M[6],T\"Tbi\",},{M[8],M[0],T\"is_active_c2_uvms\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 2, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_uvms_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_uvmsInstanceStruct *chartInstance;
    chartInstance = (SFc2_uvmsInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart(_uvmsMachineNumber_,
          2,
          1,
          1,
          3,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"q");
          _SFD_SET_DATA_PROPS(1,1,1,0,"DH");
          _SFD_SET_DATA_PROPS(2,2,0,1,"Tbi");
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
        _SFD_CV_INIT_EML(0,1,6,0,0,0,1,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,1517);
        _SFD_CV_INIT_EML_FCN(0,1,"getHom",1623,-1,1967);
        _SFD_CV_INIT_EML_FCN(0,2,"getPos",2014,-1,2061);
        _SFD_CV_INIT_EML_FCN(0,3,"getRot",2121,-1,2169);
        _SFD_CV_INIT_EML_FCN(0,4,"getAdgbi",2172,-1,2279);
        _SFD_CV_INIT_EML_FCN(0,5,"skew",2343,-1,2440);
        _SFD_CV_INIT_EML_FOR(0,1,0,224,234,457);
        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 6;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c2_c_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(1,SF_STRUCT,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_DH_bus_io,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_STRUCT,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_Tbi_bus_io,(MexInFcnForType)NULL);

        {
          c2_slBus1 *c2_DH;
          c2_slBus2 *c2_Tbi;
          real_T (*c2_q)[6];
          c2_Tbi = (c2_slBus2 *)ssGetOutputPortSignal(chartInstance->S, 1);
          c2_DH = (c2_slBus1 *)ssGetInputPortSignal(chartInstance->S, 1);
          c2_q = (real_T (*)[6])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c2_q);
          _SFD_SET_DATA_VALUE_PTR(1U, c2_DH);
          _SFD_SET_DATA_VALUE_PTR(2U, c2_Tbi);
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
  return "lWmcLwobqKohOixkogYl9G";
}

static void sf_opaque_initialize_c2_uvms(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc2_uvmsInstanceStruct*) chartInstanceVar)->S,0);
  initialize_params_c2_uvms((SFc2_uvmsInstanceStruct*) chartInstanceVar);
  initialize_c2_uvms((SFc2_uvmsInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c2_uvms(void *chartInstanceVar)
{
  enable_c2_uvms((SFc2_uvmsInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c2_uvms(void *chartInstanceVar)
{
  disable_c2_uvms((SFc2_uvmsInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c2_uvms(void *chartInstanceVar)
{
  sf_c2_uvms((SFc2_uvmsInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c2_uvms(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c2_uvms((SFc2_uvmsInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_uvms();/* state var info */
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

extern void sf_internal_set_sim_state_c2_uvms(SimStruct* S, const mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_uvms();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c2_uvms((SFc2_uvmsInstanceStruct*)chartInfo->chartInstance,
                        mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c2_uvms(SimStruct* S)
{
  return sf_internal_get_sim_state_c2_uvms(S);
}

static void sf_opaque_set_sim_state_c2_uvms(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c2_uvms(S, st);
}

static void sf_opaque_terminate_c2_uvms(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_uvmsInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c2_uvms((SFc2_uvmsInstanceStruct*) chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }

  unload_uvms_optimization_info();
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc2_uvms((SFc2_uvmsInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_uvms(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c2_uvms((SFc2_uvmsInstanceStruct*)(((ChartInfoStruct *)
      ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c2_uvms(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_uvms_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,2,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,2,
      "gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,2,2);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,2,1);
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,2);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(913296113U));
  ssSetChecksum1(S,(4253184671U));
  ssSetChecksum2(S,(1287656868U));
  ssSetChecksum3(S,(3044291470U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c2_uvms(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_uvms(SimStruct *S)
{
  SFc2_uvmsInstanceStruct *chartInstance;
  chartInstance = (SFc2_uvmsInstanceStruct *)malloc(sizeof
    (SFc2_uvmsInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc2_uvmsInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c2_uvms;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c2_uvms;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c2_uvms;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_uvms;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_uvms;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c2_uvms;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c2_uvms;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c2_uvms;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_uvms;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_uvms;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c2_uvms;
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

void c2_uvms_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_uvms(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_uvms(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_uvms(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_uvms_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
