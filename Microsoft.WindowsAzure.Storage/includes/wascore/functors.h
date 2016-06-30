// -----------------------------------------------------------------------------------------
// <copyright file="functors.h" company="Microsoft">
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
#include "was/common.h"
#include "wascore/basic_types.h"

namespace azure { namespace storage { namespace functor {

	class request_builder
	{
	public:
		virtual web::http::http_request build_request(web::http::uri_builder& uri_builder, const std::chrono::seconds& timeout, operation_context context)
		{
			UNREFERENCED_PARAMETER(uri_builder);
			UNREFERENCED_PARAMETER(timeout);
			UNREFERENCED_PARAMETER(context);
			return web::http::http_request();
		}
	};

	// create a request builder with zero extra parameter.
#define Create_Request_Builder_Zero(Name, Method)													\
	class Name :  public request_builder															\
	{																								\
	public:																							\
		web::http::http_request build_request(web::http::uri_builder& uri_builder, const std::chrono::seconds& timeout, operation_context context)	\
		{																							\
			return protocol::Method(uri_builder, timeout, context);									\
		}																							\
	};
	
	// create a request builder with one extra parameter.
#define Create_Request_Builder_One(Name, Method, _P1)												\
	class Name :  public request_builder															\
	{																								\
	public:																							\
		explicit Name(_P1 para1) :	m_para1(para1)													\
		{																							\
		}																							\
		web::http::http_request build_request(web::http::uri_builder& uri_builder, const std::chrono::seconds& timeout, operation_context context)	\
		{																							\
			return protocol::Method(m_para1, uri_builder, timeout, context);						\
		}																							\
	private:																						\
		_P1 m_para1;																				\
	};

	// create a request builder with two extra parameters.
#define Create_Request_Builder_Two(Name, Method, _P1, _P2)											\
	class Name :  public request_builder															\
	{																								\
	public:																							\
		explicit Name(_P1 para1, _P2 para2) :														\
			m_para1(para1), m_para2(para2)															\
		{																							\
		}																							\
		web::http::http_request build_request(web::http::uri_builder& uri_builder, const std::chrono::seconds& timeout, operation_context context)	\
		{																							\
			return protocol::Method(m_para1, m_para2, uri_builder, timeout, context);				\
		}																							\
	private:																						\
		_P1 m_para1;																				\
		_P2 m_para2;																				\
	};

	// creat a request builder with three extra parameters.
#define Create_Request_Builder_Three(Name, Method, _P1, _P2, _P3) 									\
	class Name :  public request_builder															\
	{																								\
	public:																							\
		explicit Name(_P1 para1, _P2 para2, _P3 para3) :											\
			m_para1(para1), m_para2(para2), m_para3(para3)											\
		{																							\
		}																							\
		web::http::http_request build_request(web::http::uri_builder& uri_builder, const std::chrono::seconds& timeout, operation_context context)	\
		{																							\
			return protocol::Method(m_para1, m_para2, m_para3, uri_builder, timeout, context);		\
		}																							\
	private:																						\
		_P1 m_para1;																				\
		_P2 m_para2;																				\
		_P3 m_para3;																				\
	};

	// creat a request builder with four extra parameters.
#define Create_Request_Builder_Four(Name, Method, _P1, _P2, _P3, _P4) 								\
	class Name :  public request_builder															\
	{																								\
	public:																							\
		explicit Name(_P1 para1, _P2 para2, _P3 para3, _P4 para4) :									\
			m_para1(para1), m_para2(para2), m_para3(para3), m_para4(para4)							\
		{																							\
		}																							\
		web::http::http_request build_request(web::http::uri_builder& uri_builder, const std::chrono::seconds& timeout, operation_context context)	\
		{																							\
			return protocol::Method(m_para1, m_para2, m_para3, m_para4, uri_builder, timeout, context);		\
		}																							\
	private:																						\
		_P1 m_para1;																				\
		_P2 m_para2;																				\
		_P3 m_para3;																				\
		_P4 m_para4;																				\
	};

	// creat a request builder with five extra parameters.
#define Create_Request_Builder_Five(Name, Method, _P1, _P2, _P3, _P4, _P5) 							\
	class Name :  public request_builder															\
	{																								\
	public:																							\
		explicit Name(_P1 para1, _P2 para2, _P3 para3, _P4 para4, _P5 para5) :						\
			m_para1(para1), m_para2(para2), m_para3(para3), m_para4(para4), m_para5(para5)			\
		{																							\
		}																							\
		web::http::http_request build_request(web::http::uri_builder& uri_builder, const std::chrono::seconds& timeout, operation_context context)	\
		{																							\
			return protocol::Method(m_para1, m_para2, m_para3, m_para4, m_para5, uri_builder, timeout, context);		\
		}																							\
	private:																						\
		_P1 m_para1;																				\
		_P2 m_para2;																				\
		_P3 m_para3;																				\
		_P4 m_para4;																				\
		_P5 m_para5;																				\
	};

}}}
