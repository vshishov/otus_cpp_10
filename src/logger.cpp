#include "logger.h"

namespace Otus {

std::shared_ptr<Logger> Logger::Create(const std::string& a_strName, std::shared_ptr<Reader>& a_pReader)
{
  auto ptr = std::shared_ptr<Logger>{new Logger{a_strName}};
  ptr->SetReader(a_pReader);
  return ptr;
}

void Logger::Update(const CommandBlock& a_CommandBlock)
{
  std::string strLogName{"bulk" + a_CommandBlock.GetTimeStamp() + ".log"};
  std::ofstream log(strLogName, std::ios::out);

  log << "bulk: ";
  log << a_CommandBlock;
  log << std::endl;
  log.close();

  ++m_counters.blockCounter;
  m_counters.commandCounter = a_CommandBlock.Size();
}

Logger::Logger(const std::string& a_strName)
  : m_strName{a_strName}
{}

Logger::~Logger()
{
  std::cout << m_strName << " " << m_counters << std::endl;
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
