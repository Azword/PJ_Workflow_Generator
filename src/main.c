/*
 *
 *
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include "struct.h"
#include "get_next_line.h"

t_config config;
int	DEBUG = 0;
char	*query;

int     is_present(char *s1, char *s2)
{
  int   i = 0;
  int   j = 0;
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

  dest = malloc(sizeof(char) * strlen(s));
  memset(dest, 0, strlen(s));
  while (s[i] != '\0' && s[i] != '=')
    i++;
  i++;
  while (s[i])
    {
      dest[k] = s[i];
      k++;
      i++;
    }
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
	  strcat(contains[i], s);
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
    while (i != 12)
      {
	free(config_contain[i]);
	i++;
      }

  if (config_contain == NULL)
    {
      config_contain = malloc(sizeof(char *) * 12);
      while (i != 12)
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
	  strcat(key, return_key(config_contain[i]));
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
  get_configkey("node_shape", &*config->node_shape);
  get_configkey("node_style", &*config->node_style);
  get_configkey("edge_color", &*config->edge_color);
  get_configkey("worc_shape", &*config->worc_shape);
  get_configkey("worc_style", &*config->worc_style);
  get_configkey("worc_color", &*config->worc_color);
  get_configkey("worc_shape", &*config->worc_shape);
  get_configkey("worc_style", &*config->worc_style);
  get_configkey("worc_color", &*config->worc_color);
  set_default_key(&*config);
  get_configkey(NULL, NULL); // Instructio for free
  (DEBUG == 1) ? print_config(config) : 0;
}

void	initialize_config(t_config *config)
{
  config->rabbit_shape = malloc(sizeof(char) * 20);
  config->rabbit_style = malloc(sizeof(char) * 20);
  config->node_shape = malloc(sizeof(char) * 20);
  config->node_style = malloc(sizeof(char) * 20);
  config->edge_color = malloc(sizeof(char) * 20);
  config->worc_shape = malloc(sizeof(char) * 20);
  config->worc_style = malloc(sizeof(char) * 20);
  config->worc_color = malloc(sizeof(char) * 20);
  config->event_shape = malloc(sizeof(char) * 20);
  config->event_style = malloc(sizeof(char) * 20);
  config->event_color = malloc(sizeof(char) * 20);
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

void	analyze(char *s)
{
  if (is_present(s, query) == 0)
    {
      if (is_present(s, "branch=") == 0)
	{
	  printf("Global !\n");
	}
      else if (is_present(s, ".from=") == 0)
	{
	  printf("From !\n");
	}
      else if (is_present(s, ".to=") == 0)
	{
	  printf("To !\n");
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
  while ((s = get_next_line(fd)))
    {
      if (s[0] != '#') // We skip all comments
	analyze(s);
      free(s);
    }
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
