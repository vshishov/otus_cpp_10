#include "executer.h"

namespace Otus {

std::shared_ptr<Excuter> Excuter::Create(std::shared_ptr<Reader>& a_pReader, std::ostream& a_osOut)
{
  auto ptr = std::shared_ptr<Excuter>{new Excuter{a_osOut}};
  ptr->SetReader(a_pReader);
  return ptr;
}

void Excuter::Update(const Commands_t& a_Commands) 
{
  m_osOut << "bulk: ";
  for (auto command_it = a_Commands.begin(); command_it != a_Commands.cend(); ++command_it) {
    if (command_it != a_Commands.begin()) {
      m_osOut << ", ";
    }
    m_osOut << command_it->GetName();
    
  }
  m_osOut << std::endl;
}

Excuter::Excuter(std::ostream& a_osOut)
  : m_osOut(a_osOut)
{ }

void Excuter::SetReader(std::shared_ptr<Reader>& a_pReader)
{
  m_pReader = a_pReader;
  auto ptrReader = m_pReader.lock();
  if (ptrReader) {
    ptrReader->Subscribe(shared_from_this());
  }
}


} // Otus::
