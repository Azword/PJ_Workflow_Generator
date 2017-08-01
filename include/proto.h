typedef struct s_config {
  char *regex;
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

void  get_configcontain(char **contains);
void	get_configkey(char *prefix, char *key);

void	logger(char *log_name, char *log_contain);

void	print_dot_header();
void	print_dot_footer();
int	  ask_for_path();
char	*ask_for_query();

int	  branch_type_one(char **result, int n);
void	branch_type_two(char *s);
int	  branch_type_three(char **result);
void	analyze(char *s);
void	transcompile(int fd);

char	**my_strsep(char *s, char c);
int   is_present(char *s1, char *s2);

void	    print_config(t_config *config);
void	    set_default_key(t_config *config);
t_config	get_config(t_config *config);
void	    initialize_config(t_config *config);

char	*getChild(char *key);
char	*getParent(char *key);
char    *return_key(char *s);
