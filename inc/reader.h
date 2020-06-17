#pragma once

#include "observer.h"
#include "command.h"

#include <iostream>

namespace Otus {

class Reader : public BaseObservable<Commands_t>
{
public: 
  Reader(std::size_t a_szBlockSize, std::istream& a_isIn = std::cin);

  void Exec();

private:
  void Flush();

private:
  std::istream& m_isIn;
  std::size_t m_szBlockSize;
  Commands_t m_vCommands;  
};

} // Otus::
