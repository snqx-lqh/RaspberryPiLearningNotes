objects = block.o command.o input.o main.o scene.o test.o

sudoku: $(objects)
	g++ -o $@ $(objects)

%.o: %.cpp  
	g++ -c $<

clean:
	rm $(objects)
	rm sudoku 