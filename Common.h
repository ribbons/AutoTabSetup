/*
 * This file is part of Auto Tab Setup.
 * Copyright © 2014 by the authors - see the AUTHORS file for details.
 *
 * This program is free software: you can redistribute it and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation, either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
 * License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#pragma once

// Windows Headers

#define _WIN32_WINNT _WIN32_WINNT_VISTA
#define WIN32_LEAN_AND_MEAN

#include <windows.h>

// Boost Headers

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

// Programmer's Notepad Headers

#define PNASSERT assert

#include "allocator.h"
#include "pnextstring.h"
#include "extiface.h"
#include "Scintilla.h"

// Global variables

static extensions::IPN* g_pn;
