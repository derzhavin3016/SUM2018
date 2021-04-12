/* Derzhavin Andrey, 11-6, 08.07.2018 */

typedef double DBL;

struct Compl
{
  DBL Re, Im;

  Compl( DBL x = 0, DBL y = 0 ) : Re(x), Im(y)
  {
  }

  Compl operator+( const Compl &C) const
  {
    return Compl(C.Re + Re, C.Im + Im);
  }

  Compl & operator+=( const Compl &C)
  {
    Re += C.Re;
    Im += C.Im;
    return *this;
  }

  Compl operator*( const Compl &C) const
  {
    return Compl(Re * C.Re - Im * C.Im, Re * C.Im + Im * C.Re);
  }

  Compl & operator*=( const Compl &C)
  {
    Compl mem(Re, Im), mem2 = C;

    Re = Re * C.Re - Im * C.Im;
    Im = mem.Re * mem2.Im + mem.Im * mem2.Re;

    return *this;
  }

  DBL operator!( void ) const
  {
    return sqrt(Re * Re + Im * Im);
  }

  Compl & operator=( const Compl &C )
  {
    Re = C.Re;
    Im = C.Im;
    return *this;
  }

  Compl & operator-( void )
  {
    Re = -Re;
    Im = -Im;
    return *this;
  }

  int operator()( const Compl &C )
  {
    int n = 0;
    Compl z = *this;

    while (!z <= 2 && n < 255)
      z = z * z * z * z * z + C, n++;
    return n;
  }

  int operator()( void )
  {                          
    return (*this)(*this);
  }
};