/* Derzhavin Andrey, 10-6, 01.06.2018 */
#include <windows.h>
#include <stdio.h>

void main( void )
{
  printf("Hello");
  MessageBox(NULL, "World", "Good morning", MB_OK | MB_ICONINFORMATION);
}