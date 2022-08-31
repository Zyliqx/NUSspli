/***************************************************************************
 * This file is part of NUSspli.                                           *
 * Copyright (c) 2022 Xpl0itU <DaThinkingChair@protonmail.com>             *
 * Copyright (c) 2022 V10lator <v10lator@myway.de>                         *
 *                                                                         *
 * This program is free software; you can redistribute it and/or modify    *
 * it under the terms of the GNU General Public License as published by    *
 * the Free Software Foundation; either version 3 of the License, or       *
 * (at your option) any later version.                                     *
 *                                                                         *
 * This program is distributed in the hope that it will be useful,         *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 * GNU General Public License for more details.                            *
 *                                                                         *
 * You should have received a copy of the GNU General Public License along *
 * with this program; if not, If not, see <http://www.gnu.org/licenses/>.  *
 ***************************************************************************/

#pragma once

#include <wut-fixups.h>

#include <filesystem.h>
#include <list.h>
#include <titles.h>
#include <tmd.h>

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct
    {
        TMD *tmd;
        size_t ramBufSize;
        const TitleEntry *entry;
        char titleVer[33];
        char folderName[FS_MAX_PATH - 11];
        bool inst;
        NUSDEV dlDev;
        bool toUSB;
        bool keepFiles;
    } TitleData;

    bool initQueue();
    void shutdownQueue();
    void addToQueue(TitleData *data);
    void proccessQueue();
    LIST *getTitleQueue();

#ifdef __cplusplus
}
#endif