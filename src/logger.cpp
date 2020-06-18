#include "logger.h"

namespace Otus {

std::shared_ptr<Logger> Logger::Create(const std::string& a_strName, std::shared_ptr<Reader>& a_pReader)
{
  auto ptr = std::shared_ptr<Logger>{new Logger{a_strName}};
  ptr->SetReader(a_pReader);
  return ptr;
}

void Logger::Update(const Commands_t& a_Commands)
{
  std::string strLogName{"bulk" + a_Commands.begin()->GetTimeStamp() + ".log"};
  std::ofstream log(strLogName, std::ios::out);

  log << "bulk: ";
  for (auto it = a_Commands.begin(); it != a_Commands.end(); ++it) {
    if (it != a_Commands.begin()) {
      log << ", ";
    }
    log << it->GetName();
    
  }
  log << std::endl;
  log.close();
}

Logger::Logger(const std::string& a_strName)
  : m_strName{a_strName}
{}

void Logger::SetReader(std::shared_ptr<Reader>& a_pReader)
{
  m_pReader = a_pReader;
  auto ptrReader = m_pReader.lock();
  if (ptrReader) {
    ptrReader->Subscribe(shared_from_this());
  }
}

} // Otus::
