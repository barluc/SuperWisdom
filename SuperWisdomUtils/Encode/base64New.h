/*
  Copyright (c) 2005-2009 by Jakob Schroeter <js@camaya.net>
  This file is part of the gloox library. http://camaya.net/gloox

  This software is distributed under a license. The full license
  agreement can be found in the file LICENSE in this distribution.
  This software may not be copied, modified, sold or distributed
  other than expressed in the named license agreement.

  This software is distributed without any warranty.
*/

#pragma  once

#include "macros.h"

#include <string>


/**
 * @brief An implementation of the Base64 data encoding (RFC 3548)
 *
 * @author Jakob Schroeter <js@camaya.net>
 * @since 0.8
 */
namespace Base64New
{

	/**
	 * Base64-encodes the input according to RFC 3548.
	 * @param input The data to encode.
	 * @return The encoded string.
	 */
	std::string encode64(const std::string& input);

	/**
	 * Base64-decodes the input according to RFC 3548.
	 * @param input The encoded data.
	 * @return The decoded data.
	 */
	std::string decode64(const std::string& input);

}
