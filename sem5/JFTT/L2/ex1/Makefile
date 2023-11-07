ex1: ex1.c
	gcc $< -o $@
ex1.c: ex1.l
	flex -o $@ $<
test1: test1.c
	gcc $< -o $@
test1.c: test1.l
	flex -o $@ $<
	
clean:
	rm ex1
	rm ex1.c
