/******************************************************************************
* Copyright 2018 The Apollo Authors. All Rights Reserved.
*
* Licensed under the Apache License, Version 2.0 (the License);
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an AS IS BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*****************************************************************************/
#ifndef RADAR_LIB_INTERFACE_BASE_ROI_FILTER_H_
#define RADAR_LIB_INTERFACE_BASE_ROI_FILTER_H_

// SAMPLE CODE:
//
// class DefaultRoiFilter : public BaseRoiFilter {
//  public:
//   DefaultRoiFilter() : BaseRoiFilter() {}
//   virtual ~DefaultRoiFilter() {}
//
//   virtual bool Init() override {
//     // Do something.
//     return true;
//   }
//
//   virtual bool RoiFilter(
//           const RoiFilterOptions& options,
//           base::FramePtr radar_frame) override {
//      // Do something.
//     return true;
//   }
//
//   virtual std::string Name() const override {
//        return "DefaultRoiFilter";
//   }
//
// };
//
// // Register plugin.
// PERCEPTION_REGISTER_ROIFITLER(DefaultRoiFilter);
////////////////////////////////////////////////////////
// USING CODE:
//
// BaseRoiFilter* roi_filter =
//    BaseRoiFilterRegisterer::GetInstanceByName("DefaultRoiFilter");
// using roi_filter to do somethings.
// ////////////////////////////////////////////////////

#include <string>
#include <vector>
#include "Eigen/Core"
#include "modules/perception/base/frame.h"
#include "cybertron/common/log.h"
#include "modules/perception/lib/config_manager/config_manager.h"
#include "modules/perception/lib/registerer/registerer.h"
#include "modules/perception/common/geometry/roi_filter.h"

namespace apollo {
namespace perception {
namespace radar {

struct RoiFilterOptions {
  base::HdmapStructPtr roi = nullptr;
};

class BaseRoiFilter {
 public:
  BaseRoiFilter() = default;
  virtual ~BaseRoiFilter() = default;

  virtual bool Init() = 0;

  // @brief: fliter the objects outside the ROI
  // @param [in]: options.
  // @param [in / out]: origin total objects / the objects in the ROI.
  virtual bool RoiFilter(
          const RoiFilterOptions& options,
          base::FramePtr radar_frame) = 0;

  virtual std::string Name() const = 0;

 private:
  BaseRoiFilter(const BaseRoiFilter&) = delete;
  BaseRoiFilter& operator=(const BaseRoiFilter&) = delete;
};

PERCEPTION_REGISTER_REGISTERER(BaseRoiFilter);
#define PERCEPTION_REGISTER_ROI_FILTER(name) \
  PERCEPTION_REGISTER_CLASS(BaseRoiFilter, name)

}  // namespace radar
}  // namespace perception
}  // namespace apollo

#endif  // RADAR_LIB_INTERFACE_BASE_ROI_FILTER_H_
