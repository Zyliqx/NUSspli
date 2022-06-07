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

#include <wut-fixups.h>

#include <filesystem.h>
#include <iosuhaxx.h>
#include <state.h>
#include <utils.h>

#include <stdbool.h>

#include <coreinit/filesystem.h>
#include <iosuhax.h>

#define IOSUHAX_FSA_DEFFLAGS	0x0 // TODO: What do they do?

static bool dotUnlocked = false;
static bool usbMounted = false;
static bool mlcMounted = false;
static bool usb01;

extern FSClient *__wut_devoptab_fs_client;

bool isUSB01()
{
	return usb01;
}

static bool initFsa()
{
	if(!openIOSUhax())
        return false;

	if(dotUnlocked)
		return true;

	dotUnlocked = IOSUHAX_UnlockFSClient(__wut_devoptab_fs_client) == FS_ERROR_NOERROR;
	return dotUnlocked;
}

bool mountUSB()
{
	if(usbMounted)
		return true;

	if(!initFsa())
		return false;

	FSError ret = IOSUHAX_FSAMount(__wut_devoptab_fs_client, "/dev/usb01", "/vol/usb", IOSUHAX_FSA_DEFFLAGS, NULL, 0);

	if(ret != FS_ERROR_NOERROR)
	{
		debugPrintf("IOSUHAX: error mounting USB drive 1: %#010x", ret);
		ret = IOSUHAX_FSAMount(__wut_devoptab_fs_client, "/dev/usb02", "/vol/usb", IOSUHAX_FSA_DEFFLAGS, NULL, 0);
		if(ret != FS_ERROR_NOERROR)
		{
			debugPrintf("IOSUHAX: error mounting USB drive 2: %#010x", ret);
			return false;
		}
		usb01 = false;
	}
	else
		usb01 = true;

	debugPrintf("IOSUHAX: USB drive %s mounted!", usb01 ? "1" : "2");
	usbMounted = true;
	return true;
}

bool mountMLC()
{
	if(mlcMounted)
		return true;

	if(!initFsa())
		return false;

	FSError ret = IOSUHAX_FSAMount(__wut_devoptab_fs_client, "/dev/mlc01", "/vol/mlc", IOSUHAX_FSA_DEFFLAGS, NULL, 0);
	if(ret != FS_ERROR_NOERROR)
	{
		debugPrintf("IOSUHAX: error mounting MLC: %#010x", ret);
		return false;
	}

	debugPrintf("IOSUHAX: MLC mounted!");
	mlcMounted = true;
	return true;
}

void unmountUSB()
{
	if(!usbMounted)
		return;

	FSError ret = IOSUHAX_FSAUnmount(__wut_devoptab_fs_client, "/vol/usb");
	if(ret == FS_ERROR_NOERROR)
	{
		usbMounted = false;
		debugPrintf("IOSUHAX: USB drive unmounted!");
	}
	else
		debugPrintf("IOSUHAX: error unmounting USB drive: %#010x", ret);
}

void unmountMLC()
{
	if(!mlcMounted)
		return;

	FSError ret = IOSUHAX_FSAUnmount(__wut_devoptab_fs_client, "/vol/mlc");
	if(ret == FS_ERROR_NOERROR)
	{
		mlcMounted = false;
		debugPrintf("IOSUHAX: MLC drive unmounted!");
	}
	else
		debugPrintf("IOSUHAX: error unmounting MLC drive: %#010x", ret);
}
