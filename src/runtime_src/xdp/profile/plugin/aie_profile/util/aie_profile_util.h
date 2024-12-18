/**
 * Copyright (C) 2022-2023 Advanced Micro Devices, Inc. - All rights reserved
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

#ifndef AIE_PROFILE_UTIL_DOT_H
#define AIE_PROFILE_UTIL_DOT_H

#include <cstdint>
#include <string>
#include <unordered_map>
#include "xdp/profile/plugin/aie_profile/aie_profile_defs.h"
#include "xdp/profile/database/static_info/aie_constructs.h"

extern "C" {
#include <xaiengine.h>
#include <xaiengine/xaiegbl_params.h>
}

namespace xdp::aie::profile {

  const std::map<xdp::module_type, uint16_t> counterBases = {
    {module_type::core,     static_cast<uint16_t>(0)},
    {module_type::dma,      BASE_MEMORY_COUNTER},
    {module_type::shim,     BASE_SHIM_COUNTER},
    {module_type::mem_tile, BASE_MEM_TILE_COUNTER}
  };

  const std::vector<XAie_ModuleType> falModuleTypes = {
    XAIE_CORE_MOD,
    XAIE_MEM_MOD,
    XAIE_PL_MOD,
    XAIE_MEM_MOD
  };

  #define START_TO_BYTES_TRANSFERRED_REPORT_EVENT_ID 3600
  #define INTF_TILE_LATENCY_REPORT_EVENT_ID          3601
  enum adfAPI {
    START_TO_BYTES_TRANSFERRED,
    INTF_TILE_LATENCY
  };

  struct adfAPIResourceInfo {
    uint8_t srcPcIdx;
    uint8_t destPcIdx;
    uint64_t profileResult;
    bool isSourceTile = false;
  };

  const std::unordered_map<std::string, uint16_t> adfApiMetricSetMap = {
    {METRIC_BYTE_COUNT, static_cast<uint16_t>(3600)},
    {METRIC_LATENCY,    static_cast<uint16_t>(3601)}
  };

  /**
   * @brief   Get metric sets for core modules
   * @param   hwGen integer representing the hardware generation
   * @return  Map of core metric set names with vectors of event IDs
   */
  std::map<std::string, std::vector<XAie_Events>> getCoreEventSets(const int hwGen);

  /**
   * @brief   Get metric sets for memory modules
   * @param   hwGen integer representing the hardware generation
   * @return  Map of memory metric set names with vectors of event IDs
   */
  std::map<std::string, std::vector<XAie_Events>> getMemoryEventSets(const int hwGen);
 
  /**
   * @brief   Get metric sets for interface modules
   * @return  Map of interface metric set names with vectors of event IDs
   */
  std::map<std::string, std::vector<XAie_Events>> getInterfaceTileEventSets(const int hwGen);

  /**
   * @brief   Get metric sets for memory tile modules
   * @return  Map of memory tile metric set names with vectors of event IDs
   */
  std::map<std::string, std::vector<XAie_Events>> getMemoryTileEventSets();

  /**
   * @brief  Modify configured events
   * @param type module type 
   * @param subtype plio/gmio type
   * @param events vector of events to replace with the respective channel 1 events
   * @param hwGen AIE hardware generation
   */
  void modifyEvents(const module_type type, const io_type subtype, const uint8_t channel,
                    std::vector<XAie_Events>& events, const int hwGen);

  /**
   * @brief  Check if event is generated by a stream switch monitor port
   * @param  event Event ID to check
   * @return True if given event is from a stream switch port
   */
  bool isStreamSwitchPortEvent(const XAie_Events event);

  /**
   * @brief  Check if event is a port running event
   * @param  event Event ID to check
   * @return True if given event is a port running event
   */
  bool isPortRunningEvent(const XAie_Events event);

  /**
   * @brief  Check if event is a port stalled event
   * @param  event Event ID to check
   * @return True if given event is a port stalled event
   */
  bool isPortStalledEvent(const XAie_Events event);

  /**
   * @brief  Check if event is a port idle event
   * @param  event Event ID to check
   * @return True if given event is a port idle event
   */
  bool isPortIdleEvent(const XAie_Events event);

  /**
   * @brief  Check if event is a port tlast event
   * @param  event Event ID to check
   * @return True if given event is a port tlast event
   */
  bool isPortTlastEvent(const XAie_Events event);

  uint8_t getPortNumberFromEvent(const XAie_Events event);
  
  /**
   * @brief Get XAie module enum at the module index 
   * @param moduleIndex module index
   * @return  
   */
  XAie_ModuleType getFalModuleType(const int moduleIndex);

  /**
   * @brief Get base event number for a module
   * @param type module type
   * @return  
   */
  uint16_t getCounterBase(const xdp::module_type type);

  /**
   * @brief Check the match of the XAie enum module type with our xdp::module_type
   * @param type xdp::module_type enum type
   * @param mod AIE driver enum type
   */
  bool isValidType(const module_type type, const XAie_ModuleType mod);

  bool metricSupportsGraphIterator(std::string metricSet);
  bool profileAPIMetricSet(const std::string metricSet);
  uint16_t getAdfApiReservedEventId(const std::string metricSet);
  inline bool adfAPIStartToTransferredConfigEvent(uint32_t eventID) { return START_TO_BYTES_TRANSFERRED_REPORT_EVENT_ID==eventID; }
  inline bool adfAPILatencyConfigEvent(uint32_t eventID) { return INTF_TILE_LATENCY_REPORT_EVENT_ID==eventID; }
  std::pair<int, XAie_Events> getPreferredPLBroadcastChannel();

  uint32_t convertToBeats(const std::string& metricSet, uint32_t bytes, uint8_t hw_gen);

}  // namespace xdp::aie::profile

#endif
