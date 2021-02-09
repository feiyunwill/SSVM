// SPDX-License-Identifier: Apache-2.0
#include "api/ssvm.h"

#include "common/errcode.h"
#include "common/value.h"

#ifdef __cplusplus
extern "C" {
#endif

/// >>>>>>>> SSVM version functions >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

const char *SSVM_VersionGet() { return SSVM_VERSION; }

uint32_t SSVM_VersionGetMajor() { return SSVM_VERSION_MAJOR; }

uint32_t SSVM_VersionGetMinor() { return SSVM_VERSION_MINOR; }

uint32_t SSVM_VersionGetPatch() { return SSVM_VERSION_PATCH; }

/// <<<<<<<< SSVM version functions <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/// >>>>>>>> SSVM value functions >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

SSVM_Value SSVM_ValueGenI32(const int32_t Val) {
  return SSVM_Value{.Value = SSVM::retrieveValue<unsigned __int128>(
                        SSVM::ValVariant(static_cast<uint32_t>(Val)))};
}

SSVM_Value SSVM_ValueGenI64(const int64_t Val) {
  return SSVM_Value{.Value = SSVM::retrieveValue<unsigned __int128>(
                        SSVM::ValVariant(static_cast<uint64_t>(Val)))};
}

SSVM_Value SSVM_ValueGenF32(const float Val) {
  return SSVM_Value{
      .Value = SSVM::retrieveValue<unsigned __int128>(SSVM::ValVariant(Val))};
}

SSVM_Value SSVM_ValueGenF64(const double Val) {
  return SSVM_Value{
      .Value = SSVM::retrieveValue<unsigned __int128>(SSVM::ValVariant(Val))};
}

SSVM_Value SSVM_ValueGenV128(const __int128 Val) {
  return SSVM_Value{.Value = static_cast<unsigned __int128>(Val)};
}

SSVM_Value SSVM_ValueGenNullRef(const SSVM_RefType T) {
  return SSVM_Value{
      .Value = SSVM::retrieveValue<unsigned __int128>(
          SSVM::ValVariant(SSVM::genNullRef(static_cast<SSVM::RefType>(T))))};
}

SSVM_Value SSVM_ValueGenFuncRef(const uint32_t Index) {
  return SSVM_Value{.Value = SSVM::retrieveValue<unsigned __int128>(
                        SSVM::ValVariant(SSVM::genFuncRef(Index)))};
}

SSVM_Value SSVM_ValueGenExternRef(void *Ref) {
  return SSVM_Value{.Value = SSVM::retrieveValue<unsigned __int128>(
                        SSVM::ValVariant(SSVM::genExternRef(Ref)))};
}

int32_t SSVM_ValueGetI32(const SSVM_Value Val) {
  return SSVM::retrieveValue<int32_t>(SSVM::ValVariant(Val.Value));
}

int64_t SSVM_ValueGetI64(const SSVM_Value Val) {
  return SSVM::retrieveValue<int64_t>(SSVM::ValVariant(Val.Value));
}

float SSVM_ValueGetF32(const SSVM_Value Val) {
  return SSVM::retrieveValue<float>(SSVM::ValVariant(Val.Value));
}

double SSVM_ValueGetF64(const SSVM_Value Val) {
  return SSVM::retrieveValue<double>(SSVM::ValVariant(Val.Value));
}

__int128 SSVM_ValueGetV128(const SSVM_Value Val) {
  return SSVM::retrieveValue<__int128>(SSVM::ValVariant(Val.Value));
}

uint32_t SSVM_ValueGetFuncIdx(const SSVM_Value Val) {
  return SSVM::retrieveFuncIdx(SSVM::ValVariant(Val.Value));
}

void *SSVM_ValueGetExternRef(const SSVM_Value Val) {
  return &SSVM::retrieveExternRef<uint32_t>(SSVM::ValVariant(Val.Value));
}

/// <<<<<<<< SSVM value functions <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/// >>>>>>>> SSVM result functions >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

struct SSVM_Result {
  SSVM::ErrCode Code;
};

bool SSVM_ResultOK(SSVM_Result Res) {
  if (Res.Code == SSVM::ErrCode::Success ||
      Res.Code == SSVM::ErrCode::Terminated) {
    return true;
  } else {
    return false;
  }
}

uint32_t SSVM_ResultGetCode(SSVM_Result Res) {
  return static_cast<uint32_t>(Res.Code);
}

const char *SSVM_ResultGetMessage(SSVM_Result Res) {
  return SSVM::ErrCodeStr[Res.Code].c_str();
}

/// <<<<<<<< SSVM result functions <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/// >>>>>>>> SSVM configure functions >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

struct SSVM_ConfigureContext {
  SSVM::Configure Conf;
};

SSVM_ConfigureContext *SSVM_ConfigureCreate() {
  return new SSVM_ConfigureContext;
}

void SSVM_ConfigureAddProposal(SSVM_ConfigureContext *Cxt, SSVM_Proposal Prop) {
  if (Cxt) {
    Cxt->Conf.addProposal(static_cast<SSVM::Proposal>(Prop));
  }
}

void SSVM_ConfigureRemoveProposal(SSVM_ConfigureContext *Cxt,
                                  SSVM_Proposal Prop) {
  if (Cxt) {
    Cxt->Conf.removeProposal(static_cast<SSVM::Proposal>(Prop));
  }
}

bool SSVM_ConfigureHasProposal(SSVM_ConfigureContext *Cxt, SSVM_Proposal Prop) {
  if (Cxt) {
    return Cxt->Conf.hasProposal(static_cast<SSVM::Proposal>(Prop));
  }
  return false;
}

void SSVM_ConfigureAddHostRegistration(SSVM_ConfigureContext *Cxt,
                                       SSVM_HostRegistration Host) {
  if (Cxt) {
    Cxt->Conf.addHostRegistration(static_cast<SSVM::HostRegistration>(Host));
  }
}

void SSVM_ConfigureRemoveHostRegistration(SSVM_ConfigureContext *Cxt,
                                          SSVM_HostRegistration Host) {
  if (Cxt) {
    Cxt->Conf.removeHostRegistration(static_cast<SSVM::HostRegistration>(Host));
  }
}

bool SSVM_ConfigureHasHostRegistration(SSVM_ConfigureContext *Cxt,
                                       SSVM_HostRegistration Host) {
  if (Cxt) {
    return Cxt->Conf.hasHostRegistration(
        static_cast<SSVM::HostRegistration>(Host));
  }
  return false;
}

void SSVM_ConfigureSetMaxMemoryPage(SSVM_ConfigureContext *Cxt,
                                    const uint32_t Page) {
  if (Cxt) {
    Cxt->Conf.setMaxMemoryPage(Page);
  }
}

const uint32_t SSVM_ConfigureGetMaxMemoryPage(SSVM_ConfigureContext *Cxt) {
  if (Cxt) {
    return Cxt->Conf.getMaxMemoryPage();
  }
  return 0;
}

void SSVM_ConfigureDelete(SSVM_ConfigureContext *Cxt) {
  if (Cxt == nullptr) {
    return;
  }
  delete Cxt;
}

/// <<<<<<<< SSVM configure functions <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#ifdef __cplusplus
} /// extern "C"
#endif