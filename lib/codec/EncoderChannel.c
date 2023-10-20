/*
 * Copyright (C) 2007-2018 Siemens AG
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
 * @author Daniel.Peintner.EXT@siemens.com
 * @version 2017-03-02 
 * @contact Richard.Kuntschke@siemens.com
 *
 * <p>Code generated by EXIdizer</p>
 * <p>Schema: V2G_CI_MsgDef.xsd</p>
 *
 *
 ********************************************************************/



#include "openv2g/EncoderChannel.h"
#include "openv2g/EXIOptions.h"
#include "openv2g/BitOutputStream.h"
#include "openv2g/EXITypes.h"
#include "openv2g/ErrorCodes.h"
#include "openv2g/MethodsBag.h"
/*#include "v2gEXICoder.h"*/

#ifndef ENCODER_CHANNEL_C
#define ENCODER_CHANNEL_C

int encodeUnsignedInteger(bitstream_t* stream, exi_integer_t* iv) {
	int errn = 0;
	switch (iv->type) {
	/* Unsigned Integer */
	case EXI_UNSIGNED_INTEGER_8:
		errn = encodeUnsignedInteger32(stream, iv->val.uint8);
		break;
	case EXI_UNSIGNED_INTEGER_16:
		errn = encodeUnsignedInteger32(stream, iv->val.uint16);
		break;
	case EXI_UNSIGNED_INTEGER_32:
		errn = encodeUnsignedInteger32(stream, iv->val.uint32);
		break;
	case EXI_UNSIGNED_INTEGER_64:
		errn = encodeUnsignedInteger64(stream, iv->val.uint64);
		break;
		/* (Signed) Integer */
	case EXI_INTEGER_8:
		if (iv->val.int8 < 0) {
			return EXI_NEGATIVE_UNSIGNED_INTEGER_VALUE;
		}
		errn = encodeUnsignedInteger32(stream, (uint32_t)(iv->val.int8));
		break;
	case EXI_INTEGER_16:
		if (iv->val.int16 < 0) {
			return EXI_NEGATIVE_UNSIGNED_INTEGER_VALUE;
		}
		errn = encodeUnsignedInteger32(stream, (uint32_t)(iv->val.int16));
		break;
	case EXI_INTEGER_32:
		if (iv->val.int32 < 0) {
			return EXI_NEGATIVE_UNSIGNED_INTEGER_VALUE;
		}
		errn = encodeUnsignedInteger32(stream, (uint32_t)(iv->val.int32));
		break;
	case EXI_INTEGER_64:
		if (iv->val.int64 < 0) {
			return EXI_NEGATIVE_UNSIGNED_INTEGER_VALUE;
		}
		errn = encodeUnsignedInteger64(stream, (uint64_t)(iv->val.int64));
		break;
	default:
		errn = EXI_UNSUPPORTED_INTEGER_VALUE_TYPE;
		break;
	}

	return errn;
}

/**
 * Encode an arbitrary precision non negative integer using a sequence of
 * octets. The most significant bit of the last octet is set to zero to
 * indicate sequence termination. Only seven bits per octet are used to
 * store the integer's value.
 */
int encodeUnsignedInteger16(bitstream_t* stream, uint16_t n) {
	int errn = 0;
	if (n < 128) {
		/* write byte as is */
		errn = encode(stream, (uint8_t) n);
	} else {
		uint8_t n7BitBlocks = numberOf7BitBlocksToRepresent(n);

		switch (n7BitBlocks) {
		case 3:
			errn = encode(stream, (uint8_t) (128 | n));
			n = n >> 7;
			if (errn != 0) {
				break;
			}
			/* no break */
		case 2:
			errn = encode(stream, (uint8_t) (128 | n));
			n = n >> 7;
			if (errn != 0) {
				break;
			}
			/* no break */
		case 1:
			/* 0 .. 7 (last byte) */
			errn = encode(stream, (uint8_t) (0 | n));
			/* no break */
		}
	}

	return errn;
}

/**
 * Encode an arbitrary precision non negative integer using a sequence of
 * octets. The most significant bit of the last octet is set to zero to
 * indicate sequence termination. Only seven bits per octet are used to
 * store the integer's value.
 */
int encodeUnsignedInteger32(bitstream_t* stream, uint32_t n) {
	int errn = 0;
	if (n < 128) {
		/* write byte as is */
		errn = encode(stream, (uint8_t) n);
	} else {
		uint8_t n7BitBlocks = numberOf7BitBlocksToRepresent(n);

		switch (n7BitBlocks) {
		case 5:
			errn = encode(stream, (uint8_t) (128 | n));
			n = n >> 7;
			if (errn != 0) {
				break;
			}
			/* no break */
		case 4:
			errn = encode(stream, (uint8_t) (128 | n));
			n = n >> 7;
			if (errn != 0) {
				break;
			}
			/* no break */
		case 3:
			errn = encode(stream, (uint8_t) (128 | n));
			n = n >> 7;
			if (errn != 0) {
				break;
			}
			/* no break */
		case 2:
			errn = encode(stream, (uint8_t) (128 | n));
			n = n >> 7;
			if (errn != 0) {
				break;
			}
			/* no break */
		case 1:
			/* 0 .. 7 (last byte) */
			errn = encode(stream, (uint8_t) (0 | n));
			/* no break */
		}
	}

	return errn;
}

/**
 * Encode an arbitrary precision non negative integer using a sequence of
 * octets. The most significant bit of the last octet is set to zero to
 * indicate sequence termination. Only seven bits per octet are used to
 * store the integer's value.
 */
int encodeUnsignedInteger64(bitstream_t* stream, uint64_t n) {
	int errn = 0;
	uint8_t lastEncode = (uint8_t) n;
	n >>= 7;

	while (n != 0 && errn == 0) {
		errn = encode(stream, lastEncode | 128);
		lastEncode = (uint8_t) n;
		n >>= 7;
	}

	if (errn == 0) {
		errn = encode(stream, lastEncode);
	}

	return errn;
}

void _shiftRight7(uint8_t* buf, int len) {
	const int shift = 7;
    unsigned char tmp = 0x00, tmp2 = 0x00;
    for (int k = 0; k <= len; k++) {
        if (k == 0) {
            tmp = buf[k];
            buf[k] >>= shift;
        } else {
            tmp2 = buf[k];
            buf[k] >>= shift;
            buf[k] |= ((tmp & 0x7F) << (8 - shift));

            if (k != len) {
                tmp = tmp2;
            }
        }
    }
}

/**
 * Encode an arbitrary precision non negative integer using a sequence of
 * octets. The most significant bit of the last octet is set to zero to
 * indicate sequence termination. Only seven bits per octet are used to
 * store the integer's value.
 */
int encodeUnsignedIntegerBig(bitstream_t* stream, size_t size, uint8_t* data, size_t len) {
	int errn = 0;
	int i;
	int lenM1 = len - 1;
	const int MAX_BIGINT_ARRAY = 25;
	uint8_t lastEncode = 0;
	uint8_t bytesToShift[MAX_BIGINT_ARRAY]; // MAXIMUM
	size_t bitsToEncode = len * 8;

	if(MAX_BIGINT_ARRAY <= len) {
		return -1;
	}

	/* init */
	for(i=0; i<MAX_BIGINT_ARRAY; i++) {
		bytesToShift[i] = 0;
	}

	/* copy bytes first in same order for shifting */
	for(i=0; i < len; i++) {
		bytesToShift[i] = data[i];
	}

	while(bitsToEncode > 7) {
		lastEncode = bytesToShift[lenM1];
		lastEncode = lastEncode | 128;
		errn = encode(stream, lastEncode);
		_shiftRight7(bytesToShift, len);
		bitsToEncode -= 7;
	}

	if (errn == 0) {
		errn = encode(stream, bytesToShift[lenM1]);
	}

	return errn;
}

int encodeInteger(bitstream_t* stream, exi_integer_t* iv) {
	int errn = 0;
	switch (iv->type) {
	/* Unsigned Integer */
	case EXI_UNSIGNED_INTEGER_8:
		errn = encodeInteger32(stream, iv->val.uint8);
		break;
	case EXI_UNSIGNED_INTEGER_16:
		errn = encodeInteger32(stream, iv->val.uint16);
		break;
	case EXI_UNSIGNED_INTEGER_32:
		errn = encodeInteger64(stream, iv->val.uint32);
		break;
	case EXI_UNSIGNED_INTEGER_64:
		errn = encodeInteger64(stream, (int64_t)(iv->val.uint64));
		break;
		/* (Signed) Integer */
	case EXI_INTEGER_8:
		errn = encodeInteger32(stream, iv->val.int8);
		break;
	case EXI_INTEGER_16:
		errn = encodeInteger32(stream, iv->val.int16);
		break;
	case EXI_INTEGER_32:
		errn = encodeInteger32(stream, iv->val.int32);
		break;
	case EXI_INTEGER_64:
		errn = encodeInteger64(stream, iv->val.int64);
		break;
	default:
		errn = EXI_UNSUPPORTED_INTEGER_VALUE_TYPE;
		break;
	}

	return errn;
}


/**
 * Encode an arbitrary precision integer using a sign bit followed by a
 * sequence of octets. The most significant bit of the last octet is set to
 * zero to indicate sequence termination. Only seven bits per octet are used
 * to store the integer's value.
 */
int encodeInteger16(bitstream_t* stream, int16_t n) {
	int errn;
	/* signalize sign */
	if (n < 0) {
		errn = encodeBoolean(stream, 1);
		/* For negative values, the Unsigned Integer holds the
		 * magnitude of the value minus 1 */
		n = (int16_t)((-n) - 1);
	} else {
		errn = encodeBoolean(stream, 0);
	}
	if (errn == 0) {
		errn = encodeUnsignedInteger16(stream, (uint16_t)n);
	}
	return errn;
}



/**
 * Encode an arbitrary precision integer using a sign bit followed by a
 * sequence of octets. The most significant bit of the last octet is set to
 * zero to indicate sequence termination. Only seven bits per octet are used
 * to store the integer's value.
 */
int encodeInteger32(bitstream_t* stream, int32_t n) {
	int errn;
	/* signalize sign */
	if (n < 0) {
		errn = encodeBoolean(stream, 1);
		/* For negative values, the Unsigned Integer holds the
		 * magnitude of the value minus 1 */
		n = (-n) - 1;
	} else {
		errn = encodeBoolean(stream, 0);
	}
	if (errn == 0) {
		errn = encodeUnsignedInteger32(stream, (uint32_t)n);
	}
	return errn;
}

/**
 * Encode an arbitrary precision integer using a sign bit followed by a
 * sequence of octets. The most significant bit of the last octet is set to
 * zero to indicate sequence termination. Only seven bits per octet are used
 * to store the integer's value.
 */
int encodeInteger64(bitstream_t* stream, int64_t n) {
	int errn;
	/* signalize sign */
	if (n < 0) {
		errn = encodeBoolean(stream, 1);
		/* For negative values, the Unsigned Integer holds the
		 * magnitude of the value minus 1 */
		n = (-n) - 1;
	} else {
		errn = encodeBoolean(stream, 0);
	}
	if (errn == 0) {
		errn = encodeUnsignedInteger64(stream, (uint64_t)n);
	}
	return errn;
}


/**
 * Encode an arbitrary precision integer using a sign bit followed by a
 * sequence of octets. The most significant bit of the last octet is set to
 * zero to indicate sequence termination. Only seven bits per octet are used
 * to store the integer's value.
 */
int encodeIntegerBig(bitstream_t* stream, int negative, size_t size, uint8_t* data, size_t len) {
	int errn;
	/* signalize sign */
	if (negative) {
		errn = encodeBoolean(stream, 1);
		/* For negative values, the Unsigned Integer holds the
		 * magnitude of the value minus 1 */
		/* n = (-n) - 1; */
	} else {
		errn = encodeBoolean(stream, 0);
	}
	if (errn == 0) {
		errn = encodeUnsignedIntegerBig(stream, size, data, len);
	}
	return errn;
}

/**
 * The Float datatype representation is two consecutive Integers.
 * The first Integer represents the mantissa of the floating point
 * number and the second Integer represents the base-10 exponent
 * of the floating point number.
 */
int encodeFloat(bitstream_t* stream, exi_float_me_t* f) {
	int errn = encodeInteger64(stream, f->mantissa);
	if (errn == 0) {
		errn = encodeInteger32(stream, f->exponent);
	}
	return errn;
}

/**
 * Encode a decimal represented as a Boolean sign followed by two Unsigned
 * Integers. A sign value of zero (0) is used to represent positive Decimal
 * values and a sign value of one (1) is used to represent negative Decimal
 * values The first Integer represents the integral portion of the Decimal
 * value. The second positive integer represents the fractional portion of
 * the decimal with the digits in reverse order to preserve leading zeros.
 */
int encodeDecimal(bitstream_t* stream, exi_decimal_t* d) {
	/* sign, integral, reverse fractional */
	int errn = encodeBoolean(stream, d->negative);
	if (errn == 0) {
		errn = encodeUnsignedInteger(stream, &d->integral);
		if (errn == 0) {
			errn = encodeUnsignedInteger(stream, &d->reverseFraction);
		}
	}
	return errn;
}

/**
 * Encode a length prefixed sequence of characters.
 */
int encodeString(bitstream_t* stream, exi_string_t* string) {
	int errn = encodeUnsignedInteger32(stream, string->len);
	if (errn == 0) {
		errn = encodeCharacters(stream, string->characters, string->len);
	}
	return errn;
}

/**
 * Encode a sequence of characters according to a given length.
 * Each character is represented by its UCS [ISO/IEC 10646]
 * code point encoded as an Unsigned Integer
 */
int encodeCharacters(bitstream_t* stream, exi_string_character_t* chars, size_t len) {
	unsigned int i;
	int errn = 0;
	for (i = 0; i < len && errn == 0; i++) {
#if STRING_REPRESENTATION == STRING_REPRESENTATION_ASCII
		errn = encode(stream, (uint8_t)chars[i]);
#endif /* STRING_REPRESENTATION_ASCII */
#if STRING_REPRESENTATION == STRING_REPRESENTATION_UCS
		errn = encodeUnsignedInteger32(stream, chars[i]);
#endif /* STRING_REPRESENTATION_UCS */
	}
	return errn;
}


int encodeRCSCharacters(bitstream_t* stream, exi_string_character_t* chars, size_t len, size_t rcsCodeLength, size_t rcsSize, const exi_string_character_t rcsSet[]) {
	unsigned int i;
	unsigned int k;
	int errn = 0;
	size_t rcsCode = SIZE_MAX;

	for (i = 0; i < len && errn == 0; i++) {
		/* try to find short code */
		rcsCode = SIZE_MAX;
		for(k=0; k<rcsSize && rcsCode == SIZE_MAX; k++) {
			if(rcsSet[k] == chars[i]) {
				rcsCode = k;
			}
		}

		if( rcsCode == SIZE_MAX) {
			/* RCS mis-match */
			errn = encodeNBitUnsignedInteger(stream, rcsCodeLength, rcsSize);
#if STRING_REPRESENTATION == STRING_REPRESENTATION_ASCII
			errn = encode(stream, (uint8_t)chars[i]);
#endif /* STRING_REPRESENTATION_ASCII */
#if STRING_REPRESENTATION == STRING_REPRESENTATION_UCS
			errn = encodeUnsignedInteger32(stream, chars[i]);
#endif /* STRING_REPRESENTATION_UCS */

		} else {
			/* RCS match */
			errn = encodeNBitUnsignedInteger(stream, rcsCodeLength, (uint32_t)rcsCode);
		}
	}
	return errn;
}

/**
 * Encode a binary value as a length-prefixed sequence of octets.
 */
int encodeBinary(bitstream_t* stream, exi_bytes_t* bytes) {
	int errn = encodeUnsignedInteger32(stream, bytes->len);

	if(errn == 0) {
		errn = encodeBytes(stream, bytes->data, bytes->len);
	}

	return errn;
}

int encodeBytes(bitstream_t* stream, uint8_t* data, size_t len) {
	unsigned int i;
	int errn = 0;

	for (i = 0; i < len && errn == 0; i++) {
		errn = encode(stream, data[i]);
	}
	return errn;
}

/**
 * Encode a datetime representation which is a sequence of values
 * representing the individual components of the Date-Time
 */
int encodeDateTime(bitstream_t* stream, exi_datetime_t* datetime) {
	int errn = 0;
	switch (datetime->type) {
	case EXI_DATETIME_GYEAR: /* Year, [Time-Zone] */
		errn = encodeInteger32(stream, datetime->year - DATETIME_YEAR_OFFSET);
		break;
	case EXI_DATETIME_GYEARMONTH: /* Year, MonthDay, [TimeZone] */
	case EXI_DATETIME_DATE: /* Year, MonthDay, [TimeZone] */
		errn = encodeInteger32(stream, datetime->year - DATETIME_YEAR_OFFSET);
		if (errn == 0) {
			errn = encodeNBitUnsignedInteger(stream, DATETIME_NUMBER_BITS_MONTHDAY,
					datetime->monthDay);
		}
		break;
	case EXI_DATETIME_DATETIME: /* Year, MonthDay, Time, [FractionalSecs], [TimeZone] */
		errn = encodeInteger32(stream, datetime->year - DATETIME_YEAR_OFFSET);
		if (errn == 0) {
			errn = encodeNBitUnsignedInteger(stream, DATETIME_NUMBER_BITS_MONTHDAY,
					datetime->monthDay);
			if (errn != 0) {
				break;
			}
		}
		/* no break */
	case EXI_DATETIME_TIME: /* Time, [FractionalSecs], [TimeZone] */
		errn = encodeNBitUnsignedInteger(stream, DATETIME_NUMBER_BITS_TIME,
				datetime->time);
		if (errn == 0) {
			if (datetime->presenceFractionalSecs) {
				errn = encodeBoolean(stream, 1);
				if (errn == 0) {
					errn = encodeUnsignedInteger32(stream, datetime->fractionalSecs);
				}
			} else {
				errn = encodeBoolean(stream, 0);
			}
		}
		break;
	case EXI_DATETIME_GMONTH: /* MonthDay, [TimeZone] */
	case EXI_DATETIME_GMONTHDAY: /* MonthDay, [TimeZone] */
	case EXI_DATETIME_GDAY: /* MonthDay, [TimeZone] */
		errn = encodeNBitUnsignedInteger(stream, DATETIME_NUMBER_BITS_MONTHDAY,
				datetime->monthDay);
		break;
	default:
		errn = EXI_UNSUPPORTED_DATETIME_TYPE;
		break;
	}
	if (errn == 0) {
		/* [TimeZone] */
		if (datetime->presenceTimezone) {
			errn = encodeBoolean(stream, 1);
			if (errn == 0) {
				errn = encodeNBitUnsignedInteger(stream, DATETIME_NUMBER_BITS_TIMEZONE,
						datetime->timezone + DATETIME_TIMEZONE_OFFSET_IN_MINUTES);
			}
		} else {
			errn = encodeBoolean(stream, 0);
		}
	}

	return errn;
}




int encode(bitstream_t* stream, uint8_t b) {
#if EXI_OPTION_ALIGNMENT == BIT_PACKED
	return writeBits(stream, 8, b);
#endif /* EXI_OPTION_ALIGNMENT == BIT_PACKED */
#if EXI_OPTION_ALIGNMENT == BYTE_ALIGNMENT
	int errn = 0;
#if EXI_STREAM == BYTE_ARRAY
	if ( (*stream->pos) < stream->size ) {
		stream->data[(*stream->pos)++] = b;
	} else {
		errn = EXI_ERROR_OUTPUT_STREAM_EOF;
	}
#endif /* EXI_STREAM == BYTE_ARRAY */
#if EXI_STREAM == FILE_STREAM
	if ( putc(b, stream->file) == EOF ) {
		errn = EXI_ERROR_OUTPUT_STREAM_EOF;
	}
#endif /* EXI_STREAM == FILE_STREAM */
	return errn;
#endif /* EXI_OPTION_ALIGNMENT == BYTE_ALIGNMENT */
}

/**
 * Encode a single boolean value. A false value is encoded as bit 0 and true
 * value is encode as bit 1.
 */
int encodeBoolean(bitstream_t* stream, int b) {
#if EXI_OPTION_ALIGNMENT == BIT_PACKED
	uint8_t val = b ? 1 : 0;
	return writeBits(stream, 1, val);
#endif /* EXI_OPTION_ALIGNMENT == BIT_PACKED */
#if EXI_OPTION_ALIGNMENT == BYTE_ALIGNMENT
	uint8_t val = b ? 1 : 0;
	return encode(stream, val);
#endif /* EXI_OPTION_ALIGNMENT == BYTE_ALIGNMENT */
}


/**
 * Encode n-bit unsigned integer. The n least significant bits of parameter
 * b starting with the most significant, i.e. from left to right.
 */
int encodeNBitUnsignedInteger(bitstream_t* stream, size_t nbits, uint32_t val)  {
#if EXI_OPTION_ALIGNMENT == BIT_PACKED
	int errn = 0;
	if (nbits > 0) {
		errn = writeBits(stream, nbits, val);
	}
	return errn;
#endif /* EXI_OPTION_ALIGNMENT == BIT_PACKED */
#if EXI_OPTION_ALIGNMENT == BYTE_ALIGNMENT
	int errn = 0;
	if (nbits > 0) {
		if (nbits < 9) {
			/* 1 byte */
			errn = encode(stream, val & 0xff);
		} else if (nbits < 17) {
			/* 2 bytes */
			errn = encode(stream, val & 0x00ff);
			if(errn == 0) {
				errn = encode(stream, (uint8_t)((val & 0xff00) >> 8));
			}
		} else if (nbits < 25) {
			/* 3 bytes */
			errn = encode(stream, val & 0x0000ff);
			if(errn == 0) {
				errn = encode(stream, (uint8_t)((val & 0x00ff00) >> 8));
				if(errn == 0) {
					errn = encode(stream, (uint8_t)((val & 0xff0000) >> 16));
				}
			}
		} else if (nbits < 33) {
			/* 4 bytes */
			errn = encode(stream, val & 0x000000ff);
			if(errn == 0) {
				errn = encode(stream, (uint8_t)((val & 0x0000ff00) >> 8));
				if(errn == 0) {
					errn = encode(stream, (uint8_t)((val & 0x00ff0000) >> 16));
					if(errn == 0) {
						errn = encode(stream, (uint8_t)((val & 0xff000000) >> 24));
					}
				}
			}
		} else {
			/* TODO Currently not more than 4 Bytes allowed for NBitUnsignedInteger */
			errn = EXI_UNSUPPORTED_NBIT_INTEGER_LENGTH;
		}
	}
	return errn;
#endif /* EXI_OPTION_ALIGNMENT == BYTE_ALIGNMENT */
}

/**
 * Flush underlying output stream.
 */
int encodeFinish(bitstream_t* stream) {
#if EXI_OPTION_ALIGNMENT == BIT_PACKED
#endif /* EXI_OPTION_ALIGNMENT == BIT_PACKED */
	return flush(stream);
#if EXI_OPTION_ALIGNMENT == BYTE_ALIGNMENT
	/* no pending bits in byte-aligned mode */
	return 0;
#endif /* EXI_OPTION_ALIGNMENT == BYTE_ALIGNMENT */
}



#endif
