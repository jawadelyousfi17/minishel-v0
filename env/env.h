#define DEFAULT_PATH "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:."

int ft_set_env(char ***env, char *var, char *value);
char **ft_copy_env(char **env);
void **ft_env_realloc(void **env, size_t old_size, size_t new_size);
char **ft_free_env(char **env);
int hl_change_env_value(char *var, char *value, char **env);
int ft_free_env_value(char *var, char **env);
char **ft_create_env();
char *ft_extract_var(char *s);
char *gb_get_env(char **env, char *var);
char **gb_get_all_env(char **env);
size_t ft_max(size_t a, size_t b);
int ft_matrix_len(char **matrix);
char **ft_copy_export_env(char **env);