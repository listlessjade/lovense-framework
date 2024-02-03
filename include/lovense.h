#include <ArduinoBLE.h>
#include "command.h"

namespace Lovense

{
    using namespace Commands;
    static char scratch_buffer[128];

    inline bool on_off_to_bool(char *s)
    {
        return strcasecmp(s, "on") == 0;
    }
    // LOVENSE TYPES

    struct Identifier
    {
        const char *name;
        int firmware;
        const char *address;
    };

    struct AutoSwitchOpts
    {
        bool turn_off_on_disconnect;
        bool last_level_on_reconnect;
    };

    struct PresetLevels
    {
        int high;
        int med;
        int low;
    };

    struct BatchInfo
    {
        int year;
        int month;
        int day;
    };

    class LovenseHandler
    {
    public:
        virtual Identifier DeviceType() = 0;
        virtual int Battery() = 0;
        virtual void PowerOff() = 0;
        virtual int Status() = 0;
        virtual void Vibrate(int step) = 0;
        virtual AutoSwitchOpts GetAutoSwitch() = 0;
        virtual void SetAutoSwitch(AutoSwitchOpts settings) = 0;
        virtual bool GetLight() = 0;
        virtual void SetLight(bool state) = 0;
        virtual bool GetALight()
        {
            return false;
        };
        virtual void SetALight(bool state){};
        virtual PresetLevels GetLevels()
        {
            return PresetLevels{
                5, 10, 15};
        };
        virtual void SetLevel(int idx, int step){

        };
        virtual void RotateChange(){

        };
        virtual void Rotate(int step){

        };
        virtual void SetAbsoluteAirLevel(int step){

        };
        virtual void Inflate(int step){

        }; // Adds to current inflation level by <step>
        virtual void Deflate(int step){

        }; // Subtracts from current inflation level by <step>
        virtual BatchInfo GetBatch()
        {
            return BatchInfo{
                99,
                01,
                01};
        };
    };

    // BLE MANAGER
    //    =^.^=  =^.^=  =^.^=  =^.^=  =^.^=  =^.^=  =^.^=  =^.^=  =^.^=  =^.^=  =^.^=  =^.^=  =^.^=  =^.^=  =^.^=  =^.^=  =^.^=  =^.^=  =^.^=  =^.^=  =^.^=  =^.^=  =^.^=  =^.^=  =^.^=  =^.^=  =^.^=  =^.^=  =^.^=  =^.^=  =^.^=

    // static BLEService vibrator_service("0000fff0-0000-1000-8000-00805f9b34fb");
    static BLEService vibrator_service("54300001-0023-4bd4-bbd5-a6920e4c5653");
    // static BLECharacteristic lovense_tx("0000fff2-0000-1000-8000-00805f9b34fb", BLERead | BLENotify | BLEWrite | BLEWriteWithoutResponse, 32);
    // static BLECharacteristic lovense_rx("0000fff1-0000-1000-8000-00805f9b34fb", BLERead | BLENotify | BLEWrite | BLEWriteWithoutResponse, 32);
    static BLECharacteristic lovense_tx("54300002-0023-4bd4-bbd5-a6920e4c5653", BLERead | BLENotify | BLEWrite | BLEWriteWithoutResponse, 32);
    static BLECharacteristic lovense_rx("54300003-0023-4bd4-bbd5-a6920e4c5653", BLERead | BLENotify | BLEWrite | BLEWriteWithoutResponse, 32);
    static void *handler_ptr;

    template <typename T>
    class Manager
    {
    private:
    public:
        static void handle_message(BLEDevice central, BLECharacteristic characteristic)
        {
            T *handler = (T *)handler_ptr;

            Command cmd = Command(characteristic);

#if LOVENSE_LOG_LEVEL >= 3
            Serial.print("Command kind: ");
            Serial.println(command_kind_to_s(cmd.kind));
            Serial.print("Arguments: ");

            if (cmd.args_len() > 0)
            {
                Serial.print("[");
                Serial.print("\"");
                Serial.print(cmd.arg(0));
                Serial.print("\"");

                for (int i = 1; i < cmd.args_len(); i++)
                {
                    Serial.print(", \"");
                    Serial.print(cmd.arg(i));
                    Serial.print("\"");
                }

                Serial.println("]");
            }
            else
            {
                Serial.println("[]");
            }
#endif

            char output[128] = {'\0'};

            switch (cmd.kind)
            {
            case DeviceType:
            {
                Identifier i = handler->DeviceType();
                strcat(output, i.name);
                strcat(output, ":");
                strcat(output, itoa(i.firmware, scratch_buffer, 10));
                strcat(output, ":");
                strcat(output, i.address);
                break;
            }
            case Battery:
            {
                strcat(output, itoa(handler->Battery(), scratch_buffer, 10));
                break;
            }
            case PowerOff:
            {
                handler->PowerOff();
                strcat(output, "OK");
                break;
            }
            case Status:
            {
                strcat(output, "2");
                break;
            }
            case Vibrate:
            {
                handler->Vibrate(atoi(cmd.arg(0)));
                strcat(output, "OK");
                break;
            }
            case GetAutoSwitch:
            {
                strcat(output, "AutoSwith:");
                AutoSwitchOpts opts = handler->GetAutoSwitch();
                strcat(output, itoa(opts.turn_off_on_disconnect, scratch_buffer, 10));
                strcat(output, ":");
                strcat(output, itoa(opts.last_level_on_reconnect, scratch_buffer, 10));
                break;
            }
            case AutoSwitch:
            {
                handler->SetAutoSwitch(AutoSwitchOpts{on_off_to_bool(cmd.arg(0)), on_off_to_bool(cmd.arg(1))});
                strcat(output, "OK");
                break;
            }
            case GetLight:
            {
                strcat(output, "Light:");
                strcat(output, itoa(handler->GetLight(), scratch_buffer, 10));
                break;
            }
            case Light:
            {
                handler->SetLight(on_off_to_bool(cmd.arg(0)));
                strcat(output, "OK");
                break;
            }
            case GetALight:
            {
                strcat(output, "Alight:");
                strcat(output, itoa(handler->GetALight(), scratch_buffer, 10));
                break;
            }
            case ALight:
            {
                handler->SetLight(on_off_to_bool(cmd.arg(0)));
                strcat(output, "OK");
                break;
            }
            case GetLevel:
            {
                PresetLevels levels = handler->GetLevels();
                strcat(output, itoa(levels.low, scratch_buffer, 10));
                strcat(output, ",");
                strcat(output, itoa(levels.med, scratch_buffer, 10));
                strcat(output, ",");
                strcat(output, itoa(levels.high, scratch_buffer, 10));
                break;
            }
            case SetLevel:
            {
                handler->SetLevel(atoi(cmd.arg(0)), atoi(cmd.arg(1)));
                strcat(output, "OK");
                break;
            }
            }

            strcat(output, ";");
#if LOVENSE_LOG_LEVEL >= 2
            Serial.print("Sending back: ");
            Serial.println(output);
#endif
            lovense_rx.writeValue(output);
        }

        Manager(T *custom_handler, char *ble_name)
        {
            handler_ptr = (void *)custom_handler;

            BLE.begin();

            BLE.setLocalName(ble_name);
            BLE.setAdvertisedService(vibrator_service);
            vibrator_service.addCharacteristic(lovense_tx);
            vibrator_service.addCharacteristic(lovense_rx);
            BLE.addService(vibrator_service);

            lovense_rx.setEventHandler(BLEWritten, handle_message);
            lovense_tx.setEventHandler(BLEWritten, handle_message);

            BLE.advertise();
        }
    };
}
