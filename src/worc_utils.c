
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "proto.h"

extern int DEBUG;

char	*getChild(char *key)
{
  int	i = 0;
  int	k = 0;
  char *dest;

  dest = malloc(sizeof(char) * (strlen(key) * 2));
  memset(dest, 0, strlen(key) * 2);
  while (key[i] != '\0' && key[i] != '.')
    i++;
  (key[i] == '.') ? i++ : 0;
  while (key[i])
    {
      dest[k] = key[i];
      k++;
      i++;
    }
  (DEBUG == 1) ? printf("[getChild()]_return : %s\n", dest) : 0;
  dest[i] = '\0';
  return (dest);
}

char	*getParent(char *key)
{
  int	i = 0;
  char	*dest;

  dest = malloc(sizeof(char) * strlen(key));
  memset(dest, 0, strlen(key));
  while (key[i] != '\0' && key[i] != '.')
    {
      dest[i] = key[i];
      i++;
    }
  dest[i] = '\0';
  return (dest);
}

char    *return_key(char *s)
{
  int   i = 0;
  int   k = 0;
  char  *dest;

  dest = malloc(sizeof(char) * (strlen(s) * 2));
  memset(dest, 0, strlen(s) * 2);
  while (s[i] != '\0' && s[i] != '=')
    i++;
  i++;
  while (s[i])
    {
      dest[k] = s[i];
      k++;
      i++;
    }
  (DEBUG == 1) ? printf("[Return_Key()]_return : %s\n", dest) : 0;
  return (dest);
}
