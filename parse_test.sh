#!/bin/bash
set -uo pipefail

# ANSI color codes for output
COLOR_GREEN="\033[0;32m"
COLOR_RED="\033[0;31m"
COLOR_YELLOW="\033[1;33m"
COLOR_RESET="\033[0m"

# Set environment variables
export a="AA"
export b="BB"
export c="CC"
export s="first second third"
export t="  first  second  third  "
export u="first second  "
export v="  first3"
export w="  f 'g h i'  "
export x="  f' g h 'i"
export y="f\"ghi\""
export z="f\" g hi\""
export wa=" f\"g hi\"i'j k l'"
export wb="  leadind_space"
export wc="trailing_space  "
export wd="  both_space  "

# Global counter for failures
total_failures=0

# Store failed test details for summary
declare -a failed_tests_details=()
declare -a failed_tests_numbers=()

# Function to print a colored header
print_header() {
  echo -e "\n${COLOR_YELLOW}==> $1 ${COLOR_RESET}\n"
}

# Function to run tests with simplified output for failures
run_test() {
	local test_number=$3
	local command="$1"
	local expected_output="$2"
	
	# Run the test command and redirect stderr to stdout
	result=$(./test "$command" 2>&1)
	# Properly trim whitespace while preserving internal spaces.
	# Convert newlines to spaces and trim trailing whitespace.
	result=$(echo "$result" | tr '\n' ' ' | sed 's/ *$//')

	expected_output=$(echo "$expected_output" | tr '\n' ' ' | sed 's/ *$//')
	
	# Compare output with expected output
	if [ "$result" = "$expected_output" ]; then
		echo -e "${COLOR_GREEN}✅ Passed:${COLOR_RESET} Test #$test_number"
	else
		echo -e "${COLOR_RED}❌ Failed:${COLOR_RESET} Test #$test_number"
		total_failures=$((total_failures + 1))
		
		# Store failed test details for summary
		failed_tests_numbers+=("$test_number")
		failed_tests_details+=("Test #$test_number: $command
----------------------------------------
Expected:
\"$expected_output\"
----------------------------------------
Got:
\"$result\"
----------------------------------------")
	fi
}

# Define test cases grouped by category.
test_cases() {
	print_header "Basic tests"
	# Test case 1
	run_test "ls" "No files
cmds: {ls}" 1
	
	# Test case 2
	run_test "grep hello < text.txt >> output.log" "file: text.txt
type: REDIRECT_INPUT
is_ambs: false
file: output.log
type: APPEND
is_ambs: false
cmds: {grep} {hello}" 2
	
	# Test case 3
	run_test "cat < EOF | wc -l > result.txt" "pipes: 
file: EOF
type: REDIRECT_INPUT
is_ambs: false
cmds: {cat} 

file: result.txt
type: REDIRECT_OUTPUT
is_ambs: false
cmds: {wc} {-l}" 3
	
	# Test case 4
	run_test "l's' < inf'ile' >> out'fi'le\$ -l -a >> last'file'" "file: infile
type: REDIRECT_INPUT
is_ambs: false
file: outfile\$
type: APPEND
is_ambs: false
file: lastfile
type: APPEND
is_ambs: false
cmds: {ls} {-l} {-a}" 4
	
	# Test case 5
	run_test "echo 'hello 'world 'how are''you' >> out_?file" "file: out_?file
type: APPEND
is_ambs: false
cmds: {echo} {hello world} {how areyou}" 5
	
	# Test case 6
	run_test "echo \$a<in\$b>out\$c | a=\$s" "pipes: 
file: inBB
type: REDIRECT_INPUT
is_ambs: false
file: outCC
type: REDIRECT_OUTPUT
is_ambs: false
cmds: {echo} {AA} 

No files
cmds: {a=first second third}" 6
	
	# Test case 7
	run_test "echo \$t | wc -w > out\$c" "pipes: 
No files
cmds: {echo} {first} {second} {third} 

file: outCC
type: REDIRECT_OUTPUT
is_ambs: false
cmds: {wc} {-w}" 7
	
	# Test case 8
	run_test "echo \$u | wc -w > out\$c" "pipes: 
No files
cmds: {echo} {first} {second} 

file: outCC
type: REDIRECT_OUTPUT
is_ambs: false
cmds: {wc} {-w}" 8
	
	# Test case 9
	run_test "export a=\$a\"ok\" < inf\"file\"\$a\$s" "file: inffile$a$s
type: REDIRECT_INPUT
is_ambs: true
cmds: {export} {a=AAok}" 9
	
	# Test case 10
	run_test "export a=\$a\"ok\" < inf\"file\"\$a\$s | a=\$s" "pipes: 
file: inffile$a$s
type: REDIRECT_INPUT
is_ambs: true
cmds: {export} {a=AAok} 

No files
cmds: {a=first second third}" 10
	
	# Test case 11
	run_test "export a=\$a\"ok\" < inf\"file\"\$a\$s | a=\$s | a=\$u" "pipes: 
file: inffile$a$s
type: REDIRECT_INPUT
is_ambs: true
cmds: {export} {a=AAok} 

No files
cmds: {a=first second third} 

No files
cmds: {a=first second  }" 11
	
	# Test case 12
	run_test "export a=\$a\"ok\" < inf\"file\"\$a\$s | a=\$s | a=\$u | a=\$v >> out\$c >> out\"file\"" "pipes: 
file: inffile$a$s
type: REDIRECT_INPUT
is_ambs: true
cmds: {export} {a=AAok} 

No files
cmds: {a=first second third} 

No files
cmds: {a=first second  } 

file: outCC
type: APPEND
is_ambs: false
file: outfile
type: APPEND
is_ambs: false
cmds: {a=  first3}" 12
	
	# Test case 13
	run_test "\$df | \$df | \$df" "pipes: 
No files
No cmds

No files
No cmds

No files
No cmds" 13
	
	# Test case 14
	run_test "echo \$a | echo \$b | echo \$c" "pipes: 
No files
cmds: {echo} {AA} 

No files
cmds: {echo} {BB} 

No files
cmds: {echo} {CC}" 14
	
	# Test case 15
	run_test "> \$a\$b\"\" ls -la" "file: AABB
type: REDIRECT_OUTPUT
is_ambs: false
cmds: {ls} {-la}" 15
	
	# Test case 16
	run_test "< \$df\$df\"u\" export var=\$s<in" "file: u
type: REDIRECT_INPUT
is_ambs: false
file: in
type: REDIRECT_INPUT
is_ambs: false
cmds: {export} {var=first second third}" 16
	
	# Test case 17
	run_test "echo '\"hello\"' '\"world\"' >> \"out'file'\"" "file: out'file'
type: APPEND
is_ambs: false
cmds: {echo} {\"hello\"} {\"world\"}" 17
	
	# Test case 18
	run_test "echo '\"hello world\"' | grep '\"hello\"'" "pipes: 
No files
cmds: {echo} {\"hello world\"} 

No files
cmds: {grep} {\"hello\"}" 18
	
	# Test case 19
	run_test "cat <EOF | grep '\"pattern\"' >> \"out'file'\"" "pipes: 
file: EOF
type: REDIRECT_INPUT
is_ambs: false
cmds: {cat} 

file: out'file'
type: APPEND
is_ambs: false
cmds: {grep} {\"pattern\"}" 19
	
	print_header "Ambiguous tests"
	# Test case 20
	run_test "< \$v" "file: $v
type: REDIRECT_INPUT
is_ambs: false
No cmds" 20
	
	# Test case 21
	run_test "< \$w" "file: \$w
type: REDIRECT_INPUT
is_ambs: true
No cmds" 21
	
	# Test case 22
	run_test "< \$x" "file: \$x
type: REDIRECT_INPUT
is_ambs: true
No cmds" 22
	
	# Test case 23
	run_test "< \$y" "file: $y
type: REDIRECT_INPUT
is_ambs: false
No cmds" 23
	
	# Test case 24
	run_test "< \$z" "file: \$z
type: REDIRECT_INPUT
is_ambs: true
No cmds" 24
	
	# Test case 25
	run_test "< \$wa" "file: \$wa
type: REDIRECT_INPUT
is_ambs: true
No cmds" 25
	
	# Test case 26
	run_test "< \$wb" "file: $wb
type: REDIRECT_INPUT
is_ambs: false
No cmds" 26
	
	# Test case 27
	run_test "< \$w\" lead\""  "file: \$w\" lead\"
type: REDIRECT_INPUT
is_ambs: true
No cmds" 27
	
	# Test case 28
	run_test "< \"ts \"\$x" "file: \"ts \"\$x
type: REDIRECT_INPUT
is_ambs: true
No cmds" 28
	
	# Test case 29
	run_test "< \"  tricky\"\$c" "file:   tricky$c
type: REDIRECT_INPUT
is_ambs: false
No cmds" 29
	
	# Test case 30
	run_test "< \"  t\"\$c\"  t\"" "file:   t\$c  
type: REDIRECT_INPUT
is_ambs: false
No cmds" 30
	
	print_header "Syntax error tests"
	# Test case 31
	run_test "echo \$a | | echo \$b" "minishell: syntax error: unexpected token \`|'" 31
	
	# Test case 32
	run_test "echo \$a | echo \$b |" "minishell: syntax error: unexpected token \`newline'" 32
	
	# Test case 33
	run_test "echo \$a | echo \$b | echo \$c |" "minishell: syntax error: unexpected token \`newline'" 33
	
	# Test case 34
	run_test "<|ls" "minishell: syntax error: unexpected token \`|'" 34
	
	# Test case 35
	run_test "<< < ls | ok" "minishell: syntax error: unexpected token \`<'" 35
	
	# Test case 36
	run_test ">>> out < in" "minishell: syntax error: unexpected token \`>'" 36
	
	# Test case 37
	run_test "out < in >  " "minishell: syntax error: unexpected token \`newline'" 37
	
	# Test case 38
	run_test "in <<o>>i<<o>>                 o>         " "minishell: syntax error: unexpected token \`newline'" 38
	
	# Test case 39
	run_test ">>|< in     " "minishell: syntax error: unexpected token \`|'" 39


	echo -e "\n${COLOR_YELLOW}Env tests${COLOR_RESET}"
	# Test case 40
	run_test "\$undef \$undef \$undef \$undef \$undef" "No files
No cmds" 40

	# Test case 41
	run_test " " "" 41

	# Test case 42
	run_test "\$s\" heloo \"" "No files
cmds: {first} {second} {third heloo }" 42

	# Test case 43
	run_test "      		" "" 43

	# Test case 44
	run_test "ok\$a\"\"Bye" "No files
cmds: {okAABye}" 44

	# Test case 45
	run_test "F\$s?F" "No files
cmds: {Ffirst} {second} {third?F}" 45

	# Test case 46
	run_test "$a=$a" "No files
cmds: {AA=AA}" 46
	
}

# Run all tests
print_header "Running All Tests..."
test_cases

# Print summary of failed tests
echo -e "\n${COLOR_YELLOW}Test Summary${COLOR_RESET}"
if [ "$total_failures" -ne 0 ]; then
  echo -e "${COLOR_RED}Total failures: $total_failures${COLOR_RESET}"
  echo -e "\n${COLOR_YELLOW}Failed Tests Details:${COLOR_RESET}"
  
#   for ((i=0; i<${#failed_tests_numbers[@]}; i++)); do
#     echo -e "${COLOR_RED}Failed Test #${failed_tests_numbers[$i]}${COLOR_RESET}"
#     echo -e "${failed_tests_details[$i]}"
#     echo ""
#   done
else
  echo -e "${COLOR_GREEN}All tests passed successfully!${COLOR_RESET}"
fi

# Current Date and Time info
echo -e "\n${COLOR_YELLOW}Test Run Information:${COLOR_RESET}"
echo "Date/Time (UTC): 2025-03-23 08:54:10"
echo "Run by: jawadelyousfi17"