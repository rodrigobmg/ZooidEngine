#ifndef __ZE_TOOLS_DIR__
#define __ZE_TOOLS_DIR__

#include <string>

namespace ZETools
{
	namespace Dir
	{
		bool CreateDirectory(std::string pathName);

		std::string CombinePath(std::string path1, std::string path2);

		inline char separator()
		{
#if defined(_WIN32) || defined(_WIN64)
			return '\\';
#else
			return '/'
#endif
		}
	}
}

#endif
