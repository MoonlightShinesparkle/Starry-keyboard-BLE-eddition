printf "%s" "Reboot pico? (y/n): "
read Response

if [[ "$Response" == "y" ]]; then
	echo "Rebooting..."
	picotool reboot -F
fi