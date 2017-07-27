/*
 *
 *
 *
 */

#define RED     "\x1b[31m"
#define NORMAL	"\x1b[0m"
#define GREEN	"\x1b[32m"

#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

char	**main_obj;
char	**child;
char	*version;
char	*workflow;
char	*search;
clock_t	begin;
clock_t	end;
int	step;

int	is_present(char *s1, char *s2)
{
  int	i = 0;
  int	j = 0;
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

char	*return_key(char *s)
{
  int	i = 0;
  int	k = 0;
  char	*dest;

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

char	**my_strsep(char *s, char c)
{
  char	**dest;
  int	i = 0;
  int	k = 0;
  int	j = 0;
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
      dest[i] = malloc(sizeof(char) * strlen(s));
      memset(dest[i], 0, strlen(s));
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
      dest[j][k] = s[i];
      i++;
      k++;
    }
  return (dest);
}

void	store_main_obj(char **main_obj)
{
  int	i = 0;
  while (main_obj[i][0] != ' ' && main_obj[i] != '\0' && main_obj[i][0] != '\0')
    {
      printf("\t\"WORC-%s\" [label=\"WORC-%s\", shape=\"box\", color=blue, fontcolor=white];\n", main_obj[i], main_obj[i]);
      printf("\tRabbitMQ -> \"WORC-%s\";\n", main_obj[i]);
      i++;
    }
}

void	store_child_obj(char *child_name, char **child)
{
  int	i = 0;
  while (child[i][0] != '\0')
    {
      printf("\t\"WORC-%s\" -> \"%s\";\n", child_name, child[i]);
      i++;
    }
}

char	*get_child_operator(char *s)
{
  int	i = 0;
  int	k = 0;
  char	*dest;

  dest = malloc(sizeof(char) * strlen(s));
  memset(dest, 0, strlen(s));
  while (s[i] != '\0')
    {
      if (s[i] == '.' && s[i + 1] == 'o' && s[i + 2] == 'p')
	break;
      i++;
    }
  if (s[i] == '\0')
    return (NULL);
  i--;
  while (s[i] != '.')
    i--;
  i++;
  while (s[i] != '\0')
    {
      if (s[i] == '.' && s[i + 1] == 'o' && s[i + 2] == 'p')
	break;
      dest[k] = s[i];
      k++;
      i++;
    }
  dest[k] = '\0';
  return (dest);
}

void	print_link_from(char **result, char *s)
{
  printf("\t\"%s\" -> ", result[1]);
}

void	print_link_to(char **result, char *s)
{
  printf("\"%s\";\n", result[1]);
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

char	*getChild(char *key)
{
  int	i = 0;
  int	k = 0;
  char *dest;

  dest = malloc(sizeof(char) * strlen(key));
  memset(dest, 0, strlen(key));
  while (key[i] != '\0' && key[i] != '.')
    i++;
  (key[i] == '.') ? i++ : 0;
  while (key[i])
    {
      dest[k] = key[i];
      k++;
      i++;
    }
  dest[i] = '\0';
  return (dest);    
}

void	apply_link(char **result)
{
  int	i = 0;
  while (result[i][0] != '\0')
    {
      printf("\t\"%s\" [label=\"déclenchement suite à un event %s\"];\n", getChild(result[i]), getChild(result[i]));
      printf("\tRabbitMQ -> \"%s\" -> \"WORC-%s\"\n", getChild(result[i]), getParent(result[i]), step);
      i++;
      step++;
    }
}

void	apply_link_from(char *key)
{
  printf("\t\"WORC-%s\" -> RabbitMQ [label=\"Step : %d Go to -> %s\"];\n", getParent(key), step, getChild(key));
  step++;
}

void	apply_link_to(char **result)
{
  int	i = 0;
  while (result[i][0] != '\0')
    {
      printf("\t\"WORC-%s\" -> RabbitMQ [label=\"Step : %d Go to -> %s\" arrowtail=dot];\n", getParent(result[i]), step, getChild(result[i]));
      i++;
      step++;
    }
}

void	setRank(char **obj)
{
  int	i = 0;
  printf(" {\n\trank = same\n");
  while (obj[i][0] != '\0')
    {
      printf("\t\"WORC-%s\";\n", obj[i]);
      i++;
    }
  printf(" }\n");
}

void	analyze(char *s)
{
  if (is_present(s, "amqp.worc=") == 0)
    {
      setRank(my_strsep(return_key(s), ','));
    }
  /*  else if (is_present(s, search) == 0)
    {
      if (is_present(s, "branch=") == 0) // ex : desactiverCompte.1.0.branch=contact.mailUtilisateur,contributiondiffuserAvisUtilisateur
	{
	  apply_link(my_strsep(return_key(s), ','));
	}
      else if (is_present(s, ".from=") == 0)
	{
	  printf("\tRabbitMQ -> \"%s\" -> \"WORC-%s\"\n", getChild(return_key(s)), getParent(return_key(s)));
	}
      else if (is_present(s, ".to=") == 0)
	{
	  apply_link_to(my_strsep(return_key(s), ','));
	}
	}*/
  else
    return;
}

int	main(int ac, char **av)
{
  char	*s;
  int	fd;

  begin = clock();
  step = 0;
  printf("You must give the worc file's %spath%s\n", GREEN, NORMAL);
  s = get_next_line(0);
  if ((fd = open(s, O_RDONLY)) == -1)
    {
      printf("%sError, bad path\n%s", RED, NORMAL);
      return (84);
    }
  free(s);
  printf("Give the workflow %sname%s\n", GREEN, NORMAL);
  workflow = get_next_line(0);
  printf("Which version do you want ? (%s1.0, 1.1, 1.2%s)\n", GREEN, NORMAL);
  version = get_next_line(0);
  printf("\n\nThe graph will be set on : %s%s.%s%s\n", GREEN, workflow, version, NORMAL);
  //sleep(3);
  printf("# GraphDot transcompiled by Az' #\n# MainSettings #\n");
  printf("digraph G {\n");
  printf("\tsplines = ortho;\n\tconcentrate = true;\n");
  printf("\tnode [shape=\"box\", style=\"rounded\", penwidth = 2];\n\tedge [color=\"#142b30\",  penwidth=2];\n");
  printf("\tRabbitMQ [shape=polygon,sides=5,peripheries=3];\n\n");
  printf("###############\n\n");
  search = malloc(sizeof(char) * (strlen(version) + strlen(workflow) + 2));
  memset(search, 0, (strlen (version) + strlen(workflow)));
  strcat(search, workflow);
  strcat(search, ".");
  strcat(search, version);
  while ((s = get_next_line(fd)))
    {
      if (s[0] != '#' && s[0] != ' ' && s[0] != '\t')
	analyze(s);
      free(s);
    }
  printf("}\n");
  end = clock();
  return (0);
}
