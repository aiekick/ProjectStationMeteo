
install:
	mkdir -p /usr/share/bme280Server
	cp build/bme280Server /usr/share/bme280Server/
	chmod u+x /usr/share/bme280Server/bme280Server
	cp bme280Server.service /usr/share/bme280Server/
	$(shell test -e | rm /etc/systemd/system/bme280Server.service)	
	ln -s /usr/share/bme280Server/bme280Server.service /etc/systemd/system/bme280Server.service
	sudo systemctl daemon-reload
	sudo systemctl enable bme280Server.service
	sudo systemctl start bme280Server.service

