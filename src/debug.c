#include <stdio.h>
#include "proto.h"

void	logger(char *log_name, char *log_contain)
{
  printf("##### %s #####\n", log_name);
  printf("%s\n", log_contain);
  printf("#### End%s ####", log_name);
}
