
install:
	mkdir -p /usr/share/bme280Server
	cp build/bme280Server /usr/share/bme280Server/
	chmod u+x /usr/share/bme280Server/bme280Server
	cp bme280Server.service /usr/share/bme280Server/
	$(shell test -e /etc/systemd/system/bme280Server.service | rm /etc/systemd/system/bme280Server.service)
	ln -s /usr/share/bme280Server/bme280Server.service /etc/systemd/system/bme280Server.service
	systemctl daemon-reload
	systemctl enable bme280Server.service
	systemctl start bme280Server.service
	
uninstall:
	systemctl stop bme280Server.service
	systemctl disable bme280Server.service
	systemctl daemon-reload
	rm /usr/share/bme280Server/bme280Server.service
