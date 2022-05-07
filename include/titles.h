/***************************************************************************
 * This file is part of NUSspli.                                           *
 * Copyright (c) 2020-2022 V10lator <v10lator@myway.de>                    *
 *                                                                         *
 * This program is free software; you can redistribute it and/or modify    *
 * it under the terms of the GNU General Public License as published by    *
 * the Free Software Foundation; either version 2 of the License, or       *
 * (at your option) any later version.                                     *
 *                                                                         *
 * This program is distributed in the hope that it will be useful,         *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 * GNU General Public License for more details.                            *
 *                                                                         *
 * You should have received a copy of the GNU General Public License along *
 * with this program; if not, write to the Free Software Foundation, Inc., *
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.             *
 ***************************************************************************/

#pragma once

#include <wut-fixups.h>

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include <gtitles.h>

#include <coreinit/mcp.h>

#ifdef __cplusplus
	extern "C" {
#endif

#define MAX_TITLENAME_LENGTH	256 // incl '\0'
#define MCP_REGION_UNKNOWN		0

typedef enum
{
	TID_HIGH_GAME =			0x00050000,
	TID_HIGH_DEMO =			0x00050002,
	TID_HIGH_SYSTEM_APP =		0x00050010,
	TID_HIGH_SYSTEM_DATA =		0x0005001B,
	TID_HIGH_SYSTEM_APPLET =	0x00050030,
	TID_HIGH_VWII_IOS =		0x00000007,
	TID_HIGH_VWII_SYSTEM_APP =	0x00070002,
	TID_HIGH_VWII_SYSTEM =		0x00070008,
	TID_HIGH_DLC =			0x0005000C,
	TID_HIGH_UPDATE =		0x0005000E,
} TID_HIGH;

#define getTidHighFromTid(tid) (*(uint32_t *)&tid)

const TitleEntry *getTitleEntries(TITLE_CATEGORY cat);
const TitleEntry *getTitleEntryByTid(uint64_t tid);
const char *tid2name(const char *tid);
bool name2tid(const char *name, char *out);
bool initTitles();
void clearTitles();

static inline bool isGame(const TitleEntry *entry)
{
	return (TID_HIGH)(entry->tid >> 32) == TID_HIGH_GAME;
}

static inline bool isDLC(const TitleEntry *entry)
{
	return (TID_HIGH)(entry->tid >> 32) == TID_HIGH_DLC;
}

static inline bool isUpdate(const TitleEntry *entry)
{
	return (TID_HIGH)(entry->tid >> 32) == TID_HIGH_UPDATE;
}

static inline bool isDemo(const TitleEntry *entry)
{
	return (TID_HIGH)(entry->tid >> 32) == TID_HIGH_DEMO;
}

// TODO

#ifdef __cplusplus
	}
#endif
