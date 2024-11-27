#ifndef AIE_TRACE_COMMON_CONFIG_DOT_H
#define AIE_TRACE_COMMON_CONFIG_DOT_H

#include <cstdint>
#include "xdp/profile/plugin/aie_trace/aie_trace_metadata.h"

extern "C" {
  #include <xaiengine.h>
  #include <xaiengine/xaiegbl_params.h>
}

namespace xdp::aie::trace {  
    module_type getTileType(std::shared_ptr<AieTraceMetadata> metadata, uint8_t absRow);
    void build2ChannelBroadcastNetwork(XAie_DevInst* aieDevInst, void *handle, std::shared_ptr<AieTraceMetadata> metadata, uint8_t broadcastId1, uint8_t broadcastId2, XAie_Events event);
    void reset2ChannelBroadcastNetwork(XAie_DevInst* aieDevInst, void *handle, std::shared_ptr<AieTraceMetadata> metadata, uint8_t broadcastId1, uint8_t broadcastId2);
}

#endif