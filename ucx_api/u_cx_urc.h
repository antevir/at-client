/*
* This file was automatically generated using csnake v0.3.5.
*
* This file should not be edited directly, any changes will be
* overwritten next time the script is run.
*
* Source code for csnake is available at:
* https://gitlab.com/andrejr/csnake
*
* csnake is also available on PyPI, at :
* https://pypi.org/project/csnake
*/
#ifndef _U_CX_URC_H_
#define _U_CX_URC_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "u_cx.h"

/* ------------------------------------------------------------
 * PUBLIC FUNCTIONS
 * ---------------------------------------------------------- */

int32_t uCxUrcParse(uCxHandle_t * puCxHandle, const char * pUrcName, char * pParams, size_t paramsLength);

void uCxUrcRegisterWiFiLinkDown(struct uCxHandle * puCxHandle, uUEWLD_t callback);

void uCxUrcRegisterWiFiStationNetworkUp(struct uCxHandle * puCxHandle, uUEWSNU_t callback);

void uCxUrcRegisterWiFiStationNetworkDown(struct uCxHandle * puCxHandle, uUEWSND_t callback);

void uCxUrcRegisterWiFiApNetworkUp(struct uCxHandle * puCxHandle, uUEWAPNU_t callback);

void uCxUrcRegisterWiFiApNetworkDown(struct uCxHandle * puCxHandle, uUEWAPND_t callback);

void uCxUrcRegisterWiFiApUp(struct uCxHandle * puCxHandle, uUEWAPU_t callback);

void uCxUrcRegisterWiFiApDown(struct uCxHandle * puCxHandle, uUEWAPD_t callback);

void uCxUrcRegisterSocketConnect(struct uCxHandle * puCxHandle, uUESOC_t callback);

void uCxUrcRegisterSocketDataAvailable(struct uCxHandle * puCxHandle, uUESODA_t callback);

void uCxUrcRegisterSocketClosed(struct uCxHandle * puCxHandle, uUESOCL_t callback);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _U_CX_URC_H_ */