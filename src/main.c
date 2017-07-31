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

int	branch_type_one(char **result, int n) // global
{
  int	ret = 0;
  int	i = 0;
  int	cal = step;

  if (result[1] != NULL && result[1] != '\0' && result[1][0] != '\0') // When we have parallele event
    ret = 1;
  (n == 1) ? cal++ : 0;
  printf("subgraph cluster_%d {\n", step);
  cluster_is_open = true;
  while (result[i][0] != '\0')
    {
      printf("\t\"EVENT-%s\" [shape=\"%s\" style=\"%s\" color=\"%s\"];\n", getChild(result[i]), config.event_shape, config.event_style, config.event_color);
      printf("\tRabbitMQ -> \"EVENT-%s\" [label=\"%d\"];\n", getChild(result[i]), step);
      printf("\t\"WORC-%s%d\" [shaper=\"%s\" style=\"%s\" color=\"%s\"];\n", getParent(result[i]), cal, config.worc_shape, config.worc_style, config.worc_color);
      printf("\t\"EVENT-%s\" -> \"WORC-%s%d\"\n", getChild(result[i]), getParent(result[i]), cal);
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
  if (previous_worc[0] != '\0')
    {
      // TODO, HANDLE when multiple Event Back to Rabbit
      printf("\t\"%s\" -> RabbitMQ [label=\"%s\\n%d\", style=dotted];\n", previous_worc, getChild(result[0]), step);
      printf("\t\"WORC-%s%d\" [shape=\"%s\" style=\"%s\" color=\"%s\"];\n", getParent(result[0]), step - 1, config.worc_shape, config.worc_style, config.worc_color);
      printf("\t\"EVENT-%s\" [shape=\"%s\" style=\"%s\" color=\"%s\"];\n", getChild(result[0]), config.event_shape, config.event_style, config.event_color);
      printf("\tRabbitMQ -> \"EVENT-%s\" [label=\"%d\"];\n", getChild(result[0]), step);
      printf("\t\"EVENT-%s\" -> \"WORC-%s%d\"\n", getChild(result[0]), getParent(result[0]), step - 1);
    }
  else {
    printf("\t\"WORC-%s%d\" [shape=\"%s\" style=\"%s\" color=\"%s\"];\n", getParent(result[0]), step - 1, config.worc_shape, config.worc_style, config.worc_color);
    // printf("\tRabbitMQ -> \"WORC-%s%d\" [label=%d];\n", getParent(result[0]), step - 1, step);
    printf("\t\"WORC-%s%d\" -> RabbitMQ [label=\"%s\\n%d\", style=dotted];\n", getParent(result[0]), step - 1, full_back, step);
  }
  printf("}\n");
  cluster_is_open = false;
  free(full_back);
  step++;
  (previous_worc[0] != '\0') ? step++ : 0;
  if (i > 1)
    {
      ret = 1;
      branch_type_one(result, 1);
    }
  return (ret);
}

void	branch_type_two(char *s) // .from
{
  if (cluster_is_open = false)
    {
      printf("subgraph cluster_%d {\n", step);
      cluster_is_open = true;
    }
  if (last_action != 0)
    {
      printf("subgraph cluster_%d {\n", step);
      printf("\t\"EVENT-%s\" [shape=\"%s\" style=\"%s\" color=\"%s\"];\n", getChild(s), config.event_shape, config.event_style, config.event_color);
      printf("\tRabbitMQ -> \"EVENT-%s\" [label=\"%d\"];\n", getChild(s), step);
      printf("\t\"WORC-%s%d\" [shape=\"%s\" style=\"%s\" color=\"%s\"];\n", getParent(s), step, config.worc_shape, config.worc_style, config.worc_color);
      printf("\t\"EVENT-%s\" -> \"WORC-%s%d\"\n", getChild(s), getParent(s), step);
      step++;
    }
}

void	analyze(char *s)
{
  static	int skipper = 0;
  if (skipper != 0)
    {
      if (last_action == 2)
	{
	  sprintf(previous_worc, "WORC-%s%d", getParent(return_key(s)), step + 1);
	}
      else
	memset(previous_worc, 0, 100);
      skipper--;
      return;
    }
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
	  if (last_action = 2)
	    {
	      
	    }
	}
    }
  else
    {
      return;
    }
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
  if (cluster_is_open == true)
    printf("\t}\n}\n");
}

int	main(int ac, char **av)
{
  int	fd;

  if (ac == 2 && strcmp(av[1], "-d") == 0)
    DEBUG = 1;
  initialize_config(&config);
  get_config(&config);
  fd = ask_for_path();
  query = ask_for_query();
  if (fd == 84)
    return (84);
  print_dot_header();
  transcompile(fd);
  print_dot_footer();
}
