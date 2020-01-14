USB_LINK=/dev/ttyUSB0

install_board:
	arduino-cli  core update-index --additional-urls https://arduino.esp8266.com/stable/package_esp8266com_index.json
	arduino-cli board install esp8266:esp8266:generic
compile:
	arduino-cli compile --fqbn esp8266:esp8266:generic
upload:
	arduino-cli upload -p $(USB_LINK) --fqbn esp8266:esp8266:generic
clean:
	rm -rf *.elf *.bin

