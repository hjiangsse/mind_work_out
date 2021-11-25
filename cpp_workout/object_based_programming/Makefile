default: class_hacking

little_stack.o: little_stack.cpp little_stack.h
	g++ -c little_stack.cpp -o little_stack.o

little_matrix.o: little_matrix.cpp little_matrix.h
	g++ -c little_matrix.cpp -o little_matrix.o

little_iterator.o: little_iterator.cpp little_iterator.h
	g++ -c little_iterator.cpp -o little_iterator.o
	
class_hacking.o: class_hacking.cpp
	g++ -c class_hacking.cpp -o class_hacking.o

class_hacking: little_stack.o little_matrix.o little_iterator.o class_hacking.o 
	g++ little_stack.o little_matrix.o little_iterator.o class_hacking.o -o class_hacking

clean:
	-rm -f *.o
	-rm -f *.gch
	-rm -f class_hacking