#pragma once

#include "command.h"
#include "observer.h"
#include "reader.h"
#include "common.h"

#include <memory>
#include <string>
#include <thread>
#include <atomic>

namespace Otus {

class Excuter : public IObserver<CommandBlock>, public std::enable_shared_from_this<Excuter>
{
public:
  static std::shared_ptr<Excuter> Create(const std::string& a_strName, std::shared_ptr<Reader>& a_pReader, std::ostream& a_osOut = std::cout);
  ~Excuter();

  void Update(const CommandBlock& a_CommandBlock) override;

private:
  Excuter(const std::string& a_strName, std::ostream& a_osOut);
  void SetReader(std::shared_ptr<Reader>& a_pReader);
  
  void Procces();
  void JoinThred();
  

private:
  std::string m_strName;
  std::ostream& m_osOut;
  std::weak_ptr<Reader> m_pReader;
  Counters m_counters;

  QueueCommandBllock_t m_queueCommand;
  std::thread m_thread;
  std::atomic<bool> m_bExit;
};

} // Otus::
