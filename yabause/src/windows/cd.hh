/*  Copyright 2004-2005 Theo Berkau
    Copyright 2005 Joost Peters

    This file is part of Yabause.

    Yabause is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    Yabause is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Yabause; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <ddk/ntddcdrm.h>
#include <ddk/ntddscsi.h>
#include <wnaspi32.h>
#include "../cdbase.hh"

#ifndef CD_HH
#define CD_HH

class SPTICDDrive : public CDInterface {
public:
        SPTICDDrive(const char *cdrom_name);
        virtual ~SPTICDDrive();

	bool isCDPresent();
	long readTOC(unsigned long *TOC);
	int getStatus();
	bool readSectorFAD(unsigned long FAD, void *buffer);
	const char *deviceName();
	
private:
	int init(const char *iso);
	int deinit();
	
        HANDLE hCDROM;
        SCSI_PASS_THROUGH_DIRECT sptd;
};

class ASPICDDrive : public CDInterface {
public:
        ASPICDDrive(const char *cdrom_name);
        virtual ~ASPICDDrive();

	bool isCDPresent();
	long readTOC(unsigned long *TOC);
	int getStatus();
	bool readSectorFAD(unsigned long FAD, void *buffer);
	const char *deviceName();
        HINSTANCE aspidll;	
        unsigned char scsiAdapterNumber;
        unsigned char lun;
        unsigned char targetId;

        DWORD (*GetASPI32SupportInfo)(void);
        DWORD (*SendASPI32Command)(LPSRB);
private:
	int init(const char *iso);
	int deinit();
	
        HANDLE hCDROM;
        SCSI_PASS_THROUGH_DIRECT sptd;
};

#endif
