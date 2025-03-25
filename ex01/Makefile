NAME=RPN

SRC=main.cpp RPN.cpp

OBJ = $(SRC:.cpp=.o)

CXXFLAGS=-Wall -Wextra -Werror -std=c++98

all: $(NAME)

$(NAME) : $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME) 

test: all
	@printf "\n\033[32m1. Subject tests\033[0m\n\n"

	./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"	# 8 * 9 - 9 - 9 - 9 - 4 + 1 = 42
	./RPN "7 7 * 7 -"					# 7 * 7 - 7 = 42
	./RPN "1 2 * 2 / 2 * 2 4 - +"		# ((1 * 2) / 2) * 2 + 2 - 4 = 0
	./RPN "(1 + 1)" || true				# Error!

	@printf "\n\033[31m2. Validation tests\033[0m\n\n"
	
	./RPN "3 +" || true  	  		# Error! Not enough digits.
	./RPN "3 4 + 4" || true      	# Error! Not enough operations.
	./RPN "3 a + 4 -" || true      	# Error! Invalid key.
	./RPN "3 4 + 4 &" || true      	# Error! Invalid key.
	./RPN "3 4 + 40" || true      	# Error! Invalid key.

	@printf "\n\033[34m3. Personal tests\033[0m\n\n"

	./RPN ""         	   #
	./RPN "3"         	   # 3
	./RPN "3 3 +"          # 3 + 3 = 6
	./RPN "3 -3 +"         # 3 + (-3) = 0
	./RPN "9 5 -"          # 9 - 5 = 4
	./RPN "6 4 *"          # 6 * 4 = 24
	./RPN "8 2 /"          # 8 / 2 = 4
	./RPN "1 2 + 3 +"      # (1 + 2) + 3 = 6
	./RPN "9 2 5 * +"      # 9 + (2 * 5) = 19
	./RPN "5 5 / 2 +"      # (5 / 5) + 2 = 3
	./RPN "9 7 5 / -"      # 9 - (7 / 5) = 7.6
	./RPN "9 3 / 2 *"      # (9 / 3) * 2 = 6
	./RPN "5 1 2 + 4 * +"  # 5 + ((1 + 2) * 4) = 17
	./RPN "5 -6 2 + 4 * +" # 5 + ((-6 + 2) * 4) = -11


re: fclean all

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)