typedef struct s_config {
  // RabbitMQ Box, color, ...
  char *rabbit_shape;
  char *rabbit_style;
  char *rabbit_size;
  char *rabbit_color;
  // Node
  char *node_shape;
  char *node_style;
  // Edge
  char *edge_color;

  // Worc
  char *worc_shape;
  char *worc_style;
  char *worc_color;

  // Event;
  char *event_shape;
  char *event_style;
  char *event_color;
}	t_config;
