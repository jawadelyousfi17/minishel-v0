#include "../include/minishell.h"

int succeded_tests = 0;
int failed_tests = 0;
int test_n = 0;


int set_env_test(char ***env)
{

    {
        test_n++;
        ft_set_env(env, "T", "T");
        char *value = ft_get_env(*env, "T");
        if (!is_equal(value, "T"))
        {
            printf("❌Test %d\n", test_n);
            failed_tests++;
        }
        else
        {
            printf("✅ Test %d\n", test_n);
            ;
            succeded_tests++;
        }
    }

    {
        test_n++;
        char *value = ft_get_env(*env, "undefined");
        if (value)
        {
            printf("❌Test %d\n", test_n);
            failed_tests++;
        }
        else
        {
            printf("✅ Test %d\n", test_n);
            ;
            succeded_tests++;
        }
    }
    {
        test_n++;
        ft_set_env(env, "val", "Hello");
        char *value = ft_get_env(*env, "val");
        if (!is_equal(value, "Hello"))
        {
            printf("❌Test %d\n", test_n);
            failed_tests++;
        }
        else
        {
            printf("✅ Test %d\n", test_n);
            ;
            succeded_tests++;
        }
    }

    {
        test_n++;
        ft_set_env(env, "VALUE", "hi this is a test 458 ");
        char *value = ft_get_env(*env, "VALUE");
        if (!is_equal(value, "hi this is a test 458 "))
        {
            printf("❌Test %d\n", test_n);
            failed_tests++;
        }
        else
        {
            printf("✅ Test %d\n", test_n);
            ;
            succeded_tests++;
        }
    }

    {
        test_n++;
        ft_set_env(env, "v", "   ");
        char *value = ft_get_env(*env, "v");
        if (!is_equal(value, "   "))
        {
            printf("❌Test %d\n", test_n);
            failed_tests++;
        }
        else
        {
            printf("✅ Test %d\n", test_n);
            ;
            succeded_tests++;
        }
    }
}

int unset_env_test(char ***env)
{

    {
        test_n++;
        hl_ft_unset("a", env);
        char *value = ft_get_env(*env, "a");
        if (value)
        {
            printf("❌Test %d\n", test_n);
            failed_tests++;
        }
        else
        {
            printf("✅ Test %d\n", test_n);
            ;
            succeded_tests++;
        }
    }
    {
        test_n++;
        hl_ft_unset("b", env);
        char *value = ft_get_env(*env, "b");
        if (value)
        {
            printf("❌Test %d\n", test_n);
            failed_tests++;
        }
        else
        {
            printf("✅ Test %d\n", test_n);
            ;
            succeded_tests++;
        }
    }

    {
        test_n++;
        hl_ft_unset("c", env);
        char *value = ft_get_env(*env, "c");
        if (value)
        {
            printf("❌Test %d\n", test_n);
            failed_tests++;
        }
        else
        {
            printf("✅ Test %d\n", test_n);
            ;
            succeded_tests++;
        }
    }

    {
        test_n++;
        hl_ft_unset("d", env);
        char *value = ft_get_env(*env, "d");
        if (value)
        {
            printf("❌Test %d\n", test_n);
            failed_tests++;
        }
        else
        {
            printf("✅ Test %d\n", test_n);
            ;
            succeded_tests++;
        }
    }
}

int get_env_test(char **env)
{
    {
        test_n++;
        char *value = ft_get_env(env, "a");
        if (is_equal(value, getenv("a")))
        {
            printf("✅ Test %d\n", test_n);
            succeded_tests++;
        }
        else
        {
            printf("❌Test %d\n", test_n);
            failed_tests++;
        }
    }

    {
        test_n++;
        char *value = ft_get_env(env, "b");
        if (is_equal(value, getenv("b")))
        {
            printf("✅ Test %d\n", test_n);
            succeded_tests++;
        }
        else
        {
            printf("❌Test %d\n", test_n);
            failed_tests++;
        }
    }

    {
        test_n++;
        char *value = ft_get_env(env, "c");
        if (is_equal(value, getenv("c")))
        {
            printf("✅ Test %d\n", test_n);
            succeded_tests++;
        }
        else
        {
            printf("❌Test %d\n", test_n);
            failed_tests++;
        }
    }

    {
        test_n++;
        char *value = ft_get_env(env, "d");
        if (is_equal(value, getenv("d")))
        {
            printf("✅ Test %d\n", test_n);
            succeded_tests++;
        }
        else
        {
            printf("❌Test %d\n", test_n);
            failed_tests++;
        }
    }

    {
        test_n++;
        char *value = ft_get_env(env, "e");
        if (is_equal(value, getenv("e")))
        {
            printf("✅ Test %d\n", test_n);
            succeded_tests++;
        }
        else
        {
            printf("❌Test %d\n", test_n);
            failed_tests++;
        }
    }

    {
        test_n++;
        char *value = ft_get_env(env, "f");
        if (is_equal(value, getenv("f")))
        {
            printf("✅ Test %d\n", test_n);
            succeded_tests++;
        }
        else
        {
            printf("❌Test %d\n", test_n);
            failed_tests++;
        }
    }

    {
        test_n++;
        char *value = ft_get_env(env, "g");
        if (is_equal(value, getenv("g")))
        {
            printf("✅ Test %d\n", test_n);
            succeded_tests++;
        }
        else
        {
            printf("❌Test %d\n", test_n);
            failed_tests++;
        }
    }

    {
        test_n++;
        char *value = ft_get_env(env, "h");
        if (is_equal(value, getenv("h")))
        {
            printf("✅ Test %d\n", test_n);
            succeded_tests++;
        }
        else
        {
            printf("❌Test %d\n", test_n);
            failed_tests++;
        }
    }
}

int main(int c, char **v, char **env)
{
    {
        char **new_env = gb_get_all_env(env);
        get_env_test(new_env);
        ft_free_env(new_env);
        ft_malloc(0, GB_CLEAR);
    }

    {
        char **new_env = gb_get_all_env(env);
        set_env_test(&new_env);
        ft_free_env(new_env);
        ft_malloc(0, GB_CLEAR);
    }

    {
        char **new_env = gb_get_all_env(env);
        unset_env_test(&new_env);
        ft_free_env(new_env);
        ft_malloc(0, GB_CLEAR);
    }


    printf("Succeded tests: %d\n", succeded_tests);
    printf("Failed tests: %d\n", failed_tests);

    return (0);
}
