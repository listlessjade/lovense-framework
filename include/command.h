#include "command_hash.h"
#include <ArduinoBLE.h>

namespace Commands {
    static char input_buffer[128];


    class Command
    {
        private:
        char argv[3][32] = { { '\0' }, { '\0' }, { '\0' } };
        int arg_num = 0;

        public:
        CommandKind kind;
        
        Command(BLECharacteristic characteristic) {
            char *src = (char *)characteristic.value();
            char *src_end = (char *)memchr(src, ';', characteristic.valueSize());
            int len = src_end ? src_end - src : characteristic.valueSize();
            memcpy(input_buffer, src, len);
            input_buffer[len] = '\0';

            #if LOVENSE_LOG_LEVEL >= 2
                Serial.print("Received command: ");
                Serial.println(input_buffer);
            #endif

            char *token = strtok(input_buffer, ":");
            while (token)
            {
                strcpy(argv[arg_num], token);
                token = strtok(NULL, ":");
                arg_num++;
            }

            const ParsedCommandType* cmd = CommandHash::in_word_set(argv[0], strlen(argv[0]));
            kind = cmd == 0 ? CommandKind::Unknown : cmd->kind;

            arg_num -= 1;
        }

        char* arg(int idx) {
            if (idx > arg_num) {
                return NULL;
            }

            return argv[idx + 1];
        }

        int args_len() {
            return arg_num;
        }
    };
}