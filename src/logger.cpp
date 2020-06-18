#include "logger.h"

namespace Otus {

Logger::Logger(const std::string& a_strName)
{
  for (size_t i = 0; i < 2; ++i) {
    std::string strThreadName = a_strName + std::to_string(i + 1);
    m_threads.emplace_back( std::thread(&Logger::Process, this, strThreadName) );
  }
}

Logger::~Logger()
{
  JoinTread();
}

std::shared_ptr<Logger> Logger::Create(const std::string& a_strName, std::shared_ptr<Reader>& a_pReader)
{
  auto ptr = std::shared_ptr<Logger>{new Logger{a_strName}};
  ptr->SetReader(a_pReader);
  return ptr;
}

void Logger::Update(const CommandBlock& a_CommandBlock)
{
  m_queueCommand.push(a_CommandBlock); 
}

void Logger::Process(std::string a_strName)
{
  CommandBlock commandBlock;
  Counters counters;
  while (!m_bExit) {
    {
      std::lock_guard<std::recursive_mutex> locker(m_lock);
      if (!m_queueCommand.empty()) {
        commandBlock = m_queueCommand.front();
        m_queueCommand.pop();
      }
    }
    if (commandBlock.Size()) {
      std::string strLogName{"bulk_" + a_strName + "_" + commandBlock.GetTimeStamp() + ".log"};
      std::ofstream log(strLogName, std::ios::out);


      if (commandBlock.Size()){
        log << "bulk: " << commandBlock << std::endl;
        ++counters.blockCounter;
        counters.commandCounter += commandBlock.Size();
        commandBlock.Clear();
        log.close();
      }
    }
    std::this_thread::sleep_for(std::chrono::microseconds(100));
  }
  std::cout << a_strName << ": " << counters << std::endl;
}

void Logger::JoinTread()
{
  m_bExit = true;
  for ( auto& thread : m_threads ) {
    if (thread.joinable()) {
      thread.join();
    }
  }
}

void Logger::SetReader(std::shared_ptr<Reader>& a_pReader)
{
  m_pReader = a_pReader;
  auto ptrReader = m_pReader.lock();
  if (ptrReader) {
    ptrReader->Subscribe(shared_from_this());
  }
}

} // Otus::
