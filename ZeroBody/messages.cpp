#include <Wire.h>
#include <MechaQMC5883.h>
#include "messages.h"
#include "commands.h"
#include "util.h"

bool handle_incoming_message(uint8_t message_type)
{
    switch (message_type)
    {
        case MSG_PING:
            DBG("got ping message\n");
            return (send_msg_pong());

        case MSG_CMD:
            uint8_t cmd_type;
            msgpck_read_integer(&Serial, &cmd_type, 1);
            DBG("got cmd message type: %d\n", cmd_type);
            return (handle_incoming_command(cmd_type));
            
        case MSG_I2C_SCAN:
            DBG("Scanning i2c bus\n");
            return (send_i2c_scan());
                        
        default:
            break;
    }
    return (send_msg_unknown());
}

bool send_msg_pong()
{
    msgpck_read_integer(&Serial, &body_health.last_ping_seq, 1);
    msgpck_write_array_header(&Serial,2);
    msgpck_write_integer(&Serial, MSG_PONG);
    msgpck_write_integer(&Serial, body_health.last_ping_seq);
    return (true);
}

bool send_msg_unknown()
{
    msgpck_write_array_header(&Serial, 1);
    msgpck_write_integer(&Serial, MSG_UNKNOWN);
    return (true);
}

bool send_i2c_scan()
{
    byte address;
    byte error;
    byte online[128];
    byte device_count = 0;
    
    for (address = 1; address < 127; address++)
    {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
		
        if (error == 0)
        {
            online[device_count] = address;
            device_count++;
        }
        else
        {
            online[address] = false;
        }
    }
    
    msgpck_write_array_header(&Serial, device_count+2);
    msgpck_write_integer(&Serial, MSG_I2C_SCAN_RESULT);
    msgpck_write_integer(&Serial, device_count);
    
    for (int i = 0; i < device_count; i++)
    {
        msgpck_write_integer(&Serial, online[i]);
    }
    
    msgpck_write_nil(&Serial);
    
    return (true);
}

bool send_health_update()
{
    msgpck_write_array_header(&Serial, 2);
    msgpck_write_integer(&Serial, MSG_HEALTH_UPDATE);
    msgpck_write_bin(&Serial, (uint8_t *)&body_health, sizeof(body_health));
    
    return (true);
}