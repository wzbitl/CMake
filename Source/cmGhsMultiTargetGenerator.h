/* Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
   file Copyright.txt or https://cmake.org/licensing for details.  */
#ifndef cmGhsMultiTargetGenerator_h
#define cmGhsMultiTargetGenerator_h

#include "cmGhsMultiGpj.h"

#include "cmTarget.h"

class cmCustomCommand;
class cmGeneratedFileStream;
class cmGeneratorTarget;
class cmGlobalGhsMultiGenerator;
class cmLocalGhsMultiGenerator;
class cmMakefile;
class cmSourceFile;

class cmGhsMultiTargetGenerator
{
public:
  cmGhsMultiTargetGenerator(cmGeneratorTarget* target);

  virtual ~cmGhsMultiTargetGenerator();

  virtual void Generate();

  bool IncludeThisTarget();
  std::vector<cmSourceFile*> GetSources() const;

private:
  cmGlobalGhsMultiGenerator* GetGlobalGenerator() const;

  void GenerateTarget();

  bool IsTargetGroup() const { return this->TargetGroup; }

  void WriteTargetSpecifics(std::ostream& fout, const std::string& config,
                            bool notKernel);
  void WriteCompilerFlags(std::ostream& fout, const std::string& config,
                          const std::string& language);
  void WriteCompilerDefinitions(std::ostream& fout, const std::string& config,
                                const std::string& language);

  void SetCompilerFlags(std::string const& config, const std::string& language,
                        bool const notKernel);
  std::string GetDefines(const std::string& langugae,
                         std::string const& config);

  void WriteIncludes(std::ostream& fout, const std::string& config,
                     const std::string& language);
  void WriteTargetLinkLine(std::ostream& fout, std::string const& config);
  void WriteCustomCommands(std::ostream& fout);
  void WriteCustomCommandsHelper(
    std::ostream& fout, std::vector<cmCustomCommand> const& commandsSet,
    cmTarget::CustomCommandType commandType);
  void WriteSources(std::ostream& fout_proj);
  static std::map<const cmSourceFile*, std::string> GetObjectNames(
    std::vector<cmSourceFile*>* objectSources,
    cmLocalGhsMultiGenerator* localGhsMultiGenerator,
    cmGeneratorTarget* generatorTarget);
  static void WriteObjectLangOverride(std::ostream& fout,
                                      const cmSourceFile* sourceFile);

  static std::string ComputeLongestObjectDirectory(
    cmLocalGhsMultiGenerator const* localGhsMultiGenerator,
    cmGeneratorTarget* generatorTarget, cmSourceFile* const sourceFile);

  bool IsNotKernel(std::string const& config, const std::string& language);
  static bool DetermineIfTargetGroup(const cmGeneratorTarget* target);
  bool DetermineIfDynamicDownload(std::string const& config,
                                  const std::string& language);

  cmGeneratorTarget* GeneratorTarget;
  cmLocalGhsMultiGenerator* LocalGenerator;
  cmMakefile* Makefile;
  bool TargetGroup;
  bool DynamicDownload;
  static std::string const DDOption;
  std::map<std::string, std::string> FlagsByLanguage;
  std::map<std::string, std::string> DefinesByLanguage;

  std::string TargetNameReal;
  GhsMultiGpj::Types TagType;
  std::string const Name;
  std::string ConfigName; /* CMAKE_BUILD_TYPE */
};

#endif // ! cmGhsMultiTargetGenerator_h
