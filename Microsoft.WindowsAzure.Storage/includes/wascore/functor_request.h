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

	// Common request factory methods

	Create_Request_Builder_Zero(get_service_properties, get_service_properties);
	Create_Request_Builder_Zero(set_service_properties, set_service_properties);
	Create_Request_Builder_Zero(get_service_stats, get_service_stats);

	// Blob request factory methods

	Create_Request_Builder_Two(blob_create_blob_container_request_builder, create_blob_container, blob_container_public_access_type, const cloud_metadata&);
	Create_Request_Builder_One(blob_delete_blob_container_request_builder, delete_blob_container, const access_condition&);
	Create_Request_Builder_One(blob_get_blob_container_properties_request_builder, get_blob_container_properties, const access_condition&);
	Create_Request_Builder_Two(blob_set_blob_container_metadata_request_builder, set_blob_container_metadata, const cloud_metadata&, const access_condition&);
	Create_Request_Builder_One(blob_get_blob_container_acl_request_builder, get_blob_container_acl, const access_condition&);
	Create_Request_Builder_Two(blob_set_blob_container_acl_request_builder, set_blob_container_acl, blob_container_public_access_type, const access_condition&);
	Create_Request_Builder_Four(blob_list_containers_request_builder, list_containers, const utility::string_t&, container_listing_details::values, int, const continuation_token&);
	Create_Request_Builder_Five(blob_list_blobs_request_builder, list_blobs, const utility::string_t&, const utility::string_t&, blob_listing_details::values, int, const continuation_token&);
	Create_Request_Builder_Five(blob_lease_blob_container_request_builder, lease_blob_container, const utility::string_t&, const utility::string_t&, const lease_time&, const lease_break_period&, const access_condition&);
	Create_Request_Builder_Five(blob_lease_blob_request_builder, lease_blob, const utility::string_t&, const utility::string_t&, const lease_time&, const lease_break_period&, const access_condition&);
	Create_Request_Builder_Three(blob_put_block_request_builder, put_block, const utility::string_t&, const utility::string_t&, const access_condition&);
	Create_Request_Builder_Four(blob_put_block_list_request_builder, put_block_list, const cloud_blob_properties&, const cloud_metadata&, const utility::string_t&, const access_condition&);
	Create_Request_Builder_Three(blob_get_block_list_request_builder, get_block_list, block_listing_filter, const utility::string_t&, const access_condition&);
	Create_Request_Builder_Four(blob_get_page_ranges_request_builder, get_page_ranges, utility::size64_t, utility::size64_t, const utility::string_t&, const access_condition&);
	Create_Request_Builder_Four(blob_put_page_request_builder, put_page, page_range, page_write, const utility::string_t&, const access_condition&);
	Create_Request_Builder_Two(blob_append_block_request_builder, append_block, const utility::string_t&, const access_condition&);
	Create_Request_Builder_Three(blob_put_block_blob_request_builder, put_block_blob, const cloud_blob_properties&, const cloud_metadata&, const access_condition&);
	Create_Request_Builder_Five(blob_put_page_blob_request_builder, put_page_blob, utility::size64_t, int64_t, const cloud_blob_properties&, const cloud_metadata&, const access_condition&);
	Create_Request_Builder_Three(blob_put_append_blob_request_builder, put_append_blob, const cloud_blob_properties&, const cloud_metadata&, const access_condition&);
	Create_Request_Builder_Five(blob_get_blob_request_builder, get_blob, utility::size64_t, utility::size64_t, bool, const utility::string_t&, const access_condition&);
	Create_Request_Builder_Two(blob_get_blob_properties_request_builder, get_blob_properties, const utility::string_t&, const access_condition&);
	Create_Request_Builder_Three(blob_set_blob_properties_request_builder, set_blob_properties, const cloud_blob_properties&, const cloud_metadata&, const access_condition&);
	Create_Request_Builder_Two(blob_resize_page_blob_request_builder, resize_page_blob, utility::size64_t, const access_condition&);
	Create_Request_Builder_Two(blob_set_page_blob_sequence_number_request_builder, set_page_blob_sequence_number, const azure::storage::sequence_number&, const access_condition&);
	Create_Request_Builder_Two(blob_snapshot_blob_request_builder, snapshot_blob, const cloud_metadata&, const access_condition&);
	Create_Request_Builder_Two(blob_set_blob_metadata_request_builder, set_blob_metadata, const cloud_metadata&, const access_condition&);
	Create_Request_Builder_Three(blob_delete_blob_request_builder, delete_blob, delete_snapshots_option, const utility::string_t&, const access_condition&);
	Create_Request_Builder_Four(blob_copy_blob_request_builder, copy_blob, const web::http::uri&, const access_condition&, const cloud_metadata&, const access_condition&);
	Create_Request_Builder_Two(blob_abort_copy_blob_request_builder, abort_copy_blob, const utility::string_t&, const access_condition&);
	
	// Table request factory methods

	Create_Request_Builder_Two(table_execute_table_operation_request_builder, execute_table_operation, const cloud_table&, table_operation_type);
	Create_Request_Builder_Two(table_execute_operation_request_builder, execute_operation, const table_operation&, table_payload_format);
	Create_Request_Builder_Five(table_execute_batch_operation_request_builder, execute_batch_operation, Concurrency::streams::stringstreambuf&, const cloud_table&, const table_batch_operation&, table_payload_format, bool);
	Create_Request_Builder_One(table_execute_query_request_builder, execute_query, table_payload_format);
	Create_Request_Builder_Zero(table_get_table_acl_request_builder, get_table_acl);
	Create_Request_Builder_Zero(table_set_table_acl_request_builder, set_table_acl);
	
	// Queue request factory methods

	Create_Request_Builder_Zero(queue_list_queues_request_builder, list_queues);
	Create_Request_Builder_Zero(queue_create_queue_request_builder, create_queue);
	Create_Request_Builder_Zero(queue_delete_queue_request_builder, delete_queue);
	Create_Request_Builder_Three(queue_add_message_request_builder, add_message, const cloud_queue_message&, std::chrono::seconds, std::chrono::seconds);
	Create_Request_Builder_Three(queue_get_messages_request_builder, get_messages, size_t, std::chrono::seconds, bool);
	Create_Request_Builder_One(queue_delete_message_request_builder, delete_message, const cloud_queue_message&);
	Create_Request_Builder_Three(queue_update_message_request_builder, update_message, const cloud_queue_message&, std::chrono::seconds, bool);
	Create_Request_Builder_Zero(queue_clear_messages_request_builder, clear_messages);
	Create_Request_Builder_Zero(queue_download_queue_metadata_request_builder, download_queue_metadata);
	Create_Request_Builder_One(queue_upload_queue_metadata_request_builder, upload_queue_metadata, const cloud_metadata&);
	Create_Request_Builder_Zero(queue_get_queue_acl_request_builder, get_queue_acl);
	Create_Request_Builder_Zero(queue_set_queue_acl_request_builder, set_queue_acl);

}}}