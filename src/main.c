/*
 *
 *
 *
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "struct.h"
#include "get_next_line.h"
#include "proto.h"

t_config	config;
int		DEBUG = 0;
char		*query;
int		step = 1;
int		last_action = -1;
char		*previous_worc;
bool		cluster_is_open = false;
bool		star = false;
char		*previous_result;
char		*previous_from;

int	is_dual(int n)
{
  if (n % 2 == 0)
    return (0);
  else
    return (84);
}

int	is_from_regex(char *s)
{
  int	i = 0;
  int	k = 0;
  while (s[i])
    {
      while (s[i] != '\0' && config.regex[k] != '\0' && s[i] == config.regex[k])
	{
	  k++;
	  i++;
	}
      if (config.regex[k] == '*')
	return (0);
      else
	k = 0;
      i++;
    }
  return (84);
}

int	branch_type_one(char **result, int n) // global
{
  int	ret = 0;
  int	i = 0;
  int	cal = step;
  int	length = 0;
  
  //  if (result[1] != NULL && result[1] != '\0' && result[1][0] != '\0') // When we have parallele event
  //  ret = 1;
  (n == 1) ? cal++ : 0;
  printf("subgraph cluster_%d {\n", step);
  cluster_is_open = true;
  while (result[i][0])
    {
      length += strlen(result[i]);
      i++;
    }
  i = 0;
  previous_result = malloc(sizeof(char) * (length * 2));
  memset(previous_result, 0, (length * 2));
  while (result[i][0])
    {
      strcat(previous_result, result[i]);
      i++;
    }
  i = 0;
  while (result[i][0] != '\0')
    {
      // TODO Add, a verif before print and a IF for the printf (IS_REGEX ? TRUE -> Print '*' : FALSE -> Do like others times
      if (i != 0 && strcmp(getParent(result[i]), getParent(result[i - 1])) == 0)
	cal++;
      printf("\t\"EVENT-%s\" [shape=\"%s\" style=\"%s\" color=\"%s\"];\n", getChild(result[i]), config.event_shape, config.event_style, config.event_color);
      printf("\tRabbitMQ -> \"EVENT-%s\" [label=\"%d\"];\n", getChild(result[i]), step);
      printf("\t\"WORC-%s(%s)\" [shaper=\"%s\" style=\"%s\" color=\"%s\"];\n", getParent(result[i]), getChild(result[i]), config.worc_shape, config.worc_style, config.worc_color);
      printf("\t\"EVENT-%s\" -> \"WORC-%s(%s)\"\n", getChild(result[i]), getParent(result[i]), getChild(result[i]));
      if (is_from_regex(getChild(result[i])) == 0)
	  star = true;
      (n == 1) ? cal++ : 0;
      i++;
    }
  step++;
  return (ret);
}

int	branch_type_three(char **result) // .to
{
  int	ret = 0;
  int	i = 0;
  char	*full_back;

  full_back = malloc(sizeof(char) * 200);
  memset(full_back, 0, 200);
  while (result[i][0] != '\0')
    {
      strcat(full_back, getChild(result[i]));
      if (result[i + 1][0] != '\0')
	strcat(full_back, "\\n");
      i++;
    }
  i = 0;
  if (previous_from != NULL && previous_from[0] != '\0')
    {
      if (is_from_regex(getChild(result[i])) == 0)
	printf("\t\"%s\" -> RabbitMQ [label=\"*\\n%s\\n%d\", style=dotted];\n", previous_from, full_back, step);
      else
	printf("\t\"%s\" -> RabbitMQ [label=\"%s\\n%d\", style=dotted];\n", previous_from, full_back, step);
      while (result[i][0])
	{
	  (i == 0) ? step++ : 0;
	  printf("\t\"WORC-%s(%s)\" [shape=\"%s\" style=\"%s\" color=\"%s\"];\n", getParent(result[i]), getChild(result[i]), config.worc_shape, config.worc_style, config.worc_color);
	  printf("\t\"EVENT-%s\" [shape=\"%s\" style=\"%s\" color=\"%s\"];\n", getChild(result[i]), config.event_shape, config.event_style, config.event_color);
	  printf("\tRabbitMQ -> \"EVENT-%s\" [label=\"%d\"];\n", getChild(result[i]), step);
	  printf("\t\"EVENT-%s\" -> \"WORC-%s(%s)\"\n", getChild(result[i]), getParent(result[i]), getChild(result[i]));
	  i++;
	}
      step++;
    }
  printf("}\n");
  cluster_is_open = false;
 free(full_back);
 return (ret);
}

void	branch_type_two(char *s) // .from
{
  if (cluster_is_open == false)
    {
      printf("subgraph cluster_%d {\n", step);
      cluster_is_open = true;
    }
  if (last_action != 12)
    {
      previous_from = malloc(sizeof(char) * (strlen(getParent(s) + 10)));
      memset(previous_from, 0, strlen(getParent(s) + 10));
      sprintf(previous_from, "WORC-%s(%s)", getParent(s), getChild(s)); 
      if (previous_worc == NULL)
	free(previous_worc);
    }
}

void	analyze(char *s)
{
  static	int skipper = 0;
  if (is_present(s, query) == 0)
    {
      (DEBUG == 1) ? printf("------------> {%s} <--------------\n", s) : 0;
      if (is_present(s, "branch=") == 0)
	{
	  (DEBUG == 1) ? printf("[Global] {\n") : 0;
	  skipper = branch_type_one(my_strsep(return_key(s), ','), 0);
	  (DEBUG == 1) ? printf("}\n") : 0;
	  last_action = 0;
	}
      else if ((is_present(s, ".from=") == 0))
	{
	  (DEBUG == 1) ? printf("[From] {\n") : 0;
	  branch_type_two(return_key(s));
	  (DEBUG == 1) ? printf("}\n") : 0;
	  last_action = 1;
	}
      else if (is_present(s, ".to=") == 0)
	{
	  (DEBUG == 1) ? printf("[To] {\n") : 0;
	  skipper = branch_type_three(my_strsep(return_key(s), ','));
	  (DEBUG == 1) ? printf("}\n") : 0;
	  last_action = 2;	
	}
    }
  else
    return;
}

void	transcompile(int fd)
{
  char	*s;

  if (DEBUG == 1)
    {
      printf("#### DEBUG ####\n The query : %s\n#### #####\n", query);
    }
  printf("subgraph cluster_init {\n\nrank = same;\n");
  while ((s = get_next_line(fd)))
    {
      if (s[0] != '#') // We skip all comments
	analyze(s);
      free(s);
    }
  printf("}\n");
}

int	main(int ac, char **av)
{
  int	fd;

  if (ac == 2 && av[1][0] == '-' && av[1][1] == 'd')
    {
      DEBUG = 1;
    }

  initialize_config(&config);
  get_config(&config);
  fd = ask_for_path();
  query = ask_for_query();
  previous_result = malloc(sizeof(char *) * 20);
  if (fd == 84)
    return (84);
  print_dot_header();
  transcompile(fd);
  print_dot_footer();
}
