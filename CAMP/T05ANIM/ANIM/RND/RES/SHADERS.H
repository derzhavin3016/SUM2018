/* FILE NAME: shaders.h
* PROGRAMMER: AD6
* LAST UPDATE: 14.07.2018
* PURPOSE
*/

#ifndef __SHADERS_H_
#define __SHADERS_H_

#include "../../../DEF.H"



using namespace std;

namespace degl
{
  class shader
  {
  private:
    
    CHAR * LoadTextFromFile( const string FileName );

    VOID ShdLog( const string & Prefix, const string & Type, const string &Text );

  public:
    static map<string, INT> shaders;

    INT ShdLoad( string ShaderFileNamePrefix );
    
    /* Unload shader program from memory files function.
     * ARGUMENTS:
     *   - shader program Id:
     *       INT ProgId;
     * RETURNS: None.
     */
    VOID ShdDelete( INT ProgId );



    /* Shader class destructor function
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    ~shader( VOID );

      /* Shader add function
      * ARGUMENTS:
      *   - shader file name:
      *          (string) &ShaderFileNamePrefix;
      * RETURNS: None.
      */
    VOID ShdAdd( string ShaderFileNamePrefix );

      /* Shaders update function
      * ARGUMENTS: None.
      * RETURNS: None.
      */
    VOID ShdUpdate( VOID );

      /* Shader_manager class constructor function
      * ARGUMENTS: None.
      * RETURNS: None.
      */
    VOID ShdInit( VOID );


  };
}



#endif /* __SHADERS_H_ */



/* End of 'shaders.h' file */
