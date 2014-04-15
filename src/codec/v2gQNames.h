/*
 * Copyright (C) 2007-2013 Siemens AG
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
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*******************************************************************
 *
 * @author Daniel.Peintner.EXT@siemens.com
 * @version 0.8 
 * @contact Joerg.Heuer@siemens.com
 *
 * <p>Code generated by EXIdizer.com</p>
 * <p>Schema: input/test_v2g/V2G_CI_MsgDef.xsd</p>
 *
 *
 ********************************************************************/



#ifndef EXI_v2g_QNAMES_H
#define EXI_v2g_QNAMES_H

#include "EXITypes.h"

/**
 * \brief  	Returns efficient qname (namespaceURI & localName) IDs for qnameID
 *
 * \param       state		   	Codec state
 * \param       qnameID		   	Qualified name ID
 * \param       namespaceURI	QName namespace URI ID
 * \param       localPart		QName local name ID
 * \return                  	Error-Code <> 0
 *
 */
int exiv2gGetEQName(exi_state_t* state, uint16_t qnameID, uint16_t* namespaceURI, uint16_t* localPart);


/**
 * \brief  	Returns qnameID for qname namespaceURI & localName
 *
 * \param       state		   	Codec state
 * \param       namespaceURI	QName namespace URI ID
 * \param       localPart		QName local name ID
 * \param       qnameID		   	QName ID (out)
 * \return                  	Error-Code <> 0
 *
 */
int exiv2gGetQNameID(exi_state_t* state, uint16_t namespaceURI, uint16_t localPart, uint16_t* qnameID);


/**
 * \brief  	Add  efficient qname (namespaceURI & localName) IDs for qnameID
 *
 * \param       state		   	Codec state
 * \param       qnameID		   	Qualified name ID
 * \param       namespaceURI	QName namespace URI ID
 * \param       localPart		QName local name ID
 * \return                  	Error-Code <> 0
 *
 */
int exiv2gAddEQName(exi_state_t* state, uint16_t* qnameID, uint16_t namespaceURI, uint16_t localPart);

#endif
