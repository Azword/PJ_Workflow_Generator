
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "proto.h"
#include "get_next_line.h"

void	get_configcontain(char **contains)
{
  int	fd;
  int	i = 0;
  char	*s;

  fd = open("./config", O_RDONLY);
  while ((s = get_next_line(fd)))
    {
      if (s[0] != '\0')
	{
	  sprintf(contains[i], "%s%s" , contains[i], s);
	  i++;
	}
      free(s);
    }
}

void	get_configkey(char *prefix, char *key)
{
  static char **config_contain;
  int	i = 0;
  if (prefix == NULL && key == NULL)
    while (i != 15)
      {
	free(config_contain[i]);
	i++;
      }

  if (config_contain == NULL)
    {
      config_contain = malloc(sizeof(char *) * 15);
      while (i != 15)
	{
	  config_contain[i] = malloc(sizeof(char) * 100);
	  memset(config_contain[i], 0, 100);
	  i++;
	}
      get_configcontain(&*config_contain);
    }
  (i != 0) ? i = 0 : 0;
  while (config_contain[i][0] != '\0')
    {
      if (is_present(config_contain[i], prefix) == 0)
	{
	  sprintf(key, "%s%s" , key, return_key(config_contain[i]));
	  return;
	}
      i++;
    }
}
