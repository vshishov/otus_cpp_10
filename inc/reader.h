#pragma once

#include "observer.h"
#include "command.h"
#include <counter.h>

#include <iostream>
#include <string>

namespace Otus {

class Reader : public BaseObservable<CommandBlock>
{
public:
  static std::shared_ptr<Reader> Create(const std::string& a_strName, std::size_t a_szBlockSize, std::istream& a_isIn = std::cin, std::ostream& a_osMetricsOut = std::cout);
  ~Reader();

  void Exec();

private:
  Reader(const std::string& a_strName, std::size_t a_szBlockSize, std::istream& a_isIn = std::cin, std::ostream& a_osMetricsOut = std::cout);
  
  void Flush();

private:
  std::istream& m_isIn;
  std::ostream& m_osMetricsOut;
  std::size_t m_szBlockSize;  
  Counters m_counters;
  CommandBlock m_CommandBlock;  
};

} // Otus::
