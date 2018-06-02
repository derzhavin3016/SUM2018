/* Derzhavin Andrey, 10-6, 01.06.2018 */
#include <windows.h>
#include <stdio.h>

INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT ShowCmd )
{
  INT l = 1, r = 100, m = (l + r) / 2, answer;
  CHAR Buf[100];

  MessageBox(NULL, "Загадайте число от 1 до 100", "Игра", MB_OK);
  while (l != 0)
  {
    sprintf(Buf, "Ваше число больше, меньше или равно %i?", m);
    answer = MessageBox(NULL, Buf, "Вопрос", MB_YESNOCANCEL);
    if (answer == IDYES)
    {
      l = m + 1;
      m = (l + r) / 2;
    }
    if (answer == IDNO)
    {
      r = m - 1;
      m = (l + r) / 2;
    }
    if (answer == IDCANCEL)
    {
      sprintf(Buf, "Ваше число %i", m);
      MessageBox(NULL, Buf, "Вопрос", MB_OK);
      break;
    }
    if (l == r)
    {
      sprintf(Buf, "Ваше число %i", l);
      MessageBox(NULL, Buf, "Вопрос", MB_OK);
      break;
    }  
  }
  return 0;  
}