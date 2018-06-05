#include <Wire.h>
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
    bool online[128];
    byte device_count = 0;
    
    for (address = 1; address < 127; address++)
    {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
		
        if (error == 0)
        {
            online[address] = true;
            device_count++;
        }
    }
    
    msgpck_write_array_header(&Serial, device_count+1);
    msgpck_write_integer(&Serial, MSG_I2C_SCAN_RESULT);
    for (address = 1; address < 127; address++)
    {
        if (online[address])
            msgpck_write_integer(&Serial, address);
    }
    
    return (true);
}
