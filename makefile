traba2: traba2.o my_date.o medico.o paciente.o consulta.o
	gcc -o traba2 traba2.o my_date.o medico.o paciente.o consulta.o
	
traba2.o: traba2.c medico.h paciente.h consulta.h
	gcc -c traba2.c

medico.o: medico.c medico.h
	gcc -c medico.c
	
paciente.o: paciente.c paciente.h
	gcc -c paciente.c

consulta.o: consulta.c consulta.h medico.h paciente.h my_date.h
	gcc -c consulta.c
	
my_date.o: my_date.c my_date.h
	gcc -c my_date.c
