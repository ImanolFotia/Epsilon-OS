#include <stdio.h>
#include <string.h>
#include <kernel/tty.h>

class shell
{
    public:
        shell() = default;
        ~shell(){}

        const char* commands[2] = {
            "clear",
            "test_color"
        };

        int parse(const char* in);
        {
            for(int i = 0; i < 2; i++){
                if(strcpm(in, commands[i]))
                {
                    return i;
                }
            }
            return -1;
        }

        void execute(int index)
        {
            switch(index)
            {
                case 0:
                    tty::terminal_clear();
                break;
                case 1:
                	tty::terminal_test_color();
                break;
                default:
                	tty::printk("Command not found\n");
                break;
            }
        }

        void set_input_buffer(uint16_t* buffer)
        {
            stdout = buffer;
        }

    private:
        uint16_t* stdout;
};
