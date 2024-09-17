RES=./res
SRC=./src
LOG=./log
BIN=./bin
INPUT=./input
ARM2X=../../bin/arm2x

CC=arm-none-eabi-g++
CCFLAGS=-O2 -marm -nostartfiles -mno-thumb-interwork -msoft-float -static
CCINC=-I ./inc/

BENCHMARKS=$(addprefix ${BIN}/, $(notdir $(patsubst %.cpp,%,$(sort $(wildcard ${SRC}/*.cpp)))))

all: ${BIN} ${LOG} ${BENCHMARKS}

${BIN}/%: ${SRC}/%.cpp
	${CC} ${CCFLAGS} ${CCINC} -o $@ $^

${BIN}:
	@mkdir -p ${BIN}

${LOG}:
	@mkdir -p ${LOG}

run: ${BIN} ${LOG} ${BENCHMARKS}
	@{ \
		for bench in ${BENCHMARKS}; do \
			echo "Running $$bench: "; \
			cat ${INPUT}/$$(basename $$bench) | /usr/bin/time -f " - Real: %Es\n - User: %Us\n - System: %Ss" ${ARM2X} $$bench > ${LOG}/$$(basename $$bench).log; \
			result="${LOG}/$$(basename $$bench).log"; \
			expected="${RES}/$$(basename $$bench).r"; \
			errors=`diff -y --suppress-common-lines $$expected $$result | grep '^' | wc -l`; \
			if [ "$$errors" -eq 0 ]; then \
				printf " - status: \033[0;32mverified\033[0m\n\n"; \
				test_passed=$$((test_passed+1)); \
			else \
				printf " - status: \033[0;31merror\033[0m\n\n"; \
				test_failed=$$((test_failed+1)); \
			fi; \
		done; \
	}

clean:
	rm -rf ${BIN}/* ${LOG}/*

.PHONY: run
.PHONY: clean
.PHONY: all
