#include "executer.h"

namespace Otus {

std::shared_ptr<Excuter> Excuter::Create(const std::string& a_strName, std::shared_ptr<Reader>& a_pReader, std::ostream& a_osOut)
{
  auto ptr = std::shared_ptr<Excuter>{new Excuter{a_strName, a_osOut}};
  ptr->SetReader(a_pReader);
  return ptr;
}

void Excuter::Update(const CommandBlock& a_CommandBlock) 
{
  m_osOut << "bulk: ";
  m_osOut << a_CommandBlock;
  m_osOut << std::endl;

  ++m_counters.blockCounter;
  m_counters.commandCounter = a_CommandBlock.Size();
}

Excuter::Excuter(const std::string& a_strName, std::ostream& a_osOut)
  : m_strName{a_strName}
  , m_osOut(a_osOut)
{ }

Excuter::~Excuter()
{
  std::cout << m_strName << " " << m_counters << std::endl;
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
