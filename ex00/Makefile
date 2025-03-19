NAME=btc

SRC=main.cpp BitcoinExchange.cpp

OBJ = $(SRC:.cpp=.o)

CXXFLAGS=-Wall -Wextra -Werror -std=c++98

all: $(NAME)

$(NAME) : $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME) 

re: fclean all

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)