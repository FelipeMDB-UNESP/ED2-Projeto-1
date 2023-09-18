funcoes_log.o:
	gcc -c funcoes_log.c -o funcoes_log.o
biblioteca: funcoes_log.o
	ar rvs libproject1.a funcoes_log.o
teste: biblioteca
	gcc teste_log.c -L. libproject1.a -o teste
final_teste: teste
	./teste