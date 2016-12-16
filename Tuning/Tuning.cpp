// Tuning.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <ctime>

#include "was\storage_account.h"
#include "was\blob.h"

#include "cpprest\rawptrstream.h"

const int times = 5;
const int parallel = 20;

class Performance
{
public:
    Performance(utility::string_t settings)
        :account(azure::storage::cloud_storage_account::parse(settings)), client(account.create_cloud_blob_client())
    {
    }

    // a single download test with length and parallelism
    // return the time costs in milli-seconds.
	int single_download_test(size_t length, int parallelism);

	int single_download_test_raw_memory(size_t length, int parallelism);
    
    int single_download_test_filestream(size_t length, int parallelism);

	utility::string_t download_test()
	{
		utility::stringstream_t out;
		std::vector<size_t> lens{ 3, 30, 100, 1000 };
		for (size_t index = 0; index < lens.size(); ++index)
		{
			size_t length(lens[index]);
			for (int i = 1; i <= parallel; ++i)
			{
				ucout << length << L" " << i << " " << single_download_test(length, i) << std::endl;
			}
		}
		return out.str();
	}
	utility::string_t download_test_raw_memory()
	{
		utility::stringstream_t out;
		std::vector<size_t> lens{ 3, 30, 100, 1000 };
		for (size_t index = 0; index < lens.size(); ++index)
		{
			size_t length(lens[index]);
			for (int i = 1; i <= parallel; ++i)
			{
				ucout << length << L" " << i << " " << single_download_test_raw_memory(length, i) << std::endl;
			}
		}
		return out.str();
	}

    utility::string_t download_test_filestream()
    {
        utility::stringstream_t out;
        std::vector<size_t> lens{ 3, 30, 100, 1000};
        for (size_t index = 0; index < lens.size(); ++index)
        {
            size_t length(lens[index]);
            for (int i = 1; i <= parallel; ++i)
            {
				ucout << length << L" " << i << " " << single_download_test_filestream(length, i) << std::endl;
            }
        }
        return out.str();
    }

private:
    azure::storage::cloud_storage_account account;
    azure::storage::cloud_blob_client client;
};

int Performance::single_download_test(size_t length, int parallelism)
{
    azure::storage::cloud_blob_container container = client.get_container_reference(L"perftests");
    container.create_if_not_exists();
    azure::storage::cloud_append_blob blob = container.get_append_blob_reference(utility::conversions::print_string(length));
	azure::storage::blob_request_options option;
	if (!(blob.exists() && (blob.properties().size() == length * 1024 * 1024)))
	{
		blob.create_or_replace();
		// upload data
		size_t target_length = length * 1024 * 1024;
		option.set_parallelism_factor(5);
		option.set_use_transactional_md5(true);
		if (length <= 100)
		{
			std::vector<uint8_t> data;
			data.resize(length * 1024 * 1024);
			concurrency::streams::container_buffer<std::vector<uint8_t>> upload_buffer(data);
			blob.upload_from_stream(upload_buffer.create_istream(), azure::storage::access_condition(), option, azure::storage::operation_context());
		}
		else
		{
			for (int len = 0; len < length; len += 100)
			{
				std::vector<uint8_t> data;
				data.resize(100 * 1024 * 1024);
				concurrency::streams::container_buffer<std::vector<uint8_t>> upload_buffer(data);
				blob.append_from_stream(upload_buffer.create_istream(), azure::storage::access_condition(), option, azure::storage::operation_context());
			}
		}
	}
	int total = 0;
	for (int i = 0; i < times; ++i)
	{
		// download data
		option.set_disable_content_md5_validation(true);
		option.set_parallelism_factor(parallelism);
		concurrency::streams::container_buffer<std::vector<uint8_t>> download_buffer;
		auto start = clock();
		blob.download_to_stream(download_buffer.create_ostream(), azure::storage::access_condition(), option, azure::storage::operation_context());
		auto end = clock();
		total += end - start;
	}

    return total / times;
}

int Performance::single_download_test_raw_memory(size_t length, int parallelism)
{
	azure::storage::cloud_blob_container container = client.get_container_reference(L"perftests");
	container.create_if_not_exists();
	azure::storage::cloud_append_blob blob = container.get_append_blob_reference(utility::conversions::print_string(length));
	azure::storage::blob_request_options option;
	if (!(blob.exists() && (blob.properties().size() == length * 1024 * 1024)))
	{
		blob.create_or_replace();
		// upload data
		size_t target_length = length * 1024 * 1024;
		option.set_parallelism_factor(5);
		option.set_use_transactional_md5(true);
		if (length <= 100)
		{
			std::vector<uint8_t> data;
			data.resize(length * 1024 * 1024);
			concurrency::streams::container_buffer<std::vector<uint8_t>> upload_buffer(data);
			blob.upload_from_stream(upload_buffer.create_istream(), azure::storage::access_condition(), option, azure::storage::operation_context());
		}
		else
		{
			for (int len = 0; len < length; len += 100)
			{
				std::vector<uint8_t> data;
				data.resize(100 * 1024 * 1024);
				concurrency::streams::container_buffer<std::vector<uint8_t>> upload_buffer(data);
				blob.append_from_stream(upload_buffer.create_istream(), azure::storage::access_condition(), option, azure::storage::operation_context());
			}
		}
	}
    int total = 0;
    for (int i = 0; i < times; ++i)
    {
        // download data
        option.set_disable_content_md5_validation(true);
        option.set_parallelism_factor(parallelism);
        uint8_t* buffer = new uint8_t[length * 1024 * 1024];
        auto download_buffer = concurrency::streams::rawptr_stream<uint8_t>::open_ostream(buffer, length * 1024 * 1024);
        auto start = clock();
        blob.download_to_stream(download_buffer, azure::storage::access_condition(), option, azure::storage::operation_context());
        auto end = clock();
        total += end - start;
        delete[] buffer;
    }

	return total / times;
}

int Performance::single_download_test_filestream(size_t length, int parallelism)
{
    azure::storage::cloud_blob_container container = client.get_container_reference(L"perftests");
    container.create_if_not_exists();
    azure::storage::cloud_append_blob blob = container.get_append_blob_reference(utility::conversions::print_string(length));
	azure::storage::blob_request_options option;

	if (!(blob.exists() && (blob.properties().size() == length * 1024 * 1024)))
	{
		blob.create_or_replace();
		// upload data
		size_t target_length = length * 1024 * 1024;
		option.set_parallelism_factor(5);
		option.set_use_transactional_md5(true);
		if (length <= 100)
		{
			std::vector<uint8_t> data;
			data.resize(length * 1024 * 1024);
			concurrency::streams::container_buffer<std::vector<uint8_t>> upload_buffer(data);
			blob.upload_from_stream(upload_buffer.create_istream(), azure::storage::access_condition(), option, azure::storage::operation_context());
		}
		else
		{
			std::vector<uint8_t> data;
			data.resize(100 * 1024 * 1024);
			concurrency::streams::container_buffer<std::vector<uint8_t>> upload_buffer(data);
			for (int len = 0; len < length; len += 100)
			{
				blob.append_from_stream(upload_buffer.create_istream(), azure::storage::access_condition(), option, azure::storage::operation_context());
			}
		}
	}
	int total = 0;
	for (int i = 0; i < times; ++i)
	{
		// download data
		option.set_disable_content_md5_validation(true);
		option.set_parallelism_factor(parallelism);
		concurrency::streams::container_buffer<std::vector<uint8_t>> download_buffer;
		auto start = clock();
		blob.download_to_file(L"File", azure::storage::access_condition(), option, azure::storage::operation_context());
		auto end = clock();
		total += end - start;
	}

    return total / times;
}

int main()
{
    Performance instance(L"DefaultEndpointsProtocol=https;AccountName=jasonunittest;AccountKey=BD1ax46VII51dNjVzwuBiMMbwh7PIwPxu010yHtd+r34Pzmd1y8PsVXNKT1Hz0j6J8SulwPiHEIVuemo+eyN1A==");
	//ucout << instance.single_download_test(1000, 8) << std::endl;
	//ucout << instance.single_download_test_raw_memory(1000, 8) << std::endl;
	// ucout << instance.single_download_test_filestream(1000, 8) <<std::endl;
	ucout << instance.download_test() << std::endl;
	ucout << L"*******************************************" << std::endl;
	ucout << instance.download_test_raw_memory() << std::endl;
	ucout << L"*******************************************" << std::endl;
	ucout << instance.download_test_filestream() << std::endl;

    return 0;
}

