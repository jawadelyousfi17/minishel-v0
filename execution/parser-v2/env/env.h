#define DEFAULT_PATH "/usr/local/bin:/usr/bin:/bin:/sbin:/usr/sbin"

int ft_set_env(char ***env, char *var, char *value);
char **ft_copy_env(char **env);
void **ft_env_realloc(void **env, size_t old_size, size_t new_size);
char **ft_free_env(char **env);
char **ft_create_env();
char *ft_extract_var(char *s);
char *gb_get_env(char **env, char *var);
char **gb_get_all_env(char **env);
void ft_sort(char **env);
size_t ft_max(size_t a, size_t b);