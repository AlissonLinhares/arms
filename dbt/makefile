all:
	arm-none-eabi-g++ -nostartfiles arm.s
	arm-linux-gnueabi-objcopy -O binary --only-section=.text a.out arm.raw
	arm-linux-gnueabi-objdump -D -b binary -marm arm.raw
	g++ -O3 -Wall main.cpp
	./a.out ../bin/microcode.bin ../bin/table.bin arm.raw > riscv.raw
	echo ".data\n.text\n.globl _start\n_start:\n" > riscv.s
	~/Unicamp/riscv/riscv/bin/riscv64-unknown-linux-gnu-objdump -D -b binary -mriscv riscv.raw | tail -n +8 | cut -d'	' -f3- | sed "s/^0x/.word\ 0x/g" >> riscv.s
	~/Unicamp/riscv/riscv/bin/riscv64-unknown-linux-gnu-gcc -nostdlib -nostartfiles riscv.s
	~/Unicamp/riscv/riscv/bin/riscv64-unknown-linux-gnu-objdump -D a.out
	mv a.out ~/Unicamp/phd/gem5/tests/test-progs/hello/bin/riscv/linux/hello
	cd ~/Unicamp/phd/gem5 && make run

clean:
	rm *.raw
	rm *.out

