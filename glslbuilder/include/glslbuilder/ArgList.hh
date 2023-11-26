#pragma once

#include "ArgListCommons.hh"
#include <vector>
#include <utility>
#include <list>
#include <regex>


namespace GLSLBuilder
{
	

	/**
	* The ArgTree is a static class to wrap all necessary arguments to be sent to D3DCompiler (until HLSL 5.1) or DXC (since HLSL 6.0)
	* When an argument is pushed, it is treated, and, if passes all filters, is stored on a queue to be processed later. All arguments
	* and parameters work with a whitelist system, block unknown args and assignments to be pushed.
	*
	* There are two types of argument: info and control. Info args tells how the program works, otherside, control args pass necessary values to further processing.
	* The complete list of avaliable arguments can be found in [Properties](@ref docs/properties.md).
	*
	* There is 6 types of filters, that are detected with a base ArgException, thrown when an error occurs:
	*   * Multiple evaluation: if an arg receives more than one value, is thrown a BadAssignmentException.
	*	* Invalid argument: if the argument doesn't match the valid argument list, is thrown an InvalidArgException.
	*	* Mismatch control and info args: if the argument is mismatched, it generates a MismatchArgException.
	*   * Bad Evaluation: if is sent an invalid argument, a BadEvaluationException will be generated.
	*   * Multiple Push: if an argument is pushed more than one time, a MultipleArgPushException will be generated.
	*   * Invalid Usage: there can be only one info arg, and if an info arg is called, there can't be control args, if this situation occurs, an InvalidUsageException is thrown.
	*/
	class GLSLB_API ArgList
	{
	public:
		/**
		* Push arg allows the user push arguments to call the compiler,
		*
		*
		*/
		static void PushRawArg(std::string_view arg);

		/**
		 * Resolve args will reallocate and validate all pushed args, in category and value.
		 *
		 */

		 /* now is time to test the [Class linkage](@ref ProjectReader) */
		static void ResolveArgs();

		/**
		* Clear all insert args and allows new arg list
		*/
		static void ClearArgs();

		/**
		*
		* Get the info arg to be processed
		*
		*/
		static ArgCategory GetInfoArg();

		/**
		*
		* Get the control args to be processed, structured in a FIFO format, in a list.
		* Stored in a pair mode, with the casted arg category and its value
		*
		*/
		static std::list<std::pair<ArgCategory, std::string>> GetControlArgs();
	private:
		static std::vector<std::string> s_StrArgs;

		static void ClassifyAndEvaluateArgs(std::string_view arg);
		static void PushInfoArgTreated(std::string_view arg);
		static void PushControlArgTreated(std::sregex_token_iterator* arg);
		static bool ArgumentPushed(ArgCategory category);

		static const std::unordered_map<std::string_view, ArgCategory> s_ArgMapper;
		static std::unordered_map<ArgCategory, std::string_view> s_ArgValues;

		static const std::list<ArgCategory> s_InfoArgs;
		static const std::list<ArgCategory> s_ControlArgs;

		static ArgCategory s_InfoArg;
		static bool s_InfoAssigned;
		static std::list<std::pair<ArgCategory, std::string>> s_ControlArgTree;
	};
}