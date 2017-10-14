/**
  Header file for stock declares the classes for stocks
*/

#include <iostream>
#include <cstdio>
#include <string>
#include <cstdlib>

/**
  The Share class represents a single share of Stock
*/ 
class Share {
public:
  /**
    Constructs a Share with a price.
    @param p the price of one share
  */
  Share( int p ) : price{p} {}
private:
  /** The price of theh Share */
  int price;
};


/**
  A security that can be bought and sold. The stock has a name, a ticker, and a quantity of shares.
*/
class Stock {
public:
  /** 
    Constructs a Stock with a name, ticker, and number of outstanding shares. The constructor sets the name and ticker to the appropriate fields and calls the
    issueOutstanding function to grow the share vector.
    @param nm the name of the company
    @param tkr the ticker of the company
    @param qty the number of share to be issued by this stock
  */
  Stock( std::string nm, std::string tkr, int qty ) {
    name = nm;
    ticker = tkr;
    issueOutstanding( shares, qty );
  }

  Stock(){}
  
  /**
    Grows the vector by the quantity passed into the function.

    @param vec a reference to the share vector
    @param qty the number of shares to be issued
    @return a reference to the vector of shares
  */  
  vector<Share> &issueOutstanding( vector<Share> &vec, int qty );

  /**
    Returns a average price for a Stock over a given number of days.
    @param s the Stock
    @param n the number of days
    @return avg the average price
  */
  int avg( Stock s, int n ); 
  
  /** 
    Overloads the right shift operator to output the Stock name, ticker, and the number of shares outstanding, to the console.
  
    @param out reference to ostream
    @param st reference to Stock to be output
    @return out reference to ostream
  */
  friend std::ostream &operator<<( std::ostream &out, Stock &st );

private:
  /** The name of the stock */
  string name;
  /** The ticker for the stock */
  string ticker;
  /** The number of shares currently */
  vector<Share> shares;
};