#include "reader.h"

#include <string>

namespace Otus {

Reader::Reader(const std::string& a_strName, std::size_t a_szBlockSize, std::istream& a_isIn) 
  : m_strName{a_strName}
  , m_isIn(a_isIn)
  , m_szBlockSize(a_szBlockSize)
  , m_CommandBlock(a_szBlockSize)
{ }

void Reader::Exec()
{
  std::string strLine;
  std::size_t nBlockDepth{0};

  while ( std::getline(m_isIn, strLine) ) {
    ++m_counters.lineCounter;
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
      m_CommandBlock << strLine;
    }

    if (!nBlockDepth && m_CommandBlock.Size() >= m_szBlockSize) {
      Flush();
    }
  }
  std::cout << m_strName << ": " << m_counters << std::endl;
}

void Reader::Flush() 
{
  if (m_CommandBlock.Size() > 0) {
    Notify(m_CommandBlock);    
    m_counters.commandCounter += m_CommandBlock.Size();
    ++m_counters.blockCounter;
    m_CommandBlock.Clear();
  }
}

} // Otus::
