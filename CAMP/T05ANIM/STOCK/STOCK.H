/* FILE NAME: stock.h
* PROGRAMMER: AD6
* LAST UPDATE: 14.07.2018
* PURPOSE
*/

#ifndef __STOCK_H_
#define __STOCK_H_

//#include "../ANIM/TIMER/TIMER.H"
#include "../DEF.H"
#include <cassert>

  namespace degl
  {
    template <class T>
    class stock
    {
    private:
      int RealSize, MaxSize;
      T *Array;
    public:
      stock( VOID ) : Array(NULL), RealSize(0), MaxSize(0)      {      }

      ~stock( VOID )      {        if (Array != NULL)          delete Array;      }


      stock( const stock<T> &CopyData ) : Array(new T [CopyData.MaxSize]), RealSize(CopyData.RealSize), MaxSize(CopyData.MaxSize)      {        for (int i = 0; i < RealSize; i++)          Array[i] = CopyData.Array[i];      }


      stock<T> & operator=( stock<T> & CopyData )      {        if (Array != NULL)          delete[] Array;        Array = new T [CopyData.MaxSize];        RealSize = CopyData.RealSize;        MaxSize = CopyData.MaxSize;        for (int i = 0; i < RealSize; i++)          Array[i] = CopyData.Array[i];        return *this;      }


      stock<T> & Add( const T &NewData )
      {
        if (RealSize >= MaxSize)
        {
          if (MaxSize == 0)
            MaxSize = 1;
          else
            MaxSize *= 2;
          T new_bulk = new T [MaxSize];

          if (Array != NULL)
          {
            for (int i = 0; i < RealSize; i++)              new_bulk[i] = Array[i];
            delete [] Array;
          }
          Array = new_bulk;
        }

        Array[RealSize++] = NewData;
        return *this;
      }


      INT Size( VOID )
      {
        return RealSize;
      }


      VOID Clear( VOID )
      {
        RealSize = 0;
      }


      stock<T> & operator<<( const T &NewData )
      {
        return Add(NewData);
      }



      T & operator[]( const int Index )
      {
        assert(Index >= 0 && Index < RealSize);
        return Array[Index];
      }


      T operator[]( const int Index ) const
      {
        assert(Index >= 0 && Index < RealSize);
        return Array[Index];
      }      template <class T2>        VOID Walk( const T2 &Walker )        {          for (int i = 0; i < RealSize; i++)            Walker(Array[i]);         }
    };
}
#endif


/* End of 'stock.h' file */