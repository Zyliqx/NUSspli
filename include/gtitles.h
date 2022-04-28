/***************************************************************************
 * This file is part of NUSspli.                                           *
 * Copyright (c) 2022 V10lator <v10lator@myway.de>                         *
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

#ifndef NUSSPLI_GTITLES_H
#define NUSSPLI_GTITLES_H

#include <wut-fixups.h>

#include <stdint.h>

#include <coreinit/mcp.h>

#ifdef __cplusplus
	extern "C" {
#endif

typedef enum
{
	TITLE_CATEGORY_GAME = 0,
	TITLE_CATEGORY_UPDATE = 1,
	TITLE_CATEGORY_DLC = 2,
	TITLE_CATEGORY_DEMO = 3,
	TITLE_CATEGORY_ALL = 4,
} TITLE_CATEGORY;

typedef enum
{
	TITLE_KEY_mypass	= 0,
	TITLE_KEY_nintendo	= 1,
	TITLE_KEY_test		= 2,
	TITLE_KEY_1234567890	= 3,
	TITLE_KEY_Lucy131211	= 4,
	TITLE_KEY_fbf10		= 5,
	TITLE_KEY_5678		= 6,
	TITLE_KEY_1234		= 7,
	TITLE_KEY_		= 8
} TITLE_KEY;

typedef struct
{
	const char *name;
	uint64_t tid;
	const MCPRegion region;
	const TITLE_KEY key;
} TitleEntry;

const TitleEntry *getAllTitleEntries();
size_t getTitleEntriesSize(TITLE_CATEGORY cat);

#ifdef __cplusplus
	}
#endif

#endif // ifndef NUSSPLI_TITLES_H