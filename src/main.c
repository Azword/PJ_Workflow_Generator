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

t_config	config;
int		DEBUG = 0;
char		*query;
int		step = 1;
int		last_action = -1;
char		*previous_worc;
bool		cluster_is_open = false;

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
    while (i != 14)
      {
	free(config_contain[i]);
	i++;
      }

  if (config_contain == NULL)
    {
      config_contain = malloc(sizeof(char *) * 14);
      while (i != 14)
	{
	  config_contain[i] = malloc(sizeof(char) * 120);
	  memset(config_contain[i], 0, 120);
	  i++;
	}
      get_configcontain(&*config_contain);
    }
  (i != 0) ? i = 0 : 0;
  while (config_contain[i][0] != '\0')
    {
      if (is_present(config_contain[i], prefix) == 0)
	{
	  //	  memset(key, 0, strlen(config_contain[i]));
	  sprintf(key, "%s%s" , key, return_key(config_contain[i]));
	  return;
	}
      i++;
    }
}

void	print_config(t_config *config)
{
  printf("############## DEBUG ##############\n");
  printf("            Config File            \n");
  printf("rabbit_shape : %s\n", config->rabbit_shape);
  printf("rabbit_style : %s\n", config->rabbit_style);
  printf("rabbit_size  : %s\n", config->rabbit_size);
  printf("rabbit_color : %s\n", config->rabbit_color);
  printf("node_shape   : %s\n", config->node_shape);
  printf("node_style   : %s\n", config->node_style);
  printf("edge_color   : %s\n", config->edge_color);
  printf("worc_shape   : %s\n", config->worc_shape);
  printf("worc_style   : %s\n", config->worc_style);
  printf("worc_color   : %s\n", config->worc_color);
  printf("event_shape  : %s\n", config->event_shape);
  printf("event_style  : %s\n", config->event_style);
  printf("event_color  : %s\n", config->event_color);
  printf("###################################\n\n");
}

void	set_default_key(t_config *config)
{
  (config->rabbit_shape[0] == '\0') ? config->rabbit_shape = "box" : 0;
  (config->rabbit_style[0] == '\0') ? config->rabbit_style = "rounded" : 0;
  (config->rabbit_size[0] == '\0') ? config->rabbit_size = "10" : 0;
  (config->rabbit_color[0] == '\0') ? config->rabbit_color = "yellow" : 0;
  (config->node_shape[0] == '\0') ? config->node_shape = "box" : 0;
  (config->node_style[0] == '\0') ? config->node_style = "rounded" : 0;
  (config->edge_color[0] == '\0') ? config->edge_color = "white" : 0;
  (config->worc_shape[0] == '\0') ? config->worc_shape = "box" : 0;
  (config->worc_style[0] == '\0') ? config->worc_style = "rounded" : 0;
  (config->worc_color[0] == '\0') ? config->worc_color = "black" : 0;
  (config->event_shape[0] == '\0') ? config->event_shape = "box" : 0;
  (config->event_style[0] == '\0') ? config->event_style = "rounded" : 0;
  (config->event_color[0] == '\0') ? config->event_color = "black" : 0;
}

t_config	get_config(t_config *config)
{
  char	*s;
  int	fd;

  if ((fd = open("./config", O_RDONLY)) == -1)
    exit (84);
  get_configkey("rabbit_shape", &*config->rabbit_shape);
  get_configkey("rabbit_style", &*config->rabbit_style);
  get_configkey("rabbit_size", &*config->rabbit_size);
  get_configkey("rabbit_color", &*config->rabbit_color);
  get_configkey("node_shape", &*config->node_shape);
  get_configkey("node_style", &*config->node_style);
  get_configkey("edge_color", &*config->edge_color);
  get_configkey("worc_shape", &*config->worc_shape);
  get_configkey("worc_style", &*config->worc_style);
  get_configkey("worc_color", &*config->worc_color);
  get_configkey("event_shape", &*config->event_shape);
  get_configkey("event_style", &*config->event_style);
  get_configkey("event_color", &*config->event_color);
  set_default_key(&*config);
  get_configkey(NULL, NULL); // Instructio for free
  (DEBUG == 1) ? print_config(config) : 0;
}

void	initialize_config(t_config *config)
{
  config->rabbit_shape = malloc(sizeof(char) * 20);
  config->rabbit_style = malloc(sizeof(char) * 20);
  config->rabbit_size = malloc(sizeof(char) * 20);
  config->rabbit_color = malloc(sizeof(char) * 20);
  config->node_shape = malloc(sizeof(char) * 20);
  config->node_style = malloc(sizeof(char) * 20);
  config->edge_color = malloc(sizeof(char) * 20);
  config->worc_shape = malloc(sizeof(char) * 20);
  config->worc_style = malloc(sizeof(char) * 20);
  config->worc_color = malloc(sizeof(char) * 20);
  config->event_shape = malloc(sizeof(char) * 20);
  config->event_style = malloc(sizeof(char) * 20);
  config->event_color = malloc(sizeof(char) * 20);
  previous_worc = malloc(sizeof(char) * 100);
  memset(previous_worc, 0, 100);
}

void	print_dot_header()
{
  printf("# Transcompile from Worc's file to Dot, by Az' generator #\n\n");
  printf("##### Header #####\n\n");
  printf("digraph G {\n");
  printf("\tsplines = ortho;\n");
  printf("\tconcentrate = true;\n\n");
  printf("\tnode [shape=\"%s\", style=\"%s\", penwidth = 2];\n", config.node_shape, config.node_style);
  printf("\tedge [color=\"%s\"];\n\n", config.edge_color);
  printf("subgraph cluster_0 {\n\tRabbitMQ [label=\"%s --- RabbitMQ\" shape=\"%s\" width=\"%s\" style=\"%s\" color=\"%s\"];\n}\n", query, config.rabbit_shape, config.rabbit_size, config.rabbit_style, config.rabbit_color);
  printf("### EndHeader ###\n\n");
  
}

void	print_dot_footer()
{
  printf("}\n");
}

int	ask_for_path()
{
  char	*s;
  int	fd;

  write(0, "Worc_file Path : ", strlen("Worc_file Path : "));
  s = get_next_line(0);
  printf("\n");
  if ((fd = open(s, O_RDONLY)) == -1)
    {
      free(s);
      printf("Bad Path.\n");
      return (84);
    }
  else
    {
      free(s);
      return (fd);
    }
}

void	logger(char *log_name, char *log_contain)
{
  printf("##### %s #####\n", log_name);
  printf("%s\n", log_contain);
  printf("#### End%s ####", log_name);
}

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
      printf("\t\"WORC-%s%d\" [shaper=\"%s\" style=\"%s\" color=\"%s\"];\n", getParent(s), step, config.worc_shape, config.worc_style, config.worc_color);
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
  while ((s = get_next_line(fd)))
    {
      if (s[0] != '#') // We skip all comments
	analyze(s);
      free(s);
    }
  if (cluster_is_open == true)
    printf("}\n");
}

char	*ask_for_query()
{
  char	*s;

  write(0, "WorkflowName : ", strlen("WorkFlowName : "));
  s = get_next_line(0);
  query = malloc(sizeof(char) * (strlen(s) + 5));
  memset(query, 0, (strlen(s) + 5));
  strcat(query, s);
  strcat(query, ".");
  free(s);
  write(0, "Version : ", strlen("Version : "));
  s = get_next_line(0);
  strcat(query, s);
  free(s);
  return (query);
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
