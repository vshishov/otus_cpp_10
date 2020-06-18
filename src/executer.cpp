#include "executer.h"

namespace Otus {

Excuter::Excuter(const std::string& a_strName, std::ostream& a_osOut)
  : m_strName{a_strName}
  , m_osOut(a_osOut)
  , m_thread(&Excuter::Procces, this)
{ }

Excuter::~Excuter()
{
  JoinThred();
  std::cout << m_strName << " " << m_counters << std::endl;
}

std::shared_ptr<Excuter> Excuter::Create(const std::string& a_strName, std::shared_ptr<Reader>& a_pReader, std::ostream& a_osOut)
{
  auto ptr = std::shared_ptr<Excuter>{new Excuter{a_strName, a_osOut}};
  ptr->SetReader(a_pReader);
  return ptr;
}

void Excuter::Update(const CommandBlock& a_CommandBlock) 
{
  m_queueCommand.push(a_CommandBlock);  
}

void Excuter::Procces()
{
  m_bExit = false;
  while (!m_bExit) {
    if (m_queueCommand.size()) {
      CommandBlock commandBlock = m_queueCommand.front();
      m_queueCommand.pop();
      
      if (commandBlock.Size()){
        m_osOut << "bulk: ";
        m_osOut << commandBlock;
        m_osOut << std::endl;

        ++m_counters.blockCounter;
        m_counters.commandCounter += commandBlock.Size();
      }
    }
  }
}

void Excuter::JoinThred()
{
  m_bExit = true;
  if (m_thread.joinable()) {
    m_thread.join();
  }
}

void Excuter::SetReader(std::shared_ptr<Reader>& a_pReader)
{
  m_pReader = a_pReader;
  auto ptrReader = m_pReader.lock();
  if (ptrReader) {
    ptrReader->Subscribe(shared_from_this());
  }
}

} // Otus::
