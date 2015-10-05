# This file is part of Auto Tab Setup.
# Copyright © 2015 by the authors - see the AUTHORS file for details.
#
# This program is free software: you can redistribute it and/or modify it under the terms of the GNU General
# Public License as published by the Free Software Foundation, either version 3 of the License, or (at your
# option) any later version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
# License for more details.
#
# You should have received a copy of the GNU General Public License along with this program.  If not, see
# <http://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.3)
project("Auto Tab Setup")

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED)

if(DEFINED ENV{PN_SDK_DIR})
	set(PN_SDK_DIR "$ENV{PN_SDK_DIR}")
	set(PN_SDK_DIR "$ENV{PN_SDK_DIR}" CACHE PATH "Programmer's Notepad SDK directory")
endif()

if(NOT PN_SDK_DIR)
	message(FATAL_ERROR "Please set PN_SDK_DIR to the directory containing the Programmer's Notepad SDK")
endif()

if(NOT IS_DIRECTORY "${PN_SDK_DIR}")
	message(FATAL_ERROR "Directory \"${PN_SDK_DIR}\" does not exist")
endif()

INCLUDE_DIRECTORIES(libfindindent ${Boost_INCLUDE_DIR} ${PN_SDK_DIR})

add_subdirectory(libfindindent)

add_library(AutoTabSetup SHARED
            AppEventSink.cpp DocEventSink.cpp plugin.cpp
            AppEventSink.h DocEventSink.h Properties.h Common.h
            "Auto Tab Setup.rc" "Auto Tab Setup.def")
set_target_properties(AutoTabSetup PROPERTIES OUTPUT_NAME "Auto Tab Setup")
TARGET_LINK_LIBRARIES(AutoTabSetup libfindindent)
