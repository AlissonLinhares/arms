SECTIONS {
	. = 0;

	.text : ALIGN(4k) {
		*(.text)
	} = 0

	.data : ALIGN(4k) {
		*(.data)
	} = 0

	/DISCARD/ : {
		*(.comment)
		*(.bss)
		*(COMMON)
		*(.rodata)
		*(.eh_frame)
	}
}
