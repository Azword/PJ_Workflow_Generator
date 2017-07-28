#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "proto.h"

extern int DEBUG;

char	**my_strsep(char *s, char c)
{
  char	**dest;
  int	i = 0;
  int	k = 0;
  int	j = 0;
  (DEBUG == 1) ? printf("[Strsep()]_receive : s->%s\n", s) : 0;
  while (s[i])
    {
      if (s[i] == c)
	k++;
      i++;
    }
  dest = malloc(sizeof(char *) * (k + 2));
  i = 0;
  while (i != k + 2)
    {
      dest[i] = malloc(sizeof(char) * (strlen(s) + 10));
      memset(dest[i], 0, strlen(s) + 10);
      i++;
    }
  i = k = 0;
  while (s[i])
    {
      if (s[i] == c)
	{
	  i++;
	  j++;
	  k = 0;
	}
      if (s[i] == '\0')
	break;
      dest[j][k] = s[i];
      i++;
      k++;
    }
  (DEBUG == 1) ? printf("[Strsep()]_return : %s / %s\n", dest[0], ((dest[1] != NULL) ? dest[1] : "nullVolontaire")) : 0;
  return (dest);
}

int     is_present(char *s1, char *s2)
{
  int   i = 0;
  int   j = 0;

  if (s1 == NULL || s2 == NULL || s1[0] == '\0' || s2[0] == '\0')
    return (84);
  while (s1[i])
    {
      while (s1[i] == s2[j])
	{
	  i++, j++;
	}
      if (s2[j] == '\0')
	return (0);
      else
	j = 0;
      i++;
    }
  return (84);
}
