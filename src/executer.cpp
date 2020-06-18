#include "executer.h"

namespace Otus {

Excuter::Excuter(const std::string& a_strName, std::ostream& a_osOut)
  : m_osOut(a_osOut)
  , m_thread(&Excuter::Procces, this, a_strName)
{ }

Excuter::~Excuter()
{
  JoinThred();
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

void Excuter::Procces(std::string a_strName)
{
  m_bExit = false;
  Counters counters;
  CommandBlock commandBlock;
  while (!m_bExit) {
    {
      std::lock_guard<std::recursive_mutex> locker(m_lock);
      if (!m_queueCommand.empty()) {
        commandBlock = m_queueCommand.front();
        m_queueCommand.pop();
      }
    }
      
    if (commandBlock.Size()){
      m_osOut << "bulk: ";
      m_osOut << commandBlock;
      m_osOut << std::endl;

      ++counters.blockCounter;
        counters.commandCounter += commandBlock.Size();
      commandBlock.Clear();
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  std::cout << a_strName << ": " << counters << std::endl;
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
