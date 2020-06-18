#pragma once

#include "command.h"
#include "observer.h"
#include "reader.h"
#include "common.h"

#include <memory>
#include <fstream>
#include <string>

namespace Otus {

class Logger : public IObserver<CommandBlock>, public std::enable_shared_from_this<Logger>
{
public:
  static std::shared_ptr<Logger> Create(const std::string& a_strName, std::shared_ptr<Reader>& a_pReader);
  ~Logger();

  void Update(const CommandBlock& a_Commands) override;

  void SetReader(std::shared_ptr<Reader>& a_pReader);

private:
  Logger(const std::string& a_strName);

private:
  std::string m_strName;
  std::weak_ptr<Reader> m_pReader;
  Counters m_counters;
};

} // Otus::
