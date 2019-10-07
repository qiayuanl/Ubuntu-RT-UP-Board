# 1.Let system under stress
stress --cpu 4 --io 1 --vm 1  --vm-bytes 128M -d 1&
# 2. Run cyclictest
cyclictest -l500000 -m -Sp99 -i200 -h400 -q >output
# 3. Get maximum latency
max=`grep "Max Latencies" output | tr " " "\n" | sort -n |
tail -1 | sed s/^0*//`
# 4. Grep data lines, no empty lines a common field separator
grep -v -e "^#" -e "^$" output | tr " " "\t" >histogram
# 5. Set the number of cores, for example
cores=4
# 5. Create two-column data sets
for i in `seq 1 $cores`
do
  column=`expr $i + 1`
  cut -f1,$column histogram >histogram$i
done
# 6. Create plot command header
echo -n  "set title \"Latency plot\"\n\
set terminal png\n\
set xlabel \"Latency (us), max $max us\"\n\
set logscale y\n\
set xrange [0:400]\n\
set yrange [0.8:*]\n\
set ylabel \"Number of latency samples\"\n\
set output \"plot.png\"\n\
plot " >plotcmd
# 7. Append plot command data references
for i in `seq 1 $cores`
do
   if test $i != 1
   then
      echo -n ", " >>plotcmd
   fi
   cpuno=`expr $i - 1`
   if test $cpuno -lt 10
   then
      title=" CPU$cpuno"
   else
      title="CPU$cpuno"
   fi
   echo -n "\"histogram$i\" using 1:2 title \"$title\" with histeps" >>plotcmd
   done
# 8. Execute plot command
gnuplot -persist <plotcmd
rm  histogram*
rm output
rm plotcmd
killall stress
echo finish
