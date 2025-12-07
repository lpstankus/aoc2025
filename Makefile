CC := gcc
CFLAGS := -Wall -Wextra -std=gnu99 -O3

DAYS := $(patsubst src/day%/main.c,%,$(wildcard src/day*/main.c))
DAYS := $(sort $(DAYS))

all: $(DAYS)

out:
	@mkdir -p $@

day%: src/day%/main.c | out
	$(CC) $(CFLAGS) $(CPPFLAGS) $< -o out/$@

run-day%: day%
	@out/$<

bench-day%: day%
	hyperfine ./out/$<

benchmark: $(addprefix bench-day,$(DAYS))

clean:
	@rm -rf out

help:
	@echo "AOC 2025 Makefile"
	@echo "Available days: $(DAYS)"
	@echo ""
	@echo "Targets:"
	@echo "  make all          - Build all days"
	@echo "  make day<N>       - Build day N"
	@echo "  make run-day<N>   - Run day N"
	@echo "  make benchmark    - Benchmark all days"
	@echo "  make bench-day<N> - Benchmark day N"
	@echo "  make clean        - Clean build artifacts"

.PHONY: all day% run-day% benchmark bench-day% clean help
