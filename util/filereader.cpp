/**
  The implementation file for filereader.h
*/
#include "filereader.h"
std::string delims = ",";
std::string dateDelim = "-";

void readLine( std::string &str, std::string &delims )
{
  std::vector<std::string> output;
  std::vector<std::string> date;
  double open, high, low, close, adjClose;
  long vol;
  for_each_token(str.cbegin(), str.cend(), delims.cbegin(), delims.cend(), [&output] (auto first, auto second) {
    if( first != second ) {
      output.emplace_back(first, second);
    }
  });
  for_each_token(output[0].cbegin(), output[0].cend(), dateDelim.cbegin(), dateDelim.cend(), [&date] (auto first, auto second) {
    if( first != second ) {
      date.emplace_back(first, second);
    }
  });
  open = stod(output[1]);
  high = stod(output[2]);
  low = stod(output[3]);
  close = stod(output[4]);
  adjClose = stod(output[5]);
  vol = stol(output[6]);
  std::cout << open << high << low << close << adjClose << vol << std::endl;
  
  /*
  double open, high, low, close, adjClose;
  long vol;
  Date date;
  
  std::istringstream iss(line);
  iss.exceptions(std::ios_base::badbit | std::ios_base::failbit);
  std::locale spaces(std::locale::classic(), new new_delimiter);
  iss.imbue(spaces);
  */

  try {
 
  } catch(...) {
    /*
      if(iss.fail()) {
        std::cout << "Something unexpected happened while reading a line." << std::endl;
      } else if(iss.bad()) {
        std::cout << "Something serious happened while reading a line." << std::endl;
      }
    */
  }

}

void FileReader::askForName( std::string &s )
{
  std::cout << "Enter a name for this stock: ";
  std::cin >> s;
  std::cout << std::endl;
}

void FileReader::askForSymbol( std::string &s )
{
  std::cout << "Enter a ticker for this stock: ";
  std::cin >> s;
  std::cout << std::endl;
}

void FileReader::toTransactionFromString( Stock &s1, std::vector<std::string> &output, Date &date )
{
  Transaction topen(date, std::stod(output[1]));
  Transaction thigh(date, std::stod(output[2]));
  Transaction tlow(date, std::stod(output[3]));
  Transaction tclose(date, std::stod(output[4]));
  Transaction tadjclose(date, std::stod(output[5])); 

  s1.addOpen(topen);
  s1.addHigh(thigh);
  s1.addLow(tlow);
  s1.addClose(tclose);
  s1.addAdjClose(tadjclose);
  s1.addVolume( std::stoi(output[6]) );

}

Date FileReader::toDateFromString( std::vector<std::string> &output )
{
  Date date;
  std::istringstream dat{output[0]};
  dat.exceptions(std::ios_base::badbit | std::ios_base::failbit);
  try {
    //dat.str(output[0]);
    dat >> date;
    dat.clear();
  } catch(...) {
    if(dat.bad()) {
      std::cout << "A serious error occurred reading the last date." << std::endl;
    } else if (dat.fail()) {
      std::cout << "Something unexpected happened when reading the last date." << std::endl;
      dat.clear(std::ios_base::goodbit);
    }
  }
  return date;
  
}

void FileReader::loadPrices( StockList &list )
{

  std::string name; 
  askForName(name);

  std::string symbol; 
  askForSymbol(symbol);
  
  Stock s( name, symbol, 0.0);

  std::string line; // string to store a line in the file
  std::vector<std::string> output; // vector to hold tokens from the line
  
  /** Date and istringstream to read from. badbit and failbit are set in the exception mask */
  Date date;

  /** set the source to the filename string held in buffer and set the failbit/badbit flags in source's exception mask */
  source.open(FileReader::buffer.str());
  source.exceptions(std::ios_base::badbit | std::ios_base::failbit);
  source.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  /** read and tokenize one line at a time from the file. tokenize the date string separately. */
  while(!source.eof()) {
    try {

      source >> line;
      for_each_token(line.cbegin(), line.cend(), delims.cbegin(), delims.cend(), [&output] (auto first, auto second) {
        if( first != second ) {
          output.emplace_back(first, second);
        }
      });
      
      date = toDateFromString( output );
      toTransactionFromString(s,output,date);
      
      line.clear();
      output.clear();
      
    } catch(...) {

      if(source.fail() ) {
        std::cout << "Something unexpected happened while reading a file." << std::endl;
        continue;
      } else if (source.bad()) {
        std::cout << "Something serious happened while reading a file." << std::endl;
        exit(1);
      }

    }

  }
  Stock *ptr = &s;
  list.addToFront(ptr);
  source.close();
  buffer.clear();

}


bool FileReader::isWhitespace( char c ) 
{
  for(char w : white)
    if(c == w) return true;
  return false;

}

FileReader::operator bool()
{
  return !(source.fail() || source.bad()) && source.good(); 
}


std::string &operator>>(std::string &input, FileReader &fr)
{
  
  return input;
}

std::string &operator<<(std::string &output, const FileReader &fr)
{
  
  return output;
}

bool FileReader::defineWhitespace()
{
  std::vector<std::string> vs;
  std::string line;
  while( getline(source,line) && !source.bad() ) {
    for (char &ch : line) { 
      if ( ch == ',')
        ch = ' ';
    }
    std::stringstream in{line};
    for(std::string word; in >> word;)
      vs.push_back(word);
    //for(std::vector<std::string>::iterator it = vs.begin(); it != vs.end(); ++it)
      //std::cout << ' ' << *it;
    //std::cout << '\n' << std::endl;
  }
  return true;
}

