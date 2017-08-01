#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "proto.h"

extern int DEBUG;
extern char * previous_worc;

void	print_config(t_config *config)
{
  printf("############## DEBUG ##############\n");
  printf("            Config File            \n");
  printf("regex        : %s\n", config->regex);
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
  (config->regex[0] == '\0') ? config->regex = "\0" : 0;
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
  get_configkey("pattern_regex_star", &*config->regex);
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
  config->regex = malloc(sizeof(char) * 30);
  config->rabbit_shape = malloc(sizeof(char) * 30);
  config->rabbit_style = malloc(sizeof(char) * 30);
  config->rabbit_size = malloc(sizeof(char) * 30);
  config->rabbit_color = malloc(sizeof(char) * 30);
  config->node_shape = malloc(sizeof(char) * 30);
  config->node_style = malloc(sizeof(char) * 30);
  config->edge_color = malloc(sizeof(char) * 30);
  config->worc_shape = malloc(sizeof(char) * 30);
  config->worc_style = malloc(sizeof(char) * 30);
  config->worc_color = malloc(sizeof(char) * 30);
  config->event_shape = malloc(sizeof(char) * 30);
  config->event_style = malloc(sizeof(char) * 30);
  config->event_color = malloc(sizeof(char) * 30);
  previous_worc = malloc(sizeof(char) * 100);
  memset(config->regex, 0, 30);
  memset(config->rabbit_shape, 0, 30);
  memset(config->rabbit_style, 0, 30);
  memset(config->rabbit_color, 0, 30);
  memset(config->rabbit_size, 0, 30);
  memset(config->node_shape, 0, 30);
  memset(config->node_style, 0, 30);
  memset(config->edge_color, 0, 30);
  memset(config->worc_color, 0, 30);
  memset(config->worc_style, 0, 30);
  memset(config->worc_shape, 0, 30);
  memset(config->event_color, 0, 30);
  memset(config->event_style, 0, 30);
  memset(config->event_shape, 0, 30);
  memset(previous_worc, 0, 100);
}
