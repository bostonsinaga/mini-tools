#ifndef __MINI_TOOLS__TYPE_H__
#define __MINI_TOOLS__TYPE_H__

#include <string>
#include <vector>

namespace mini_tools {

  /** Flags for direction of sorting process */

  enum SortOrderFlag {DESCENDING, ASCENDING};
  enum SortPriorityFlag {LETTER_LOWER, LETTER_UPPER};

  /** SHORTENED TYPES */
  
  typedef short int SI;
  typedef long int LI;
  typedef long long int LLI;
  typedef unsigned short int USI;
  typedef unsigned int UI;
  typedef unsigned long int ULI;
  typedef unsigned long long int ULLI;
  typedef long double LD;

  /** SHORTENED VALUE VECTORS */

  typedef std::vector<bool> VEC_BOL;
  typedef std::vector<std::string> VEC_STR;
  typedef std::vector<char> VEC_CHR;
  typedef std::vector<wchar_t> VEC_WCH;
  typedef std::vector<int> VEC_INT;
  typedef std::vector<SI> VEC_SI;
  typedef std::vector<LI> VEC_LI;
  typedef std::vector<LLI> VEC_LLI;
  typedef std::vector<USI> VEC_USI;
  typedef std::vector<UI> VEC_UI;
  typedef std::vector<ULI> VEC_ULI;
  typedef std::vector<ULLI> VEC_ULLI;
  typedef std::vector<size_t> VEC_SZ;
  typedef std::vector<time_t> VEC_TM;
  typedef std::vector<float> VEC_FLT;
  typedef std::vector<double> VEC_DBL;
  typedef std::vector<LD> VEC_LD;

  typedef std::vector<VEC_BOL> VEC2_BOL;
  typedef std::vector<VEC_STR> VEC2_STR;
  typedef std::vector<VEC_CHR> VEC2_CHR;
  typedef std::vector<VEC_WCH> VEC2_WCH;
  typedef std::vector<VEC_INT> VEC2_INT;
  typedef std::vector<VEC_SI> VEC2_SI;
  typedef std::vector<VEC_LI> VEC2_LI;
  typedef std::vector<VEC_LLI> VEC2_LLI;
  typedef std::vector<VEC_USI> VEC2_USI;
  typedef std::vector<VEC_UI> VEC2_UI;
  typedef std::vector<VEC_ULI> VEC2_ULI;
  typedef std::vector<VEC_ULLI> VEC2_ULLI;
  typedef std::vector<VEC_SZ> VEC2_SZ;
  typedef std::vector<VEC_TM> VEC2_TM;
  typedef std::vector<VEC_FLT> VEC2_FLT;
  typedef std::vector<VEC_DBL> VEC2_DBL;
  typedef std::vector<VEC_LD> VEC2_LD;

  /** SHORTENED POINTER VECTORS */

  typedef std::vector<bool*> VEC_BOL_P;
  typedef std::vector<std::string*> VEC_STR_P;
  typedef std::vector<char*> VEC_CHR_P;
  typedef std::vector<wchar_t*> VEC_WCH_P;
  typedef std::vector<int*> VEC_INT_P;
  typedef std::vector<SI*> VEC_SI_P;
  typedef std::vector<LI*> VEC_LI_P;
  typedef std::vector<LLI*> VEC_LLI_P;
  typedef std::vector<USI*> VEC_USI_P;
  typedef std::vector<UI*> VEC_UI_P;
  typedef std::vector<ULI*> VEC_ULI_P;
  typedef std::vector<ULLI*> VEC_ULLI_P;
  typedef std::vector<size_t*> VEC_SZ_P;
  typedef std::vector<time_t*> VEC_TM_P;
  typedef std::vector<float*> VEC_FLT_P;
  typedef std::vector<double*> VEC_DBL_P;
  typedef std::vector<LD*> VEC_LD_P;

  typedef std::vector<VEC_BOL_P> VEC2_BOL_P;
  typedef std::vector<VEC_STR_P> VEC2_STR_P;
  typedef std::vector<VEC_CHR_P> VEC2_CHR_P;
  typedef std::vector<VEC_WCH_P> VEC2_WCH_P;
  typedef std::vector<VEC_INT_P> VEC2_INT_P;
  typedef std::vector<VEC_SI_P> VEC2_SI_P;
  typedef std::vector<VEC_LI_P> VEC2_LI_P;
  typedef std::vector<VEC_LLI_P> VEC2_LLI_P;
  typedef std::vector<VEC_USI_P> VEC2_USI_P;
  typedef std::vector<VEC_UI_P> VEC2_UI_P;
  typedef std::vector<VEC_ULI_P> VEC2_ULI_P;
  typedef std::vector<VEC_ULLI_P> VEC2_ULLI_P;
  typedef std::vector<VEC_SZ_P> VEC2_SZ_P;
  typedef std::vector<VEC_TM_P> VEC2_TM_P;
  typedef std::vector<VEC_FLT_P> VEC2_FLT_P;
  typedef std::vector<VEC_DBL_P> VEC2_DBL_P;
  typedef std::vector<VEC_LD_P> VEC2_LD_P;
}

using mt = mini_tools;
#endif // __MINI_TOOLS__TYPE_H__