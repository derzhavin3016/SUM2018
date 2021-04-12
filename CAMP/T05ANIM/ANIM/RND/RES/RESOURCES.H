/* FILE NAME: resources.h
* PROGRAMMER: AD6
* LAST UPDATE: 14.07.2018
* PURPOSE
*/

#ifndef __RESOURCES_H_
#define __RESOURCES_H_

#include "../../../DEF.H"
#include <map>

namespace degl
{
  template<class T>
  class resource_manager
  {
  protected:
    std::map<std::string, T> Stock;
  public:
    INT ProgId;
  resource_manager & Add( std::string &Name, T &Res )
  {
    Stock[Name] = *Res;

    return *this;
  }

  ~resource_manager( VOID )
  {
    for (auto s : Stock)
      delete s;
  }

  type * Find( const std::string &Name )
  {
    if(Stock.find(Name) == Stock.end())
      return nullptr;
    return Stock[Name];
  }

  };
}



#endif /* __RESOURCES_H_ */



/* End of 'resources.h' file */
