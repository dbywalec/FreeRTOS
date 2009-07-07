/*
	FreeRTOS.org V5.4.0 - Copyright (C) 2003-2009 Richard Barry.

	This file is part of the FreeRTOS.org distribution.

	FreeRTOS.org is free software; you can redistribute it and/or modify it
	under the terms of the GNU General Public License (version 2) as published
	by the Free Software Foundation and modified by the FreeRTOS exception.
	**NOTE** The exception to the GPL is included to allow you to distribute a
	combined work that includes FreeRTOS.org without being obliged to provide
	the source code for any proprietary components.  Alternative commercial
	license and support terms are also available upon request.  See the 
	licensing section of http://www.FreeRTOS.org for full details.

	FreeRTOS.org is distributed in the hope that it will be useful,	but WITHOUT
	ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
	FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
	more details.

	You should have received a copy of the GNU General Public License along
	with FreeRTOS.org; if not, write to the Free Software Foundation, Inc., 59
	Temple Place, Suite 330, Boston, MA  02111-1307  USA.


	***************************************************************************
	*                                                                         *
	* Get the FreeRTOS eBook!  See http://www.FreeRTOS.org/Documentation      *
	*                                                                         *
	* This is a concise, step by step, 'hands on' guide that describes both   *
	* general multitasking concepts and FreeRTOS specifics. It presents and   *
	* explains numerous examples that are written using the FreeRTOS API.     *
	* Full source code for all the examples is provided in an accompanying    *
	* .zip file.                                                              *
	*                                                                         *
	***************************************************************************

	1 tab == 4 spaces!

	Please ensure to read the configuration and relevant port sections of the
	online documentation.

	http://www.FreeRTOS.org - Documentation, latest information, license and
	contact details.

	http://www.SafeRTOS.com - A version that is certified for use in safety
	critical systems.

	http://www.OpenRTOS.com - Commercial support, development, porting,
	licensing and training services.
*/

/*
Changes from V3.0.0

Changes from V3.0.1
*/

/*
** Here are the configuration words set. See the PIC datasheet
** and the wizC manual for an explanation
*/
#include <pic.h>

/*
** These fuses are for PIC18F4620
*/
#pragma __config _CONFIG1H,_IESO_OFF_1H & _FCMEN_OFF_1H & _OSC_HSPLL_1H
#pragma __config _CONFIG2L,_BORV_21_2L & _BOREN_SBORDIS_2L & _PWRT_ON_2L
#pragma __config _CONFIG2H,_WDTPS_32768_2H & _WDT_OFF_2H
#pragma __config _CONFIG3H,_MCLRE_ON_3H & _LPT1OSC_OFF_3H & _PBADEN_OFF_3H & _CCP2MX_PORTC_3H
#pragma __config _CONFIG4L,_DEBUG_OFF_4L & _XINST_OFF_4L & _LVP_OFF_4L & _STVREN_OFF_4L
#pragma __config _CONFIG5L,_CP3_OFF_5L & _CP2_OFF_5L & _CP1_OFF_5L & _CP0_OFF_5L
#pragma __config _CONFIG5H,_CPD_OFF_5H & _CPB_OFF_5H
#pragma __config _CONFIG6L,_WRT3_OFF_6L & _WRT2_OFF_6L & _WRT1_OFF_6L & _WRT0_OFF_6L
#pragma __config _CONFIG6H,_WRTD_OFF_6H & _WRTB_OFF_6H & _WRTC_OFF_6H
#pragma __config _CONFIG7L,_EBTR3_OFF_7L & _EBTR2_OFF_7L & _EBTR1_OFF_7L & _EBTR0_OFF_7L
#pragma __config _CONFIG7H,_EBTRB_OFF_7H
