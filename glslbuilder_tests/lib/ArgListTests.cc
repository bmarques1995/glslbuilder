#include <gtest/gtest.h>
#include <iostream>
#include <GLSLBuilder/GLSLBuilder.hh>

namespace GLSLBuilder
{
	TEST(GLSLBuilder, InvalidArg)
	{
		ArgList::PushRawArg("--chaos");
		ASSERT_THROW(ArgList::ResolveArgs(), GLSLBuilder::InvalidArgException);
		ArgList::ClearArgs();
	}

	TEST(GLSLBuilder, MultiAssignment)
	{
		ArgList::PushRawArg("--Build:./:./uchigatana");
		ASSERT_THROW(ArgList::ResolveArgs(), GLSLBuilder::BadAssignmentException);
		ArgList::ClearArgs();
	}

	TEST(GLSLBuilder, MismatchControlAssignment)
	{
		ArgList::PushRawArg("--build");
		ASSERT_THROW(ArgList::ResolveArgs(), GLSLBuilder::MismatchArgException);
		ArgList::ClearArgs();
	}

	TEST(GLSLBuilder, MismatchInfoAssignment)
	{
		ArgList::PushRawArg("--version:chaos");
		ASSERT_THROW(ArgList::ResolveArgs(), GLSLBuilder::MismatchArgException);
		ArgList::ClearArgs();
	}

	TEST(GLSLBuilder, MultipeInfoPush)
	{
		ArgList::PushRawArg("--version");
		ArgList::PushRawArg("-h");
		ASSERT_THROW(ArgList::ResolveArgs(), GLSLBuilder::InvalidUsageException);
		ArgList::ClearArgs();
	}

	TEST(GLSLBuilder, MultipleControlPush)
	{
		ArgList::PushRawArg("--build:./");
		ArgList::PushRawArg("-b:./chaos");
		ASSERT_THROW(ArgList::ResolveArgs(), GLSLBuilder::MultipleArgPushException);
		ArgList::ClearArgs();
	}

	TEST(GLSLBuilder, InvalidControlUsage)
	{
		ArgList::PushRawArg("-b:./CSO");
		ArgList::PushRawArg("--version");
		ASSERT_THROW(ArgList::ResolveArgs(), GLSLBuilder::InvalidUsageException);
		ArgList::ClearArgs();
	}

	TEST(GLSLBuilder, InvalidInfoUsage)
	{
		ArgList::PushRawArg("--version");
		ArgList::PushRawArg("-b:./CSO");
		ASSERT_THROW(ArgList::ResolveArgs(), GLSLBuilder::InvalidUsageException);
		ArgList::ClearArgs();
	}

	TEST(GLSLBuilder, ValidInfoUsage)
	{
		ArgList::PushRawArg("--VERSIOn");
		ASSERT_NO_THROW(ArgList::ResolveArgs());
		auto arg = ArgList::GetInfoArg();
		ArgList::ClearArgs();
		ASSERT_EQ(arg, GLSLBuilder::ArgCategory::VERSION);
	}

	TEST(GLSLBuilder, ValidControlUsage)
	{
		ArgList::PushRawArg("-b:./");
		std::list<std::pair<ArgCategory, std::string>> expectedValues =
		{
			{ArgCategory::BUILD, "./"}
		};
		ASSERT_NO_THROW(ArgList::ResolveArgs());
		auto arg = ArgList::GetControlArgs();
		ArgList::ClearArgs();

		ASSERT_EQ(expectedValues.size(), arg.size());
		auto expected_it = expectedValues.begin();
		for (auto it = arg.begin(); it != arg.end(); expected_it++, it++)
		{
			ASSERT_EQ(expected_it->first, it->first);
			ASSERT_STREQ(expected_it->second.c_str(), it->second.c_str());
		}
	}
}