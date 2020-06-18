#pragma once

#include "command.h"
#include "observer.h"
#include "reader.h"
#include "common.h"

#include <memory>
#include <fstream>
#include <string>
#include <thread>
#include <atomic>
#include <mutex>

namespace Otus {

class Logger : public IObserver<CommandBlock>, public std::enable_shared_from_this<Logger>
{
public:
  static std::shared_ptr<Logger> Create(const std::string& a_strName, std::shared_ptr<Reader>& a_pReader);
  ~Logger();

  void Update(const CommandBlock& a_Commands) override;
  void SetReader(std::shared_ptr<Reader>& a_pReader);

  void Process(std::string a_strName);
  void JoinTread();

private:
  Logger(const std::string& a_strName);

private:
  std::weak_ptr<Reader> m_pReader;

  std::vector<std::thread> m_threads;
  std::atomic<bool> m_bExit;

  std::recursive_mutex m_lock;
  QueueCommandBllock_t m_queueCommand;
};

} // Otus::
