# https://www.gnu.org/software/gawk/manual/html_node/Numeric-Functions.html
awk 'BEGIN {
   # seed
   # If the argument x is omitted, as in ‘srand()’, then the current date and
   # time of day are used for a seed. This is the way to get random numbers
   # that are truly unpredictable. 
   srand()
   for (i=1;i<=1000;i++){
     print int(1 + rand() * 1000000)
   }
}'
