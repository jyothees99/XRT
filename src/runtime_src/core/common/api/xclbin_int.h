/*
 * Copyright (C) 2020-2021, Xilinx Inc - All rights reserved
 * Xilinx Runtime (XRT) Experimental APIs
 *
 * Licensed under the Apache License, Version 2.0 (the "License"). You may
 * not use this file except in compliance with the License. A copy of the
 * License is located at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 */

#ifndef _XRT_COMMON_XCLBIN_INT_H_
#define _XRT_COMMON_XCLBIN_INT_H_

// This file defines implementation extensions to the XRT XCLBIN APIs.
#include "core/include/experimental/xrt_xclbin.h"
#include "core/common/xclbin_parser.h"

#include <set>

// Provide access to xrt::xclbin data that is not directly exposed
// to end users via xrt::xclbin.   These functions are used by
// XRT core implementation.
namespace xrt_core { namespace xclbin_int {

// is_valid_or_error() - Throw if invalid handle
void
is_valid_or_error(xrtXclbinHandle handle);

// get_axlf() - Retrieve complete axlf from handle
const axlf*
get_axlf(xrtXclbinHandle);

// get_xclbin() - Convert handle to object
xrt::xclbin
get_xclbin(xrtXclbinHandle);

// get_axlf_section() - Retrieve specified section
std::pair<const char*, size_t>
get_axlf_section(const xrt::xclbin& xclbin, axlf_section_kind kind);

// get_axlf_sections() - Retrieve specified sections
std::vector<std::pair<const char*, size_t>>
get_axlf_sections(const xrt::xclbin& xclbin, axlf_section_kind kind);

// read_xclbin() - Read specified xclbin file 
std::vector<char>
read_xclbin(const std::string& fnm);

// get_properties() - Get kernel properties
const xrt_core::xclbin::kernel_properties&
get_properties(const xrt::xclbin::kernel& kernel);

// get_arginfo() - Get xclbin kernel argument metadata
// Sorted by arg index, but appended with rtinfo args (if any)
// which have no index
const std::vector<xrt_core::xclbin::kernel_argument>&
get_arginfo(const xrt::xclbin::kernel& kernel);

// get_ip_idx() - Get the ip_layout index of a ip in the xclbin
// This is used to cross-correlated to connectivity information
// To be rooted out after refactoring completes
unsigned int
get_ip_idx(const xrt::xclbin::ip& ip);

// get_ip_data() - Get the ip_data element of an ip in the xclbin
// To be rooted out after refactoring completes
const ip_data*
get_ip_data(const xrt::xclbin::ip& ip);

}} // xclbin_int, xrt_core

#endif
