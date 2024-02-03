/* C++ code produced by gperf version 3.1 */
/* Command-line: gperf -t commands.gperf  */
/* Computed positions: -k'1,5' */
namespace Commands {

#line 1 "commands.gperf"

#include <Arduino.h>

    enum CommandKind
    {
        DeviceType,
        Battery,
        PowerOff,
        Status,
        Vibrate,
        GetAutoSwitch,
        AutoSwitch,
        GetLight,
        Light,
        ALight,
        GetALight,
        GetLevel,
        SetLevel,
        RotateChange,
        Rotate,
        Air,
        GetBatch,        
        Unknown
    };

    const char* command_kind_to_s(CommandKind kind) {
        switch (kind) {
            case DeviceType:
                return "DeviceType";
            case Battery:
                return "Battery";
            case PowerOff:
                return "PowerOff";
            case Status:
                return "Status";
            case Vibrate:
                return "Vibrate";
            case GetAutoSwitch:
                return "GetAutoSwitch";
            case AutoSwitch:
                return "AutoSwitch";
            case GetLight:
                return "GetLight";
            case Light:
                return "Light";
            case ALight:
                return "ALight";
            case GetALight:
                return "GetAlight";
            case GetLevel:
                return "GetLevel";
            case SetLevel:
                return "SetLevel";
            case RotateChange:
                return "RotateChange";
            case Rotate:
                return "Rotate";
            case Air:
                return "Air";
            case GetBatch:
                return "GetBatch";
            default:
                return "Unknown";
        }
    }
#line 73 "commands.gperf"
struct ParsedCommandType { char *name; CommandKind kind; };

#define COMMANDHASH_TOTAL_KEYWORDS 17
#define COMMANDHASH_MIN_WORD_LENGTH 3
#define COMMANDHASH_MAX_WORD_LENGTH 13
#define COMMANDHASH_MIN_HASH_VALUE 3
#define COMMANDHASH_MAX_HASH_VALUE 33
/* maximum key range = 31, duplicates = 0 */

class CommandHash
{
private:
  static inline unsigned int hash (const char *str, size_t len);
public:
  static const struct ParsedCommandType *in_word_set (const char *str, size_t len);
};

inline unsigned int
CommandHash::hash (const char *str, size_t len)
{
  static const unsigned char asso_values[] =
    {
      34, 34, 34, 34, 34, 34, 34, 34, 34, 34,
      34, 34, 34, 34, 34, 34, 34, 34, 34, 34,
      34, 34, 34, 34, 34, 34, 34, 34, 34, 34,
      34, 34, 34, 34, 34, 34, 34, 34, 34, 34,
      34, 34, 34, 34, 34, 34, 34, 34, 34, 34,
      34, 34, 34, 34, 34, 34, 34, 34, 34, 34,
      34, 34, 34, 34, 34,  0,  0, 34,  0, 34,
      34,  5, 34, 34, 34, 34,  0, 34, 34, 34,
      15, 34,  5,  0, 34, 34,  0, 34, 34, 34,
      34, 34, 34, 34, 34, 34, 34, 15, 34,  0,
      34,  0, 34, 34, 10, 10, 34, 34,  0, 34,
      34, 34, 34, 34, 10, 34,  0,  0, 34, 34,
      34, 34, 34, 34, 34, 34, 34, 34
    };
  unsigned int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[static_cast<unsigned char>(str[4])];
      /*FALLTHROUGH*/
      case 4:
      case 3:
      case 2:
      case 1:
        hval += asso_values[static_cast<unsigned char>(str[0])];
        break;
    }
  return hval;
}

const struct ParsedCommandType *
CommandHash::in_word_set (const char *str, size_t len)
{
  static const struct ParsedCommandType wordlist[] =
    {
#line 91 "commands.gperf"
      {"Air", Air},
#line 84 "commands.gperf"
      {"Light", Light},
#line 79 "commands.gperf"
      {"Status", Status},
#line 77 "commands.gperf"
      {"Battery", Battery},
#line 88 "commands.gperf"
      {"SetLevel", SetLevel},
#line 82 "commands.gperf"
      {"AutoSwith", AutoSwitch},
#line 76 "commands.gperf"
      {"DeviceType", DeviceType},
#line 90 "commands.gperf"
      {"Rotate", Rotate},
#line 87 "commands.gperf"
      {"GetLevel", GetLevel},
#line 86 "commands.gperf"
      {"GetAlight", GetALight},
#line 85 "commands.gperf"
      {"ALight", ALight},
#line 89 "commands.gperf"
      {"RotateChange", RotateChange},
#line 81 "commands.gperf"
      {"GetAutoSwitch", GetAutoSwitch},
#line 80 "commands.gperf"
      {"Vibrate", Vibrate},
#line 83 "commands.gperf"
      {"GetLight", GetLight},
#line 92 "commands.gperf"
      {"GetBatch", GetBatch},
#line 78 "commands.gperf"
      {"PowerOff", PowerOff}
    };

  if (len <= COMMANDHASH_MAX_WORD_LENGTH && len >= COMMANDHASH_MIN_WORD_LENGTH)
    {
      unsigned int key = hash (str, len);

      if (key <= COMMANDHASH_MAX_HASH_VALUE && key >= COMMANDHASH_MIN_HASH_VALUE)
        {
          const struct ParsedCommandType *resword;

          switch (key - 3)
            {
              case 0:
                resword = &wordlist[0];
                goto compare;
              case 2:
                resword = &wordlist[1];
                goto compare;
              case 3:
                resword = &wordlist[2];
                goto compare;
              case 4:
                resword = &wordlist[3];
                goto compare;
              case 5:
                resword = &wordlist[4];
                goto compare;
              case 6:
                resword = &wordlist[5];
                goto compare;
              case 7:
                resword = &wordlist[6];
                goto compare;
              case 8:
                resword = &wordlist[7];
                goto compare;
              case 10:
                resword = &wordlist[8];
                goto compare;
              case 11:
                resword = &wordlist[9];
                goto compare;
              case 13:
                resword = &wordlist[10];
                goto compare;
              case 14:
                resword = &wordlist[11];
                goto compare;
              case 15:
                resword = &wordlist[12];
                goto compare;
              case 19:
                resword = &wordlist[13];
                goto compare;
              case 20:
                resword = &wordlist[14];
                goto compare;
              case 25:
                resword = &wordlist[15];
                goto compare;
              case 30:
                resword = &wordlist[16];
                goto compare;
            }
          return 0;
        compare:
          {
            const char *s = resword->name;

            if (*str == *s && !strcmp (str + 1, s + 1))
              return resword;
          }
        }
    }
  return 0;
}
}