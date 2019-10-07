while true
do
	echo 1 > /sys/class/leds/upboard\:green\:/brightness
	sleep 0.1
	echo 0 > /sys/class/leds/upboard\:green\:/brightness
	sleep 0.1
done
