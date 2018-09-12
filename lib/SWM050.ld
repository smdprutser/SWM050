


SECTIONS {
        . = 0x00000000;
        .text : {
                * (vectors);
		* (crt0);
		. = 0x000001FC;
		* (protection);
		* (.text);
		. = ALIGN(4);
		* (.rodata*);
		. = ALIGN(4);
        }
	end_rom = .;

        . = 0x20000000;
	start_ram = .;
        .data : AT (end_rom) { 
		* (.data); 
	}
	end_ram = .;
	data_size = end_ram - start_ram;

	sbss = .;
        .bss : {
             * (.bss);
        }
        ebss = .;
        bss_size = ebss - sbss;

}
