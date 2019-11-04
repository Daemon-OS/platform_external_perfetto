/*
 * Copyright (C) 2019 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef INCLUDE_PERFETTO_TRACING_TRACK_EVENT_CONTEXT_H_
#define INCLUDE_PERFETTO_TRACING_TRACK_EVENT_CONTEXT_H_

#include "perfetto/protozero/message_handle.h"
#include "protos/perfetto/trace/trace_packet.pbzero.h"

namespace perfetto {
namespace internal {
class TrackEventInternal;
}

// Allows adding custom arguments into track events. Example:
//
//   TRACE_EVENT_BEGIN("category", "Title",
//                     [](perfetto::TrackEventContext ctx) {
//                       auto* dbg = ctx.track_event()->add_debug_annotations();
//                       dbg->set_name("name");
//                       dbg->set_int_value(1234);
//                     });
//
class TrackEventContext {
 public:
  TrackEventContext(TrackEventContext&&) = default;
  ~TrackEventContext();

  protos::pbzero::TrackEvent* track_event() const { return track_event_; }

 private:
  using TracePacketHandle =
      ::protozero::MessageHandle<protos::pbzero::TracePacket>;

  friend class internal::TrackEventInternal;
  TrackEventContext(TracePacketHandle);
  TrackEventContext(const TrackEventContext&) = delete;

  TracePacketHandle trace_packet_;
  protos::pbzero::TrackEvent* track_event_;
};

}  // namespace perfetto

#endif  // INCLUDE_PERFETTO_TRACING_TRACK_EVENT_CONTEXT_H_