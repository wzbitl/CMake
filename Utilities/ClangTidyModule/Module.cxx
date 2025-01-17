/* Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
   file Copyright.txt or https://cmake.org/licensing for details.  */
#include <clang-tidy/ClangTidyModule.h>
#include <clang-tidy/ClangTidyModuleRegistry.h>

namespace clang {
namespace tidy {
namespace cmake {
class CMakeClangTidyModule : public ClangTidyModule
{
public:
  void addCheckFactories(ClangTidyCheckFactories& CheckFactories) override
  {
    // TODO
  }
};

static ClangTidyModuleRegistry::Add<CMakeClangTidyModule> X(
  "cmake-clang-tidy", "Adds lint checks for the CMake code base.");
}
}
}
