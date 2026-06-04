NAME = piscine-simulator

CC = cc
CFLAGS = -Wall -Wextra -Werror -I include -D_GNU_SOURCE

SRC_DIR = src
BUILD_DIR = build

SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/engine/exam_engine.c \
       $(SRC_DIR)/engine/level_engine.c \
       $(SRC_DIR)/engine/score_engine.c \
       $(SRC_DIR)/engine/runner.c \
       $(SRC_DIR)/core/exam_init.c \
       $(SRC_DIR)/core/level_init.c \
       $(SRC_DIR)/core/exercise_loader.c \
       $(SRC_DIR)/core/exercise.c \
       $(SRC_DIR)/core/exam.c\
       $(SRC_DIR)/core/config_loader.c \
       $(SRC_DIR)/logic/random_picker.c \
       $(SRC_DIR)/logic/validator.c \
       $(SRC_DIR)/logic/retry_system.c \
       $(SRC_DIR)/logic/progression.c \
       $(SRC_DIR)/ui/display.c \
       $(SRC_DIR)/ui/banner.c \
       $(SRC_DIR)/ui/progress_bar.c \
       $(SRC_DIR)/ui/certificate.c \
       $(SRC_DIR)/ui/menu.c \
       $(SRC_DIR)/io/input_handler.c \
       $(SRC_DIR)/io/file_reader.c \
       $(SRC_DIR)/io/logger.c \
       $(SRC_DIR)/utils/strings.c \
       $(SRC_DIR)/utils/memory.c \
       $(SRC_DIR)/utils/time.c \
       $(SRC_DIR)/grader/grader.c \
       $(SRC_DIR)/grader/exercise_grader.c \
       $(SRC_DIR)/grader/grading_handler.c

OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))
TEST_OBJS = $(filter-out $(BUILD_DIR)/main.o,$(OBJS))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
	rm -f test_score test_levels test_engine

fclean: clean
	rm -f $(NAME)

re: fclean all

run: $(NAME)
	./$(NAME)

test: $(NAME)
	@mkdir -p ./trace
	@echo "Running unit tests..."
	@$(CC) $(CFLAGS) tests/test_score.c $(TEST_OBJS) -o test_score
	@./test_score
	@echo ""
	@$(CC) $(CFLAGS) tests/test_levels.c $(TEST_OBJS) -o test_levels
	@./test_levels
	@echo ""
	@$(CC) $(CFLAGS) tests/test_engine.c $(TEST_OBJS) -o test_engine
	@./test_engine
	@echo ""
	@echo "Test logs saved in ./trace/"
	@echo ""
	@cat ./trace/test_score.log
	@echo ""
	@cat ./trace/test_levels.log
	@echo ""
	@cat ./trace/test_engine.log

.PHONY: all clean fclean re run test
