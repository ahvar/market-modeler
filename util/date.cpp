#include "date.h"

std::ifstream &operator>>(std::ifstream &is, Date &dat)
{
	
  int tmp;
  is >> tmp; dat.tm_date.tm_year = tmp-1900;
  is.ignore();
  is >> tmp; dat.tm_date.tm_mon = tmp - 1;
  is.ignore();
  is >> dat.tm_date.tm_mday;
  
  return is;
}

std::ofstream &operator<<(std::ofstream &os, const Date &dat)
{
  
  os << dat.tm_date.tm_mon << "-" << dat.tm_date.tm_mday << "-" << dat.tm_date.tm_year;
  	
  return os;
}