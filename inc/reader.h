#pragma once

#include "observer.h"
#include "command.h"
#include <common.h>

#include <iostream>
#include <string>

namespace Otus {

class Reader : public BaseObservable<CommandBlock>
{
public: 
  Reader(const std::string& a_strName, std::size_t a_szBlockSize, std::istream& a_isIn = std::cin);
  ~Reader();

  void Exec();

private:
  void Flush();

private:
  std::string m_strName;
  std::istream& m_isIn;
  std::size_t m_szBlockSize;
  CommandBlock m_CommandBlock;  
  Counters m_counters;
};

} // Otus::
