#pragma once

#include "command.h"
#include "observer.h"
#include "reader.h"

#include <memory>
#include <string>
#include <thread>
#include <atomic>
#include <mutex>

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
  
  void Procces(std::string a_strName);
  void JoinThred();
  

private:
  std::ostream& m_osOut;
  std::weak_ptr<Reader> m_pReader;

  std::thread m_thread;
  std::atomic<bool> m_bExit;

  std::recursive_mutex m_lock;
  QueueCommandBllock_t m_queueCommand;
};

} // Otus::
