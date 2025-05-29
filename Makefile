CC=clang
NAME=dlci
SRC := $(wildcard *.c)
OBJ := $(SRC:.c=.o)

COUNT := $(words $(OBJ))
$(eval COUNT := $(shell echo $$(($(COUNT) + 1))))
I := 0

CFLAGS := -I/opt/homebrew/opt/ncurses/include \
		  -I/opt/homebrew/opt/curl/include/curl

LDFLAGS := -L/opt/homebrew/opt/curl/lib \
		   -L/opt/homebrew/opt/ncurses/lib

LDLIBS := -lncurses -lcurl

DESTDIR=$(shell pwd)/dist

GREEN := \033[0;32m
NC := \033[0m

all: echovars $(NAME) git

$(NAME): $(OBJ)
	$(eval I := $(shell echo $$(($(I) + 1))))
	@printf "\r[%s/%s] LD: %s" "$(I)" "$(COUNT)" "$@"
	@$(CC) $(OBJ) $(LDFLAGS) -o $(NAME) $(LDLIBS)
	@echo "\n\n"

%.o: %.c
	$(eval I := $(shell echo $$(($(I) + 1))))
	@printf "\r[%s/%s] CC: %s" "$(I)" "$(COUNT)" "$<"
	@$(CC) $(CFLAGS) -c $< -o $@

install: $(NAME)
	@ if [ ! -d $(DESTDIR) ]; then \
		mkdir -p $(DESTDIR); \
	  fi
	@echo "CP: $(NAME)"
	@cp $(NAME) $(DESTDIR)/$(NAME) 2>/dev/null

test: $(NAME)
	./dist/dlci

clean:
	@echo "RM: dlci $(wildcard *.o dist)"
	@rm -rf dlci $(wildcard *.o) dist

git:
	@git add .
	@git status
	@echo "$(GREEN)Committing Changes$(NC)"
	@git commit -m "Updated $(shell date)" > /dev/null 2>&1
	@echo "$(GREEN)Pushing Changes$(NC)"
	@git push origin main > /dev/null 2>&1

echovars:
	@echo "$(GREEN)C Compiler:$(NC) $(CC)"
	@echo "$(GREEN)Name:$(NC) $(NAME)"
	@echo "$(GREEN)Source Files:$(NC) $(SRC)"
	@echo "$(GREEN)Compiled Object Files:$(NC) $(OBJ)"
	@echo "\n"
	@echo "$(GREEN)Compiler Flags:$(NC) $(CFLAGS)"
	@echo "$(GREEN)Linker Flags:$(NC) $(LDFLAGS)"
	@echo "$(GREEN)Linker Library Flags:$(NC) $(LDLIBS)"
	@echo "\n"
	@echo "$(GREEN)Destination Directory:$(NC) $(DESTDIR)"
	@echo "\n\n"

.PHONY: clean install all test git echovars