
/*
 * Copyright (C) 2007-2012 Siemens AG
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*******************************************************************
 *
 * @author Sebastian.Kaebisch.EXT@siemens.com
 * @version 0.6
 * @contact Joerg.Heuer@siemens.com
 *
 ********************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SERVICECLIENTDATATRANSMITTER_H_
#define SERVICECLIENTDATATRANSMITTER_H_

#include <stdint.h>
/*
 * This method sends EXI stream (outStream) to the EVSE and receives a response stream (inStream)*/
int serviceDataTransmitter(uint8_t* outStream, uint16_t outStreamLength, uint8_t* inStream);

#endif /* V2G_SERVICECLIENTDATATRANSMITTER_H_ */

#ifdef __cplusplus
}
#endif