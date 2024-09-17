BIN=./bin
LOG=./log
EXT=./scripts

TST_SRC=./test/src
TST_INC=./test/inc
TST_RES=./test/res

CC=g++
CCFLAGS=-std=gnu++11 -O3 -static -fno-rtti -Wno-deprecated-register -Wno-return-type
INC=-I ./ -I ./inc/ -I ./cpu/ -I ./cpu/instructions/ -I ./cpu/decoder/ -I ./target/default/

TGT_CC=riscv64-unknown-linux-gnu-g++
TGT_LD=riscv64-unknown-linux-gnu-ld
TGT_COPY=riscv64-unknown-linux-gnu-objcopy
TGT_CCFLAGS=-DRISCV -static -Os -fomit-frame-pointer -ffixed-reg -nostartfiles -nostdlib -fPIC -fno-jump-tables -fno-align-functions
TGT_INC=-I ./ -I ./inc/ -I ./cpu/ -I ./cpu/instructions/ -I ./cpu/decoder/ -I ./target/riscv/

CROSS_AS=arm-none-eabi-as
CROSS_LD=arm-none-eabi-ld
CROSS_FLAGS=-I ${TST_INC}

TESTS=$(addprefix ${BIN}/, $(notdir $(patsubst %.s,%,$(sort $(wildcard ${TST_SRC}/*.s)))))
ARM2X=${BIN}/arm2x

all: ${BIN} ${LOG} ${ARM2X}

${ARM2X}: *.h ./*/*.h ./*/*/*.h
	@mkdir -p ${BIN}
	${CC} ${CCFLAGS} ${INC} main.cpp -o ${ARM2X}

${BIN}:
	@mkdir -p ${BIN}

${LOG}:
	@mkdir -p ${LOG}

${BIN}/%.o: ${TST_SRC}/%.s
	${CROSS_AS} ${CROSS_FLAGS} -o $@ $^

${BIN}/%: ${BIN}/%.o
	${CROSS_LD} -o $@ $^

microcode:
	${TGT_CC} ${TGT_CCFLAGS} ${TGT_INC} microcode.cpp -o ${BIN}/microcode.o
	${TGT_LD} -o ${BIN}/mapping.bin -T ${EXT}/microcode.ld ${BIN}/microcode.o
	${TGT_COPY} --dump-section .data=${BIN}/table.bin ${BIN}/mapping.bin
	${TGT_COPY} --dump-section .text=${BIN}/microcode.bin ${BIN}/mapping.bin

report:
	${TGT_CC} ${TGT_CCFLAGS} ${TGT_INC} -S microcode.cpp -o ${BIN}/microcode.s
	${EXT}/extract.sh ${BIN}/microcode.s ${BIN}/mapping.s
	cat ${BIN}/mapping.s | awk -f ${EXT}/script.awk | sed 's/:/ /g' | sort -rn -k2 > ${BIN}/histogram
	${EXT}/gen_hist.sh "${BIN}/histogram" "${BIN}/histogram.png" "ARM over RV64I" "#FF0000"

test: ${BIN} ${LOG} ${ARM2X} ${TESTS}
	@{  echo "************************* Tests ******************************"; \
		test_failed=0; \
		test_passed=0; \
		for test in ${TESTS}; do \
			result="${LOG}/$$(basename $$test).log"; \
			expected="${TST_RES}/$$(basename $$test).r"; \
			printf "Running $$test: "; \
			${ARM2X} $$test > $$result 2>&1; \
			errors=`diff -y --suppress-common-lines $$expected $$result | grep '^' | wc -l`; \
			if [ "$$errors" -eq 0 ]; then \
				printf "\033[0;32mPASSED\033[0m\n"; \
				test_passed=$$((test_passed+1)); \
			else \
				printf "\033[0;31mFAILED [$$errors errors]\033[0m\n"; \
				test_failed=$$((test_failed+1)); \
			fi; \
		done; \
		echo "*********************** Summary ******************************"; \
		echo "- $$test_passed tests passed"; \
		echo "- $$test_failed tests failed"; \
		echo "**************************************************************"; \
	}

run: ${ARM2X}
	cd bench/freestanding && make run

reset:
	@{  for test in ${TESTS}; do \
			echo "$${test} > ${TST_RES}/$$(basename $$test).r"; \
			qemu-arm-static $${test} > ${TST_RES}/$$(basename $$test).r; \
		done; \
	}

setup:
	sudo apt-get install qemu-user-static binutils-arm-linux-gnu* g++-multilib libc6-dev-i386

clean:
	rm -rf ${BIN}/* ${LOG}/*
	cd bench/freestanding && make clean

.PHONY: test
.PHONY: clean
.PHONY: all
.PHONY: microcode
