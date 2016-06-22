// -----------------------------------------------------------------------------------------
// <copyright file="functor_request.h" company="Microsoft">
//    Copyright 2013 Microsoft Corporation
//
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//      http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.
// </copyright>
// -----------------------------------------------------------------------------------------

#pragma once

#include "stdafx.h"
#include "functors.h"
#include "protocol.h"
#include "was/common.h"
#include "wascore/basic_types.h"

namespace azure { namespace storage { namespace functor {

	// Queue request builder

	Create_Request_Builder_Three(queue_add_message_request_builder, add_message, const cloud_queue_message, std::chrono::seconds, std::chrono::seconds);

}}}