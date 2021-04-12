/* Derzhavin Andrey, 11-6, 10.07.2018 */

#include <iostream>
#include <conio.h>

namespace ad6
{
  struct list
  {
    struct list_entry
    {
      int Data;
      list_entry *Next;
    } *Start;

    list( void ) : Start(NULL)
    {
    }
    ~list( void )
    {
      //Clear();
    }

    list & AddFront( int l )
    {
      list_entry *Prev = new list_entry;

      Prev->Next = Start;
      Prev->Data = l;
      Start = Prev;
      return *this;
    }

    list & AddBack( int l )
    {
      list_entry **Prev = new list_entry*;
      list_entry *Last = new list_entry;
      Prev = &Start;

      while((*Prev)->Next != NULL)
        Prev = &(*Prev)->Next;

      Last->Data = l;
      Last->Next = NULL;
      (*Prev)->Next = Last;
      return *this;
    }

    void Display( void )
    {
      if (Start == NULL)
        std::cout << "Empty list" << std::endl;
      else
      {
        while (Start != NULL)
        {

          std::cout << Start->Data;
          printf((Start = Start->Next) == NULL ? "\n" : ",");
        }
      }
    }



    void PopFront( void )
    {
      list_entry *News = new list_entry;
      if (Start == NULL)
      {
        printf("Error delete front\n");
        return;
      }
      News = Start->Next;
      Start = News;
    }

    void PopBack( void )
    {
      list_entry **Prev = new list_entry*;
      Prev = &Start;
      if (*Prev == NULL)
        return;
      while ((*Prev)->Next != NULL)
        Prev = &(*Prev)->Next;

      delete(*Prev);

      *Prev = NULL;
    }

    void IsEmpty( void )
    {
      if (Start == NULL)
        std::cout << "Empty list" << std::endl;
      else
      {
        std::cout << "Not empty list" << std::endl;
      }
    }

    void Clear( void )
    {
      
    }
   };
}

int main( void )
{
  ad6::list L;
  int N, i;
   
  printf("********* Menu *********\nInput number from 0 to 5\n");
  printf(" 0 - Add to front       \n 1 - Add to back        \n");
  printf(" 2 - Show list          \n 3 - Delete first       \n");
  printf(" 4 - Delete last        \n 5 - Exit               \n");
  Start:
  std::cin >> N;
  switch (N)
  {
  case 0:
    printf("Input number to add to front:\n");
    std::cin >> i;
    L.AddFront(i);
    break;
  case 1:
    printf("Input number to add to back:\n");
    std::cin >> i;
    L.AddBack(i);
    break;
  case 2:
    L.Display();
    break;
  case 3:
    L.PopFront();
    break;
  case 4:
    L.PopBack();
    break;
  case 5:
    L.IsEmpty();
    break;
  }
  goto Start;
  //int x = L.PopFront();

  _getch();
  return 30;
}   