funcoes_arq.o:
	gcc -c funcoes_arq.c -o funcoes_arq.o
funcoes_log.o:
	gcc -c funcoes_log.c -o funcoes_log.o
fun_reg_var.o:
	gcc -c fun_reg_var.c -o fun_reg_var.o
biblioteca: funcoes_arq.o funcoes_log.o fun_reg_var.o
	ar rvs libproject1.a funcoes_arq.o funcoes_log.o fun_reg_var.o
teste: biblioteca
	gcc teste.c -L. libproject1.a -o teste
	./teste
main: biblioteca
	gcc main.c -L. libproject1.a -o proj1
	./proj1
