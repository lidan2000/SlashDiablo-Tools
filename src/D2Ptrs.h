/*****************************************************************************
 *                                                                           *
 *   D2Ptrs.h                                                                *
 *                                                                           *
 *   Licensed under the Apache License, Version 2.0 (the "License");         *
 *   you may not use this file except in compliance with the License.        *
 *   You may obtain a copy of the License at                                 *
 *                                                                           *
 *   http://www.apache.org/licenses/LICENSE-2.0                              *
 *                                                                           *
 *   Unless required by applicable law or agreed to in writing, software     *
 *   distributed under the License is distributed on an "AS IS" BASIS,       *
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.*
 *   See the License for the specific language governing permissions and     *
 *   limitations under the License.                                          *
 *                                                                           *
 *---------------------------------------------------------------------------*
 *                                                                           *
 *   https://github.com/olivier-verville/D2Template                          *
 *                                                                           *
 *   This file is used to declare pointers, be it function or variable       *
 *   pointers, from the game's libraries.                                    *
 *                                                                           *
 *   It is recommended that you keep this file organized by which dll the    *
 *   pointer is imported from, what type of pointer it is, etc. Ordering     *
 *   them by address can also end up being very useful                       *
 *                                                                           *
 *****************************************************************************/

#pragma once

#ifndef _D2PTRS_H
#define _D2PTRS_H

#include "D2Offset.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  These are the macros used by the template core to declare                                                                                                                                   ///
//  pointers. Do not touch unless you know what you're doing                                                                                                                                    ///
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define D2FUNC(DLL, NAME, RETURN, CONV, ARGS, OFFSETS) \
    typedef RETURN (CONV * DLL##_##NAME##_t) ARGS; \
    static D2Offset DLL##_##NAME##_FUNC_OFFSET OFFSETS; \
    static DLL##_##NAME##_t DLL##_##NAME = (DLL##_##NAME##_t)(DLLBASE_##DLL + DLL##_##NAME##_FUNC_OFFSET.getCurrentOffset());

#define D2VAR(DLL, NAME, TYPE, OFFSETS) \
    typedef TYPE DLL##_##NAME##_vt; \
    static D2Offset DLL##_##NAME##_VAR_OFFSET OFFSETS; \
    static DLL##_##NAME##_vt * DLL##_##NAME = (DLL##_##NAME##_vt *)(DLLBASE_##DLL + DLL##_##NAME##_VAR_OFFSET.getCurrentOffset());

#define D2PTR(DLL, NAME, OFFSETS) \
    static D2Offset DLL##_##NAME##_PTR_OFFSET OFFSETS; \
    static DWORD NAME = (DLLBASE_##DLL + DLL##_##NAME##_PTR_OFFSET.getCurrentOffset());

/********************************************************************************
 *                                                                               *
 *   D2GAME.DLL POINTERS                                                         *
 *                                                                               *
 *********************************************************************************/

/********************************************************************************
 *                                                                               *
 *   D2CLIENT.DLL POINTERS                                                       *
 *                                                                               *
 *********************************************************************************/
D2VAR(D2CLIENT, ScreenSizeX, int, ( { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xDBC48,
        0xF7034, 0, 0, 0, 0 }));
D2VAR(D2CLIENT, ScreenSizeY, int, ( { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0xDBC4C,
        0xF7038, 0, 0, 0, 0 }));
D2VAR(D2CLIENT, PanelOffsetX, int, ( { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x11B9A0,
        0x11D354, 0, 0, 0, 0 }));
D2VAR(D2CLIENT, PanelOffsetY, int, ( { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x11B9A4,
        0x11D358, 0, 0, 0, 0 }));

/********************************************************************************
 *                                                                               *
 *   D2COMMON.DLL POINTERS                                                       *
 *                                                                               *
 *********************************************************************************/

// end of file -----------------------------------------------------------------
#endif
