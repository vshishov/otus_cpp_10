#pragma once

#include "command.h"
#include "observer.h"
#include "reader.h"

#include <memory>
#include <fstream>

namespace Otus {

class Logger : public IObserver<Commands_t>, public std::enable_shared_from_this<Logger>
{
public:
  static std::shared_ptr<Logger> Create(std::shared_ptr<Reader>& a_pReader);

  void Update(const Commands_t& a_Commands) override;

  void SetReader(std::shared_ptr<Reader>& a_pReader);
private:
  Logger();

private:
  std::weak_ptr<Reader> m_pReader;
};

} // Otus::
