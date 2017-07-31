
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "proto.h"
#include "get_next_line.h"

extern t_config config;
extern char * query;

void	print_dot_header()
{
  printf("# Transcompile from Worc's file to Dot, by Az' generator #\n\n");
  printf("##### Header #####\n\n");
  printf("digraph G {\n");
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
