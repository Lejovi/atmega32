/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <joerg@FreeBSD.ORG> wrote this file.  As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.        Joerg Wunsch
 * ----------------------------------------------------------------------------
 *
 * $Id: defines.h 2186 2010-09-22 10:25:15Z aboyapati $
 * Aangepast aan eigen behoefte 12 augustus 2012. LJV
 */

#ifndef DEFINES_H
#define DEFINES_H

/* CPU frequency */
//-----------------------------------------------------------------------------
#ifndef F_CPU
#define F_CPU 1600000UL
#endif

//definieer welke poort gebruikt moet worden
//-----------------------------------------------------------------------------
#define GATE A

/* Whether to read the busy flag, or fall back to
   worst-time delays. */
#define USE_BUSY_BIT 1

/* geef de afmetingen van het display op */
#define RegelsMax 4
#define TekensMax 20

#endif