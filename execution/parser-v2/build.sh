cc  -c parser/*.c garbage_collector/garbage_collector.c builtin/*.c env/*.c -lreadline; 
ar -r libparser.a *.o;
rm *.o 

echo "\033[1;32m✅ Compilation successful!\033[0m"
# echo -e "\033[1;34mRun \033[1;33m./parser_test\033[0m"
# echo -e "\033[1;34mCall \033[1;33mft_init(s)\033[0m \033[1;34mto initialize the parser\033[0m"
# echo -e "\033[1;34mIf the return value is \033[1;31mNULL\033[0m, \033[1;34mthe initialization failed\033[0m"
# echo -e "\033[1;34mYou don't need to print any error message, the parser will print it for you\033[0m"
# echo -e "\033[1;34mYou have to call \033[1;33mft_malloc(0,1)\033[0m \033[1;34mto free all the memory allocated by the parser\033[0m"
