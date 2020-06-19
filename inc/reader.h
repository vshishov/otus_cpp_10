#pragma once

#include "observer.h"
#include "command.h"
#include <counter.h>

#include <iostream>
#include <string>

#include <mutex>

namespace Otus {

class Reader : public BaseObservable<CommandBlock>
{
public: 
  Reader(const std::string& a_strName, std::size_t a_szBlockSize, std::istream& a_isIn = std::cin, std::ostream& a_osMetricsOut = std::cout);
  ~Reader() = default;

  void Exec();

private:
  void Flush();

private:
  std::string m_strName;
  std::istream& m_isIn;
  std::ostream& m_osMetricsOut;
  std::size_t m_szBlockSize;
  CommandBlock m_CommandBlock;  
  Counters m_counters;

  std::mutex m_printLock;
};

} // Otus::
