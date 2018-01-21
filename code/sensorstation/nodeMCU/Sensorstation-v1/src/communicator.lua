gbl = {}
gbl["DEV_ID"] = "AB:AB:AB:AB"
gbl["SSID"] = "Apartment_EG_2.4GHz_new"
gbl["WIFI_KEY"] = "5455922329870587"
gbl["SERVER_PORT"] = 8080
 
function string:split(sep)
   local sep, fields = sep or ":", {}
   local pattern = string.format("([^%s]+)", sep)
   self:gsub(pattern, function(c) fields[#fields+1] = c end)
   return fields
end
 
Command = {
  devID = gbl["DEV_ID"],
  cmdValues = {}
}
  
function Command:new (o)
  o = o or {}   -- create object if user does not provide one
  setmetatable(o, self)
  self.__index = self
  return o
end  

function Command:parse(cmdString)
  local cmd_split = cmdString:split(";")  
  self.devID = cmd_split[1]
  self.cmdID = cmd_split[2]
  self.cmdArg = cmd_split[3]
  self.cmdValues = cmd_split[4]:split(",")
end

function Command.createString(cmdID, cmdArg, cmdValues)
  return table.concat({gbl["DEV_ID"], cmdID, cmdArg, table.concat(cmdValues, ",")}, ";")
end

function Command:toString()
  return table.concat({self.devID, self.cmdID, self.cmdArg, table.concat(self.cmdValues, ",")}, ";")
end

function Command:setID(cmdID)
  self.cmdID = cmdID
end

function Command:setArg(cmdArg)
  self.cmdArg = cmdArg
end

function Command:setValues(cmdValues)
  self.cmdValues = cmdValues
end

function Command:addValue(cmdValue)
  self.cmdValues[#self.cmdValues+1] = cmdValue
end

function Command:print()
  print("Device ID: ", "", self.devID)
  print("Command ID: ", "", self.cmdID)
  print("Command Arguments: ", self.cmdArg)
  print("Command Values: ")
  print("", "#", "Value")
  for i, value in pairs(self.cmdValues) do print("", i, value) end 
end

 
Connection = {
  ip = nil,
  station_cfg={},
  --station_cfg.ssid=gbl["SSID"],
  --station_cfg.pwd=gbl["WIFI_KEY"]
}

function Connection.setup() 
  wifi.mode(wifi.STATION)
  wifi.start()
  wifi.sta.config(Connection.station_cfg)
  wifi.sta.on("got_ip", function(ev, info)
    Connection.client_ip = info.ip
    --Connection.server_ip = info.gw
    Connection.server_ip = "192.168.5.154"
    wifi.sta.on("got_ip", nil)
    end
  )
end

function Connection.communicate()
  -- Wait for wifi connection is fully established and got a ip from server 
  if Connection.client_ip == nil then
    local mtmr = tmr.create()
    mtmr:alarm(1000, tmr.ALARM_AUTO, function() 
      if not Connection.client_ip == nil then
        mtmr:stop()
      end
    end)
  end
  local con = net.createConnection()
    con:on("receive", function(sck, c)
      -- TODO: implement command receiving
      cmd = Command:new()
      cmd:parse(c)
      cmd:print()
      -- TODO: implement command sending
      con:send("Test")
    end)
    con:on("connection", function(sck, c)
        --con:close()
        --node.dsleep(10000000, 4)
    end)
    con:on("sent", function(sck, c)
        con:close()
    end)
    con:connect(gbl["SERVER_PORT"], Connection.server_ip)
end
  
 cmd1 = "XX:XX:XX:XX;0;0;1.000,2.000"
 c2 = Command:new()
 c2:setID(13)
 c2:setArg("ARGH")
 c2:addValue(1.4123)
 c2:addValue(4.123)
 print(c2:toString())
 
 c1 = Command:new()
 c1:parse(cmd1)
 c1:print()
 print(c1:toString())
 print(c2:toString())
 
 print(Command.createString(123, "ADS", {1.5, 2.1}))