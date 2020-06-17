#include "reader.h"

#include <string>

namespace Otus {

Reader::Reader(std::size_t a_szBlockSize, std::istream& a_isIn) 
  : m_isIn(a_isIn)
  , m_szBlockSize(a_szBlockSize)
{ }

void Reader::Exec()
{
  m_vCommands.reserve(m_szBlockSize);

  std::string strLine;
  std::size_t nBlockDepth{0};
  while ( std::getline(m_isIn, strLine) ) {
    if ( strLine == "{" ) {
      if (nBlockDepth == 0) {
        Flush();
      }
      nBlockDepth++;
    } 
    else if ( strLine == "}" ) {
      if (nBlockDepth == 0) {
        throw std::logic_error("unexpected symbol '}'");
      }
      nBlockDepth--;
    }
    else {
      m_vCommands.emplace_back(Command(strLine));
    }

    if (!nBlockDepth && m_vCommands.size() >= m_szBlockSize) {
      Flush();
    }
  }
}

void Reader::Flush() 
{
  if (m_vCommands.size() > 0) {
    Notify(m_vCommands);
    m_vCommands.clear();
  }
}

} // Otus::
