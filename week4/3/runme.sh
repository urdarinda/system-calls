# The program demonstrates the concept of fifo using multiple clients and a server
# The client echoes something to server
# The server returns the echo
# 
if [ $# != 1 ]; then
    echo "Usage : runme [no. of clients]"
    exit;
fi

./server $1 &

for(( i=$1 ; i>0 ; i--))
do
./client
done
