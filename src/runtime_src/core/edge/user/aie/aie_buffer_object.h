// SPDX-License-Identifier: Apache-2.0
// Copyright (C) 2024 Advanced Micro Devices, Inc. All rights reserved.

#ifndef _ZYNQ_AIE_BUFFER_OBJECT_H_
#define _ZYNQ_AIE_BUFFER_OBJECT_H_

#include "core/edge/user/aie/aie.h"
#include "core/edge/user/aie/common_layer/adf_api_config.h"
#include "core/common/message.h"
#include "core/common/shim/shared_handle.h"
#include "core/common/shim/aie_buffer_handle.h"
#include "core/include/xrt/xrt_uuid.h"
#include "xrt/xrt_graph.h"

#include <memory>

namespace zynqaie {
  // Shim handle for graph object
  class hwctx_object;
  class aie_buffer_object: public xrt_core::aie_buffer_handle
  {
    std::string name;
    std::shared_ptr<Aie> m_aie_array;

  public:
    aie_buffer_object(xrt_core::device* device , const xrt::uuid uuid, const char* name, const zynqaie::hwctx_object* hwctx=nullptr);

    void
    sync(std::vector<xrt::bo>& bos, xclBOSyncDirection dir, size_t size, size_t offset) const;

    std::string
    get_name() const;

  }; // aie_buffer_object
}
#endif
