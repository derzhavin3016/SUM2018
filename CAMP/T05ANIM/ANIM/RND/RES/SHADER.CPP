#include "SHADERS.H"

map<string, INT> degl::shader::shaders;


CHAR * degl::shader::LoadTextFromFile( const string FileName )
{

  ifstream f(FileName);
  string S, ln;
  if(!f)
    return NULL;
  while(!f.eof())
  {
    getline(f, ln);
    S += ln;
    S += '\n';
  }
  f.close();

  CHAR *m;
  m = new CHAR[S.size() + 1];
  for (int i = 0; i < S.size(); i++)
  {
    m[i] = S[i];
    m[i + 1] = 0;
  }
  return m;
}

VOID degl::shader::ShdLog( const string & Prefix, const string & Type, const string &Text )
{
  ofstream("BIN/SHADERS/LOG/AD6{30}SHD.LOG", ios_base::app) << Prefix << "/" << Type << ".GLSL:\n" << Text << "\n";
}

INT degl::shader::ShdLoad( string ShaderFileNamePrefix )
{
  struct 
  {
    string Name;       // Shader file suffix name 
    INT Type;          // Shader OpenGL type
    INT Id;            // Shader Id created by OpenGL
  } shd[] = 
  {
    {"VERT", GL_VERTEX_SHADER},
  {"FRAG", GL_FRAGMENT_SHADER}
  };

  INT prg = 0, res, Ns = sizeof(shd) / sizeof(shd[0]);
  CHAR *txt;
  BOOL is_ok = TRUE;
  static CHAR Buf[3000];

  for (INT i = 0; is_ok && i < Ns; i++)
  {
    // Load shader text from file
    sprintf(Buf, "%s/%s.GLSL", ShaderFileNamePrefix.c_str(), shd[i].Name.c_str());
    if ((txt = LoadTextFromFile(std::string(Buf))) == NULL)
    {
      ShdLog(ShaderFileNamePrefix, shd[i].Name, "Error load file");
      is_ok = FALSE;
      break;
    }

    /* Create shader */
    if ((shd[i].Id = glCreateShader(shd[i].Type)) == 0)
    {
      ShdLog(ShaderFileNamePrefix, shd[i].Name, "Error create shader");
      free(txt);
      is_ok = FALSE;
      break;
    }

    // Attach shader source code to shader
    glShaderSource(shd[i].Id, 1, &txt, NULL);
    free(txt);

    // Compile shader
    glCompileShader(shd[i].Id);
    glGetShaderiv(shd[i].Id, GL_COMPILE_STATUS, &res);
    if (res != 1)
    {
      glGetShaderInfoLog(shd[i].Id, sizeof(Buf), &res, Buf);
      ShdLog(ShaderFileNamePrefix, shd[i].Name, Buf);
      is_ok = FALSE;
      break;
    }
  }

  if (is_ok)
  {
    if ((prg = glCreateProgram()) == 0)
    {
      is_ok = FALSE;
      ShdLog(ShaderFileNamePrefix, "PROG", "Error creating program");
    }
    else
    {
      // Attach shaders to program
      for (INT i = 0; i < Ns; i++)
        if (shd[i].Id != 0)
          glAttachShader(prg, shd[i].Id);
      // Link shader program
      glLinkProgram(prg);
      glGetProgramiv(prg, GL_LINK_STATUS, &res);
      if (res != 1)
      {
        glGetProgramInfoLog(prg, sizeof(Buf), &res, Buf);
        ShdLog(ShaderFileNamePrefix, "PROG",  Buf);
        is_ok = FALSE;
      }
    }
  }

  // Error handle
  if (!is_ok)
  {
    // Remove all shaders
    for (INT i = 0; i < Ns; i++)
      if (shd[i].Id != 0)
      {
        if (prg != 0)
          glDetachShader(prg, shd[i].Id);
        glDeleteShader(shd[i].Id);
      }
    // Remove program
    if (prg != 0)
      glDeleteProgram(prg);
    prg = 0;
  }

  return prg;
} /* End of 'ShdLoad' functon */

  /* Unload shader program from memory files function.
  * ARGUMENTS:
  *   - shader program Id:
  *       INT ProgId;
  * RETURNS: None.
  */
VOID degl::shader::ShdDelete( INT ProgId )
{
  INT shdrs[5], n;


  if (ProgId == 0)
    return;
  glGetAttachedShaders(ProgId, 5, &n, (UINT *)shdrs);
  for (INT i = 0; i < n; i++)
  {
    glDetachShader(ProgId, shdrs[i]);
    glDeleteShader(shdrs[i]);
  }
  glDeleteProgram(ProgId);
} /* End of 'ShdDelete' function */

  /* Shader class destructor function
  * ARGUMENTS: None.
  * RETURNS: None.
  */
degl::shader::~shader( VOID )
{
  for (auto s : shaders)
    ShdDelete(s.second);
} /* End of shader class destructor function */

  /* Shader add function
  * ARGUMENTS:
  *   - shader file name:
  *          (string) &ShaderFileNamePrefix;
  * RETURNS: None.
  */
VOID degl::shader::ShdAdd( string ShaderFileNamePrefix )
{
  shaders[ShaderFileNamePrefix] = ShdLoad(ShaderFileNamePrefix);
} /* End of 'ShdAdd' function */

  /* Shaders update function
  * ARGUMENTS: None.
  * RETURNS: None.
  */
VOID degl::shader::ShdUpdate( VOID )
{
  for (auto s : shaders)
  {

    ShdDelete(s.second);
    s.second = ShdLoad(s.first);
  }
} /* End of 'ShdUpdate' function */

  /* Shader class constructor function
  * ARGUMENTS: None.
  * RETURNS: None.
  */
VOID degl::shader::ShdInit( VOID )
{
  ShdAdd("BIN/SHADERS/DEFAULT");
} /* End of shader_manager class constructor function */