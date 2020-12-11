.name	"Booster !"
.comment "Alors la, si ca marche, trop content !  :)"


#	fork %:fork0
#
#
#
#

master:






live %66
	ld %0,r3
	ld %16777216,r6
#	ldi %:master,%0,r6
	ld %0,r5
	zjmp %:ready

ready:	sti r6,r3,%:ecriture

ecriture*:




