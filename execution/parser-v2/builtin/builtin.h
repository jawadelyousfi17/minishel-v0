#define VALID_START "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_"
#define VALID "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789"

#define NORMAL_EXPORT 1
#define APPEND_EXPORT 2
#define ERROR_FORMAT 3

int ft_print_error4(char *s1, char *s2, char *s3, char *s4);
int ft_export_no_args(char **env);

int ft_export(char **s, char ***env);

int ft_is_start_with(char *src, char *target);

int ft_echo(char **s, char ***env);

int ft_unset(char **args, char ***env);

int ft_env(char **env);



// expander
char *ft_get_var_name(char **s);