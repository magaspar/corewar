.name "Shenron"
.comment "I will wait no longer Do you have a wish or not"

fwall:
		live %0
		live %0
		live %0
		live %0
		ld 9,r4
		ld 900,r5
		sti r4, r5, %0
		sub r5, r1, r5
		ld 0,r2
		zjmp %:fwall
