;
;	Program ro count occurrences of a character in a file.
;	Character to be input from the keyboard.
;	Result to be displayed on the monitor.
;	Program works only if no more than 9 occurences are found.
;
;
;	Initilization
;
		.ORIG	x3000
		AND		R2, R2, #0
		LD		R3, PTR
		TRAP	x23
		LDR		R1, R3, #0
;
;	Test character for end of file
;
TEST	ADD		R4, R1, #-4
		BRz		OUTPUT

;
;	Test character for match. If a match, increment count.
;
	
NOT		R1, R1
		ADD		R1, R1, R0
		NOT		R1, R1
		BRnp	GETCHAR
		ADD		R2, R2, #1
;
;	Get next character from the file.
;
GETCHAR	ADD		R3, R3, #1
		LDR		R1, R3, #0
		BRnzp	TEST

;
;	Output the count.
;
OUTPUT	LD		R0, ASCII
		ADD		R0, R0, R2
		TRAP	x21
		TRAP	x25

;
;	Storage for pointer and ASCII template
;
ASCII	.FILL	x0030
PTR		.FILL	x4000
		.END


