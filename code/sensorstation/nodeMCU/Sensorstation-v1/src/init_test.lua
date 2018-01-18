print("Start")
wifi.mode(wifi.STATION)
wifi.start()
station_cfg={}
station_cfg.ssid="Apartment_EG_2.4GHz_new"
station_cfg.pwd="5455922329870587"
wifi.sta.config(station_cfg)

lines=0
if file.open("counter.txt", "r") then
    while file.readline()~=nil do
        lines=lines+1
    end
end
file.close()
if file.open("counter.txt", "a+") then
    file.writeline("X")
    lines=lines+1
end
file.close()

wifi.sta.on("got_ip", function(ev, info)
    print("Got IP:")
    print("IP: ", info.ip)
    wifi.sta.on("got_ip", nil)
    wifiReady()
    end
    )
    
function wifiReady()
    done=false;
    con = net.createConnection()
    con:on("receive", function(sck, c)
        print("RCV:",c)
        con:send("This is a test\n\r")
    end)
    con:on("connection", function(sck, c)
        print("Connected")
        --node.dsleep(10000000, 4)
    end)
    con:on("sent", function(sck, c)
        con:close()
    end)
    con:connect(8080, "192.168.5.154")
end
--http.get("192.168.5.154:8080", nil, function(code, data)+
