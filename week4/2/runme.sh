# The program demonstrates the concept of fifo using two files reader and writer
# The writer will write to fifo and reader will read from it.
# The reader waits untill the writer writes in the fifo


./writer & 
./reader
