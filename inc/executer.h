#pragma once

#include "command.h"
#include "observer.h"
#include "reader.h"

#include <memory>

namespace Otus {

class Excuter : public IObserver<Commands_t>, public std::enable_shared_from_this<Excuter>
{
public:
  static std::shared_ptr<Excuter> Create(std::shared_ptr<Reader>& a_pReader, std::ostream& a_osOut = std::cout);

  void Update(const Commands_t& a_Commands) override;

private:
  Excuter(std::ostream& a_osOut);
  void SetReader(std::shared_ptr<Reader>& a_pReader);

private:
  std::ostream& m_osOut;
  std::weak_ptr<Reader> m_pReader;
};

} // Otus::
